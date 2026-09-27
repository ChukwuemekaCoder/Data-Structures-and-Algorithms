// CSC 255 Fall 2026 – Dr. Wheat
// Program 4 BST
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

//******************************************************************************

#include <iostream>
#include "BST.h"

using namespace std;

//******************************************************************************

// Written by Ojonimi Edime

//a new tree starts empty with no root and no entries
BST::BST() {
    root = NULL;
    nCount = 0;
}

//******************************************************************************

// Written by Chukwuemeka Obinna

//we use clear because it already knows how to free every node
BST::~BST() {
    clear();
}

//******************************************************************************

// Written by Chukwuemeka Obinna

//starts the recursive insert at the root
bool BST::insert(KEY_VALUE kv) {
    return insert(kv, root);
}

//******************************************************************************

// Written by Ojonimi Edime

//p is a reference to whichever pointer we're currently using
bool BST::insert(KEY_VALUE kv, node * &p) {
    bool result;

    if (p == NULL) {
        p = new node(kv);//found an empty spot for where the new node begins
        nCount++;
        result = true;
    }
    else if (kv.key < p->kv.key) {//belongs somewhere in the left subtree
        result = insert(kv, p->left);
    }
    else if (kv.key > p->kv.key) {//belongs somewhere in the right subtree
        result = insert(kv, p->right);
    }
    else {
        result = false;
    }

    return result;
}

//******************************************************************************

// Written by Ojonimi Edime

//starts the recursive remove at the root
bool BST::remove(int key) {
    return remove(key, root);
}

//******************************************************************************

// Written by Chukwuemeka Obinna

// Handles the two child and single child removal cases
bool BST::remove(int key, node * &p) {
    bool result;

    if (p == NULL) {
        //no key was found so returns false
        result = false;
    }
    else if (key < p->kv.key) {
        result = remove(key, p->left);
    }
    else if (key > p->kv.key) {
        result = remove(key, p->right);
    }
    else {
        //this is the node to remove
        if (p->left != NULL && p->right != NULL) {
        //this has two children
        //we have to take the smallest value from the right of the children 
        //then remove the borrowed node
            KEY_VALUE successor = findMin(p->right);
            p->kv = successor;
            result = remove(successor.key, p->right);
        }
        else {
            //this has zero or one child
            //splice p out and replace it with whichever child it has or NULL
            //if it has a leaf
            node *temp = p;
            p = (p->left != NULL) ? p->left : p->right;
            delete temp;
            nCount--;
            result = true;
        }
    }

    return result;
}

//******************************************************************************

// Written by Ojonimi Edime

//the minimum key is always the leftmost node but if there's no left child
//then the node is the minimum
KEY_VALUE BST::findMin(node *p) const {
    KEY_VALUE result;

    if (p->left == NULL) {
        result = p->kv;
    }
    else {
        result = findMin(p->left);
    }

    return result;    
}

//******************************************************************************

// Written by Chukwuemeka Obinna

//moves from left to the current node and then right visits every key in 
//ascending order
void BST::printIt(node *p) const {
    if (p != NULL) {
        printIt(p->left);
        cout << p << endl;
        printIt(p->right);
    }
}

//******************************************************************************

// Written by Chukwuemeka Obinna

//starts the recursive print at the root
void BST::printIt() const {
    printIt(root);
}

//******************************************************************************

// Written by Chukwuemeka Obinna

//traverses the tree from left to right to get the node value
bool BST::getValue(int key, int &value, node *p) const {
    bool result;

    if (p == NULL) {
        result = false;
    }
    else if (key < p->kv.key) {
        result = getValue(key, value, p->left);
    }
    else if (key > p->kv.key) {
        result = getValue(key, value, p->right);
    }
    else {
        value = p->kv.value;
        result = true;
    }

    return result;
}

//******************************************************************************

// Written by Ojonimi Edime

//starts the recursive search at the root
bool BST::getValue(int key, int &value) const {
    return getValue(key, value, root);
}

//******************************************************************************

// Written by Ojonimi Edime

unsigned int BST::count() const {
    return nCount;
}

//******************************************************************************

// Written by Ojonimi Edime

//deletes left then right then the current node so we never free a node before
//we're done using the child pointers to recurse
void BST::clear(node *p) {
    if (p != NULL) {
        clear(p->left);
        clear(p->right);
        delete p;
    }
}

//******************************************************************************

// Written by Chukwuemeka Obinna

//free every node then reset the tree to empty
void BST::clear() {
    clear(root);
    root = NULL;
    nCount = 0;
}
