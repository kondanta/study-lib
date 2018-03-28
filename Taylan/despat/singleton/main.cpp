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
  /* static LoadBalancer *instance; */
  LoadBalancer() = default;
  LoadBalancer(const LoadBalancer &) = delete;
  LoadBalancer &operator=(const LoadBalancer &) = delete;
};

/* LoadBalancer *LoadBalancer::instance = nullptr; */

class Server {
public:
  Server(std::string n, const LoadBalancer &l) : _name{std::move(n)}, lb{l} {
    std::cout << "Server is created";
  };
  void getServer() { std::cout << "You're in " << _name << std::endl; }
  ~Server() { std::cout << "Deleting the Server"; }

private:
  std::string _name;
  const LoadBalancer &lb;
};

void test1() {
  LoadBalancer &i = LoadBalancer::GetLoadBalancer();
  std::cout << "Address of the LoadBalancer: " << &i << std::endl;
  Server *obj = new Server("Server 1", i);
  obj->getServer();
  delete obj;
}

void test2() {
  LoadBalancer &i = LoadBalancer::GetLoadBalancer();
  std::cout << "Address of the LoadBalancer instance: " << &i << std::endl;
  Server *obj = new Server("Server 2", i);
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
