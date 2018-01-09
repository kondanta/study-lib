#include <iostream>
#include <utility>

using namespace std;

class Stack {
public:
  Stack() = default;
  ~Stack() = default;
  // Set and Get
  void SetTop(int /*top*/);
  int GetTop();
  // Stack Functions
  void Push(int /*value*/);
  int Pop();
  bool isEmpty();

private:
  int topValue{-1};
};

void Stack::SetTop(int x) { topValue = move(x); }

int Stack::GetTop() { return topValue; }

int main() {
  Stack obj;
  cout << obj.GetTop(); // Exp. Out -> -1
  obj.SetTop(5);
  cout << obj.GetTop(); // Exp. Out -> 5;
  return 0;
}
