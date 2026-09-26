//CSC 255 Fall 2026 - Dr. Wheat
//Program 2 cList
//Team 9: Chukwuemeka Obinna and Ojonimi Edime

#include <iostream>
#include "cList.h"

using namespace std;

//******************************************************************************

//Written by Chukwuemeka Obinna

unsigned int cList::virtualToPhysical(unsigned int virtualIndex) const {
    //we want to convert the values the user sees to its physical index   
    return (first + virtualIndex) % listCapacity;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

unsigned int cList::physicalToVirtual(unsigned int physicalIndex) const {
    //we want to convert the values in memory to the index the user sees
    return (physicalIndex + listCapacity - first) % listCapacity;
}

//******************************************************************************

//Written by Chukwuemeka Obinna
//setLast was originally given, but provided additional comment for clarity

void cList::setLast() {
    //Recomputes last from first and listCount so it stays correct after
    last = (listCount ? ((first + listCount - 1) % listCapacity) : first);
}

//******************************************************************************

//Written by CHukwuemeka Obina

cList::cList(unsigned int listCapacity, unsigned int expandSize) {
    //the parameters and member variables of the public have the same name
    //the compiler needs to point to the member variable or the parameter
    //this-> tells the compiler to point to the member variable
    this->listCapacity = listCapacity;
    this->originalListCapacity = listCapacity;
    this->expandSize = expandSize;
    this->originalExpandSize = expandSize;
    listCount = 0;
    //decides if the list capacity is allowed to shrink when items are deleted
    shortenEnabled = false;
    first = 0;
    //because we initialized listCount to 0, we do not need to manually figure
    //out where last should start. last is automatically equal to first
    setLast();

    if (listCapacity > 0){
	//allocate key values to a new list
        keyValues = new KEY_VALUE[listCapacity];
    }
    else{
        keyValues = NULL;  
    }
}

//******************************************************************************

#ifdef DO_PART_B
cList::cList(cList *srcList) {
}
#endif

//******************************************************************************

cList::~cList() {
    if (keyValues) {
	delete [] keyValues;
    }
    keyValues = NULL;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

bool cList::expand() {

    bool result = false;//assume the operation fails unless stated otherwise
    
    if (expandSize > 0) {
        //Create a pointer with the memory address of a brand new list
	KEY_VALUE *newList = new KEY_VALUE[listCapacity + expandSize];

	for (unsigned int i = 0; i < listCount; i++){
	//Copy entries from the old array to the new array at the same index
	//However, we need to convert from virtual to physical while iterating
	newList[i] = keyValues[virtualToPhysical(i)];
	}

        delete[] keyValues;//Free up memory by deleting the old array
	keyValues = newList;
	listCapacity = listCapacity + expandSize;//expanded capacity
	//we have to reset first and last afer rebuilding the new array
	//without it first will point to the old index of the deleted array
	first = 0;
	setLast();
	result = true;
    }

    return result;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

bool cList::insert(KEY_VALUE kv) {

    bool isSpace;//declare a boolean variable to determine list capacity
    
    if (listCount == listCapacity){
        isSpace = expand();//We expand because there's no space in the list
    }
    else{
        isSpace = true;//We have space, so no need to expand the list
    }

    if (isSpace){//we move the physical position of first down a number
        cListDec(first);//we avoid re-indexing the whole list 
        keyValues[first] = kv;//insert kv as the first number in the list
        listCount++;//increment the listCount because kv has been adde
	setLast();
    }

    return isSpace;//return true or false
}

//******************************************************************************

//Written by Chukwuemeka Obinna

bool cList::add(KEY_VALUE kv) {
    
    bool isSpace;

    if (listCount == listCapacity){
        isSpace = expand();//expand the list if it's full
    }
    else{
        isSpace = true;//listCount < listCapacity so no expand needed
    }

    if (isSpace){//calculates the next available postion       
	unsigned int nextPosition = virtualToPhysical(listCount);
	keyValues[nextPosition] = kv;
	listCount++;//increment the listCount because kv is added to the list
	setLast();
    }

    return isSpace;
}

//******************************************************************************

//Written by Ojonimi Edime

bool cList::deleteFirst(KEY_VALUE &kv) {

    bool result;

    if (listCount == 0){//you cannot delete the first number of an empty list
        result = false;// return false if the list is empty
    }
    else{
        //this is the only way the reference parameter knows what to return
        kv = keyValues[first];//take whatever is at first and copy it to kv
	//we avoid traversing through the whole array
	//deleteFirst occurs in constant time 
	cListInc(first);//increment the physical position of first
	listCount--;//decrement the listCount
	result = true;
    }
    
    return result;//first number was successfully deleted
}

//******************************************************************************

//Written by Chukwuemeka Obinna

bool cList::deleteLast(KEY_VALUE &kv) {

    bool result;

    if (listCount == 0){
        result = false;//you cannot delete the last number of an empty list
    }
    else{
        //take whatever is at last and copy it to kv
        kv = keyValues[last];
	cListDec(last);//decrement the physical postion of last
	listCount--;//decrement listCount because a number has been deleted
	result = true;
    }

    return result;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

void cList::setExpandSize(unsigned int expandSize) {

    this->expandSize = expandSize;//member variable is equal to parameter
}

//******************************************************************************

//Written by Ojonimi Edime

unsigned int cList::getExpandSize() const {

    return expandSize; //returns the expand size
}

//******************************************************************************

//Written by Ojonimi Edime

void cList::clear() {

    listCount = 0;//empties the list
    listCapacity = originalListCapacity;//set the list capacity to its original
    expandSize = originalExpandSize;//set expandSize to its original
    delete [] keyValues;//delete the current list and free up old memory
    //first and last need to be reset to their original state
    first = 0;
    setLast();
    
    if (listCapacity == 0){
        keyValues = NULL;//clearing an empty array sets our array to NULL
    }
    else{//allocate a new array and assign it directly to keyValues
        keyValues = new KEY_VALUE[listCapacity];
    }
}

//******************************************************************************

//Written by Chukwuemeka Obinna

bool cList::readAt(unsigned int index, KEY_VALUE &kv) const {

    bool result;

    if (index < listCount){//if it's a valid index
	//in order to properly read the data
        //we need to convert what the user sees to its physical slot
        kv = keyValues[virtualToPhysical(index)];//reads at specific index
	result = true;
    }
    else{
        result = false;//invalid index so the function cannot read it
    }

    return result;
}

//******************************************************************************

//Written by Ojonimi Edime

unsigned int cList::getIndex(int key) const {

    unsigned int result = NEG_RESULT;//Assumes index is not found
    bool foundIndex = false;//determines if we have found the right index
			  
    //loop through the list while the index is still in range and not found
    for (unsigned int i = 0; i < listCount && !foundIndex; i++){
        if (keyValues[virtualToPhysical(i)].key == key){
            //if the physical .key struct is equal to key
	    //we have to compare the same type rather than the KEY_VALUE struct
	    result = i;//set result to the index
	    foundIndex = true;//the index has been successfully found
	}
    }

    return result;
}

//******************************************************************************

//Written by Ojonimi Edime

void cList::printIt(int n) const {

    unsigned int limit;
    //Checks if number is greater than listCount
    if (n < 0 || n > listCount){
	//if number is within parameters of not too big and not negative
        limit = listCount;
    }
    else{
        limit = n;
    }

    cout << "Printing " << limit << " of " << listCount
	 << " entries with capacity of " << listCapacity << endl;

    //Keeps checking array until it reaches limit number
    for (unsigned int i = 0; i < limit; i++){
	//when printing, we have to return the virtual index, not physical
        cout << "At index " << i << " there is (" 
	     << keyValues[virtualToPhysical(i)].key
	     << "," << keyValues[virtualToPhysical(i)].value << ")" << endl;
    }
}

//******************************************************************************

//Written by Chukwuemeka Obinna

unsigned int cList::getCount() const {

    return listCount; //get the number of entries in the list
}

//******************************************************************************

//Written by Ojonimi Edime

unsigned int cList::getCapacity() const {
    
    return listCapacity; //get the capacity of the list
}

//******************************************************************************
//  Part B code
//******************************************************************************

#ifdef DO_PART_B

bool cList::insertByKey(KEY_VALUE kv) {
}

//******************************************************************************

bool cList::insertAt(unsigned int index, KEY_VALUE kv) {
}

//******************************************************************************

bool cList::deleteAt(unsigned int index, KEY_VALUE &kv) {
}

//******************************************************************************

void cList::printItBackwards(int n) const {
}

//******************************************************************************

cList *cList::cat(cList *list2) {
}

//******************************************************************************

void cList::shortenList() {
}

//******************************************************************************

void cList::setShortenEnabled(bool shorten) {
}

//******************************************************************************

bool cList::getShortenEnabled() {
}

#endif
