//============================================================================
// Name        : Taylan Dogan
// Description : Implements the Collection Iterator and the client code.
//============================================================================
#include "taylan-dogan-lab-2.hpp"
#include <typeinfo>

using namespace std;

// Iterator Logic implementations
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
  cout << typeid(i).name() << endl;
  cout << "Iterating over collection:" << endl;
  for (i.First(); !i.IsDone(); i.Next()) {
    cout << i.CurrentItem()->getName() << endl;
  }
  cout << endl;
}
int main() {

  AbstractAggregate *aggregate = new Collection();
  aggregate->add(new Food("Burger", 5.50));
  aggregate->add(new Food("Chips", 10.2));
  aggregate->add(new Book("Concepts of X", 135.25));
  // Create Iterator
  AbstractIterator *iterator = aggregate->CreateIterator(1);

  // Traverse the Aggregate.
  printAggregate(*iterator);
  // freeing the heap
  delete iterator;
  aggregate->emptyVector();
  delete aggregate;

  return 0;
}
