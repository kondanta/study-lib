#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::move;
using std::vector;
using std::string;
using std::endl;

class PcPartFactory {
public:
    PcPartFactory(string name, int price) : name(std::move(name)), price(price) {};
    int getPrice(){
        return price;
    }
    string getName(){
        return name;
    }

private:
    string name;
    int price;
};

class Intel : public PcPartFactory {
public:
    Intel(string name, int price) : PcPartFactory(std::move(name), price) {};
    virtual void orderCPU() = 0;
};

class Nvidia : public PcPartFactory {
public:
    Nvidia(string name, int price) : PcPartFactory(std::move(name), price) {};
    virtual void orderGPU() = 0;
};

class CPU : public Intel {
public:
    CPU(const string &name, int price) : Intel(name, price) {};
    void orderCPU() override {
        cout << "Name: "<< getName() << " Price: "<< getPrice()<<endl;
    }
};

class GPU : public Nvidia {
public:
    GPU(const string &name, int price) : Nvidia(name, price) {};
    void orderGPU() override {
        cout << "Name: "<< getName() << " Price: "<< getPrice()<<endl;
    }
};


class Facade {
public:
    int createList(vector <PcPartFactory*> part, string type){
        int sum = 0;
        if(type == "gaming"){
            Intel* cpu = new CPU("i7 4790k", 3000);
            Nvidia* gpu = new GPU("GTX 1080ti", 4000);
            cpu->orderCPU();
            gpu->orderGPU();
            part.push_back(cpu);
            part.push_back(gpu);
            
            sum = calc(part);
            cout << "Total sum: " << sum <<endl;
        }
        else if(type == "casual"){
            Intel* cpu = new CPU("i5k", 2000);
            Nvidia* gpu = new GPU("GTX 1080ti", 4000);
            cpu->orderCPU();
            gpu->orderGPU();
            part.push_back(cpu);
            part.push_back(gpu);

            sum = calc(part);
            cout << "Total sum: " << sum <<endl;
        }
    }
    int calc(vector <PcPartFactory*> part){
        int sum = 0;
        for (auto &i : part) {
            sum = sum + i->getPrice();
        }
        return sum;
    }
};



int main() {
    vector <PcPartFactory*> parts;
    auto * list =new Facade();

    list->createList(parts, "gaming");

}

