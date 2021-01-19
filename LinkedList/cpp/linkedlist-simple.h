#ifndef LINKEDLISTSIMPLE_H
#define LINKEDLISTSIMPLE_H


// Includes
#include <cstddef>
#include <iostream>


// Each node has data and a pointer to the next node in the linked list
class Node {
    public:
        int nodeData;
        Node* nextNode;    
};


// Functions
void createNode(int data);
void printLinkedList(Node* i);


#endif