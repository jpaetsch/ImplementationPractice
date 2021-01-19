// Simple Linked List Implementation Practice


#include "linkedlist-simple.h"


using namespace std;


// This program created very simple linked list with 5 nodes
int main() {
    Node* head = NULL;
    Node* second = NULL;
    Node* third = NULL;
    Node* fourth = NULL;
    Node* tail = NULL;

    // Allocate nodes in the heap
    head = new Node();
    second = new Node();
    third = new Node();
    fourth = new Node();
    tail = new Node();

    // Assign data to nodes and link to the next
    head->nodeData = 1;
    head->nextNode = second;
    second->nodeData = 2;
    second->nextNode = third;
    third->nodeData = 3;
    third->nextNode = fourth;
    fourth->nodeData = 4;
    fourth->nextNode = tail;
    tail->nodeData = 5;
    tail->nextNode = NULL;

    // Print the contents of the list from the given node
    printLinkedList(head);
    printLinkedList(fourth);

    return 0;
}


// Print out the linked list starting from the given node
void printLinkedList(Node* i) {
    while(i != NULL) {
        cout << i->nodeData << " -> ";
        i = i->nextNode;
    }
    cout << "NULL" << endl;
}