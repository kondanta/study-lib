#include "singly_linked_list.h"
/*Unit tests will be added here.*/

int main(){
	//Creating a list
	std::LinkedList list;
	/*Since this part for the testing changes do not matter.*/
	//Initilizing it with 5
	list.init_list(5);
	list.insert_back(6);
	list.insert_front(4);
	list.insert_into(1, 7);
	list.print_List();
	std::cout<<'\n'<<list.from_tail_value_at(4);
	std::cout<<'\n'<<list.value_at(1);
	std::cout<<'\n'<<list.size();//output2.
	std::cout<<'\n'<<list.isEmpty();
	std::cout<<'\n'<<list.get_value_from_front();
	std::cout<<'\n'<<list.get_value_from_back();
	std::cout<<'\n'<<list.pop_front()<<'\n';
	list.print_List();
	std::cout<<'\n'<<list.pop_back()<<'\n';
	std::cout<<'\n';
	list.remove_at(7);
	list.print_List();
	std::cout<<'\n';
	list.reverse();
}
