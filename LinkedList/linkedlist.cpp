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
    Node* temp = new Node;          // Allocate space for the new node
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


// TODO create insert after certain node, delete certain node functions


// Linked List class implementation example with creation, insertion, deletion, and printing functionality
int main() {
    LinkedList mylist;
    mylist.append_node(1);
    mylist.append_node(2);
    mylist.append_node(5);
    mylist.print_entire_list(mylist.get_list_head());
    mylist.get_list_length();
    return 0;
}