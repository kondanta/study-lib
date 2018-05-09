//============================================================================
// Name        :  Ünal Muslu 20150602025
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Investor;
// 'Subject' ==> Stock
class Stock {
public:
	virtual ~Stock() = default;;
	Stock(string symbol, double price) : symbol(symbol), _price(price) {};
	Stock() = default;;
	virtual void Attach (Investor* investor, string);
	virtual void Notify(string);
	string getSymbol() {return symbol;}
	void setSymbol(string value) {symbol = std::move(value);}
	virtual double	getPrice() {return 0;};
	virtual void setPrice(double value) {};
protected:
	string symbol;          // Internal Subject state
	double _price;			// Internal Subject state
	map<Investor*, string> investors;
};

// 'ConcreteSubject' ==> IBM

class IBM : public Stock {
public:
	// Constructor
	IBM(string symbol, double price): Stock (std::move(symbol), price){};
	double getPrice() override {return _price;}
	void setPrice(double value) override {
	    string event;
	    if(_price > value){
            event = "decrease";
            _price = value;
            Notify(event);
	    } else{
            event = "increase";
            _price = value;
            Notify(event);
	    }
	}
};

// 'Observer'  ==> Abstract Observer.

class Observer {
public:
	virtual ~Observer() = default;;
	virtual void Update(Stock *stock) = 0;
};

// 'ConcreteObserver' ==> Investor

class Investor : public Observer {
private:
	 Stock *_stock;
	 string _investor_name;
	 string _stock_name;
	 double _stock_price;
public:
    Investor(string name): _investor_name(std::move(name)) {};
	 void Update(Stock *stock) override {
		 _stock = stock; 				 // Reference to Subject
		 _stock_price = stock->getPrice();
		 _stock_name = stock->getSymbol();
		 cout << "Notified " + _investor_name + " of " + _stock_name +
		         "'s " + "change to " << _stock_price << "\n";
	 }
	 Stock getStock() { return *_stock; }
	 void setStock(Stock *value) { _stock = value; }
	 string getName() { return _investor_name; }
};

// Register the Observers
void Stock::Attach(Investor* investor, string event) {
      investors.insert(std::pair<Investor*, string>(investor, event));
}

// Notify the Observers.
void Stock::Notify(string event) {
	for (auto &investor : investors) {
	    if (investor.second == event)
	    investor.first->Update(this);
	}
}
// MainApp test application
int main() {
   // Create investors
   Investor* a = new Investor("Ahmet");
   Investor* b = new Investor("Ayse");
   Investor* c = new Investor("Mehmet");

   // Event types
    string inc = "increase";
    string dec = "decrease";

   // Create IBM stock and attach investors
   IBM* ibm = new IBM("IBM", 120.00);
   ibm->Attach(a, inc);
   ibm->Attach(b, dec);
   ibm->Attach(c, inc);

   // Change price, which notifies investors
   ibm->setPrice(121);
   ibm->setPrice(122);
   ibm->setPrice(123);
   ibm->setPrice(124);

   cout<< "Now decreasing..."<<endl;

   ibm->setPrice(123);
   ibm->setPrice(122);
   ibm->setPrice(121);


   delete ibm;
}