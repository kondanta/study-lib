#ifndef __SINGLY_LINKED_LIST_H_INCLUDED__
#define	__SINGLY_LINKED_LIST_H_INCLUDED__

#include <iostream>
namespace std{

	class Node{
	private:
		int _data;
		Node *_next;

	public:
		Node(){}
		// setters and getters
		void setData(int Data){ _data = Data;}
		void setNext(Node *Next){
			if(Next == NULL){
				_next = NULL;
			}else{
			_next = Next;
			}
		}
		int Data(){return _data;}
		Node *Next(){return _next;}
	};

	class LinkedList{
	private:
		Node *head;
	public:
		LinkedList(){ head = NULL;}//init
		/*TODO: Tail will be added. */
		void insert_back(int data);//it will append the next value to the
									//front cell [x] -> [data]
		void insert_front(int data);
		bool isEmpty();
		void init_list(int data);
		void print_List();
		int size();
		void insert_into(int location, int data);
		int value_at(int index);
		int from_tail_value_at(int index);
		int get_value_from_front();
		int get_value_from_back();
		int pop_front();
		int pop_back();
		void remove_at(int index);
		Node *reverse();
	};
}
#endif