#ifndef LIST_H
#define LIST_H

#include "node.hpp"

class List
{
private:
  Node<int> *_head;
public:
  List();
  ~List();
  void append(int);
  bool isEmpty();
  int size();
  void initList(int);
  void insertFront(int);
  int getHeadValue();
  int getTailValue();
  int valueAt(int);
  int popHead();
  int popTail();
  void insert(int/*index*/, int/*value*/);
  void erase(int);
  void reverse();
  int kthValueFromTail(int);
  void removeValue(int);
};



#endif // LIST_H
