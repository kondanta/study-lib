//============================================================================
// Name        : CompositePattern.cpp
// Description :
//============================================================================

#include <iostream>
#include <utility>
#include <vector>

namespace nstd {
//
// The classes and/or objects participating in this pattern are:
// 1. Component   (DrawingElement)
//		Declares the interface for objects in the composition.
// Implements
//      default behavior for the interface common to all classes, as
//      appropriate. declares an interface for accessing and managing its
//		child components.
// 2. Leaf   (PrimitiveElement)
//		represents leaf objects in the composition. A leaf has no
// children. 	    Defines behavior for primitive objects in the composition.
// 3. Composite   (CompositeElement)
//		defines behavior for components having children. Stores child
//		components. Implements child-related operations in the Component
// interface.
// 4. Client  (CompositeApp)
//		Manipulates objects in the composition through the Component
// interface.

// This is the "Component". (i.e tree node.)

class DrawingElement {
public:
  virtual ~DrawingElement() = default;
  /* virtual void Add(DrawingElement *d){};
   * virtual void Remove(DrawingElement *d){}; */
  virtual void Display(int indent) = 0;
  std::string getName() { return name; };

protected:
  explicit DrawingElement(std::string name) : name(move(name)){};
  // copy ctor
  DrawingElement(const DrawingElement &);
  // coppy assign
  DrawingElement &operator=(const DrawingElement &);
  // move ctor.
  DrawingElement(DrawingElement &&) noexcept;
  // move assign
  DrawingElement &operator=(DrawingElement &&) noexcept;

private:
  std::string name;
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
  // copy ctor
  AbstractIterator(const AbstractIterator &);
  // copy assignment
  AbstractIterator &operator=(const AbstractIterator &);
  // move ctor
  AbstractIterator(AbstractIterator &&) noexcept;
  // move assignment
  AbstractIterator &operator=(AbstractIterator &&) noexcept;
};

// This is the "Leaf".

class PrimitiveElement : public DrawingElement {
public:
  explicit PrimitiveElement(std::string name) : DrawingElement(move(name)){};
  /*
   *   void Add(DrawingElement *c) { cout << "Cannot add to a
   * PrimitiveElement\n"; } void Remove(DrawingElement *c) { cout << "Cannot
   * remove from a PrimitiveElement \n";
   *   } */
  void Display(int indent) override {
    for (int i = 1; i <= indent; i++) {
      std::cout << "-";
    }
    std::cout << " " << getName() << std::endl;
  }
};

// forward decleration
// This is the "Composite"
class CompositeElement : public DrawingElement {

public:
  explicit CompositeElement(std::string name) : DrawingElement(move(name)){};

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
  void Display(int indent) override {
    for (int i = 1; i <= indent; i++) {
      std::cout << "-";
    }
    std::cout << "+ " + getName() << std::endl;

    // Display each child element on this node
    for (auto &element : elements) {
      element->Display(indent + 2);
    }
  }

  int getCount() const { return elements.size(); }
  DrawingElement *get(int index) const { return elements[index]; }

  void removeLeaks() {
    for (DrawingElement *it : elements) {
      delete it;
    }
    elements.clear();
  }

private:
  std::vector<DrawingElement *> elements;
};

class CompositeIterator : public AbstractIterator {
public:
  explicit CompositeIterator(const CompositeElement *comp)
      : comp(comp), _current(0){};
  void First() override { _current = 0; }
  void Next() override { _current++; }
  bool IsDone() const override { return _current >= comp->getCount(); }
  DrawingElement *CurrentItem() const override {
    return (IsDone() ? nullptr : comp->get(_current));
  }
  void show(int indent) override {
    for (int i = 1; i <= indent; i++) {
      std::cout << "-";
    }
    std::cout << "+ " + this->CurrentItem()->getName() << std::endl;
    // Display each child element on this node
    for (this->First(); !this->IsDone(); this->Next()) {
      this->CurrentItem()->Display(indent + 2);
    }
  }

private:
  const CompositeElement *comp;
  int _current;
};

AbstractIterator *CompositeElement::CreateIterator() {
  return new CompositeIterator(this);
}

} // namespace nstd
int main() {
  // Create a tree structure
  nstd::CompositeElement *root = new nstd::CompositeElement("Picture");
  root->Add(new nstd::PrimitiveElement("Red Line"));
  root->Add(new nstd::PrimitiveElement("Yellow Line"));

  nstd::CompositeElement *comp = new nstd::CompositeElement("Circles");
  comp->Add(new nstd::PrimitiveElement("Black Circle"));
  comp->Add(new nstd::PrimitiveElement("White Circle"));
  root->Add(comp);

  nstd::AbstractIterator *it = root->CreateIterator();
  it->show(1);
  // HAVE TO REMOVE EACH COLLECTION EXPLICITLY
  comp->removeLeaks();
  root->removeLeaks();
  delete it;
  delete root;
  //  root->Display(1);
  std::cout << std::endl;
  /*   DrawingElement *root = new CompositeElement("Picture");
   *   root->Add(new PrimitiveElement("Red Line"));
   *   root->Add(new PrimitiveElement("Blue Circle"));
   *   root->Add(new PrimitiveElement("Green Box"));
   *
   *   DrawingElement *comp = new CompositeElement("Two Circles");
   *   comp->Add(new PrimitiveElement("Black Circle"));
   *   comp->Add(new PrimitiveElement("White Circle"));
   *   root->Add(comp);
   *
   *   // Add and remove a PrimitiveElement
   *   DrawingElement *pe = new PrimitiveElement("Yellow Line");
   *   pe->Add(new PrimitiveElement("Red Line"));
   *   root->Add(pe);
   *   root->Remove(pe);
   *
   *   // Recursively display nodes
   *   root->Display(1);
   *   cout << endl; */
  return 0;
}
