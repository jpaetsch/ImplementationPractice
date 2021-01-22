# Python implementation of a double linked list data structure using
# a node and linked list class

# Potential Improvements Include:
# 1) Clean up functions; I especially think there must be a cleaner way to implement the reverse_this_list() function
# 2) Maybe add a tail node to better take care of edge cases the first and last node of the list are often involved in
# 3) Lots of more functionality to add; similar to my C++ versions could add node insertion instead of just adding 
#    nodes at the front and back
# 4) Instead of a unique print_list function could override __str__() to to print the object instead
# 5) Better test cases and function print feedback for information on what actions are being taken on the list


# Node - return its own data, set and get the next node that its linked to
class Node(object):

    # Initialize the node data and the pointer to the next linked node to None
    def __init__(self, data=None, nextNode=None, previousNode=None):
        self.data = data
        self.nextNode = nextNode
        self.previousNode = previousNode
        return
    
    def get_next_node(self):
        return self.nextNode
    
    def get_previous_node(self):
        return self.previousNode
    
    def set_next_node(self, newNextNode):
        self.nextNode = newNextNode
        return
    
    def set_previous_node(self, newPreviousNode):
        self.previousNode = newPreviousNode
        return
    
    def get_data(self):
        return self.data


# Linked List - insertion, deletion, search of linked nodes within its structure
class DoubleLinkedList(object):

    def __init__(self, head=None):
        self.head = head
        return


    # Push a node onto the front of the linked list to become the new head
    def push_node(self, data):
        addToFront = Node(data)
        if(self.head is None):   # if the list is empty this node is the single head item
            self.head = addToFront
        else:                   # otherwise set the previous and next links and make it the new head
            addToFront.set_next_node(self.head)
            self.head.set_previous_node(addToFront)
            self.head = addToFront
        return
    

    # Append a node onto the end of the linked list
    def append_node(self, data):
        addToBack = Node(data)
        if(self.head is None):   # if the list is empty this node becomes the single head item
            self.head = addToBack
        else:                   # otherwise iterate until you're at the current last list item and set the links
            itrNode = self.head
            while(itrNode.get_next_node()):
                itrNode = itrNode.get_next_node()
            itrNode.set_next_node(addToBack)
            addToBack.set_previous_node(itrNode)
        return


    # Get the length of the list counting from head down
    def get_length(self):
        itrNode = self.head
        numNodes = 0
        while(itrNode):
            numNodes += 1
            itrNode = itrNode.get_next_node()
        
        return numNodes


    # Search the linked list for the given value from the head down - if it isn't found inform the user
    def search_list(self, value):
        if(self.head is None):
            print("List is empty and cannot be searched")
        else:
            itrNode = self.head
            while(itrNode):
                if(itrNode.get_data() == value):
                    print("Found " + str(value) + " in the list!")
                    return
                else:
                    itrNode = itrNode.get_next_node()
            print("Unable to find " + str(value) + " in the list")
        return


    # Index the linked list like an array and delete the node at the provided index
    # If it doesn't exist, print an error message
    def delete_node(self, index):
        if(self.head is None):
            print("List is empty, requested node cannot be deleted")
        else:
            i = 0
            itrNode = self.head
            while(itrNode):
                if(i == index):
                    if(i == 0):   # Remove the first node (head)
                        temp = itrNode.get_next_node()
                        temp.set_previous_node(None)
                        itrNode = None
                        self.head = temp
                    elif(i + 1 == self.get_length()):   # Remove the last node (tail)
                        temp = itrNode.get_previous_node()
                        temp.set_next_node(None)
                        itrNode = None
                    else:   # Remove the node from within the list somewhere
                        before = itrNode.get_previous_node()
                        after = itrNode.get_next_node()
                        before.set_next_node(after)
                        after.set_previous_node(before)
                        itrNode = None

                    deleted = True
                else:
                    i += 1
                    itrNode = itrNode.get_next_node()
                    deleted = False
            
            if(deleted == False):
                print("Index out of range, node could not be deleted")
        return


    # Reverse current list order ie. 1->2->3 becomes 3->2->1
    def reverse_this_list(self):
        if(self.head is None):
            print("No elements in the list, can't reverse")
        else:

            # Grab two nodes starting at the head that will remain side-by-side as we move through the list
            itrNode = self.head
            temp = itrNode.get_next_node()

            # Change the current head as it will become the end of the list
            itrNode.set_previous_node(temp)
            itrNode.set_next_node(None)

            # Iterate through the nodes, setting previous link and then next link of the second node as you traverse through
            while(temp):
                temp.set_previous_node(temp.get_next_node())
                temp.set_next_node(itrNode)

                itrNode = temp
                temp = temp.get_previous_node()     # Get previous actually moves forward (next) along unfinished nodes, as the links have been reversed

            # Set up the new head
            self.head = itrNode
        return

    
    # Print the list in order from head to the end
    def print_list(self):
        itrNode = self.head
        if(itrNode is None):
            print("Can't print the list; nothing's here!")
        else:
            while(itrNode):
                print(str(itrNode.get_data()) + "    ->")
                itrNode = itrNode.get_next_node()
            print("END")
        return


if __name__ == "__main__":
    # Create a double linked list object and test the various functions
    dll = DoubleLinkedList()

    # Empty list tests
    dll.reverse_this_list()
    print(dll.get_length())
    dll.delete_node(0)
    dll.search_list(5)
    dll.print_list()

    # Test functionality
    dll.append_node(2)
    dll.append_node(3)
    dll.push_node(1)
    dll.append_node(4)
    dll.push_node(0)
    dll.append_node(5)
    dll.append_node(6)
    
    dll.print_list()
    print(dll.get_length())
    dll.reverse_this_list()
    dll.print_list()

    dll.delete_node(7)
    dll.search_list(0)
    dll.delete_node(6)
    dll.search_list(0)
    dll.print_list()

    dll.reverse_this_list()
    dll.delete_node(0)
    dll.search_list(20)
    dll.delete_node(1)
    dll.delete_node(2)
    dll.print_list()  # should end with just 2 4 6