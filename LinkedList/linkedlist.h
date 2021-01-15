#ifndef LINKEDLIST_H
#define LINKEDLIST_H


// Includes
#include <cstddef>
#include <iostream>


// Each node has data and a pointer to the next node in the linked list
struct Node {
    int nodeData;
    Node *nextNode; 
};

// Each linked list has a head and tail node
class LinkedList {
    private:
        Node *head, *tail;
    public:
        LinkedList();
        void print_entire_list(Node *theHead);
        void append_node(int data);
        void get_list_length();
        Node* get_list_head();
        void insert_node(int data, int index);
};


// Functions


#endif