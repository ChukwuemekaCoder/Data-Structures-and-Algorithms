// CSC 255 Fall 2025 – Dr. Wheat
// Program 3 Doubly Linked List
// Team 9: Chukwuemeka Obinna, Ojonimi Edime

//******************************************************************************

#include <iostream>
#include "dll.h"

using namespace std;

//******************************************************************************

//Written by Ojonimi Edime

node::node(KEY_VALUE kv, node *next, node *prev) {
    this->kv = kv;
    this->next = next;
    this->prev = prev;
}

//******************************************************************************

//Written by Ojonimi Edime

dll::dll() {
    first = NULL;
    last = NULL;
    listCount = 0;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

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

dll::~dll() {
    clear();
}

//******************************************************************************

//Written by Ojonimi Edime

void dll::clear(node *pn) {
    if (pn != NULL) {
        clear(pn->next);
        delete pn;
    }
}

//******************************************************************************

//Written by Chukwuemeka Obinna

void dll::clear() {
    clear(first);
    first = NULL;
    last = NULL;
    listCount = 0;
}

//******************************************************************************

//Written by Chukwuemeka Obinna

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

//Written by Ojonimi Edime

bool dll::insertAt(unsigned int index, KEY_VALUE kv) {
    bool result;

    if (index > listCount) {
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

bool dll::insertByKey(KEY_VALUE kv) {
    bool result;

    if (first == NULL || kv.key <= first->kv.key) {
        result = insert(kv);
    } else if (kv.key >= last->kv.key) {
        result = add(kv);
    } else {
        node *cur = first;
        while (cur != NULL && cur->kv.key < kv.key) {
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

//Written by Ojonimi Edime

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

int dll::getIndex(int key) const {
    return getIndex(key, first, 0);
}

//******************************************************************************

//Written by Ojonimi Edime

void dll::printIt(node *pn, unsigned int index, int limit) const {
    if (pn != NULL && limit > 0) {
        cout << "At index " << index << " there is (" << pn->kv.key << ","
             << pn->kv.value << ")" << endl;
        printIt(pn->next, index + 1, limit - 1);
    }
}

//******************************************************************************

//Written by Ojonimi Edime

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

unsigned int dll::getCapacity() const {
    return listCount;
}

//******************************************************************************

//Written by Ojonimi Edime

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
