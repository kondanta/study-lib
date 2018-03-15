#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

// EventHandler (Command)

class EventHandler {
public:
    virtual void Click() = 0;
    virtual ~EventHandler() = default;
protected:
    EventHandler() = default;
};

// MouseDriver (Receiver)

class MouseDriver {
public:
    MouseDriver() : _x(0), _y(0) {};
    void Action() {
        ofstream myfile;
        myfile.open ("output.txt", ios_base::app);
        myfile << "Mouse Cords:" <<endl;
        myfile << "X cor. is: "<< rand() % 1920 + 1 <<endl;
        myfile << "Y cor. is: "<< rand() % 1080 +1  <<endl;
        myfile.close();
        /*cout << "Mouse Cords:" <<endl;
        cout << "X cor. is: "<< rand() % 1920 + 1 <<endl;
        cout << "Y cor. is: "<< rand() % 1080 +1  <<endl;*/

    }
private:
    int _x;
    int _y;
};

// MouseEventHandler (ConcreteCommand

class MouseEventHandler : public EventHandler {
public:
    explicit MouseEventHandler(MouseDriver *driver)
            : _mousedriver(driver){}
    void Click() override {
        _mousedriver->Action();
    }
private:
    MouseDriver* _mousedriver;
};

// User (Invoker)

class User {
public:
    void Work(EventHandler *handler) {
        EventHandler *sEvent = nullptr;
        while(!status){
            cout << "Please do the click(Press enter)"<<endl;
            cin.ignore();
            _events.push_back(handler);
            if(_events.size() == 5){
                status = true;
                for (int i = 0; i < 5; i++) {
                    sEvent = _events[i];
                    sEvent->Click();
                }
                cout << "Done";
            }
        }
    }
private:
    vector<EventHandler *>	_events;
    int status = false;
};

// Main

int main(){
    srand(static_cast<unsigned int>(time(nullptr))); // For random seed gen.

    EventHandler *event = nullptr;
    auto *user = new User();
    auto *mDriver = new MouseDriver();

    event = new MouseEventHandler(mDriver);
    user->Work(event);

    // Dtor
    delete event;
    delete user;
    delete mDriver;


}

