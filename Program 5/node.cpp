// CSC 255 Fall 2026 – Dr. Wheat
// Program 4 BST
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

//******************************************************************************

#include "node.h"

//******************************************************************************

// Builds a new leaf node holding the given key value pair. Both
// pointers start out NULL, and the subtree size starts at 1. 

node::node(KEY_VALUE kv) {
    this->kv = kv;
    left = NULL;
    right = NULL;
    h = 0;
    subTreeSize = 1;
}
