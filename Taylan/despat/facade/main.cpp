#include <gsl/gsl>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::move;
using std::string;

template <typename Type> using ptr = std::unique_ptr<Type>;

// The classes and/or objects participating in this pattern are:
// 1. Facade   (Mortgage)
//		- knows which subsystem classes are responsible for a request.
//		- delegates client requests to appropriate subsystem objects.
// 2. Subsystem classes   (Bank, Credit, Loan)
//		- implement subsystem functionality.
//		- handle work assigned by the Facade object.
//		- have no knowledge of the facade and keep no reference to it.

// Client class. "Customer"

class Customer {
public:
  // Constructor
  explicit Customer(string name) : name(move(name)){};
  string getName() { return name; }

private:
  string name;
};

// Subsystem Class 1. "Bank"

class Bank {
public:
  bool HasSufficientSavings(Customer *c, int amount) {
    cout << "Check bank for " << c->getName() << " for the amount " << amount
         << endl;
    return true;
  }
};

// Subsystem Class 2. "Credit"

class Credit {
public:
  bool HasGoodCredit(Customer *c) {
    cout << "Check credit for " << c->getName() << endl;
    return true;
  }
};

// Subsystem Class 3. "Loan"

class Loan {
public:
  bool HasNoBadLoans(Customer *c) {
    cout << "Check loans for " << c->getName() << endl;
    return true;
  }
};

// Facade. "Mortgage"

class Mortgage {
public:
  Mortgage() {
    bank = new Bank();
    loan = new Loan();
    credit = new Credit();
  }
  ~Mortgage() {
    delete bank;
    delete loan;
    delete credit;
  }
  bool IsEligible(Customer *cust, int amount) {
    cout << cust->getName() << " applies for " << amount << "TL loan" << endl;
    bool eligible = true;

    // Check creditworthyness of applicant
    if (!bank->HasSufficientSavings(cust, amount)) {
      eligible = false;
    } else if (!loan->HasNoBadLoans(cust)) {
      eligible = false;
    } else if (!credit->HasGoodCredit(cust)) {
      eligible = false;
    }
    return eligible;
  }

private:
  gsl::owner<Bank *> bank;
  gsl::owner<Loan *> loan;
  gsl::owner<Credit *> credit;
};

int main() {

  // Facade
  /* Mortgage *mortgage = new Mortgage(); */
  ptr<Mortgage> mortgage(new Mortgage);
  string name;
  name = "Taylan";

  // Evaluate mortgage eligibility for customer
  gsl::owner<Customer *> customer;
  customer = new Customer(name);
  bool eligable = mortgage->IsEligible(customer, 100000);

  cout << endl << customer->getName();
  cout << " has been " << (eligable ? "Approved" : "Rejected");

  delete customer;
  return 0;
}
