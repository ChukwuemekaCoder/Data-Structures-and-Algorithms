#ifndef __NODE_H
#define __NODE_H

#include <iostream>
#include "common.h"

//******************************************************************************

class node {
    private:
	KEY_VALUE kv;
	unsigned int h, subTreeSize;
	node *left, *right;

    public:
	node(KEY_VALUE kv);

	friend std::ostream& operator << (std::ostream& os, const node &n) {
	    os << "(" << n.kv.key << "," << n.kv.value << ")";
	    return os;
	}

	friend std::ostream& operator << (std::ostream& os, const node *n) {
	    if (n == nullptr) {
		os << "(nullptr)";
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
