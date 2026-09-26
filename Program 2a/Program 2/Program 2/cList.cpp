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

// Written by Ojonimi Edime

cList::cList(cList *srcList) {

    //copy every member variable from the source list
    listCapacity = srcList->listCapacity;
    originalListCapacity = srcList->listCapacity;
    listCount = srcList->listCount;
    expandSize = srcList->expandSize;
    originalExpandSize = srcList->expandSize;
    shortenEnabled = srcList->shortenEnabled;
    first = srcList->first;
    last = srcList->last;

    //allocate our array the same size as the source list array
    if (listCapacity > 0){
        keyValues = new KEY_VALUE[listCapacity];
    
        for (unsigned int i = 0; i < listCapacity; i++){
            //copy physical array directly so that first and last line up 
            //correctly in the new copy
            keyValues[i] = srcList->keyValues[i];
        }
    }
    else{
        keyValues = NULL;
    }
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
        setLast();
        #ifdef DO_PART_B
        shortenList();//call shortenList
        #endif
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
	listCount--;//decrement listCount because a number has been deleted
        setLast();//automatically self corrects the position of last
        #ifdef DO_PART_B
        shortenList();
        #endif
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
    if (n < 0 || (unsigned int)n > listCount){
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

//Written by Ojonimi Edime

bool cList::insertByKey(KEY_VALUE kv) {
    
    unsigned int index = 0;
    bool foundSpot = false;

    //goes down the list until we get to the first key bigger than kv's key
    //this keeps the list sorted in ascending order by key
    while (index < listCount && !foundSpot){
        if (keyValues[virtualToPhysical(index)].key > kv.key){
            foundSpot = true;
        }
        else{
            index++;
        }
    }
    
    //insertAt takes care of expanding and shifting everything for us
    return insertAt(index, kv);
}

//******************************************************************************

//Written by Ojonimi Edime

bool cList::insertAt(unsigned int index, KEY_VALUE kv) {
    
    bool result;

    if (index > listCount){
        //you cannot insert at a position greater than listCount
        result = false;
    }
    else{
        bool isSpace;

    if (listCount == listCapacity){
        isSpace = expand();
    }
    else{
        isSpace = true; 
    }

    if (isSpace){
        //shift everything from index up by one slot 
        //we go from back to front so we dont overwrite values we still need
        //to move
        for (unsigned int i = listCount; i > index; i--){
            keyValues[virtualToPhysical(i)] = keyValues[virtualToPhysical(i-1)];
        }

        keyValues[virtualToPhysical(index)] = kv;
        listCount++;
        setLast();
    }
    
    result = isSpace;

    }

    return result;
    
}

//******************************************************************************

//Written by Chukwuemeka Obinna

bool cList::deleteAt(unsigned int index, KEY_VALUE &kv) {
    bool result;

    if (index >= listCount){
        result = false;
    }
    else{
        kv = keyValues[virtualToPhysical(index)];

    //shifts everything after index down by one slot to close the gap
    for (unsigned int i = index; i < listCount - 1; i++){
        keyValues[virtualToPhysical(i)] = keyValues[virtualToPhysical(i + 1)];
    }

    listCount--;//decrement the list count
    setLast();

    if (shortenEnabled){
        shortenList();
    }

    result = true;
    }

    return result;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

void cList::printItBackwards(int n) const {

    unsigned int limit;

    //n is checked against 0 first so the unsigned cast below is always safe
    if (n < 0 || (unsigned int) n > listCount){
        limit = listCount;
    }
    else{
        limit = n;
    }

    cout << "Printing " << limit << " of " << listCount
     << " entries backwards with capacity of " << listCapacity << endl;
 
    //start at the highest virtual index and count down to print in reverse
    for (unsigned int i = 0; i < limit; i++){
        unsigned int index = listCount - 1 - i;
    cout << "At index " << index << " there is ("
         << keyValues[virtualToPhysical(index)].key
         << "," << keyValues[virtualToPhysical(index)].value << ")" << endl;
    }
}

//******************************************************************************

//Written by Ojonimi Edime

cList *cList::cat(cList *list2) const{

    unsigned int list2Count;

    if (list2 != NULL) {
        list2Count = list2->listCount;
    }
    else{
        list2Count = 0;
    }

    //make the new list big enough to hold both lists combined
    cList *result = new cList(listCount + list2Count, expandSize);

    for (unsigned int i = 0; i < listCount; i++){
        //adds the entries of the first list
        result->add(keyValues[virtualToPhysical(i)]);
    }
    if (list2 != NULL){
        for (unsigned int i = 0; i < list2->listCount; i++ ){
            //add the entries of the second list
            result->add(list2->keyValues[list2->virtualToPhysical(i)]);
        }
    }
    return result;//returns the new combined list

}

//******************************************************************************

//Written by Chukwuemeka Obinna
void cList::shortenList() {

    //keep shrinking the capacity by expandSize as long as we have room
    //for one full expandSize
    if (shortenEnabled){
        KEY_VALUE *newList = new KEY_VALUE[listCapacity - 1];

    for (unsigned int i = 0; i < listCount; i++){
        //convert virtual to physical while copying
        newList[i] = keyValues[virtualToPhysical(i)];
    }

    delete[] keyValues;//free up memory
    keyValues = newList;
    listCapacity = listCapacity - 1;//decrement the listCapacity by 1
    //first has to be reset back to 0, same as in expand()
    first = 0;
    setLast();
    }
}

//******************************************************************************

//Written by Ojonimi Edime

void cList::setShortenEnabled(bool shorten) {

    shortenEnabled = shorten; //turn automatic shrinking on or off
}

//******************************************************************************

//Written by Chukwuemeka Obinna

bool cList::getShortenEnabled() const{

    return shortenEnabled;
}

#endif
