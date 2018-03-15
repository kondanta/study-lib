#include <iostream>
#include <vector>

using namespace std;

class DrawingElement {
public:
	virtual ~DrawingElement() = default;;
	virtual void Display(int indent) = 0;
	string getName() {return name;};
protected:
	DrawingElement(string name):name(name){};
private:
	string name;
};

class AbstractIterator {
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone () const = 0;
	virtual DrawingElement* CurrentItem() const = 0 ;
    virtual void trDisp(int indent) = 0;
protected:
	AbstractIterator() = default;
};

class CompositeElement;

class ItemItr : public AbstractIterator{
public:
    ItemItr(const CompositeElement *elem):collection(elem),current(0){};

    void First() override {
        current = 0;
    }
    void Next() override {
        current++;
    }
    DrawingElement *CurrentItem() const override;
    bool IsDone() const override;
    void trDisp(int indent) override {
        for(int i = 1;i <= indent;i++){
            cout <<"-";
        }
        cout <<  "+ " + this->CurrentItem()->getName() << endl;

        // Display each child element on this node
        for (this->First(); !this->IsDone(); this->Next()) {
            this->CurrentItem()->Display(indent+2);
        }
    }

private:
    const CompositeElement *collection;
    int current;
};


// This is the "Leaf".

 class PrimitiveElement : public DrawingElement {
 public:
	PrimitiveElement(string name) : DrawingElement(name) {};
	void Display(int indent) override {
		for(int i = 1;i <= indent;i++) { cout <<"-";}
		cout << " " << getName() << endl;
	}
};

// This is the "Composite"
class CompositeElement : public DrawingElement {

public:
	CompositeElement(string name) : DrawingElement(name) {};

	void Add(DrawingElement* d) {elements.push_back(d);};

	void Remove(DrawingElement* d) {
		for (unsigned int i= 0; i< elements.size(); i++) {
			if (elements[i]->getName() == d->getName()) {
				elements.erase(elements.begin()+i);
				return;
			}
		}
	}
	void Display(int indent) override {
		for(int i = 1;i <= indent;i++) { cout <<"-";}
		cout <<  "+ " + getName() << endl;

		// Display each child element on this node
		for (auto &element : elements) {
            element->Display(indent+2);
		}
	}
    int getCount () const {return static_cast<int>(elements.size()); }
	DrawingElement *get(int index) const { return elements[index];}
    AbstractIterator* CreateIterator();
private:
	vector<DrawingElement*> elements;
};

bool ItemItr::IsDone() const {
    return current >= collection->getCount();
}
DrawingElement *ItemItr::CurrentItem() const {
    return (IsDone()? nullptr :collection->get(current));
}

AbstractIterator* CompositeElement::CreateIterator(){
    return new ItemItr(this);
}

int main(){
	// Create a tree structure
	CompositeElement* root = new CompositeElement("Picture");
	root->Add(new PrimitiveElement("Red Line"));
	root->Add(new PrimitiveElement("Blue Circle"));
	root->Add(new PrimitiveElement("Green Box"));

	CompositeElement* comp = new CompositeElement("Two Circles");
	comp->Add(new PrimitiveElement("Black Circle"));
	comp->Add(new PrimitiveElement("White Circle"));
	root->Add(comp);

	// Add and remove a PrimitiveElement
	/*DrawingElement* pe = new PrimitiveElement("Yellow Line");
	root->Add(pe);
	root->Remove(pe);*/

	// Recursively display nodes
	AbstractIterator *critem = root->CreateIterator();
    critem->trDisp(1);
 	cout << endl;
	return 0;
}