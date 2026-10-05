// CSC 255 Fall 2026 – Dr. Wheat
// Program 6 minHeap and PQ
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

#include <iostream>
#include <cmath>

#include "minheap.h"

using namespace std;

//******************************************************************************

//Written by Ojonimi Edime

//allocates an array big enough for n entries and starts the heap empty
minHeap::minHeap(int n) {
    heapCapacity = n;
    heapCount = 0;
    keyValues = new KEY_VALUE[heapCapacity];
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//frees the array the constructor allocated with new[], since keyValues
//is the only dynamically allocated thing this object owns
minHeap::~minHeap() {
    delete[] keyValues;
}

//******************************************************************************

//Written by Ojonimi Edime

//index 0 is the root and has no real parent, so return 0 for it
//otherwise the parent sits at (index - 1) / 2 in the array
unsigned int minHeap::parent(unsigned int index) const {
    unsigned int result;

    if (index == 0) {
        result = 0;
    }
    else {
        result = (index - 1) / 2;
    }

    return result;
}

//******************************************************************************

//Written by Ojonimi Edime

//in a zero indexed array heap, index's left child always sits at 2*index+1
unsigned int minHeap::leftChild(unsigned int index) const {
    unsigned int result;

    result = 2 * index + 1;

    return result;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//index's right child always sits one slot after its left child
unsigned int minHeap::rightChild(unsigned int index) const {
    unsigned int result;

    result = 2 * index + 2;

    return result;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//swaps the two KEY_VALUEs pointed to by x and y using a temporary
void minHeap::swap(KEY_VALUE *x, KEY_VALUE *y) {
    KEY_VALUE temp = *x;
    *x = *y;
    *y = temp;
}

//******************************************************************************

//Written by Ojonimi Edime

//while index isn't the root and is smaller than its parent, swap it
//upward toward the root
void minHeap::bubbleUp(unsigned int index) {
    while (index != 0 && keyValues[index].key < keyValues[parent(index)].key) {
        swap(&keyValues[index], &keyValues[parent(index)]);
        index = parent(index);
    }
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//finds the smallest of index and its two children; if a child is
//smaller, swap it up and keep heapifying downward from there
void minHeap::heapify(unsigned int index) {
    unsigned int smallest = index;
    unsigned int l = leftChild(index);
    unsigned int r = rightChild(index);

    if (l < heapCount && keyValues[l].key < keyValues[smallest].key) {
        smallest = l;
    }
    if (r < heapCount && keyValues[r].key < keyValues[smallest].key) {
        smallest = r;
    }
    if (smallest != index) {
        swap(&keyValues[index], &keyValues[smallest]);
        heapify(smallest);
    }
}

//******************************************************************************

//Written by Ojonimi Edime

//if the heap is full return false, otherwise place kv at the end
//and bubble it up to its correct position
bool minHeap::insert(KEY_VALUE kv) {
    bool result;

    if (heapCount == heapCapacity) {
        result = false;
    }
    else {
        keyValues[heapCount] = kv;
        heapCount++;
        bubbleUp(heapCount - 1);
        result = true;
    }

    return result;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//if index is valid, save its kv, move the last entry into its spot,
//shrink the heap, then bubble that moved entry up or down as needed
bool minHeap::removeByIndex(unsigned int index, KEY_VALUE &kv) {
    bool result;

    if (index >= heapCount) {
        result = false;
    }
    else {
        kv = keyValues[index];
        heapCount--;
        keyValues[index] = keyValues[heapCount];
        bubbleUp(index);
        heapify(index);
        result = true;
    }

    return result;
}

//******************************************************************************

//Written by Ojonimi Edime

//finds the first index holding key, then removes it by index
bool minHeap::removeByKey(int key, KEY_VALUE &kv) {
    bool result;
    unsigned int index;

    if (getIndex(key, index)) {
        result = removeByIndex(index, kv);
    }
    else {
        result = false;
    }

    return result;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//empties the heap without reallocating the array
void minHeap::clear() {
    heapCount = 0;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//verifies the heap's shape and ordering and prints and error and returns 
//false if something is wrong
bool minHeap::integrity() const {
    bool rc = true;

    for (unsigned int index = 0; index < heapCount; index++) {
	unsigned int lc = leftChild(index);
	unsigned int rc2 = rightChild(index);

	if (rc2 != lc + 1) {
	    rc = false;
	    cout << "Integrity check fails for lc and rc" << endl;
	    break;
	}

	if (lc < heapCount) {
	    if (keyValues[index].key > keyValues[lc].key) {
		rc = false;
		cout << "Integrity check fails parent not <= than lc" << endl;
		printIt();
		exit(-1);
		break;
	    }

	    if (rc2 < heapCount) {
		if (keyValues[index].key > keyValues[rc2].key) {
		    rc = false;
		    cout << "Integrity check fails parent not <= than rc" << endl;
		    break;
		}
	    }
	}
    }

    return rc;
}

//******************************************************************************

//Written by Ojonimi Edime

//linear scan for the first index whose key matches
bool minHeap::getIndex(int key, unsigned int &returnIndex) const {
    bool result = false;

    for (unsigned int i = 0; i < heapCount && !result; i++) {
        if (keyValues[i].key == key) {
            returnIndex = i;
            result = true;
        }
    }

    return result;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//if index is valid, copy that entry into kv without removing it
bool minHeap::readByIndex(unsigned int index, KEY_VALUE &kv) const {
    bool result;

    if (index >= heapCount) {
        result = false;
    }
    else {
        kv = keyValues[index];
        result = true;
    }

    return result;
}

//******************************************************************************

//Written by Ojonimi Edime

//this is the recursive helper for printIt that prints one level of the heap
//then recurses to the next level using ind and count
void minHeap::printIt(unsigned int ind, unsigned int count) const {
    if (ind < heapCount) {
	cout << "Level[" << (int)log2(ind + 1) << "]-> ";

	for (unsigned int i = ind; i < (ind+count); i++) {
	    if (i == heapCount) {
		break;
	    } else {
		cout << "(" << keyValues[i].key << "," << keyValues[i].value << ") ";
	    }
	}

	cout << endl;
	ind = leftChild(ind);

	printIt(ind, 2*count);
    }
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//starts the recursive print at the root, printing count and capacity first
void minHeap::printIt() const {
    cout << "The Heap Count is    " << heapCount << endl;
    cout << "The Heap Capacity is " << heapCapacity << endl;

    printIt(0, 1);
}

//******************************************************************************

//Written by Ojonimi Edime

unsigned int minHeap::getCount() const {
    return heapCount;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

unsigned int minHeap::getCapacity() const {
    return heapCapacity;
}
