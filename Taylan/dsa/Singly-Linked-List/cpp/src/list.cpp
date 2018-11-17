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

void List::insertBack(int data){
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
