// CSC 255 Fall 2026 – Dr. Wheat
// Program 1 List
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

//******************************************************************************

#include <iostream>
#include "list.h"

using namespace std;

//******************************************************************************

// Written by Chukwuemeka Obinna

list::list(unsigned int listCapacity, unsigned int expandSize) {
   
    
    //the parameters and member variables of the public have the same name
    //the compiler needs to either point to the memner varible or the parameter
    //this-> tells the compiler to point to the member variable
    this->listCapacity = listCapacity; 
    this->originalListCapacity = listCapacity;
    this->expandSize = expandSize;
    this->originalExpandSize = expandSize;
    listCount = 0; 
    //decides if the list capacity is allowed to shrink when items are deleted
    shortenEnabled = false;

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

// Written by Chukwuemeka Obinna

list::list(list *srcList) {
    
    //We want to copy every single member variable directly
    this-> listCapacity = srcList->listCapacity;
    this-> originalListCapacity = srcList->listCapacity;
    this-> listCount = srcList->listCount;
    this-> expandSize = srcList->expandSize;
    this-> originalExpandSize = srcList->originalExpandSize;
    this-> shortenEnabled = srcList->shortenEnabled;

    if (listCapacity > 0){
        keyValues = new KEY_VALUE[listCapacity];//allocate a separate array

	for (unsigned int i = 0; i < listCount; i++){
	    keyValues[i] = srcList->keyValues[i];//copy each real entry
	}
    }
    else{
        keyValues = NULL;
    }
}
#endif

//******************************************************************************

// Written by Chukwuemeka Obinna

list::~list() {

    delete [] keyValues;//prevents memory leaks
}

//******************************************************************************

// Written by CHukwuemeka Obinna

bool list::expand() {    
    
    bool result = false; //assume the operation fails unless stated otherwise
    
    if (expandSize > 0){

        //Create a pointer with the memory address of a brand new list
	KEY_VALUE *newList = new KEY_VALUE[listCapacity + expandSize];

	//Copy entries from the old array into the new array at the same index
        for (unsigned int i = 0; i < listCount; i++){
             newList[i] = keyValues[i];
        }

        delete[] keyValues; // Free up memory by deleting the old array
        keyValues = newList;
        listCapacity = listCapacity + expandSize; //expanded capacity
        result = true; 
    }

    return result;
}

//******************************************************************************

// Written by CHukwuemeka Obinna

bool list::insert(KEY_VALUE kv) {

    bool isSpace;//declare a boolean variable to determine list capacity

    if (listCount == listCapacity){
        isSpace = expand();//We expand becuase there's no space in the list
    }
    else{
        isSpace = true;//We have space, so no need to expand the list
    }

    if (isSpace){
	//Iterate from the last number and reindex accordingly
        for(unsigned int i = listCount; i > 0; i--){
	    keyValues[i] = keyValues[i - 1];//Each number moves one index 
	}
	keyValues[0] = kv;//insert kv as the first number in the list
	listCount++;//increment the listCount because kv has been added
    }

    return isSpace;//returns true or false
}

//******************************************************************************

// Written by Chukwuemeka Obinna

bool list::add(KEY_VALUE kv) {
    
    bool isSpace;

    if (listCount == listCapacity){
        isSpace = expand();//expand the list if it's full
    } 
    else{
        isSpace = true;//Currently listCount < listCapacity so no expand needed  
    }
    
    if (isSpace){//if there's space, add kv to the end of the list
        keyValues[listCount] = kv;
        listCount++;//increment the listCount becuase kv is added to the list
    }

    return isSpace;//returns true or false
}

//******************************************************************************

// Written by Ojonimi Eidme

bool list::deleteFirst(KEY_VALUE &kv) {
    
    bool result;

    if (listCount == 0){//you cannot delete the first number of an empty list
        result = false;// return false if the list is empty
    }
    else{
	//this is the only way the reference parameter knows what to return
        kv = keyValues[0];//take whatever is at index 0 and copy it into kv
	for (unsigned int i = 0; i < listCount - 1; i++){
	    //move an element down an index in the list
	    keyValues[i] = keyValues[i + 1];
	}
	listCount--;//decrement listCount because a number was deleted
        #ifdef DO_PART_B 
        shortenList();//call shortenList if an entry is deleted
        #endif
	result = true;//first number was successfully deleted
    }

    return result;//return either true or false
}

//******************************************************************************

// Written by Chukwuemeka Obinna

bool list::deleteLast(KEY_VALUE &kv) {

    bool result;

    if (listCount == 0){
        result = false;// you cannot delete a number from an empty list
    }
    else{
	//take whatever is at the last index and copy it to kv
        kv = keyValues[listCount - 1];
	listCount--;//decrement the list because a number has been delete
        #ifdef DO_PART_B
	shortenList();//call shortenList if an entry is deleted
	#endif
	result = true;//last number was succesfully deleted
    }

    return result;//returns either true or false
}
//******************************************************************************

// Written by Chukwuemeka Obinna

void list::setExpandSize(unsigned int expandSize) {
	
    this->expandSize = expandSize;//member variable is equal to parameter
}

//******************************************************************************

// Written by Ojonimi Edime

unsigned int list::getExpandSize() const {

    return expandSize; //returns the expand size
}

//******************************************************************************

// Written by Ojonimi Edime

void list::clear() {
	
    listCount = 0;//empties the list 
    listCapacity = originalListCapacity;//set the list capacity to its original
    expandSize = originalExpandSize;//set expandSize to its original
    delete [] keyValues;//delete the current list and free up old memory

    if (listCapacity == 0){
        keyValues = NULL;//clearing an empty array sets our array to NULL
    }
    else{
	//allocate a new array and assign it directly to keyValues
        keyValues = new KEY_VALUE[listCapacity];    
    }
}

//******************************************************************************

// Written by CHukwuemeka Obinna

bool list::readAt(unsigned int index, KEY_VALUE &kv) const {
    
    bool result;

    if (index < listCount){//if it's a valid index
        kv = keyValues[index];//reads at that specific index
	result = true;
    }
    else{
        result = false;//invalid index so the function cannot read it
    }

    return result;
}

//******************************************************************************

// Written by Ojonimi Edime

unsigned int list::getIndex(int key) const {

    unsigned int result = NEG_RESULT;//assumes index is not found
    bool foundIndex = false;//determined if we have found the right index for key
    
    //loop through the list while the index is still in range and not found
    for (unsigned int i = 0; i < listCount && !foundIndex; i++){
        if (keyValues[i].key == key){
	    //if .key in in the struct is equal to key
	    //we have to compare the same type rather than the KEY_VALUE struct
	    result = i;//set result to the index
	    foundIndex = true;//the index has been successfully found
	}
    }

    return result;
}

//******************************************************************************

// Written by Ojonimi Edime

void list::printIt(int n) const {

    unsigned int limit;
    //Checks if number is greater than listCount
    if (n < 0 || n > listCount){
        limit = listCount;	
    //If number is within parameters of not too big and not negative
    }
    else{
        limit = n;
    }

    cout << "Printing " << limit << " of " << listCount
	 << " entries with capacity of " << listCapacity << endl;

    //Keeps checking array until it reaches limit number
    for(unsigned int i = 0; i < limit; i++){
    	cout << "At index " << i << " there is (" << keyValues[i].key 
	     << "," << keyValues[i].value << ")" << endl; 
    }
}

//******************************************************************************

// Written by Chukwuemeka Obinna

unsigned int list::getCount() const {
    
    return listCount; //get the number of entries in the list
}

//******************************************************************************

// Written by Ojonimi Edime

unsigned int list::getCapacity() const {

    return listCapacity; //get the capacity of the list
}

//******************************************************************************

#ifdef DO_PART_B

// Written by Chukwuemeka Obinna
bool list::insertAt(unsigned int index, KEY_VALUE kv) {

    bool result;

    if (index > listCount){//we want to ensure we can insert at a valid entry
        result = false;
    }

    else{
        if (listCount == listCapacity) {
	    result = expand();//calls expand if there is no space in the list
	}
        else{
	    result = true;
	}
    }

    if (result){//iterate from the end of the list to avoid wrong re-indexing
        for (unsigned int i = listCount; i > index; i--){
	    //shift all the entries at beyond the index down by one
	    keyValues[i] = keyValues[i - 1];	
	}

    keyValues[index] = kv;//insert kv at the specified index
    listCount++;//increment the list
    }

    return result;
}

//******************************************************************************

// Written by Chukwuemeka Obinna

bool list::insertByKey(KEY_VALUE kv) {

    //result defaults to listCount which inserts at the end
    //there is the edge case where no key is greater than the index
    //this is why we have to initialize result to the end of the list
    unsigned int result = listCount;
    bool found = false;//determines if we have found the right key
    
    for (unsigned int i = 0; i < listCount && !found; i++){
	//loop through till we find an index value greater than the key
        if (keyValues[i].key > kv.key){
	    result = i; //the new position becomes i
	    found = true;
	}
    }
    //the return statement calls insertAt() which was previously defined
    return insertAt(result, kv);
}

//******************************************************************************

// Written by Ojonimi Edime

// Deletes and returns entry at index and shifting later entries down by one
// and then calls shortenList. It will fail without changing anything if the 
// index is out of range. Returns true once removal is complete.
bool list::deleteAt(unsigned int index, KEY_VALUE &kv) {
	bool success = false;

	if (index < listCount) {
		kv = keyValues[index];

		// Doing this to reindex the array
		for (unsigned int i = index; i < listCount -1; i++) {
			keyValues[i] = keyValues[i + 1];
		}

		// Reduces the listCount and shortens the array because an
		// index has been removed
		listCount --;
		shortenList();

		success = true;
	}

	return success;
}

//******************************************************************************

// Written by Ojonimi Edime

// the same limit logic as printIt() the only thing different is this one is
// printing backwards
void list::printItBackwards(int n) const {
    unsigned int limit;

    if (n < 0 || (unsigned int)n > listCount) {
        limit = listCount;
    } else {
        limit = (unsigned int)n;
    }

    cout << "Printing " << limit << " of " << listCount
	 << " entries backwards with capacity of " << listCapacity << endl;
    for (unsigned int i = 0; i < limit; i++) {
	// Converts a forward counter into a backwards index so we can use
	// i < limit loop while actually reading the array from end to
	// front.
        unsigned int index = listCount - 1 - i;
        cout << "At index " << index << " there is (" << keyValues[index].key 
	     << "," << keyValues[index].value << ")" << endl;
    }	       
}

//******************************************************************************

// Written by Ojonimi Edime

// Marked as const because the cat never modifies this object, it will only
// read from it and list2 to build a new list
list *list::cat(list *list2) const {
    unsigned int l2Count = list2 ? list2->listCount : 0;
    list *r = new (std::nothrow) list(listCount + l2Count, expandSize);

    
    if (r != NULL) {
	// Copy every entry from this list into the new one
        for (unsigned int i = 0; i < listCount; i++) {
            r->add(keyValues[i]);
        }

	// This only append list2's entries if list2 actually exists
	if (list2 != NULL) {
	    for (unsigned int i = 0; i < l2Count; i++) {
	        r->add(list2->keyValues[i]);
	    }
        }
    }
    // If r comes back NULL, then both loops are skipped and r stays NULL
    return r;

}

//******************************************************************************

// Written by Chukwuemeka Obinna

void list::shortenList() {
    
    if (shortenEnabled) {
	//allocate a new array with the capacity of one less than the current
        KEY_VALUE *newList = new KEY_VALUE[listCapacity - 1];
	for (unsigned int i = 0; i < listCount; i++) {
	    //copy all the valid entries of the list to the new array
	    newList[i] = keyValues[i];
	}
        delete [] keyValues; //delete the old array
        keyValues = newList; //assign keyValues to point to the new array
	listCapacity = listCapacity - 1; //update listCapacity
    }
}

//******************************************************************************

// Written by Chukwuemeka Obinna

void list::setShortenEnabled(bool shorten) {

    shortenEnabled = shorten;//member variable set to given parameter
}

//******************************************************************************

// Written by Chukwuemeka Obinna

bool list::getShortenEnabled() const {

    return shortenEnabled; //returns the value of shortenEnabled
}
#endif
