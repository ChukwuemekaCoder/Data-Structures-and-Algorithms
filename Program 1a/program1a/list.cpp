// CSC 255 Fall 2026 – Dr. Wheat
// Program 1 List
// Team 9: Chukwuemeka Obinna and Ojonimi Edime

//******************************************************************************

#include <iostream>
#include "list.h"

using namespace std;

//******************************************************************************

list::list(unsigned int listCapacity, unsigned int expandSize) {
    // Written by Chukwuemeka Obinna
    
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
list::list(list *srcList) {
}
#endif

//******************************************************************************

list::~list() {

    //Written by Chukwuemeka Obinna

    delete [] keyValues;//prevents memory leaks
}

//******************************************************************************

bool list::expand() {

    //Written by Chukwuemeka Obinna
    
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

bool list::insert(KEY_VALUE kv) {

    //Written by Chukwuemeka Obinna

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

bool list::add(KEY_VALUE kv) {

    //Written by Chukwuemeka Obinna
    
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

bool list::deleteFirst(KEY_VALUE &kv) {
    
    //Written by Ojonimi Edime
    
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
	result = true;//first number was successfully deleted
    }

    return result;//return either true or false
}

//******************************************************************************

bool list::deleteLast(KEY_VALUE &kv) {

    //Written by Chukwuemeka Obinna

    bool result;

    if (listCount == 0){
        result = false;// you cannot delete a number from an empty list
    }
    else{
	//take whatever is at the last index and copy it to kv
        kv = keyValues[listCount - 1];
	listCount--;//decrement the list because a number has been deleted
	result = true;//last number was succesfully deleted
    }

    return result;//returns either true or false
}
//******************************************************************************

void list::setExpandSize(unsigned int expandSize) {

    //Written by Ojonimi Edime
	
    this->expandSize = expandSize;//member variable is equal to parameter
}

//******************************************************************************

unsigned int list::getExpandSize() const {

    //Written by Ojonimi Edime

    return expandSize; //returns the expand size
}

//******************************************************************************

void list::clear() {
    
    //Written by Ojonimi Edime
	
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

bool list::readAt(unsigned int index, KEY_VALUE &kv) const {

    //Written by Chukwuemeka Obinna
    
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

unsigned int list::getIndex(int key) const {

    //Written by Ojonimi Edime

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

void list::printIt(int n) const {

    //Written by Ojonimi Edime

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

unsigned int list::getCount() const {

    //Written by Chukwuemeka Obinna

    return listCount; //get the number of entries in the list
}

//******************************************************************************

unsigned int list::getCapacity() const {

    //Written by Ojonimi Edime

    return listCapacity; //get the capacity of the list
}

//******************************************************************************

#ifdef DO_PART_B
bool list::insertAt(unsigned int index, KEY_VALUE kv) {
}

//******************************************************************************

bool list::insertByKey(KEY_VALUE kv) {
}

//******************************************************************************

bool list::deleteAt(unsigned int index, KEY_VALUE &kv) {
}

//******************************************************************************

void list::printItBackwards(int n) const {
}

//******************************************************************************

list *list::cat(list *list2) {
}

//******************************************************************************

void list::shortenList() {
}

//******************************************************************************

void list::setShortenEnabled(bool shorten) {
}

//******************************************************************************

bool list::getShortenEnabled() {
}
#endif
