#include <iostream>
#include <map>
#include <utility>
#include <vector>

// Useful shortcuts
using std::cout;
using std::move;
using std::string;
template <typename T> using vector = std::vector<T>;
template <typename T, typename U> using map = std::map<T, U>;

// forward decleration
class Investors;

// Definiton of the Events.
enum class Events { INCREASE, DECREASE };

// Main stock class.
class Stock {
public:
  virtual ~Stock() = default;
  Stock() = default;
  Stock(string name, double price) : _name{move(name)}, _price(price) {}
  Stock(const Stock &) = delete;
  Stock &operator=(const Stock &) = delete;
  // functions
  virtual void Subscribe(Events type, Investors *i);
  string getName() { return _name; }
  void setName(string n) { this->_name = move(n); }
  virtual double getPrice() = 0;
  virtual void setPrice(double) = 0;

  // MUST
  virtual void Notify(Events type);

protected:
  string _name{};
  double _price{};
  map<Events, vector<Investors *>> investor{};
};

// Concrete stock.
class IBM : public Stock {
public:
  IBM() = default;
  IBM(string name, double price) : Stock(move(name), price) {}

  double getPrice() override { return _price; }
  void setPrice(double p) override {
    if (p > _price) {
      _price = p;
      Notify(Events::INCREASE);
    }
    if (p < _price) {
      _price = p;
      Notify(Events::DECREASE);
    }
  }
};

class Observer {
public:
  virtual ~Observer() = default;
  virtual void Update(Stock *s) = 0;
};

class Investors : public Observer {
public:
  // disallow copying and assigning
  Investors(const Investors &) = delete;
  Investors &operator=(const Investors &) = delete;
  Investors() = default;
  explicit Investors(string name)
      : _stock(nullptr), _investorName{move(name)} {}
  string getName() { return _investorName; }
  void Update(Stock *s) override {
    _stock = s; // push. If it was pull, we'd use s->get()
    _stockPrice = s->getPrice();
    _stockName = s->getName();
    cout << "Notified " << _investorName << " of "
         << _stockName + "'s " + "change to " << _stockPrice << "\n";
  }

private:
  Stock *_stock; // stock ref to be stored.
  string _investorName{};
  string _stockName{};
  double _stockPrice{};
};

// subscribing the subject
// It will create key on [e] and populate the vector of investors.
void Stock::Subscribe(Events type, Investors *i) {
  investor[type].push_back(i);
}

// unsubbing the subject
// Unsigned long used for preventing implicit typecasting ul to int
// then explicitly cast ul to int.
/* void Stock::UnSubscribe(Investors *inv) {
 *   for (uint64_t i = 0; i < investor.size(); ++i) {
 *     if (inv->getName() == investor[i]->getName()) {
 *       investor.erase(investor.begin() + int(i));
 *     }
 *   }
 * } */

// Notify each subscriber.
void Stock::Notify(Events type) {
  for (auto &inv : investor.at(type)) {
    inv->Update(this);
  }
}

int main() {
  string i1Name, i2Name, i3Name;
  i1Name = "Ali";
  i2Name = "Ayse";
  i3Name = "Mehmet";

  // Investors.
  Investors *i1 = new Investors(i1Name);
  Investors *i2 = new Investors(i2Name);
  Investors *i3 = new Investors(i3Name);

  // Stock
  IBM *st = new IBM("IBM", 200.000);

  st->Subscribe(Events::INCREASE, i1);
  st->Subscribe(Events::DECREASE, i2);
  st->Subscribe(Events::INCREASE, i3);

  st->setPrice(201.000);
  st->setPrice(199.000);
  st->setPrice(202.100);
  st->setPrice(201.900);

  delete st;
  delete i1;
  delete i2;
  delete i3;

  return 0;
}

/*
 ==00:00:00:01.474 25344== HEAP SUMMARY:
 ==00:00:00:01.474 25344==     in use at exit: 0 bytes in 0 blocks
 ==00:00:00:01.474 25344==   total heap usage: 17 allocs, 17 frees, 74,434 bytes
 allocated
 ==00:00:00:01.474 25344==
 ==00:00:00:01.474 25344== All heap blocks were freed -- no leaks are possible
 */
