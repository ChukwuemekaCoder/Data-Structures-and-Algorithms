#ifndef __CLIST_H
#define __CLIST_H

// CSC 255 Fall 2026 – Dr. Wheat
// Program 1 List
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

//******************************************************************************

#include "common.h"

#define cListInc(x) (x = (x + 1) % listCapacity)
#define cListDec(x) (x = (x + listCapacity - 1) % listCapacity)

//******************************************************************************

class cList {
    private:
	KEY_VALUE *keyValues;
	unsigned int listCapacity;
	unsigned int originalListCapacity;
	unsigned int listCount;
	unsigned int expandSize;
	unsigned int originalExpandSize;
	bool shortenEnabled;
	unsigned int first;//tracks the first entry of the list
	unsigned int last;//tracks the last entry of the list
			
        unsigned int virtualToPhysical(unsigned int virtualIndex) const;
	unsigned int physicalToVirtual(unsigned int physicalIndex) const;
        void setLast();

    public:
	//Constructs a clist with starting capacity and expand size
	cList(unsigned int size = 100, unsigned int expandSize = 5);
	//Builds a new clist with the same data (Copy constructor)
	cList(cList *srcList);

	// destructor
	~cList();

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
	//Changed to const as declared in cList.cpp
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
	//Insert kv at the first position whose keys greater than kv's key
	bool insertByKey(KEY_VALUE kv);
	//Inserts kv at the given index, shifiting later entries right
	bool insertAt(unsigned int index, KEY_VALUE kv);
	//Deletes the entry at index, returning it with kv
	bool deleteAt(unsigned int index, KEY_VALUE &kv);
	//This prints all the entries in reverse
	void printItBackwards(int n) const;
	//Creates and returns a new list containing this list's entries
	//followed by list 2's entries
	cList *cat(cList *list2) const;
	//Whenever shortenEnabled is true, listCapacity by one entry
	void shortenList();
	//this enables or disables automatic shrinking of the list on delete
	void setShortenEnabled(bool shorten);
	//changed to const as declared in cList.cpp
	bool getShortenEnabled() const; 

	void bubbleSort();
	void selectionSort();
	void insertionSort();
	bool isSorted() const;
};

#endif
