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
void FoodIterator::First() { _current = 0; }
void FoodIterator::Next() { _current++; }
bool FoodIterator::IsDone() const {
  return _current >= _collection->getCount();
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

  Item *food = new Food("Burger", 5);
  Book *book = new Book("Book", 2);

  AbstractAggregate *aggregate = new Collection();
  aggregate->add(food);
  aggregate->add(book);
  /*   aggregate->add(new Food("Burger", 5));
   *   aggregate->add(new Item("Item 0"));
   *   aggregate->add(new Item("Item 1"));
   *   aggregate->add(new Item("Item 2"));
   *   aggregate->add(new Item("Item 3"));
   *   aggregate->add(new Item("Item 4"));
   *   aggregate->add(new Item("Item 5"));
   *   aggregate->add(new Item("Item 6"));
   *   aggregate->add(new Item("Item 7"));
   *   aggregate->add(new Item("Item 8"));
   *  */
  // Create Iterator
  AbstractIterator *iterator = aggregate->CreateIterator(1);

  // Traverse the Aggregate.
  printAggregate(*iterator);
  // freeing the heap
  delete iterator;
  delete food;
  delete book;
  delete aggregate;

  return 0;
}
