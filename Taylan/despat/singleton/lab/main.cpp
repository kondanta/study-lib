#include <iostream>
#include <map>
#include <utility>

using std::cout, std::string, std::map, std::move;

class AbstractClass {
public:
  virtual ~AbstractClass() = default;
  virtual void printName() = 0;

protected:
  explicit AbstractClass(string name) : _name{move(name)} {};
  AbstractClass() = default;

private:
  string _name;
};

class Singleton1 : public AbstractClass {
public:
  void printName() override { cout << "Singleton1 class"; };
  static Singleton1 &getSingleton1() {
    static Singleton1 instance("Singleton1");
    return instance;
  }
  /* static Singleton1 *getSingleton1() {
   *   if (instance == nullptr) {
   *     instance = new Singleton1("Singleton1");
   *   }
   *   return instance;
   * } */

private:
  Singleton1(const Singleton1 &) = delete;
  Singleton1 &operator=(const Singleton1 &) = delete;
  explicit Singleton1(string name) : AbstractClass(move(name)){};
  /* static Singleton1 *instance; */
};

class Singleton2 : public AbstractClass {
public:
  void printName() override { cout << "Singleton2 class"; };
  static Singleton2 &getSingleton2() {
    static Singleton2 instance("Singleton2");
    return instance;
  }
  /* static Singleton2 *getSingleton2() {
   *   if (instance == nullptr) {
   *     instance = new Singleton2("Singleton2");
   *   }
   *   return instance;
   * } */

private:
  Singleton2(const Singleton2 &) = delete;
  Singleton2 &operator=(const Singleton2 &) = delete;

  explicit Singleton2(string name) : AbstractClass(move(name)){};
  /* static Singleton2 *instance; */
};

class Singleton3 : public AbstractClass {
public:
  void printName() override { cout << "Singleton3 class"; };
  static Singleton3 &getSingleton3() {
    static Singleton3 instance("Singleton1");
    return instance;
  }
  /* static Singleton3 *getSingleton3() {
   *   if (instance == nullptr) {
   *     instance = new Singleton3("Singleton3");
   *   }
   *   return instance;
   * } */

private:
  Singleton3(const Singleton3 &) = delete;
  Singleton3 &operator=(const Singleton3 &) = delete;

  explicit Singleton3(string name) : AbstractClass(move(name)){};
  /* static Singleton3 *instance; */
};

/* Singleton1 *Singleto1::instance = nullptr;
 * Singleton2 *Singleton2::instance = nullptr;
 * Singleton3 *Singleton3::instance = nullptr; */

void lookUp(string const &key, map<string, AbstractClass *> container) {
  map<string, AbstractClass *>::iterator it;
  for (it = container.begin(); it != container.end(); ++it) {
    if (key == it->first) {
      it->second->printName();
    }
  }
}

int main() {
  map<string, AbstractClass *> test;
  map<string, AbstractClass *>::iterator it;
  AbstractClass &ptr = Singleton1::getSingleton1();
  AbstractClass &ptr2 = Singleton2::getSingleton2();
  AbstractClass &ptr3 = Singleton3::getSingleton3();
  test.insert(std::pair<string, AbstractClass *>("Singleton1", &ptr));
  test.insert(std::pair<string, AbstractClass *>("Singleton2", &ptr2));
  test.insert(std::pair<string, AbstractClass *>("Singleton3", &ptr3));

  lookUp("Singleton1", test);
  lookUp("Singleton2", test);
  lookUp("Singleton3", test);

  /* delete ptr;
   * delete ptr2;
   * delete ptr3; */
  return 0;
}
