#ifndef NODE_H
#define NODE_H

template<typename T>
class Node
{
private:
  T _value;
  Node *_next;
public:
  Node();
  void setValue(T value = 0);
  T getValue();
  Node *getNext();
  void setNext(Node *next = nullptr);
  bool hasNext();
  virtual ~Node();
};

#endif // NODE_H
