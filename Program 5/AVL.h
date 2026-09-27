#ifndef __AVL_H
#define __AVL_H

// CSC 255 Fall 2026 – Dr. Wheat
// Program 5 AVL
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

//******************************************************************************

#include "BST.h"

//******************************************************************************

class AVL : public BST {
    protected:
	unsigned int height(node *p) const;
	virtual unsigned int calcHeight(node *p) const;

    private:
	bool doBal;

	void rotateRight(node * &p1);
	void rotateLeft(node * &p1);
	void bal(node * &p);

	bool insert(KEY_VALUE kv, node * &p) override;
	bool remove(int key, node * &p) override;
	virtual void printIt(node *p, unsigned int &index) const;

    public:
	AVL(bool doBal);

	using BST::insert;
	using BST::remove;
	void printIt() const;
};

#endif
