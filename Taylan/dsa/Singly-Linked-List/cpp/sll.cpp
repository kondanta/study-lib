// Some stuff

template<typename T>
class Node
{
private:
  T _value;
  Node *_next;
public:
  Node();
  void setValue(T);
  T getValue();
  Node *getNext();
  void setNext(Node *);
  bool hasNext();
  virtual ~Node();
};

template<typename T>
Node<T>::Node() = default;

template<typename T>
Node<T>::~Node() = default;

template<typename T>
void Node<T>::setValue(T value){
  this->_value = value;
}

template<typename T>
T Node<T>::getValue(){
  return this->_value;
}

template<typename T>
void Node<T>::setNext(Node<T> *next){
  this->_next = next;
}

template<typename T>
Node<T> *Node<T>::getNext(){
  return this->_next;
}

template<typename T>
bool Node<T>::hasNext(){
  return this->_next == nullptr ? false : true; 
}
