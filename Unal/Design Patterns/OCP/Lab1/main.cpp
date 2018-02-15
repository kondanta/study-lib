#include <iostream>

class PricePolicy {
private:
    double factor;
public:
    PricePolicy(){
        this->factor = 1;
    }
    void setPrice(double factor){
        this->factor = factor;
    }
    double getPrice(double price){
        return price * this->factor;
    }
};


class Part {
private:
    double price;
    PricePolicy pricePolicy;
public:
    void setPricePolicy(PricePolicy pricePolicy){
        this->pricePolicy = pricePolicy;
    }
    void setPrice(double price){
        this->price = price;
    }
    double getPrice(){
        return pricePolicy.getPrice(this->price);
    }
};

double totalPrice(Part part[], int len){
    double total = 0.0;
    for (int i = 0; i < len ; i++){
        total += part[i].getPrice();
    }
    return total;
}

class Motherboard: public Part{};
class Memory: public Part{};
class HardDisk: public Part{};
class OpticalDisk: public Part{};

int main() {
    Motherboard mb;
    HardDisk hd;
    Memory mm;
    OpticalDisk od;
    PricePolicy ppmb;
    PricePolicy pphd;
    PricePolicy ppmm;
    PricePolicy ppod;
    ppmb.setPrice(1);
    pphd.setPrice(2);
    ppmm.setPrice(3);
    ppod.setPrice(4);
    mb.setPrice(4);
    mb.setPricePolicy(ppmb);
    hd.setPrice(3);
    hd.setPricePolicy(pphd);
    mm.setPrice(2);
    mm.setPricePolicy(ppmm);
    od.setPrice(1);
    od.setPricePolicy(ppod);
    Part part[] = {mb, hd, mm, od};
    std::cout << totalPrice(part, 4);
}

