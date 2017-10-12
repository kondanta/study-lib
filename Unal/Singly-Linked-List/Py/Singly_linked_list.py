# Data and next node storage

class Node(object):

    def __init__(self, data = None, next_node = None):
        self.data = data
        self.next_node = next_node

    def get_data(self):
        return self.data

    def get_next(self):
        return self.next_node

    def set_next(self, new_next):
        self.next_node = new_next

    def __repr__(self): 
         return self.data

# Linked list

class linkedList(object):

    def  __init__(self, data_iterable):
        self.head = None # Start point
        for data in data_iterable: 
            self.insert(data)

    # Inserting "from start" // O(1)
    def insert(self, data):
        new_node = Node(data)
        new_node.set_next(self.head)
        self.head = new_node

    # Finds the size of list // O(n)    
    def size(self):
        current = self.head
        count = 0
        while current:
            count += 1
            current = current.get_next()
        return count
        
    def __repr__(self):
        node = self.head
        data = []
        while node:
            data.append(node.data)
            node = node.next_node
        return ' '.join(data)

# Calls

ll = linkedList([""]) # Creation of Linked List

# Insert
ll.insert("1")
ll.insert("2")
ll.insert("3")
ll.insert("4")
print("List:")
print(ll)

# Size check
print("Size:")
print(ll.size())