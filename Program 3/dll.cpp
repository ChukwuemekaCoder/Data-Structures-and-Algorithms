// CSC 255 Fall 2025 – Dr. Wheat
// Program 3 Doubly Linked List
// Team 9: Chukwuemeka Obinna, Ojonimi Edime

//******************************************************************************

#include <iostream>
#include "dll.h"

using namespace std;

//******************************************************************************

//Written by Ojonimi Edime

//Just stores the payload and the two links the caller suplies.
node::node(KEY_VALUE kv, node *next, node *prev) {
    //Copies kv, next, and prev directly into this node's fields
    this->kv = kv;
    this->next = next;
    this->prev = prev;
}

//******************************************************************************

//Written by Ojonimi Edime

// Empties the list
dll::dll() {
    first = NULL;
    last = NULL;
    listCount = 0;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//Walks the srcList front to back and add()s each load onto this list, so the
//copy ends up in the same order ad shares nodes with original
dll::dll(dll *srcList) {
    first = NULL;
    last = NULL;
    listCount = 0;

    if (srcList != NULL) {
        node *cur = srcList->first;
        while (cur != NULL) {
            add(cur->kv);
            cur = cur->next;
        }
    }
}

//******************************************************************************

//Written by Ojonimi Edime

//Frees up each node before the object goes away
dll::~dll() {
    clear();
}

//******************************************************************************

//Written by Ojonimi Edime

//Recurse to the tail then delete pn on the way back up
void dll::clear(node *pn) {
    if (pn != NULL) {
        clear(pn->next);
        delete pn;
    }
    
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//Clears the whole chain then reset the list to empty
void dll::clear() {
    clear(first);
    first = NULL;
    last = NULL;
    listCount = 0;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//New node's next is the old first, old first prev points back to the new node.
//Handles the empty-list case, list also needs to become the new node
bool dll::insert(KEY_VALUE kv) {
    node *n = new node(kv, first, NULL);

    if (first != NULL) {
        first->prev = n;
    } else {
        last = n;
    }
    first = n;
    listCount++;
    return true;
}

//******************************************************************************

//Written by Ojonimi Edime

// Mirror image of insert(), attaching onto the back instead of the front.
bool dll::add(KEY_VALUE kv) {
    node *n = new node(kv, NULL, last);

    if (last != NULL) {
        last->next = n;
    } else {
        first = n;
    }
    last = n;
    listCount++;
    return true;
}

//******************************************************************************

// Written by Ojonimi Edime

//Insert before position 'index' (0-based). index == 0 and index == listCount
//are just the front/back cases, so theyere handed off to insert()/add().
bool dll::insertAt(unsigned int index, KEY_VALUE kv) {
    bool result;

    if (index > listCount) {//you cannot insert at an index out of range
        result = false;
    } else if (index == 0) {
        result = insert(kv);
    } else if (index == listCount) {
        result = add(kv);
    } else {
        node *cur = first;
        for (unsigned int i = 0; i < index; i++) {
            cur = cur->next;
        }
        
        node *n = new node(kv, cur, cur->prev);
        cur->prev->next = n;
        cur->prev = n;
        listCount++;
        result = true;
    }

    return result;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//Insert while keeping the list sorted asceding by key. Walk forward until we
//find the first node whose key is >= kv.key, and splicing it in just before 
//that node.
bool dll::insertByKey(KEY_VALUE kv) {
    bool result; 
    node *cur = first;
    
    while (cur != NULL && cur->kv.key < kv.key) {
        cur = cur->next;
    }

    if (cur == NULL) {
        result = add(kv);
    } 
    else if (cur == first){
        result = insert(kv);
    } 
    else {
        node *n = new node(kv, cur, cur->prev);
        cur->prev->next = n;
        cur->prev = n;
        listCount++;
        result = true;
    }

    return result;
}

//******************************************************************************

//Written by Ojonimi Edime

//Copy front node's payload through kv, unlink, and free it.
//If list becomes empty, last has to be cleared too.
bool dll::deleteFirst(KEY_VALUE &kv) {
    bool result;

    if (first == NULL) {
        result = false;
    } else {
        node *temp = first;
        kv = temp->kv;
        first = first->next;
        if (first != NULL) {
            first->prev = NULL;
        } else {
            last = NULL;
        }
        delete temp;
        listCount--;
        result = true;
    }

    return result;
}

//******************************************************************************

//Written by Ojonimi Edime

//Like delete first byt unlink from back instead.

bool dll::deleteLast(KEY_VALUE &kv) {
    bool result; 

    if (last == NULL) {
        result = false;
    } else {
        node *temp = last;
        kv = temp->kv;
        last = last->prev;
        if (last != NULL) {
            last->next = NULL;
        } else {
            first = NULL;
        }
        delete temp;
        listCount--;
        result = true;
    }

    return result;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

// Delete the node at the position 'index'. Both ends are handed off to 
// deleteFirst()/deleteLast(), anything in between is a normal splice-out.
bool dll::deleteAt(unsigned int index, KEY_VALUE &kv) {
    bool result;

    if (index >= listCount) {
        result = false;
    } else if (index == 0) {
        result = deleteFirst(kv);
    } else if (index == listCount - 1) {
        result = deleteLast(kv);
    } else {
        node *cur = first;
        for (unsigned int i = 0; i < index; i++) {
            cur = cur->next;
        }

        kv = cur->kv;
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
        listCount--;
        result = true;
    }

    return result;
}

//******************************************************************************

//Written by Ojonimi Edime

//Read-only lookup by position, does not remove or modify anything.
//Out-of-range index leaves kv untouched and returns false.
bool dll::readAt(unsigned int index, KEY_VALUE &kv) const {
    bool result;

    if (index >= listCount) {
        result = false;
    } else {
        node *cur = first;
        for (unsigned int i = 0; i < index; i++) {
            cur = cur->next;
        }
        kv = cur->kv;
        result = true;
    }

    return result;
}

//******************************************************************************

//Written by Ojonimi Edime

//pn/index track how far we've walked down the list.
//Falling off the end (pn == NULL) means the key wasnt found, signaled by
//the NEG_RESULT sentinel from common.h 
int dll::getIndex(int key, node *pn, int index) const {
    int result;

    if (pn == NULL) {
        result = NEG_RESULT;
    } else if (pn->kv.key == key) {
        result = index;
    } else {
        result = getIndex(key, pn->next, index + 1);
    }

    return result;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//Start the recursive search at the front, index 0.
int dll::getIndex(int key) const {
    return getIndex(key, first, 0);
}

//******************************************************************************

//Written by Ojonimi Edime

//Prit the current node, then recurse to pn->next index+1 and one fewer entry
//left to print. Stops at the end of the list or once 'limit' entries have
//been printed.
void dll::printIt(node *pn, unsigned int index, int limit) const {
    if (pn != NULL && limit > 0) {
        cout << "At index " << index << " there is (" << pn->kv.key << ","
        << pn->kv.value << ")" <<endl;
        printIt(pn->next, index + 1, limit - 1);
    }
}

//******************************************************************************

//Written by Ojonimi Edime

//Same as printing but with index counting down. index is unsigned, so we
//return right after printing index 0 instead of recursing into -1.
void dll::printItBackwards(node *pn, unsigned int index, int limit) const {
    if (pn != NULL && limit > 0) {
        cout << "At index " << index << " there is (" << pn->kv.key << ","
        << pn->kv.value << ")" << endl;
        if (index > 0) {
            printItBackwards(pn->prev, index - 1, limit - 1);
        }
    }
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//Prints at most n entries, front to back, reporting "printed of total" first
void dll::printIt(int n) const {
    unsigned int numToPrint;

    if (n < 0) {
        numToPrint = listCount;
    } else {
        numToPrint = (unsigned int) n;
        if (numToPrint > listCount) {
            numToPrint = listCount;
        }
    }

    cout << "Printing " << numToPrint << " of " << listCount << " entries"
    << endl;
    printIt(first, 0, numToPrint);
}

//******************************************************************************

//Written by Ojonimi Edime

//Same as printIt but starting from the back and walking prev pointers.
void dll::printItBackwards(int n) const {
    unsigned int numToPrint;

    if (n < 0) {
        numToPrint = listCount;
    } else {
        numToPrint = (unsigned int) n;
        if (numToPrint > listCount) {
            numToPrint = listCount;
        }
    }

    cout << "Printing " << numToPrint << " of " << listCount
    << " entries backwards" << endl;
    if (listCount > 0) {
        printItBackwards(last, listCount - 1, numToPrint);
    }
}

//******************************************************************************

//Written by Ojonimi Edime

unsigned int dll::getCount() const {
    return listCount;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

//No fixed capacity for a linked list, so this just mirrors getCount()
unsigned int dll::getCapacity() const {
    return listCount;
}

//******************************************************************************

//Written by Ojonimi Edime

//Builds and returns a brand new list which contains the lists entries
//followed by list2's entries in order.
dll *dll::cat(dll *list2) {
    dll *result = new dll();
    
    node *cur = first;
    while (cur != NULL) {
        result->add(cur->kv);
        cur = cur->next;
    }
    if (list2 != NULL) {
        cur = list2->first;
        while (cur != NULL) {
            result->add(cur->kv);
            cur = cur->next;
        }
    }

    return result;
}
