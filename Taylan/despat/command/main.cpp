#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
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

// Command
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
    // Randomizing
    std::random_device rd;
    std::mt19937 mt(rd());
    // rand x y coordinates.
    std::uniform_real_distribution<double> x(1.0, 1920.0);
    std::uniform_real_distribution<double> y(1.0, 1080.0);

    // file writing
    std::ofstream myfile;
    myfile.open("output.txt", std::ios_base::app);
    myfile << "X axis :" << x(mt) << " Y axis: " << y(mt) << std::endl;
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
  explicit MouseEventHandler(MouseDriver *driver) : md{driver} {};
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
    EventHandler *each = nullptr; // WHY ?
    if (_events.size() < 5) {
      _events.push_back(event);
      current++;
    }

    // Empty the q after 5 commands stacked.
    if (_events.size() >= 5) {
      for (auto &_event : _events) {
        each = _event;
        each->Click();
	delete _event;
      }
    }
  }

private:
  std::vector<EventHandler *> _events{};
  uint64_t current;
};

int main() {
  // time
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  // event init
  EventHandler *event = nullptr;
  EventHandler *event1 = nullptr;
  EventHandler *event2 = nullptr;
  EventHandler *event3 = nullptr;
  EventHandler *event4 = nullptr;
  // invoker instance
  auto *user = new User();
  // reciever instance
  auto *md = new MouseDriver();

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

  delete event;
  delete event1;
  delete event2;
  delete event3;
  delete event4;
  delete md;
  delete user;

  return 0;
}
