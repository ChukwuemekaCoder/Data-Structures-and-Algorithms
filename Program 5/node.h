#ifndef __NODE_H
#define __NODE_H

#include <iostream>
#include "common.h"

//******************************************************************************

// A node holds a single key value pair and pointers to its left and right
// children. Pointing to a NULL child meand there is no child on that side.

class node {
    private:
	KEY_VALUE kv;
	unsigned int h, subTreeSize;    // height and subtree size
	node *left, *right;             // left and right children pointers

    public:
        // Creates a leaf node with no children, holding kv 
	node(KEY_VALUE kv);

        // Prints a node object in the form key,value   
	friend std::ostream& operator << (std::ostream& os, const node &n) {
	    os << "(" << n.kv.key << "," << n.kv.value << ")";
	    return os;
	}
        // Prints a node pointer in the form key, value or NULL if the 
        // pointer is NULL, so printing an empty position is safe. 
	friend std::ostream& operator << (std::ostream& os, const node *n) {
	    if (n == NULL) {
		os << "(NULL)";
	    } else {
		os << "(" << n->kv.key << "," << n->kv.value << ")";
	    }
	    return os;
	}


    friend class BST;
    friend class AVL;
    friend class DOS;
};

#endif
