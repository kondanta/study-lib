//============================================================================
// Name        : TemplateMethod.cpp
//
// The classes and/or objects participating in this pattern are:
// 1. AbstractClass  (CheckBackground)
//			Defines abstract primitive operations that concrete subclasses
//			define to implement steps of an algorithm implements a template
//			method defining the skeleton of an algorithm. The template method
//			calls primitive operations as well as operations defined in
//			AbstractClass or those of other objects.
// 2. ConcreteClass  (MortgageLoanApp, EquityLoanApp )
//			implements the primitive operations ot carry out subclass-specific
//			steps of the algorithm
//============================================================================
#include <iostream>
using namespace std;

int income = 50000;
int credit_score = 650;

// This is the AbstractClass class.

class CheckBackground {
public:
   string getName() { return _name;}
	// This is our template method.
    void check() {
    	prepareApplication ();
        bool status = checkBank() && checkCredit() &&
                      checkLoan() && checkStock() &&
                      checkIncome();
        finalizeApplication(status);
    }
    virtual ~CheckBackground(){};
protected:
	// These are our concrete template operations.
	void prepareApplication () {
		cout << "Prepared paperwork" << endl;
	}
	void finalizeApplication(bool status) {
		if ( status)
			cout << "Application Accepted" << endl;
		else
			cout << "Application Rejected" << endl;
	}
	// These are Primitive Operations which will be overridden
	// by the subclasses. They are all abstract.
    virtual bool checkBank() = 0;
    virtual bool checkCredit() = 0;
    virtual bool checkLoan() = 0;
    virtual bool checkStock() = 0;
    virtual bool checkIncome() = 0;
  string _name{};
};

// Concrete MortgageLoanApp class which implements the
// primitive operations.

class MortgageLoanApp : public CheckBackground {
public:
	MortgageLoanApp(string name) : _name(name) {}
    //other methods
protected:
    bool checkBank() { //ck acct, balance
        cout << "check bank..." << endl;
        return true;
    }
    bool checkCredit() { //ck score from 3 companies
        cout << "check credit..."<< (credit_score > 700?"GOOD":"BAD")<< endl;
        return credit_score > 700?true:false;
    }
    bool checkLoan() { //ck other loan info
        cout << "check other loan..." << endl;
        return true;
    }
    bool checkStock() {  //ck how many stock values
        cout << "check stock values..." << endl;
        return true;
    }
    bool checkIncome() {  //ck how much a family make
    	cout << "check income..."<< endl;
    	return (income < 50000?false:true);
    }
private:
	string _name;
};
// Concrete EquityLoanApp class which implements the
// primitive operations. checkIncome and checkCredit
// differs from MortgageLoanApp's corresponding
// methods.

class EquityLoanApp : public CheckBackground {
public:
	EquityLoanApp(string name) : _name(name) {}
protected:
    bool checkBank() { //ck acct, balance
        cout << "check bank..." << endl; return true;
    }
    bool checkCredit() { //ck score from 3 companies
        cout << "check credit..."<< endl;
        return credit_score > 600?true:false;
    }
    bool checkLoan() { //ck other loan info
        cout << "check other loan..." << endl; return true;
    }
    bool checkStock() {  //ck how many stock values
        cout << "check stock values..." << endl; return true;
    }
    bool checkIncome() {  //ck how much a family make
    	cout << "check income..."<< endl;
    	return (income < 40000?false:true);
    }
private:
	string _name;
};

// This is our test program.

int main() {

        CheckBackground *p = new MortgageLoanApp("Ahmet");
        cout << endl;
        cout << "Check client " << p->getName();
        cout <<" mortgage loan application. " << endl;
        p->check();
        delete (p);
        p = new EquityLoanApp("Ahmet");
        cout << endl;
        cout << "Check client " << p->getName();
        cout << " equity loan application. " << endl;
        p->check();
        return 0;
}
