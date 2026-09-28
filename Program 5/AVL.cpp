// CSC 255 Fall 2026 - Dr. Wheat
// Program 5
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

//*****************************************************************************

#include <iostream>
#include "AVL.h"

using namespace std;

//*****************************************************************************

//Written by Chukwuemeka Obinna

//We want to return the height stored on p, treating an empty or NULL subtree
//as 0, so that we never need to have a NULL check
unsigned int AVL::height(node *p) const{
    unsigned int result;

    if (p == NULL) {
        result = 0;
    }
    else{
        result = p->h;
    }

    return result;
}

//*****************************************************************************

//Written by Chukwuemeka Obinna

//returns the larger of a and b
int max(int a, int b){
    int result;

    if(a > b){
        result = a;
    }
    else{
        result = b;
    }

    return result;
}
//*****************************************************************************

//Written by Ojonimi Edime

//This calculates what p's height should be based on the new children's 
//current heights
unsigned int AVL::calcHeight(node *p) const {
    unsigned int result;

    result = max((int) height(p->left), (int) height(p->right)) + 1;

    return result;
}

//*****************************************************************************


//Written by Chukwuemeka Obinna

//Essentially, we want to rotate to right by simply adjusting the pointers
//This is done by re-itializing each pointer accordingly
//p1 is left heavy, so we need to make L the root and p1 its right child
//we also need to make L's right child p1s right child
void AVL::rotateRight(node *&p1) {
    node *L = p1->left;

    p1->left = L->right;
    L->right = p1;

    p1->h = calcHeight(p1);
    L->h = calcHeight(L);

    //whatever pointer the caller had pointing at the old p1 will now 
    //point at L
    p1 = L;
}

//*****************************************************************************

//Written by Ojonimi Edime

//Similar to rotate right, we want to move the pointers accordingly 
//p1 is right heavy, so we need to make R the root and p1 its left child
//at the same time we need R's left child to become p's right child
void AVL::rotateLeft(node *&p1) {
    node *R = p1->right;

    p1->right = R->left;
    R->left = p1;

    p1->h = calcHeight(p1);
    R->h = calcHeight(R);

    //whatever pointer the caller had pointing at the old p1 will now
    //point at R 
    p1 = R;

}

//*****************************************************************************

//Written by Chukwuemeka Obinna

//if balancing is off just keep p's height correct. If it's on, check whether 
//one side is more than 1 taller than the other then rotate
void AVL::bal(node * &p) {
    if (p != NULL) {
        if (!doBal) {
            p->h = calcHeight(p);
        }
        else {
            if (height(p->left) > height(p->right) + 1) {
                // left heavy, if the left child leans right, rotate it
                // left first so a single right rotation will fix p
                if (height(p->left->left) < height(p->left->right)) {
                    rotateLeft(p->left);
                }
                rotateRight(p);
            }
            else if (height(p->right) > height(p->left) + 1) {
                // right heavy, if the right child leans left, rotate it
                // right first so a single left rotation will fix p
                if (height(p->right->right) < height(p->right->left)) {
                    rotateRight(p->right);
                }
                rotateLeft(p);
            }
            else {
                // already balanced, only the height may have changed
                p->h = calcHeight(p);
            }
        }
    }
}//*****************************************************************************

//Written by Chukwuemeka Obinna

AVL::AVL(bool doBal) {
    this->doBal = doBal;
}

//*****************************************************************************

//Written by Ojonimi Edime

//p is a reference to whichever pointer we're currently using
bool AVL::insert(KEY_VALUE kv, node * &p) {
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
    bal(p);
    return result;
}

//*****************************************************************************

//Written by Chukwuemeka Obinna

// Handles the two child and single child removal cases
bool AVL::remove(int key, node * &p) {
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

    bal(p);

    return result;
}

