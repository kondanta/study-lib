#ifndef LIST_H
#define LIST_H

#include "node.hpp"

class List
{
private:
  Node<int> *_head;
public:
  List();
  void append(int);
  bool isEmpty();
  int size();
};



#endif // LIST_H
