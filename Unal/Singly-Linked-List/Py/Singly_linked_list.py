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
        new_node = Node(data) # Access to storage
        new_node.set_next(self.head)
        self.head = new_node

    # Finds the size of list // O(n)    
    def size(self):
        current = self.head
        count = 0
        while current:
            count += 1
            current = current.get_next()
        return count - 1 # -1 because of self.head = None 

    # Search an item on the list // O(n) in worst case
    def search(self, data):
        current = self.head
        found = False
        while current and found is False:
            if current.get_data() == data:
                found = True
            else:
                current = current.get_next()
        if current is None:
            return "Item was not found."
        return "Item exists."

    # Delete the said item from list // O(n) in worst case
    def remove(self, data):
        current = self.head
        previous = None # Major difference between search and delete
        found = False
        while current and found is False:
            if current.get_data() == data:
                found = True
            else:
                previous = current
                current = current.get_next()
        if current is None: # Case of not having the item
            print("Item is not in the list.")
        elif previous is None: # Case of being first item
            self.head = current.get_next()
        else:
            previous.set_next(current.get_next())

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
ll.insert("2")
ll.insert("3")
ll.insert("4")
print("List:")
print(ll)

# Size check
print("Size:")
print(ll.size())

# Search
print("Searching 3...")
print(ll.search("3"))
print("Searching 7...")
print(ll.search("7"))

# Remove
print("Removing 3...")
ll.remove("3")
# 4 2 2 1
print(ll)
print("Removing 2...")
ll.remove("2")
# 4 2 1
print(ll)
print("Removing 9...")
ll.remove("9")