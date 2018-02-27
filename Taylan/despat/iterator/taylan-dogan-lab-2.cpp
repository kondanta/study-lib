//============================================================================
// Name        : Taylan Dogan
// Description : Implements the Collection Iterator and the client code.
//============================================================================
#include "taylan-dogan-lab-2.hpp"
#include <typeinfo>

using namespace std;

//
// ============= FOOD ITERATOR ==============
//
FoodIterator::FoodIterator(const Collection *collection)
    : _collection(collection), _current(0){};
void FoodIterator::First() {
  _current = 0;
  while (!IsDone() && _collection->get(_current)->getType() != 1)
    _current++;
}
void FoodIterator::Next() {
  _current++;
  while (!IsDone() && _collection->get(_current)->getType() != 1)
    _current++;
}
bool FoodIterator::IsDone() const {
  int _num = _collection->getCount();
  while (_num >= 0 && _collection->get(_num - 1)->getType() != 1)
    _num--;
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
  while (!IsDone() && _collection->get(_current)->getType() != 2)
    _current++;
}
void BookIterator::Next() {
  _current++;
  while (!IsDone() && _collection->get(_current)->getType() != 2)
    _current++;
}
bool BookIterator::IsDone() const {
  int _num = _collection->getCount();
  while (_num >= 0 && _collection->get(_num - 1)->getType() != 2)
    _num--;
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
  // Create Iterator
  AbstractIterator *iterator = aggregate->CreateIterator(1);

  // Traverse the Aggregate.
  printAggregate(*iterator);
  iterator = aggregate->CreateIterator(2);

  printAggregate(*iterator);
  // freeing the heap
  delete iterator;
  aggregate->emptyVector();
  delete aggregate;

  return 0;
}
