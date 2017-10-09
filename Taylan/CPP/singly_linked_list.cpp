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
		void setNext(Node *Next){ _next = Next;}
		int Data(){return _data;}
		Node *Next(){return _next;}
	};

	class LinkedList{
	private:
		Node *head;
	public:
		LinkedList(){ head = NULL;}//init
		/*TODO: insert back will be added. */
		void insert_Back(int data);//it will append the next value to the
									//front cell [x] -> [data]
		//bool is_Empty();
		//TODO:: Add init();
		void init_list(int data);
		void print_List();
	};

	void LinkedList::print_List(){
		//init. the temporary pointer, so that we cannot lose
		//original head pointer of the list.
		Node *tmp = head;

		//Checking the list if there is a node or not.
		if(tmp == NULL){//TODO: isEmpty()
			cout << "List is empty\n";
			return;
		}

		//Checking only one node situation.
		if(tmp->Next() == NULL){
			cout << "Starting: " <<tmp->Data()
				 <<"Next Value > NULL\n";
		}else{
			/*we need to do traversal until the last node.
			and since after last node there won't be any value
			it'll be null.*/
			while(tmp!=NULL){
				cout << tmp->Data() << " > ";
				//incrementing the pointer;
				tmp = tmp->Next();
			}
		}
	}

	/*inserting a value infront of the */
	void LinkedList::insert_Back(int data){
		//Creating a node
		Node *newNode = new Node();
		//in struct we do it like newNode->data = data;
		newNode->setData(data);
		newNode->setNext(NULL);

		//Creating a temporary pointer.
		Node *tmp = head;

		/*Since i'm going to add a value after the last value,
		I need to go at the end of the list.*/
		if (tmp != NULL){
			while(tmp->Next() != NULL){
				tmp = tmp->Next();
			}
			tmp->setNext(newNode);
		}else{
			//First node.
			head = newNode;
		}
	}

	void LinkedList::init_list(int data){
		//creating a node
		Node *newNode = new Node();
		newNode->setData(data);
		newNode->setNext(NULL);
		//Setting head to the NULL so that we can make the our data the head.
		if(head != NULL){
			head = NULL;
		}
		head = newNode;
	}





}

int main(){
	//Creating a list
	std::LinkedList list;

	//Initilizing it with 5
	list.init_list(5);
	list.insert_Back(6);
	list.print_List();
}
