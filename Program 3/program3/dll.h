#ifndef __DLL_H
#define __DLL_H

// CSC 255 Fall 2026 – Dr. Wheat
// Program 3 dll
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

//******************************************************************************

#include "common.h"
#include "cstddef"//dll.h needs to guarantee NULL is defined

//******************************************************************************

class dll;

class node {
    private:
	KEY_VALUE kv;
	node *next, *prev;

    public:
	// Constructs a node holding kv, linked to next and prev (default NULL).
	node(KEY_VALUE kv, node *next = NULL, node *prev = NULL);

	friend class dll;
};

//******************************************************************************

class dll {
    private:
	node *first, *last;
	unsigned int listCount; // to record the number of entries in the list

	int getIndex(int key, node *pn, int index) const;
	void printIt(node *pn, unsigned int index, int limit) const;
	void printItBackwards(node *pn, unsigned int index, int limit) const;
	void clear(node *pn);

    public:
	dll();
	dll(dll *srcList);
	~dll();

	void clear();
	bool insert(KEY_VALUE kv);
	bool add(KEY_VALUE kv);
	bool insertAt(unsigned int index, KEY_VALUE kv);
	bool insertByKey(KEY_VALUE kv);
	bool deleteFirst(KEY_VALUE &kv);
	bool deleteLast(KEY_VALUE &kv);
	bool deleteAt(unsigned int index, KEY_VALUE &kv);
	bool readAt(unsigned int index, KEY_VALUE &kv) const;
	int getIndex(int key) const;
	void printIt(int n) const;
	void printItBackwards(int n) const;
	unsigned int getCount() const;
	unsigned int getCapacity() const;
	dll *cat(dll *list2);
};

#endif
