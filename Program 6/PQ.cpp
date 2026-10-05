// CSC 255 Fall 2026 – Dr. Wheat
// Program 6 minHeap and PQ
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

//******************************************************************************

#include "PQ.h"

//******************************************************************************

//Written by Ojonimi Edime

//a PQ is just a wrapper around a minHeap, allocated with the given capacity
PQ::PQ(unsigned int pqCapacity) {
    theHeap = new minHeap(pqCapacity);
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//frees the heap this PQ owns
PQ::~PQ() {
    delete theHeap;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//enqueuing a kv is just inserting it into the underlying heap
bool PQ::enq(KEY_VALUE kv) {
    return theHeap->insert(kv);
}

//******************************************************************************

//Written by Ojonimi Edime

//the least key is always at index 0 in a min-heap, so dequeue removes
//whatever is at index 0
bool PQ::deq(KEY_VALUE &kv) {
    return theHeap->removeByIndex(0, kv);
}

//******************************************************************************

//Written by Ojonimi Edime

//forwards to the heap's own printIt() 
void PQ::printIt() const {
    theHeap->printIt();
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//resets the heap's count to empty it
void PQ::clear() {
    theHeap->clear();
}

//******************************************************************************

//Written by Ojonimi Edime

//forwards to the heap's own getCount
unsigned int PQ::getCount() const {
    return theHeap->getCount();
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//forwards to the heap's own getCapacity
unsigned int PQ::getCapacity() const {
    return theHeap->getCapacity();
}
