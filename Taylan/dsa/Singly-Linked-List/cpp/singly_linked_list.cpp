#include "singly_linked_list.hpp"

namespace LinkList{
	void LinkedList::print_List(){
		//init. the temporary pointer, so that we cannot lose
		//original head pointer of the list.
		Node *tmp = head;

		//Checking the list if there is a node or not.
		if(tmp == NULL){//TODO: isEmpty()
			std::cout << "List is empty\n";
			return;
		}

		//Checking only one node situation.
		if(tmp->Next() == NULL){
			std::cout << "Starting: " <<tmp->Data()
				 <<"Next Value > NULL\n";
		}else{
			/*we need to do traversal until the last node.
			and since after last node there won't be any value
			it'll be null.*/
			while(tmp!=NULL){
				std::cout << tmp->Data() << " > ";
				//incrementing the pointer;
				tmp = tmp->Next();
			}
		}
	}


	/*inserting a value infront of the */
	void LinkedList::insert_back(int data){
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


	/*It returns to the value of given index starting from the tail.*/
	int LinkedList::from_tail_value_at(int index){
		int converter = size() - index;
		/*Creating a temporary head pointer*/
		Node *tmp = head;
		for(int i = 0; i != converter; ++i){
			tmp = tmp->Next();
		}
		return tmp->Data();
	}


	int LinkedList::get_value_from_front(){ return head->Data(); }


	int LinkedList::get_value_from_back(){
		Node *tmp = head;
		while(tmp->Next() != NULL){
			tmp = tmp->Next();
		}
		return tmp->Data();
	}


	/*Removes the first node of the list.*/
	int LinkedList::pop_front(){
		/*Creating a new node for the removal.*/
		Node *tmp = head;
		head = head->Next();
		delete tmp;

		return head->Data();
	}


	int LinkedList::pop_back(){
		/*Creating a new node for the removal.*/
		Node *curr = head;
		/*1->2->3->4->null*/
		while(curr->Next()->Next() != NULL){
			curr = curr->Next();
		}

		Node *tmp = curr;
		delete tmp->Next();
		tmp->setNext(NULL);/*Last value becomes zero and still showing up in the list.*/

		return tmp->Data();
	}


	void LinkedList::remove_at(int index){
		Node *tmp = head;
		/*If index is 0, we're removing the first value.*/
		if(index == 0){
			pop_front();
		}else{
			/*If index number is bigger than link lists size,
			if it is, we need to index = position of the last value of list.*/
			if(size() < index)
				index = size() - 1; //because our list starts with the index 0
			
			for(int ctr = 0; ctr < (index - 1); ++ctr){
				tmp = tmp->Next();
			}/*Checking the next and next > next. If null we're removing from tail*/
			Node *p = tmp->Next()->Next();
			delete tmp->Next();
			tmp->setNext(p);
		}
	}
	/*Reversing the linked list and printing the reversed order.*/
	Node * LinkedList::reverse(){
		Node *tmp = head;
		Node *sec = new Node();
		Node *reverselist = NULL;

		/*Reversing the list*/
		while(tmp != NULL){
			sec = tmp->Next();
			tmp->setNext(reverselist);
			reverselist = tmp;
			tmp = sec;
		}
		while(reverselist){
			std::cout<<reverselist->Data()<<" > ";
			reverselist = reverselist->Next();
		}
		return reverselist;
	}
}
