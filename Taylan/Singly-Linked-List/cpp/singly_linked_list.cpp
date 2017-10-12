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
		void insert_Back(int data);//it will append the next value to the
									//front cell [x] -> [data]
		void insert_front(int data);
		bool isEmpty();
		void init_list(int data);
		void print_List();
		int size();
		void insert_into(int location, int data);
		int value_at(int index);
		int value_form_tail(int index);
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
	/*Inserting a value in front of the head node.*/
	void LinkedList::insert_front(int data){
		// creating a new node.
		 Node *newNode = new Node();
		 newNode->setData(data);
		 newNode->setNext(NULL);
		 /*After creating a new node, we have to put it in front of the current head value.
		 So, first i linked the new node to the head, so that it can point to head's value
		 then i change the head, so that new node become the new head.*/
		 newNode->setNext(head);
		 head = newNode;
	}
	/*Initializing the list with a value.*/
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
	/*It returns to Linked Lists size.*/
	int LinkedList::size(){
		//counter variable
		int ctr = 0;
		Node *tmp = head;
		
		while(tmp!=NULL){
			ctr++;
			tmp = tmp->Next();
		}
		return ctr;
	}

	bool LinkedList::isEmpty(){ return (head == NULL) ? true:false;	}

	void LinkedList::insert_into(int location, int data){
        //Creatin a new node
        Node *newNode = new Node();
        newNode->setData(data);
        newNode->setNext(NULL);
        /*If we want to put our data in place of the head*/
        if(location == 0){
        	newNode->setNext(head);
        	head = newNode;

        }else{
	        //Creating temporary pointer.
	        Node *curr = head;
	        /*iterating to location*/
	        for(int ctr = 0; ctr != location; ++ctr){
	        	if(curr->Next() == NULL){
	        		break;
	        	}
	            curr = curr->Next();
	        }
	        newNode->setNext(curr->Next());
	        curr->setNext(newNode);
		}
	}

	int LinkedList::value_at(int index){
		/*Creating a temporary head pointer*/
		Node *tmp = head;
		
		for(int ctr = 0; ctr != index; ++ctr){
			tmp = tmp->Next();
		}
		return tmp->Data();
	}

	int LinkedList::value_form_tail(int index){
		int converter = size() - index;
		/*Creating a temporary head pointer*/
		Node *tmp = head;
		for(int i = 0; i != converter; ++i){
			tmp = tmp->Next();
		}
		return tmp->Data();
	}


}

int main(){
	//Creating a list
	std::LinkedList list;

	//Initilizing it with 5
	list.init_list(5);
	list.insert_Back(6);
	list.insert_front(4);
	list.insert_into(1, 7);
	list.print_List();
	std::cout<<'\n'<<list.value_form_tail(4);
	std::cout<<'\n'<<list.value_at(1);
	std::cout<<'\n'<<list.size();//output2.
	std::cout<<'\n'<<list.isEmpty();
}
