#ifndef __MINHEAP_H
#define __MINHEAP_H

//******************************************************************************

#include "common.h"

//******************************************************************************

class minHeap {
    private:
	KEY_VALUE *keyValues;
	unsigned int heapCapacity;
	unsigned int heapCount;

	unsigned int parent(unsigned int index) const;
	unsigned int leftChild(unsigned int index) const;
	unsigned int rightChild(unsigned int index) const;
	void printIt(unsigned int ind, unsigned int count) const;

	void swap(KEY_VALUE *x, KEY_VALUE *y);
	void bubbleUp(unsigned int index);
	void heapify(unsigned int i);

    public:
	minHeap(int n = 100); 

	~minHeap(); 

	bool insert(KEY_VALUE kv);
	bool removeByIndex(unsigned int index, KEY_VALUE &kv);
	bool removeByKey(int key, KEY_VALUE &kv);
	void clear();

	bool integrity() const;
	bool getIndex(int key, unsigned int &returnIndex) const;
	bool readByIndex(unsigned int index, KEY_VALUE &kv) const;
	void printIt() const;
	unsigned int getCount() const;
	unsigned int getCapacity() const;
};

#endif
