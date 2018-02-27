// Taylan Dogan
// lab2.h
//
// Iterator pattern:
//
// Provide a way to access the elements of an aggregate object
// sequentially without exposing its underlying representation.
//
// The classes and/or objects participating in this pattern are:

// 1. Iterator  (AbstractIterator)
//		defines an interface for accessing and traversing elements.
// 2. ConcreteIterator  (Iterator)
//		implements the Iterator interface.
//		keeps track of the current position in the traversal of the
// aggregate.
// 3. Aggregate  (AbstractCollection)
//		defines an interface for creating an Iterator object
// 4. ConcreteAggregate  (Collection)
//		implements the Iterator creation interface to return an instance
// of the proper ConcreteIterator
//
#ifndef __LAB_2_HPP
#define __LAB_2_HPP
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

//
// Our concrete collection consists of Items.
//

class Item {
public:
  explicit Item(string name) : _name(std::move(std::move(name))){};
  string getName() { return _name; }
  int getType() { return this->type; }

protected:
  int type{};

private:
  string _name;
};

class Food : public Item {
public:
  Food(string name, int price) : Item(std::move(name)), _price(price) {
    type = 1;
  }
  int getPrice() { return _price; }

private:
  int _price;
};

class Book : public Item {
public:
  Book(string name, int price) : Item(std::move(name)), _price(price) {
    type = 2;
  }
  int getPrice() { return this->_price; }

private:
  int _price;
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
    return new CollectionIterator(this);
  }
  int getCount() const override { return _items.size(); }
  void add(Item *item) override { _items.push_back(item); };
  Item *get(int index) const override { return _items[index]; };
};

#endif // __LAB_2_H
