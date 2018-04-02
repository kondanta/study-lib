#include <gsl/gsl>
#include <iostream>
#include <thread>
#include <utility>

class LoadBalancer {
public:
  // This implementation requires C++11 or higher versions.
  static LoadBalancer &GetLoadBalancer() {
    static LoadBalancer instance;
    return instance;
  }

private:
  LoadBalancer() = default;
  LoadBalancer(const LoadBalancer &) = delete;
  LoadBalancer &operator=(const LoadBalancer &) = delete;
};

template <class T> class Server {
public:
  Server(std::string n, const T &l) : _name{std::move(n)}, lb{l} {
    std::cout << "Server is created";
  };
  void getServer() { std::cout << "You're in " << _name << std::endl; }
  ~Server() { std::cout << "Deleting the Server"; }

private:
  std::string _name;
  const T &lb;
};

void test1() {
  LoadBalancer &i = LoadBalancer::GetLoadBalancer();
  std::string svName;
  svName = "Server 1";
  std::cout << "Address of the LoadBalancer: " << &i << std::endl;
  gsl::owner<Server<LoadBalancer> *> obj =
      gsl::owner<Server<LoadBalancer> *>(new Server(svName, i));
  obj->getServer();
  delete obj;
}

void test2() {
  LoadBalancer &i = LoadBalancer::GetLoadBalancer();
  // fuchsia-default-arguments...
  // Even default strings are not allowed....
  std::string svName;
  svName = "Server 2";
  std::cout << "Address of the LoadBalancer instance: " << &i << std::endl;
  gsl::owner<Server<LoadBalancer> *> obj =
      gsl::owner<Server<LoadBalancer> *>(new Server(svName, i));
  obj->getServer();
  delete obj;
}

int main() {
  std::thread t1 = std::thread(test1);
  std::thread t2 = std::thread(test2);

  // They both prints the same address.
  t2.join();
  t1.join();

  return 0;
}
