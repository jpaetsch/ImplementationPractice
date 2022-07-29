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
    public:
        BinaryTree();
        ~BinaryTree();

        Node *search(int data);
        void insert(int data);
        void destroy_tree();
    
    private:
        void destroy_tree(Node *leaf);
        void insert(int data, Node *leaf);
        Node *search(int data, Node *leaf);
        Node *root;
};


// Functions


#endif