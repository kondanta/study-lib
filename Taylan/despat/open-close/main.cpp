#include <iostream>

//---START OF THE PROVIDED CODE----
class PricePolicy {
private:
  double factor;

public:
  PricePolicy() : factor(1) {}
  void SetPrice(double factor) { this->factor = factor; }
  double GetPrice(double price) { return price * this->factor; }
};

class Parts {
private:
  double price;
  PricePolicy pP;

public:
  void setPricePolicy(PricePolicy pP) { this->pP = pP; }
  void setPrice(double price) { this->price = price; }
  double getPrice() { return pP.GetPrice(this->price); }
};

class MotherBoard : public Parts {
public:
  MotherBoard() = default;
};

class Memory : public Parts {
public:
};

class HardDisk : public Parts {
public:
};

class OpticalDisc : public Parts {
public:
};

double totalPrice(Parts **parts, int len) {
  double total = 0.0;
  for (int i = 0; i < len; i++) {
    total += parts[i]->getPrice();
  }
  return total;
}

// ----END OF THE PROVIDED CODE----
int main() {
  // Object creation
  MotherBoard *mb = new MotherBoard();
  Memory *mem = new Memory();
  HardDisk *hd = new HardDisk();
  // Policies
  PricePolicy mbPolicy;
  PricePolicy memPolicy;
  PricePolicy hdPolicy;
  // Setting policies
  mbPolicy.SetPrice(4.1);
  memPolicy.SetPrice(7.8);
  hdPolicy.SetPrice(1.1);

  // Each part has its own policy
  mb->setPricePolicy(mbPolicy);
  mem->setPricePolicy(memPolicy);
  hd->setPricePolicy(hdPolicy);

  /* After extending the softwear, */
  OpticalDisc *oD = new OpticalDisc();
  PricePolicy opticalPolicy;
  opticalPolicy.SetPrice(0.5);
  oD->setPricePolicy(opticalPolicy);

  /* Setting Prices */
  mb->setPrice(3);
  mem->setPrice(4);
  hd->setPrice(5);
  oD->setPrice(6);
  // Sending total
  Parts *parts[] = {mb, mem, hd, oD};
  std::cout << totalPrice(parts, 4);

  // freeing ptrs
  delete mb;
  delete mem;
  delete hd;
  return 0;
}
