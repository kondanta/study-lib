#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::move;
using std::vector;
using std::string;
using std::endl;

class Printer {
public:
    virtual void printName() = 0;
    string getName(){
        return _name;
    }
protected:
    Printer() = default;
    explicit Printer(string name) : _name(move(name)) {};
private:
    string _name;
};

class Print1 : public Printer {
public:
    static Print1 *GetLoadBalancer() {
        if(instance == nullptr) {
            instance = new Print1("First");
        }
        return instance;
    }
    void printName() override {
        cout << "This is the first printer."<<endl;
    }
private:
    static Print1* instance;
    explicit Print1(string name) : Printer(name){};
};

class Print2 : public Printer {
public:
    static Print2 *GetLoadBalancer() {
        if(instance == nullptr) {
            instance = new Print2("Second");
        }
        return instance;
    }
    void printName() override {
        cout << "This is the second printer."<<endl;
    }
private:
    static Print2* instance;
    explicit Print2(string name) : Printer(name){};
};

class Print3 : public Printer {
public:
    static Print3 *GetLoadBalancer() {
        if(instance == nullptr) {
            instance = new Print3("Third");
        }
        return instance;
    }
    void printName() override {
        cout << "This is the third printer."<<endl;
    }
private:
    static Print3* instance;
    explicit Print3(string name) : Printer(name){};
};

Print1* Print1::instance = nullptr;
Print2* Print2::instance = nullptr;
Print3* Print3::instance = nullptr;

void lookUp(vector<Printer*> contain, string sName){
    for(auto &i : contain) {
        if(i->getName() == sName){
            i->printName();
        }
    }
}
int main(){
    vector<Printer*> container;

    Print1* p1 = Print1::GetLoadBalancer();
    Print2* p2 = Print2::GetLoadBalancer();
    Print3* p3 = Print3::GetLoadBalancer();

    container.push_back(p1);
    container.push_back(p2);
    container.push_back(p3);

    lookUp(container, "First");
    lookUp(container, "Second");
    lookUp(container, "Third");

    delete p1;
    delete p2;
    delete p3;
}