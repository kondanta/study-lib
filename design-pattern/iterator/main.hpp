/*
 * =============================================================
 * NOTE: MAJOR CLASSES WERE ALREADY IMPLEMENTED.
 * I JUST MODERNIZED IT, AND CHANGED AS MY LAB WORK SUGGESTED.
 * -> ADDING A NEW TAX CLASS
 * -> ADDING 2 SUB CLASSES DERIVED FROM ITEM CLASS
 * -> ADDING ITERATOR CLASSES FOR THOSE CLASSES
 * -> AND I ALSO FIXED THE MEMORY LEAKS AS MUCH AS I CAN
 *
 * Taylan Dogan.
 *==============================================================
 *
 * iterator pattern:
 *
 * provide a way to access the elements of an aggregate object
 * sequentially without exposing its underlying representation.
 *
 * the classes and/or objects participating in this pattern are:
 *
 * 1. iterator  (abstractiterator)
 *                 defines an interface for accessing and traversing elements.
 * 2. concreteiterator  (iterator)
 *                 implements the iterator interface.
 *                 keeps track of the current position in the traversal of the
 * aggregate.
 * 3. aggregate  (abstractcollection)
 *                 defines an interface for creating an iterator object
 * 4. concreteaggregate  (collection)
 *                 implements the iterator creation interface to return an
 *instance of the proper concreteiterator
 *  */
#ifndef __MAIN_HPP
#define __MAIN_HPP
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

//
// Our concrete collection consists of Items.
//

class Tax {
public:
  void setRatio(double r) { this->_ratio = r; }

  double getRatio() { return this->_ratio; }

  double getPrice(double price) { return price * ((_ratio / 100) + 1); }

private:
  double _ratio;
};

class Item {
public:
  explicit Item(string name, int type, double price, double taxRatio)
      : _name{move(name)}, _type(type), _price(price) {
    this->tax.setRatio(taxRatio);
  };
  string getName() { return _name; }
  int getType() { return this->_type; }
  double getSolePrice() { return this->_price; }
  void setRatio(double r) { this->tax.setRatio(r); }
  double getPrice() { return tax.getPrice(_price); }

private:
  Tax tax{};
  string _name;
  int _type;
  double _price;
};

class Food : public Item {
public:
  Food(string name, double price, double taxRatio)
      : Item(move(name), 1, price, taxRatio) {}
};

class Book : public Item {
public:
  Book(string name, double price, double taxRatio)
      : Item(move(name), 2, price, taxRatio) {}
};

//
// This is the abstract "Iterator".
//		AbstractIterator
//

class AbstractIterator {
public:
  /// This was the warning reason when we want to delete
  /// Abstract Iterator in main
  virtual ~AbstractIterator() = default;
  virtual void First() = 0;
  virtual void Next() = 0;
  virtual bool IsDone() const = 0;
  virtual Item *CurrentItem() const = 0;

protected:
  AbstractIterator() = default;
  ;
};

// Forward Declaration of Collection

class Collection;
/*
 * This is how I fix the FoodIterator Error.
 * Since we already Collection forward decleration
 * It was causing circular dependency in CreateIterator function.
 *
 * */
class FoodIterator : public AbstractIterator {
public:
  explicit FoodIterator(const Collection *collection);
  void First() override;
  void Next() override;
  bool IsDone() const override;
  Item *CurrentItem() const override;

private:
  const Collection *_collection;
  int _current;
};

class BookIterator : public AbstractIterator {
public:
  explicit BookIterator(const Collection *collection);
  void First() override;
  void Next() override;
  bool IsDone() const override;
  Item *CurrentItem() const override;

private:
  const Collection *_collection;
  int _current;
};
//
// This is the "concrete" Iterator for collection.
//		CollectionIterator
//

class CollectionIterator : public AbstractIterator {
public:
  explicit CollectionIterator(const Collection *collection);
  void First() override;
  void Next() override;
  Item *CurrentItem() const override;
  bool IsDone() const override;

private:
  const Collection *_collection;
  int _current;
};

//
// This is the abstract "Aggregate".
//			AbstractAggregate
//

class AbstractAggregate {
public:
  virtual ~AbstractAggregate() = default;
  virtual AbstractIterator *CreateIterator(int type) = 0;
  virtual void add(Item *) = 0;     // Not needed for iteration.
  virtual int getCount() const = 0; // Needed for iteration.
  virtual Item *get(int) const = 0; // Needed for iteration.
  virtual void
  emptyVector() = 0; // Needed for fixing memory leak after removing
                     // aggregate object in main.

protected:
  AbstractAggregate() = default;
  ;
};
//
// This is the concrete Aggregate.
//			Collection
//
class Collection : public AbstractAggregate {
private:
  vector<Item *> _items;

public:
  AbstractIterator *CreateIterator(int type) override {
    if (type == 1) {
      return new FoodIterator(this);
    }
    if (type == 2) {
      return new BookIterator(this);
    }
    return new CollectionIterator(this);
  }
  int getCount() const override { return _items.size(); }
  void add(Item *item) override { _items.push_back(item); };
  Item *get(int index) const override { return _items[index]; };
  // clears the collection
  void emptyVector() override {
    for (Item *it : _items) {
      delete it;
    }
    _items.clear();
  }
};

#endif //__MAIN_HPP
