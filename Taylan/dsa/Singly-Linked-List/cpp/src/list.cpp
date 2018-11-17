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
