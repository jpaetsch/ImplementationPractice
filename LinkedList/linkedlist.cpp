// Linked List With Insert & Delete Implementation Practice


#include "linkedlist.h"


using namespace std;


// Constructor for the linked list
LinkedList::LinkedList() {
    head = NULL;
    tail = NULL;  
}


// Add a node to the end of the linked list
void LinkedList::append_node(int data) {
    Node *temp = new Node;          // Allocate space for the new node
    temp->nodeData = data;
    temp->nextNode = NULL;

    if(head == NULL) {              // Current node must be the head and tail for now
        head = temp;
        tail = temp;
    } else {                        // Current node is added to the end of the list
        tail->nextNode = temp;      // Set temp to be after the current tail
        tail = tail->nextNode;      // Then set temp to be the new tail
    }
}


// Get the length of the linked list from head to tail
// using loop traversal
void LinkedList::get_list_length() {
    int i = 0;
    Node *current = head;
    while(current != NULL) {
        i++;
        current = current->nextNode;
    }
    cout << "Length: " << i << endl;
}


// Get the head of the linked list
Node* LinkedList::get_list_head() {
    return head;
}


// Print the whole linked list from head to tail
// using recursion and head-getter function
void LinkedList::print_entire_list(Node *theHead) {
    if(theHead == NULL) {
        cout << "NULL" << endl;
    } else {
        cout << theHead->nodeData << " -> ";
        print_entire_list(theHead->nextNode);
    }
}


// Insert a node at the given spot (index like an array, with 0 being the head)
// Included error checking/handling if the given index doesn't exist, etc.
void LinkedList::insert_node(int data, int index) {
    Node *newN = new Node;
    newN->nodeData = data;
    newN->nextNode = NULL;          // will be temporary

    if(head == NULL) {              // if the list hasn't been initialized yet start it using this node and tell the user
        head = newN;
        tail = newN;
        cout << "[Index Ignored Warning] - list started using this element as there were no other entries" << endl;
    } else if(index == 0) {         // the node will replace / become the new head
            newN->nextNode = head;
            head = newN;
    } else {
        Node *current = head;
        bool outsideRange = false;
        for(int i = 1; i < index; ++i) {
            if(current == NULL) {
                outsideRange = true;
                break;
            }
            current = current->nextNode;
        }

        if(outsideRange) {          // the index is outside the current list length; append the node to the end and tell the user
            cout << "[Index Ignored Warning] - list was appended to using this element due to less entries than expected" << endl;
            this->append_node(data);
        } else {                    // the index is within the current list; insert after the node that has been iterated to
            newN->nextNode = current->nextNode;
            current->nextNode = newN;
        }
    }  
}


// Delete a node at the given spot (index like an array, with 0 being the head)
// Included error checking/handling if the provided index doesn't exist, etc.
void LinkedList::delete_node(int index) {
    if(head == NULL) {
        cout << "[No Deletion Warning] - no items in list, nothing deleted" << endl;
    } else if(index == 0) { 
        if(head == tail) {  // if there is only one list element delete both head and tail
            head = NULL;
            tail = NULL;
        } else {
            Node *temp = head;
            head = temp->nextNode;
            delete temp;
        }
    } else {
        Node *temp = head;
        bool outsideRange = false;
        for(int i = 1; i < index; ++i) {
            if(temp == NULL) {
                outsideRange = true;
                break;
            }
            temp = temp->nextNode;
        }

        if(outsideRange) { // Given index is too large and doesn't exist in the current list
            cout << "[No Deletion Warning] - index provided doesn't exist" << endl;
        } else { // Delete the requested node after reassinging the pointers
            Node *deleteMe = temp->nextNode;
            temp->nextNode = deleteMe->nextNode;                                         
            delete deleteMe;
        }
    }
}


// Linked List class implementation example with creation, insertion, deletion, and printing functionality
int main() {
    LinkedList mylist;
    mylist.delete_node(2);
    mylist.insert_node(0, 5);
    mylist.delete_node(0);
    mylist.append_node(1);
    mylist.append_node(2);
    mylist.append_node(5);
    mylist.insert_node(3, 2);
    mylist.insert_node(4, 3);
    mylist.insert_node(6, 20);
    mylist.print_entire_list(mylist.get_list_head());
    mylist.delete_node(0);
    mylist.delete_node(1);
    mylist.delete_node(2);
    mylist.delete_node(50);
    mylist.print_entire_list(mylist.get_list_head());
    mylist.get_list_length();
    return 0;
}