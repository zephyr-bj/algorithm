#include <iostream>

struct Node {
    int data;
    Node *left, *right, *parent;

    Node(int val) : data(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    // Helper to find the minimum node in a subtree
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) node = node->left;
        return node;
    }

    void deleteNode(Node* z) {
        if (z == nullptr) return;

        // Case 1 & 2: No child or one child
        if (z->left == nullptr) {
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            transplant(z, z->left);
        } 
        // Case 3: Two children
        else {
            Node* y = findMin(z->right); // Successor
            if (y->parent != z) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
        }
        delete z;
    }

    // Replaces one subtree as a child of its parent with another subtree
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v != nullptr) v->parent = u->parent;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    // Returns the smallest element
    Node* begin() {
        return findMin(root);
    }

    void insert(int val) {
        Node* z = new Node(val);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (z->data < x->data) x = x->left;
            else x = x->right;
        }

        z->parent = y;
        if (y == nullptr) root = z;
        else if (z->data < y->data) y->left = z;
        else y->right = z;
    }

    void erase(int val) {
        Node* z = root;
        while (z != nullptr && z->data != val) {
            if (val < z->data) z = z->left;
            else z = z->right;
        }
        deleteNode(z);
    }
};
