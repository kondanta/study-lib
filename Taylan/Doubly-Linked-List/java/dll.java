
class Node{
	public Node next;
	public Node prev;
	int data;

	public Node(int data){
		this.data = data;
	}
}

class DoublyLinkedList{
	private Node head;
	private Node tail;
	int size = 0;


	public void insertion(int data, int index){
		
		Node newNode = new Node(data);

		// It'll become the last element of the list.
		if(index > size){
			index = size;
		}
		
		if(head == null){
			head = newNode;
			tail = head;
			size++;
			return; // for exiting
		}

		if(index == 0){
			newNode.next = head; // pushing head forward
			head.prev = newNode; // connecting head's previous link to new node so that it can be the second.
			size++;
			return;
		}
		
		// NewNode become last element.
		if(index == size + 1){
			newNode.prev = tail;
			tail.next = newNode;
			tail = newNode; // tracking the tail value.
			return;
		}
		Node curr = head;
		for(int ctr = 0; ctr != index; ctr++){
			curr = curr.next;
		}

		newNode.next = curr;
		newNode.prev = curr.prev;
		curr.prev.next = newNode; // ,__, doubly linked list is killing me.....
		curr.prev = newNode;
		size++;

	}


}

class dll{
	public static void main(String[] args) {
		DoublyLinkedList list = new DoublyLinkedList();

		int data = 5;
		int index = 2;
		list.insertion(5, 2);
	}
}