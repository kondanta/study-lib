#include <gsl/gsl>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using std::cout;
using std::move;
using std::string;
template <class T> using vector = std::vector<T>;
template <class T> using ptr = std::unique_ptr<T>;

class PcParts {
public:
  virtual ~PcParts() = default;
  PcParts(string name, double price) : name_{move(name)}, price_{price} {};
  double getPrice() { return price_; }
  string getName() { return name_; }

private:
  string name_;
  double price_;
};

class Intel : public PcParts {
public:
  Intel(string name, double price) : PcParts{move(name), price} {};
  virtual void orderCpu() = 0;
};

class CPU : public Intel {
public:
  CPU(string name, double price) : Intel{move(name), price} {};
  void orderCpu() override {
    cout << "Intel i7 ----"
         << "by INTEL\n";
  }
};

class Nvidia : public PcParts {
public:
  Nvidia(string name, double price) : PcParts{move(name), price} {};
  virtual void orderGpu() = 0;
};

class GPU : public Nvidia {
public:
  GPU(string name, double price) : Nvidia{move(name), price} {};
  void orderGpu() override {
    cout << "Nvidia 1080 TI ----"
         << "by Nvidia\n";
  }
};

class AbstractFactory {
public:
  virtual ~AbstractFactory() = default;
  virtual CPU *createCPU() = 0;
  virtual GPU *createGPU() = 0;
};

class GPUFactory : public AbstractFactory {
  GPU *createGPU() override { return new GPU("1080 ti", 3000); }
  CPU *createCPU() override { return nullptr; }
};

class CPUFactory : public AbstractFactory {
public:
  CPU *createCPU() override { return new CPU("8700k", 3200); }
  GPU *createGPU() override { return nullptr; }
};

class Facade {
public:
  ~Facade() {
    delete c;
    delete gp;
  }
  double assemblyPC(vector<PcParts *> p) {
    double sum = 0.0;
    gp = new GPUFactory();
    c = new CPUFactory();
    gsl::owner<Nvidia *> gpu = gp->createGPU();
    gsl::owner<Intel *> cpu = c->createCPU();

    gpu->orderGpu();
    cpu->orderCpu();

    p.push_back(cpu);
    p.push_back(gpu);

    sum = calculatePrice(p);
    delete gpu;
    delete cpu;
    return sum;
  }

  double calculatePrice(vector<PcParts *> p) {
    double sum = 0.0;
    for (PcParts *elem : p) {
      sum += elem->getPrice();
    }
    return sum;
  }

private:
  gsl::owner<AbstractFactory *> c;
  gsl::owner<AbstractFactory *> gp;
};

int main() {
  ptr<Facade> person(new Facade());
  vector<PcParts *> parts;
  cout << person->assemblyPC(parts);
  parts.clear();

  return 0;
}
