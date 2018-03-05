//============================================================================
// Name        : CompositePattern.cpp
// Description :
//============================================================================

#include <iostream>
#include <vector>

using namespace std;
//
// The classes and/or objects participating in this pattern are:
// 1. Component   (DrawingElement)
//		Declares the interface for objects in the composition.
//Implements
//      default behavior for the interface common to all classes, as
//      appropriate. declares an interface for accessing and managing its
//		child components.
// 2. Leaf   (PrimitiveElement)
//		represents leaf objects in the composition. A leaf has no
//children. 	    Defines behavior for primitive objects in the composition.
// 3. Composite   (CompositeElement)
//		defines behavior for components having children. Stores child
//		components. Implements child-related operations in the Component
//interface.
// 4. Client  (CompositeApp)
//		Manipulates objects in the composition through the Component
//interface.

// This is the "Component". (i.e tree node.)

class DrawingElement {
public:
  virtual ~DrawingElement() = default;
  /* virtual void Add(DrawingElement *d){};
   * virtual void Remove(DrawingElement *d){}; */
  virtual void Display(int indent) = 0;
  string getName() { return name; };

protected:
  DrawingElement(string name) : name(name){};

private:
  string name;
};

class AbstractIterator {
public:
  virtual ~AbstractIterator() = default;
  virtual void First() = 0;
  virtual void Next() = 0;
  virtual bool IsDone() const = 0;
  virtual void show(int indent) = 0;
  virtual DrawingElement *CurrentItem() const = 0;

protected:
  AbstractIterator() = default;
};

// This is the "Leaf".

class PrimitiveElement : public DrawingElement {
public:
  PrimitiveElement(string name) : DrawingElement(name){};
  /*
   *   void Add(DrawingElement *c) { cout << "Cannot add to a
   * PrimitiveElement\n"; } void Remove(DrawingElement *c) { cout << "Cannot
   * remove from a PrimitiveElement \n";
   *   } */
  void Display(int indent) {
    for (int i = 1; i <= indent; i++) {
      cout << "-";
    }
    cout << " " << getName() << endl;
  }
};

// forward decleration
// This is the "Composite"
class CompositeElement : public DrawingElement {

public:
  CompositeElement(string name) : DrawingElement(name){};

  void Add(DrawingElement *d) { elements.push_back(d); };

  void Remove(DrawingElement *d) {
    for (unsigned int i = 0; i < elements.size(); i++) {
      if (elements[i]->getName() == d->getName()) {
        elements.erase(elements.begin() + i);
        return;
      }
    }
  }

  AbstractIterator *CreateIterator();
  void Display(int indent) {
    for (int i = 1; i <= indent; i++) {
      cout << "-";
    }
    cout << "+ " + getName() << endl;

    // Display each child element on this node
    for (unsigned int i = 0; i < elements.size(); i++) {
      elements[i]->Display(indent + 2);
    }
  }

private:
  vector<DrawingElement *> elements;
};

int main() {
  // Create a tree structure
  DrawingElement *root = new CompositeElement("Picture");
  root->Add(new PrimitiveElement("Red Line"));
  root->Add(new PrimitiveElement("Blue Circle"));
  root->Add(new PrimitiveElement("Green Box"));

  DrawingElement *comp = new CompositeElement("Two Circles");
  comp->Add(new PrimitiveElement("Black Circle"));
  comp->Add(new PrimitiveElement("White Circle"));
  root->Add(comp);

  // Add and remove a PrimitiveElement
  DrawingElement *pe = new PrimitiveElement("Yellow Line");
  pe->Add(new PrimitiveElement("Red Line"));
  root->Add(pe);
  root->Remove(pe);

  // Recursively display nodes
  root->Display(1);
  cout << endl;
  return 0;
}
