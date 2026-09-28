#ifndef __BST_H
#define __BST_H

// CSC 255 Fall 2026 – Dr. Wheat
// Program 4 BST
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

//******************************************************************************

#include "node.h"

//******************************************************************************

class BST {
    protected:
	unsigned int nCount;    // NO. of entries currently in tree
	node *root;             // pointer to to root node (NULL if empty)
        
        // Recursive insert rooted at p. which is a reference to the child 
        // pointer so a new node can be linked directly.
	virtual bool insert(KEY_VALUE kv, node * &p);

        //Recursive remove from from the subtree at p. which is a reference
        // so the child pointer can be rewired when a node is spliced out 
	virtual bool remove(int key, node * &p);
	//Moved from private to protected for Program 5 so AVL::remove
	//can use it when removing a node with two children
	KEY_VALUE findMin(node *p) const; 

    private:
        // Recursive in order print helper for sub tree rooted at p
	void printIt(node *p) const;
        // Recursive search helper for sub tree rooted at p
	bool getValue(int key, int &value, node *p) const;
        // Recursive helper that deletes every node in sub tree rooted at p
	void clear(node *p);

    public:
	BST();    // initializes an empty tree
	~BST();   // Deletes every node in the tree

        // Inserts kv into tree, returns false if key already exists
	bool insert(KEY_VALUE kv);
        // Removes the node with the matching key, returns false if no
        // node has the key
	bool remove(int key);
        // Sets value to value stored under key, returns false if key is
        // not found, leaving value unchanged
	bool getValue(int key, int &value) const;
        // Prints every key-value in ascending order by key, one per line
	void printIt() const;
        // Returns number of nodes currently in the tree
	unsigned int count() const;
        // Empties tree by removing every node
	void clear();
};

#endif
