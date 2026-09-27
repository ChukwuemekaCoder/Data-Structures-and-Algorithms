//CSC 255 Fall 2026 - Dr. Wheat
//Program 5
//Team 9: Chukwuemeka Obinna and Ojonimi Edime

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

//Written by Ojonimi Edime

//This calculates what p's height should be based on the new children's 
//current heights
unsigned int AVL::calcHeight(node *p) const {
    unsigned int leftHeight = height(p->left);
    unsigned int rightHeight = height(p->right);
    unsigned int result;

    if (leftHeight > rightHeight) {
        result = leftHeight + 1;
    }
    else {
        result = rightHeight + 1;
    }

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
