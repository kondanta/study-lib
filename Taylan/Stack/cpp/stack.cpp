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

  int arr[10] = {0}; // max 10
private:
  int topValue{-1};
};

void Stack::SetTop(int x) { topValue = move(x); }

int Stack::GetTop() { return topValue; }

void Stack::Push(int value) {
  // TODO Max check
  int topv = GetTop();
  arr[++topv] =
      value; //++arg bc we need to increment first since init value is -1
  SetTop(topv++);
}

int Stack::Pop() {
  int topv = GetTop();
  int poppedValue = arr[topv--];
  SetTop(topv--);
  cout << "Popped value: " << poppedValue;
  return poppedValue;
}

int main() {
  Stack obj;
  obj.Push(5);
  obj.Push(10);
  obj.Pop();
  for (int i = 0; i < 10; i++) {
    cout << obj.arr[i] << " ";
  }
  return 0;
}
