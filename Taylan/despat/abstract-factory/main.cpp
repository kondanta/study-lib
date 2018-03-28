#include <iostream>
#include <memory>
#include <utility>

//! It'll make easier to call uniqueptr
template <typename T> using ptr = std::unique_ptr<T>;

class AbstractProduct {
public:
  virtual ~AbstractProduct() = default;
  virtual void depositeMoney(double) = 0;
  virtual void withdrawMoney(double) = 0;
  virtual void displayBalance() = 0;
};

//! Concrete class of the abstract product
/// It'll contain the implementations of the abstract
/// product class.
class Bank1Product : public AbstractProduct {
public:
  Bank1Product() : _balance{0.0} {
    std::cout << "Bank1 Account is created!" << std::endl;
  };
  void depositeMoney(double money) override {
    _balance += money;
    std::cout << "You're depoisted: " << money << " and you have: " << _balance
              << " in your account!" << std::endl;
  }

  void withdrawMoney(double money) override {
    if (_balance == 0.0 || money > _balance) {
      std::cout << "You don't have enough money! " << std::endl;
      return;
    }
    _balance -= money;
    std::cout << "You've succesfully withdrawed: " << money << " and you have"
              << _balance << " in your account!" << std::endl;
  }
  void displayBalance() override { std::cout << _balance << std::endl; }

private:
  double _balance;
};

//! Concrete class of the abstract product
/// It'll contain the implementations of the abstract
/// product class.
class Bank2Product : public AbstractProduct {
public:
  Bank2Product() : _balance{0.0} {
    std::cout << "Bank2 Account is created!" << std::endl;
  };
  void depositeMoney(double money) override {
    _balance += money;
    std::cout << "You're depoisted: " << money << " and you have: " << _balance
              << " in your account!" << std::endl;
  }

  void withdrawMoney(double money) override {
    if (_balance == 0.0 || money > _balance) {
      std::cout << "You don't have enough money! " << std::endl;
      return;
    }
    _balance -= money;
    std::cout << "You've succesfully withdrawed: " << money << " and you have"
              << _balance << " in your account!" << std::endl;
  }
  void displayBalance() override { std::cout << _balance << std::endl; }

private:
  double _balance;
};

class AbstractProduct2 {
public:
  virtual ~AbstractProduct2() = default;
  virtual void test() = 0;
};

class Bank1Product2 : public AbstractProduct2 {
public:
  Bank1Product2() { std::cout << "Bank1 Product2 Created" << std::endl; }
  void test() override { std::cout << "Bank1's 2nd product!" << std::endl; }
};

class Bank2Product2 : public AbstractProduct2 {
public:
  Bank2Product2() { std::cout << "Bank2 Product2 created" << std::endl; }
  void test() override { std::cout << "Bank2's 2nd product!!" << std::endl; }
};

//! Abstract Factory class
// Contains factories production creation function.
class AbstractFactory {
public:
  virtual ~AbstractFactory() = default;
  virtual AbstractProduct *createProduct1() = 0;
  virtual AbstractProduct2 *createProduct2() = 0;
};

//! Concrete Factory method
/// We're hiding the creation part because we don't want
//  anyone be able to create product whenever they want!
class Bank1 : public AbstractFactory {
private:
  AbstractProduct *createProduct1() override { return new Bank1Product(); }
  AbstractProduct2 *createProduct2() override { return new Bank1Product2(); }
};

//! Concrete Factory method
/// We're hiding the creation part because we don't want
//  anyone be able to create product whenever they want!
class Bank2 : public AbstractFactory {
private:
  //! Get the production 1
  /// Returns to the production 1 ptr
  AbstractProduct *createProduct1() override { return new Bank2Product(); }
  //! Get the production 1
  /// Returns to the production 1 ptr
  AbstractProduct2 *createProduct2() override { return new Bank2Product2(); }
};

//! Client class which in our case the customer.
class Client {
public:
  /// We're leaving the object creation to the
  /// client which is exactly the same case if we
  /// compare it to the real life.
  /// A customer has a freedom to choose which bank
  /// they wants.
  void createAccount(std::unique_ptr<AbstractFactory> bank) {
    this->_prod1 = bank->createProduct1();
    this->_prod2 = bank->createProduct2();
    bank.reset();
  }

  //! Get the production 1
  /// Returns to the production 1 ptr
  AbstractProduct *getProduction1() { return this->_prod1; }
  //! Get the production 2
  /// Returns to the production 2 ptr
  AbstractProduct2 *getProduction2() { return this->_prod2; }

private:
  AbstractProduct *_prod1;
  AbstractProduct2 *_prod2;
};

int main() {
  /// We have two different banks.
  ptr<AbstractFactory> bank1(new Bank1());
  ptr<AbstractFactory> bank2(new Bank2());
  /// Each bank has its own customer accounts and stuff.
  /// Before that, we have to create a Client who is going to be
  /// using the banks.
  ptr<Client> customer(new Client());
  customer->createAccount(std::move(bank1));
  AbstractProduct *p1 = customer->getProduction1();
  /// Fixing the memory leak.
  /// We did not used the get production1 func in bank2
  /// that's why it is causing a memory leak
  AbstractProduct2 *p2 = customer->getProduction2();
  p1->depositeMoney(10.5);
  p1->displayBalance();
  p1->withdrawMoney(5.2);

  delete p2;
  delete p1;

  customer->createAccount(std::move(bank2));
  AbstractProduct2 *p3 = customer->getProduction2();
  /// Fixing the memory leak.
  /// We did not used the get production1 func in bank2
  /// that's why it is causing a memory leak
  AbstractProduct *p4 = customer->getProduction1();
  p3->test();

  delete p4;
  delete p3;

  return 0;
}
