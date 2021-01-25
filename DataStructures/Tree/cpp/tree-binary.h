#ifndef TREEBINARY_H
#define TREEBINARY_H


// Includes
#include <cstddef>
#include <iostream>


struct Node {
    int nodeData;
    Node *left;
    Node *right;
};


class BinaryTree {
    private:
        Node *root;
    public:
        BinaryTree();
        ~BinaryTree();

        Node *search_for(int data);
        void insert_node(int data);
};


// Functions


#endif