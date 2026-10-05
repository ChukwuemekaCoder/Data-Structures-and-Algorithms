#ifndef __PQ_H
#define __PQ_H

// CSC 255 Fall 2026 – Dr. Wheat
// Program 6 minHeap and PQ
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

//******************************************************************************

#include "minheap.h"

//******************************************************************************

class PQ {
    private:
	minHeap *theHeap;

    public:
	PQ(unsigned int pqCapacity = 100);
	~PQ();

	bool enq(KEY_VALUE kv);
	bool deq(KEY_VALUE &kv);
	void printIt() const;
	void clear();
	unsigned int getCount() const;
	unsigned int getCapacity() const;
};

#endif
