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
 * ==============================================================

 */

#include "main.hpp"
#include <typeinfo>

using namespace std;

//
// ============= FOOD ITERATOR ==============
//
FoodIterator::FoodIterator(const Collection *collection)
    : _collection(collection), _current(0){};
void FoodIterator::First() {
  _current = 0;
  while (!IsDone() && _collection->get(_current)->getType() != 1) {
    _current++;
  }
}
void FoodIterator::Next() {
  _current++;
  while (!IsDone() && _collection->get(_current)->getType() != 1) {
    _current++;
  }
}
bool FoodIterator::IsDone() const {
  int _num = _collection->getCount();
  while (_num >= 0 && _collection->get(_num - 1)->getType() != 1) {
    _num--;
  }
  return _current >= _num;
}
Item *FoodIterator::CurrentItem() const {
  return (IsDone() ? nullptr : _collection->get(_current));
}

//
//============= BOOK ITERATOR ============
//
BookIterator::BookIterator(const Collection *collection)
    : _collection(collection), _current(0){};
void BookIterator::First() {
  _current = 0;
  while (!IsDone() && _collection->get(_current)->getType() != 2) {
    _current++;
  }
}
void BookIterator::Next() {
  _current++;
  while (!IsDone() && _collection->get(_current)->getType() != 2) {
    _current++;
  }
}
bool BookIterator::IsDone() const {
  int _num = _collection->getCount();
  while (_num >= 0 && _collection->get(_num - 1)->getType() != 2) {
    _num--;
  }
  return _current >= _num;
}
Item *BookIterator::CurrentItem() const {
  return (IsDone() ? nullptr : _collection->get(_current));
}

//
// =========== Collection ITERATOR ============
//
CollectionIterator::CollectionIterator(const Collection *collection)
    : _collection(collection), _current(0) {}
void CollectionIterator::First() { _current = 0; }
void CollectionIterator::Next() { _current++; }
Item *CollectionIterator::CurrentItem() const {
  return (IsDone() ? nullptr : _collection->get(_current));
}
bool CollectionIterator::IsDone() const {
  return _current >= _collection->getCount();
}

// Printer Function
void printAggregate(AbstractIterator &i) {
  double sum = 0;
  cout << typeid(i).name() << endl;
  cout << "Iterating over collection:" << endl;
  for (i.First(); !i.IsDone(); i.Next()) {
    cout << i.CurrentItem()->getName() << endl;
    sum = sum + i.CurrentItem()->getPrice();
  }
  cout << endl;
  cout << "Total tax: " << sum << endl;
}
int main() {

  AbstractAggregate *aggregate = new Collection();
  aggregate->add(new Food("Burger", 5, 10));
  aggregate->add(new Food("Chips", 10, 10));
  aggregate->add(new Book("Concepts of X", 135.25, 100));
  aggregate->add(new Book("Concepts of Y", 135.25, 0));
  // Create Iterator
  AbstractIterator *it = aggregate->CreateIterator(1);
  AbstractIterator *nI = aggregate->CreateIterator(2);
  // Traverse the Aggregate.
  printAggregate(*it);
  printAggregate(*nI);
  // freeing the heap
  delete it;
  delete nI;
  aggregate->emptyVector();
  delete aggregate;

  return 0;
}
