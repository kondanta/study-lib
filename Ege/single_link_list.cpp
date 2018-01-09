

#include <iostream>

using namespace std;

class node{

    private:
        int data;
        node *next;

    public:

        //CONSTRUCTER OF NODE CLASS
        node( ){
            cout << "Node Object Created" << endl;
            this->next = NULL;
        }

        //PARAMETERİZET CONSTRUCTER OF NODE CLASS
        node( int data ){
            this->data = data;
            this->next = NULL;
        }

       //SET FUCNTION FOR VARİABLE DATA
        void set_node_data( int data ){
            this->data = data;
            return;
        }

        //SET FUNCTION FOR NEXT POİNTER
        void set_next_node( node *tmp_next ){
            next = tmp_next;
            return;
        }

        //GET FUNCTION FOR VARİABLE DATA
        int get_node_data(  ){
            return this->data;

        }

        //GET FUNCTION FOR NEXT POİNTER
        node* Next(  ){
            return this->next;

        }


};


class single_link_list{

    private:
        node *head;

    public:

       // CONSTRUCTER OF SINGLE LINK LIST CLASS
       single_link_list( ){
           head=NULL;
            cout << "Single Link List Object Created" <<endl;
       }


        //DİSPLAY FUNCTION FOR THE SINGLE LINK LIST CLASS
        void display_link_list(  ){

        node *tmp = head;

        if( tmp == NULL ){

            cout << "There is no element in that link" << endl;

        }else{

            while ( tmp != NULL ){

                cout << tmp->get_node_data() << "\t";
                tmp = tmp -> Next();

            }

            cout << endl;

        }
            return ;
        }


        //INSERT FUNCTION TO THE FRONT OF THE LIST
        void insert_link_list_front( int data ){

                node *tmp = new node();

                tmp->set_next_node(NULL);
                tmp->set_node_data(data);

                tmp->set_next_node(head);
                head = tmp;

            return ;

        }

        //INSERT FUNCTION TO THE END OF THE LİST
        void insert_link_list_end( int data ){

                node *tmp_node = new node();

                tmp_node->set_next_node(NULL);
                tmp_node->set_node_data(data);

                node * tmp = head;

                //I assume head is not null

                if( tmp == NULL ){

                    while( tmp->Next() != NULL ){
                        tmp = tmp->Next();
                    }
                        tmp->set_next_node(tmp_node);
                }else{

                    head = tmp_node;

                }
           return;
        }

        //SIZE FUCNTION FOR THE LINK LIST

        int size(  ){

                node *tmp = head;
                int counter;

                while( tmp != NULL ){

                    counter++;
                    tmp = tmp ->Next();
                }
            return counter;
        }

        //INSERT FUNCTION FOR SPESIFIC POSITION
        void insert_position( int location,int data ){

            node *tmp_node = new node();
            tmp_node->set_node_data(data);
            tmp_node->set_next_node(NULL);

            if( location == 0 ){

                insert_link_list_front(data);

            }else{

                node *curr = head;

                for( int i = 0 ; i < location ; i++  ){

                    if( curr->Next() == NULL ){

                        break;

                    }

                   curr = curr->Next();

                }

                tmp_node->set_next_node(curr->Next());
                curr->set_next_node(tmp_node);
            }

        }

        //FUNCTION TO CHECK WHETHER LİST EMPTY OR NOT
        bool is_link_list_empty(  ){

            bool answer;

            if( head == NULL ){

                answer = true;

            }else{

                answer = false;
            }

            return answer;
        }


};


int main()
{

    single_link_list deneme ;

    deneme.display_link_list();

    deneme.insert_link_list_front(6);

    deneme.display_link_list();

    deneme.insert_position(2,2);

    deneme.display_link_list();

    deneme.insert_position(3,56);
    deneme.insert_position(4,4);
    deneme.insert_position(5,9);
    deneme.insert_position(6,8);


    deneme.display_link_list();





    return 0;
}
