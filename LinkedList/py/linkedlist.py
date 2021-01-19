# Python implementation of a double linked list data structure using
# a node and linked list class


# Node - return its own data, set and get the next node that its linked to
class Node(object):

    # Initialize the node data and the pointer to the next linked node to None
    def __init__(self, data=None, nextNode=None, previousNode=None):
        self.data = data
        self.nextNode = nextNode
        self.previousNode = previousNode
    
    def get_next_node(self):
        return self.nextNode
    
    def get_previous_node(self):
        return self.previousNode
    
    def set_next_node(self, newNextNode):
        self.nextNode = newNextNode
    
    def set_previous_node(self, newPreviousNode):
        self.previousNode = newPreviousNode
    
    def get_data(self):
        return self.data


# Linked List - insertion, deletion, search of linked nodes within its structure
class DoubleLinkedList(object):

    def __init__(self, head=None):
        self.head = head

    # Push a node onto the front of the linked list to become the new head
    def push_node(self, data):
        addToFront = Node(data)
        if self.head is None:   # if the list is empty this node is the single head item
            self.head = addToFront
        else:                   # otherwise set the previous and next links and make it the new head
            addToFront.set_next_node(self.head)
            self.head.set_previous_node(addToFront)
            self.head = addToFront
    
    # Append a node onto the end of the linked list
    def append_node(self, data):
        addToBack = Node(data)
        if self.head is None:   # if the list is empty this node becomes the single head item
            self.head = addToBack
        else:                   # otherwise iterate until you're at the current last list item and set the links
            itrNode = self.head
            while itrNode.get_next_node():
                itrNode = itrNode.get_next_node()
            itrNode.set_next_node(addToBack)
            addToBack.set_previous_node(itrNode)

    # Get the length of the list counting from head down
    def get_length(self):
        itrNode = self.head
        numNodes = 0
        while itrNode:
            numNodes += 1
            itrNode = itrNode.get_next_node()
        
        return numNodes

    # Search the linked list for the given value from the head down - if it isn't found inform the user
    def search_list(self, value):
        itrNode = self.head
        if itrNode is None:
            print("List is empty and cannot be searched")
        else:
            while itrNode:
                if(itrNode.get_data() == value):
                    print("Found '%d' in the list!", value)
                    return
                else:
                    itrNode = itrNode.get_next_node()
            print("Unable to find '%d' in the list")


            #TODO add reverse entire list and delete node functionality, test all


if __name__=="__main__":
    myDoubleList= 