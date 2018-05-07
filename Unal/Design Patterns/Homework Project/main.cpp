#include <iostream>
#include <vector>

// Component
using namespace std;

//Pre def classes
class AbstractIterator;

// Component
class Elements{
public:
    virtual ~Elements() = default;
    virtual void Add(Elements *el){};
    virtual void Display() {};
    virtual int getCount() const = 0; // Pure virtual. Fixes non-const to const problem.
    virtual Elements *get(int) const = 0;
    virtual AbstractIterator *CreateIterator() {};
    virtual int getVal() {};
protected:
    Elements() = default;
};
// Abs Itr
class AbstractIterator {
public:
    virtual void First() {};
    virtual void Next() {};
    virtual bool IsDone () {};
    virtual Elements* CurrentItem() {};
    virtual void itrDisplay() {};
    virtual void Calculate() {};
protected:
    AbstractIterator() = default;
};

//  Leaf classes
class Symbol : public Elements {
public:
    explicit Symbol(char elem) : oprt(elem) {};
    void Add(Elements *el) override {
        cout << "You cant add to PE."<< endl;
    }
    void Display() override {
        cout << oprt;
    }
    int getCount() const override {
        return 0;
    }
    Elements *get(int) const override {
        return nullptr;
    }
    int getVal() override {
        return oprt;
    }
    AbstractIterator* CreateIterator() override;
private:
    char oprt;
};

class Number : public Elements {
public:
    explicit Number(int number) : num(number) {}; // NOTE: ERR 1
    void Add(Elements *el) override {
        cout << "You cant add to PE."<< endl;
    }
    void Display() override {
        cout << num;
    }
    int getCount() const override {
        return 0;
    }
    Elements *get(int) const override {
        return nullptr;
    }
    int getVal() override {
        return num;
    }
    AbstractIterator* CreateIterator() override;
private:
    int num;
};

// Composite classes
class Term : public Elements {
public:
    void Add(Elements* el) override {
        elements.push_back(el);
    };
    void Display() override {
        for(auto &element : elements) { // Another change from IDE. Works like forEach.
            element->Display();
        }
    }
    int getCount () const override {
        return static_cast<int>(elements.size());
    }
    Elements* get(int index) const override {
        return elements[index];
    }
    AbstractIterator *CreateIterator() override;
    int getVal() override {
        Elements *temp = elements[elements.size() - 1];
        int data = temp->getVal();
        elements.pop_back();
        delete temp;
        return data;
    }
private:
    vector<Elements*> elements;
};

class Expr : public Elements {
public:
    void Add(Elements* el) override {
        elements.push_back(el);
    };
    void Display() override {
        for(auto &element : elements) { // Another change from IDE. Works like forEach.
            element->Display();
        }
    }
    int getCount () const override {
        return static_cast<int>(elements.size());
    }
    Elements* get(int index) const override {
        return elements[index];
    }
    AbstractIterator *CreateIterator() override;
    int getVal() override {
        return 0;
    }
private:
    vector<Elements*> elements;
};


class ItemItr : public AbstractIterator{
public:
    explicit ItemItr(const Elements *elem):collection(elem),current(0) {};
    void First() override {
        current = 0;
    }
    void Next() override {
        current++;
    }
    Elements* CurrentItem() const {
        return IsDone() ? nullptr : collection->get(current);
    }
    bool IsDone() const {
        return current >= collection->getCount();
    }
    void itrDisplay() override {
        for (this->First(); !this->IsDone(); this->Next()) {
            this->CurrentItem()->Display();
        }
    }
    void Calculate() override {
        int sum = 0;
        int cnt = 0;
        for (this->First(); !this->IsDone(); this->Next()){
            cont.push_back(this->CurrentItem());
        }
        int stor[cont.size()];
        for(auto& elem:cont){
            stor[cnt] = elem->getVal();
            cnt++;
        }
        if(cont.size() >= 6){
            cout << "Only 3 numbers and 2 symbols supported for calculation."<<endl;
            return;
        }else if(stor[1] == 47){
            sum = stor[0]/stor[2];
            sum = sum - stor[4];
        }else if(stor[1] == 45){
            sum = stor[2]/stor[4];
            sum = stor[0] - sum;
        }else{
            cout << "Only - and / operations supported for calculation."<<endl;
            return;
        }
        cout << "Sum:" << sum<<endl;
    }
private:
    const Elements* collection;
    vector<Elements*> cont;
    int current;
};

// Because no header file...
AbstractIterator* Expr::CreateIterator(){
    return new ItemItr(this);
}
AbstractIterator* Term::CreateIterator(){
    return new ItemItr(this);
}
AbstractIterator* Number::CreateIterator(){
    return new ItemItr(this);
}
AbstractIterator* Symbol::CreateIterator(){
    return new ItemItr(this);
}


int main(){
    Elements* root = new Expr();
    Elements* term1 = new Term();
    term1->Add(new Number(5));
    Elements* term2 = new Term();
    term2->Add(new Number(4));
    Elements* term3 = new Term();
    term3->Add(new Number(2));
    root->Add(term1);
    root->Add(new Symbol('-'));
    root->Add(term2);
    root->Add(new Symbol('/'));
    root->Add(term3);

    AbstractIterator *critem = root->CreateIterator();
    critem->itrDisplay();
    cout << endl;
    critem->Calculate();
    return 0;
}