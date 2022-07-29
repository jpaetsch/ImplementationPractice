// Binary Tree Implementation Practice


#include "tree-binary.h"


using namespace std;


// Constructor for the binary tree class
BinaryTree::BinaryTree() {
    root = NULL;
}


// Deconstructor for the binary tree class
// Recursively delete all nodes
BinaryTree::~BinaryTree() {
    destroy_tree();
}


// Public function that inserts a new node into the tree and takes
// care of initializing the tree root node if it hasn't been yet
void BinaryTree::insert(int data) {
    if(root == NULL) {
        root = new Node;
        root->nodeData = data;
        root->left = NULL;
        root->right = NULL;
    } else {
        insert(data, root);
    }
}

// Recursive private insertion function that moves to the required NULL
// leaf location and inserts a new node there
void BinaryTree::insert(int data, Node *leaf) {
    if(data < leaf->nodeData) {
        // Insert the node at this location
        if(leaf->left == NULL) {
            leaf->left = new Node;
            leaf->left->nodeData = data;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
        } else {
            insert(data, leaf->left);
        }
    } else {
        if(leaf->right == NULL) {
            leaf->right = new Node;
            leaf->right->nodeData = data;
            leaf->right->left = NULL;
            leaf->right->left = NULL;
        } else {
            insert(data, leaf->right);
        }
    }
}


// Public function that searches the entire tree
Node *BinaryTree::search(int data) {
    return search(data, root);
}

// Private function that recursively moves down the tree from the given node - either the value will
// eventually be equal or it will hit a NULL in which case the node does not exist
Node *BinaryTree::search(int data, Node *leaf) {
    if(leaf == NULL) {
        return NULL;
    } else {
        if(data == leaf->nodeData) {
            return leaf;
        } else if(data < leaf->nodeData) {
            return search(data, leaf->left);
        } else {
            return search(data, leaf->right);
        }
    }
}

// Public function that deletes the entire tree - avoid wasted, leaking memory
void BinaryTree::destroy_tree() {
    destroy_tree(root);
}


// Private function that goes to the bottom of each part of the tree from the given node - recursively
// works back up to the node of the tree which the function was called on
void BinaryTree::destroy_tree(Node *leaf) {
    if(leaf != NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}


// Binary tree implementation with search and insert functionality
int main() {
    BinaryTree myTree;
    // ...
}