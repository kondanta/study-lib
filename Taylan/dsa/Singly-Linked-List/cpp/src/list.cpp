#include "list.hpp"

// initialize list with null
// TODO: Init with a data
List::List(){
  this->_head = nullptr;
};

bool List::isEmpty(){
  return this->_head == nullptr ? true : false;
}

int List::size(){
  int counter = 0;
  Node<int> *tmp = this->_head;
  while(tmp != nullptr){
    counter ++;
    tmp = tmp->getNext();
  }
  return counter;
}

void List::append(int data){
  Node<int> *node = new Node<int>();
  node->setValue(data);
  // Init a new node.
  Node<int> *tmp = this->_head;
  // If list is empty
  if(isEmpty()){
    this->_head = node;
    return;
  }

  while(tmp->hasNext()){
    tmp = tmp->getNext();
  }
  tmp->setNext(node);
}

void List::initList(int value){
  //overflow guard
  value < 0 ? value = 0 : value;
  Node<int> *node = new Node<int>();
  node->setValue(value);
  this->_head = node;
}

int List::getHeadValue(){
  return this->_head->getValue();
}

int List::getTailValue(){
  Node<int> *node = this->_head;
  while(node->hasNext()){
    node = node->getNext();
  }
  return node->getValue();
}

void List::insertFront(int value){
  Node<int> *node = new Node<int>();
  node->setValue(value);
  node->setNext(this->_head);
  this->_head = node;
}

int List::valueAt(int index){
  Node<int> *tmp = this->_head;
  for(int i = 0; i != index; ++i){
    tmp = tmp->getNext();
  }
  return tmp->getValue();
}

int List::popHead(){
  Node<int> *tmp = this->_head;
  int value = this->_head->getValue();
  this->_head = this->_head->getNext();
  delete tmp;
  return value;
}

int List::popTail(){
  Node<int> *tmp = this->_head;
  int value;
  while(tmp->getNext()->hasNext()){
    tmp = tmp->getNext();
  }
  value = tmp->getNext()->getValue();
  tmp->setNext();
  return value;
}

void List::insert(int index, int value){
  Node<int> *node = new Node<int>();
  node->setValue(value);
  if(index == 0){
    node->setNext(this->_head);
    this->_head = node;
    return;
  }
  if(index >= size()){
    append(value);
    delete node;
    return;
  }
  Node<int> *tmp = this->_head;
  // index - 1 because we want to change the given index
  // not the after one.
  for(int i = 0; i < index - 1; ++i){
    tmp = tmp->getNext();
  }
  node->setNext(tmp->getNext());
  tmp->setNext(node);
}

void List::erase(int index){
  Node<int> *tmp = this->_head;
  if(index == 0){
    this->_head = this->_head->getNext();
    delete tmp;
    return;
  }
  if(index >= size()){
    popTail();
    return;
  }
  for(int i = 0; i < index - 1; ++i){
    tmp = tmp->getNext();
  }
  tmp->setNext(tmp->getNext()->getNext());
  delete tmp;
}

void List::reverse(){
  Node<int> *tmp = _head;
  Node<int> *second = new Node<int>();
  Node<int> *reversedList = nullptr;

  while(tmp){
    second = tmp->getNext();
    tmp->setNext(reversedList);
    reversedList = tmp;
    tmp = second;
  }
  this->_head = reversedList;
}

int List::kthValueFromTail(int index){
  index >= size() ? index = size() - 1 : index;
  return valueAt((size() - 1) - index);
}
