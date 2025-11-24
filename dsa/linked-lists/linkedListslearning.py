class node:
    def __init__(self, data):
        self.data = data  ##element
        self.next = None  ##what it links to

class linkedList:
    def __init__(self):
        self.head = None

    def append(self, data):
        new_node = node(data) ##create the node

        if not self.head: ##if head of list does not exist
            self.head = new_node ##make new node the head  (first)
            return
        
        current = self.head ##start at the head
        while current.next: ##while there is a next node
            current = current.next ##move to the next node
        
        ##when no more next node
        current.next = new_node ##make the new node as the latest addition

    def print_list(self):
        current = self.head ##start at the head
        while current: ##while there is a current node
            print(current.data, end="-->") ##print the data
            current = current.next ##move to the next node
        print("None") ##indicate the end of the list

    def reverse_list(self):
        ##alter the linking >>>> to <<<<
        current = self.head ##start at the head
        
        prev = None ##previous node

        while current:  ##as long as current exists
            next_node = current.next  ##store the link of current
            current.next = prev ##link current node to prev

            ##for next loop
            prev = current ##make current node the previous node
            current = next_node
        
        self.head = prev ##head definition was skipped

