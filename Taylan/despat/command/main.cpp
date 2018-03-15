#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

/*
 * Command
 *      -> EventHandler
 *
 * ConcreteCommand
 *      -> Mouse Event Handler
 *
 * Client
 *      -> Client
 *
 * Invoker
 *      -> User
 *
 * Reciever
 *      -> Mouse Driver
 *
 *
 * */

class EventHandler {
public:
  virtual ~EventHandler() = default;
  virtual void Click() = 0;

protected:
  EventHandler() = default;
};

/// Reciever
class MouseDriver {
public:
  MouseDriver() : _currentX{0}, _currentY{0} {};
  void Action() {
    std::ofstream myfile;
    myfile.open("output.txt", std::ios_base::app);
    myfile << "X axis :" << std::rand() % 1920
           << " Y axis: " << std::rand() % 1080 << std::endl;
    myfile.close();
  }
  ~MouseDriver() = default;

private:
  int _currentX;
  int _currentY;
};

// concrete Command

class MouseEventHandler : public EventHandler {
public:
  MouseEventHandler(const MouseEventHandler &);
  MouseEventHandler &operator=(const MouseEventHandler &);
  explicit MouseEventHandler(MouseDriver *driver) : md{std::move(driver)} {};
  void Click() override { md->Action(); }

private:
  MouseDriver *md;
};

// Invoker
class User {
public:
  User() : current{0} {};
  void DO(EventHandler *event) {
    std::ofstream myfile("output.txt");
    EventHandler *each = nullptr;
    if (_events.size() < 5) {
      _events.push_back(event);
      current++;
    }

    if (_events.size() == 5) {
      for (unsigned long i = 0; i < _events.size(); i++) {
        each = _events[i];
        each->Click();
      }
    }
  }

private:
  std::vector<EventHandler *> _events;
  long current;
};

int main() {
  // time
  std::srand(std::time(nullptr));
  // event init
  EventHandler *event = nullptr;
  EventHandler *event1 = nullptr;
  EventHandler *event2 = nullptr;
  EventHandler *event3 = nullptr;
  EventHandler *event4 = nullptr;
  // invoker instance
  User *user = new User();
  // reciever instance
  MouseDriver *md = new MouseDriver();

  event = new MouseEventHandler(md);
  event1 = new MouseEventHandler(md);
  event2 = new MouseEventHandler(md);
  event3 = new MouseEventHandler(md);
  event4 = new MouseEventHandler(md);

  user->DO(event);
  user->DO(event1);
  user->DO(event2);
  user->DO(event3);
  user->DO(event4);

  delete md;
  delete user;
  delete event;

  return 0;
}
