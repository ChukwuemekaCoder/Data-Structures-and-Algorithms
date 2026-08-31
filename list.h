#ifndef __LIST_H
#define __LIST_H

// CSC 255 Fall 2026 – Dr. Wheat
// Program 1 List
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

//******************************************************************************

#include "common.h"

//******************************************************************************

class list {
    private:
	KEY_VALUE *keyValues;
	unsigned int listCapacity;
	unsigned int originalListCapacity;
	unsigned int listCount;
	unsigned int expandSize;
	unsigned int originalExpandSize;
	bool shortenEnabled;

    public:
	//Constructs a list with starting capacity and expand size
	list(unsigned int size = 100, unsigned int expandSize = 5);
	//Builds a new list with the same data (Copy constructor)
	list(list *srcList);

	// destructor
	~list();

	//Increases the list by expandSize
	bool expand();
	//Inserts kv at the front of the list, and shifts entries right
	bool insert(KEY_VALUE kv);
	//Inserts kv at the end of list
	bool add(KEY_VALUE kv);

	//Deletes the first entry in list and returns it via kv
	bool deleteFirst(KEY_VALUE &kv);
	//Deletes last entry in list and returns it via kv
	bool deleteLast(KEY_VALUE &kv);

	//Sets value used by expand() to grow list
	void setExpandSize(unsigned int expandSize);
	//Changed to const as declared in list.cpp
	unsigned int getExpandSize() const;
	//empties list, resets listCount to 0 resets
	void clear();

	//Reads entry at index into kv without removing it
	bool readAt(unsigned int index, KEY_VALUE &kv) const;
	//Returns index of first entry whose key matches or returns NEG_RESULT
	unsigned int getIndex(int key) const;
	//Prints up to n entries (index and key/value pair)
	void printIt(int n) const;
	//Returns number of entries currently stored in the list
	unsigned int getCount() const;
	//Returns current total allocated slots of the lsit
	unsigned int getCapacity() const;
	// part B functions
	bool insertByKey(KEY_VALUE kv);
	bool insertAt(unsigned int index, KEY_VALUE kv);
	bool deleteAt(unsigned int index, KEY_VALUE &kv);
	void printItBackwards(int n) const;
	list *cat(list *list2);
	void shortenList();
	void setShortenEnabled(bool shorten);
	//changed to const as declared in list.cpp
	bool getShortenEnabled() const;

	void bubbleSort();
	void selectionSort();
	void insertionSort();
	bool isSorted() const;
};

#endif
