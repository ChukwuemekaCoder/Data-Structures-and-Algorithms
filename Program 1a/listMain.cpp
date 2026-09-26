#include <iostream>
#ifdef CHOOSE_LIST
    #include "list.h"
    #define CHOSEN_STYLE list
#elif defined(CHOOSE_CLIST)
    #include "cList.h"
    #define CHOSEN_STYLE cList
#elif defined(CHOOSE_DLL)
    #include "dll.h"
    #define CHOSEN_STYLE dll
#endif

using namespace std;

//******************************************************************************

int sequenceNumber = 1000;
int myRand() {
    int rc = sequenceNumber;

    sequenceNumber += 10;

    return rc;
}

//******************************************************************************

int main() {
    KEY_VALUE kv;
    int count;
    bool rc;

    CHOSEN_STYLE myL;
    CHOSEN_STYLE *myLa = new CHOSEN_STYLE();
    CHOSEN_STYLE *myLb = new CHOSEN_STYLE();

    myL.printIt(-1);
    cout << "The size of the first list is " << myL.getCount() << endl << endl;

    for (kv.key = 0; kv.key < 10; kv.key++) {
	kv.value = myRand();
	cout << "insert of (" << kv.key << "," << kv.value << ") got ";
	cout << (myLa->insert(kv) ? "true" : "false") << endl;

	kv.value = -kv.value + 1;
	cout << "add of (" << kv.key << "," << kv.value << ") got ";
	cout << (myLa->add(kv) ? "true" : "false") << endl;
    }

    cout << endl;

    cout << "we have this number of entries " << myLa->getCount() << endl;
    myLa->printIt(-1);
    cout << endl;
#ifdef DO_PART_B
    myLa->printItBackwards(-1);
    
    cout << endl;

    kv.key = 100;
    kv.value = myRand();
    cout << "insertAt(5, (" << kv.key << "," << kv.value <<") got ";
    cout << (myLa->insertAt(5, kv) ? "true" : "false") << "\n\n";

    kv.key = 111;
    kv.value = myRand();
    cout << "insertAt(15, (" << kv.key << "," << kv.value <<") got ";
    cout << (myLa->insertAt(15, kv) ? "true" : "false") << "\n\n";

    kv.key = 222;
    kv.value = myRand();
    cout << "insertAt(25, (" << kv.key << "," << kv.value <<") got ";
    cout << (myLa->insertAt(25, kv) ? "true" : "false") << "\n\n";
#endif

    kv.key = 333;
    kv.value = myRand();
    cout << "insert((" << kv.key << "," << kv.value <<") got ";
    cout << (myLa->insert(kv) ? "true" : "false") << "\n\n";

    kv.key = 444;
    kv.value = myRand();
    cout << "add((" << kv.key << "," << kv.value <<") got ";
    cout << (myLa->add(kv) ? "true" : "false") << "\n\n";

    cout << "getIndex(7) returned " << myLa->getIndex(7) << "\n\n";
    cout << "getIndex(50) returned " << myLa->getIndex(50) << "\n\n";

    cout << "The list has this many entries " << myLa->getCount() << endl;
    cout << "The list has this capacity " << myLa->getCapacity() << endl << endl;

    kv.key = 123;
    kv.value = 123;
    rc = myLa->readAt(4, kv);
    cout << "readAt(4, key) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key << ","
	    << kv.value << ")\n\n";

    kv.key = 456;
    kv.value = 456;
    rc = myLa->readAt(1000000, kv);
    cout << "readAt(1000000, key) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key << ","
	    << kv.value << ")\n\n";

#ifdef DO_PART_B
    kv.key = -777;
    kv.value = -777;
    rc = myLa->deleteAt(3, kv);
    cout << "deleteAt(3, kv) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key;
    cout << "," << kv.value << ")\n\n";

    kv.key = -888;
    kv.value = -888;
    rc = myLa->deleteAt(33, kv);
    cout << "deleteAt(33, kv) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key;
    cout << "," << kv.value << ")\n\n";
#endif

    myLa->printIt(-1);

    cout << endl;

    kv.key = -555;
    kv.value = -555;

    rc = myLa->deleteFirst(kv);
    cout << "deleteFirst(kv) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key;
    cout << "," << kv.value << ")\n\n";

    kv.key = -666;
    kv.value = -666;

    rc = myLa->deleteLast(kv);
    cout << "deleteLast(kv) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key;
    cout << "," << kv.value << ")\n\n";

    myLa->printIt(10);
    cout << endl;
#ifdef DO_PART_B
    myLa->printItBackwards(10);
#endif

    count = myLa->getCount();

    for (int i = 0; i <= count; i++) {
        kv.key = -666;
        kv.value = -666;

        if (i % 2) {
#ifdef DO_PART_B
            rc = myLa->deleteAt(0, kv);
            cout << "deleteAt(0, kv) got ";
#else
            rc = myLa->deleteLast(kv);
            cout << "deleteLast(kv) got ";
#endif
        } else {
            rc = myLa->deleteFirst(kv);
            cout << "deleteFIrst(kv) got ";
        }
        cout << (rc ? "true" : "false") << " and (" << kv.key;
        cout << "," << kv.value << ")\n\n";
    }

    myLa->printIt(10);
    cout << endl;
#ifdef DO_PART_B
    myLa->printItBackwards(10);
#endif


    //************************** WORKING WITH BLIST NOW
    
    cout << endl << "Working on the B list now." << endl << endl;
    kv.key = 100;
    kv.value = 1100;
#ifdef DO_PART_B
    myLb->insertAt(0, kv);
#else
    myLb->insert(kv);
#endif

    kv.key = -888;
    kv.value = -888;
#ifdef DO_PART_B
    rc = myLb->deleteAt(0, kv);
    cout << "deleteAt(0, kv) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key;
    cout << "," << kv.value << ")\n\n";
#else
    rc = myLb->deleteFirst(kv);
    cout << "deleteFirst(kv) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key;
    cout << "," << kv.value << ")\n\n";
#endif


    myLb->printIt(10);
    cout << endl;
#ifdef DO_PART_B
    myLb->printItBackwards(10);
#endif

    for (kv.key = 0; kv.key < 40; kv.key++) {
#ifdef DO_PART_B
	kv.value = kv.key + 1000;
	myLb->insertAt(0, kv);
#else
	kv.value = kv.key + 1000;
	myLb->insert(kv);
#endif
    }

    myLb->printIt(10);
    cout << endl;
#ifdef DO_PART_B
    myLb->printItBackwards(10);
#endif

    count = myLb->getCount();

    for (int i = 0; i < count; i++) {
	myLb->readAt(i, kv);
	if (kv.key != (count - i - 1)) {
	    cout << "readAt wrong answer with i = " << i << " kv.key = "
		    << kv.key << endl;
	    myLb->printIt(5);
#ifdef DO_PART_B
	    myLb->printItBackwards(5);
#endif
	    break;
	}
    }

    for (int i = 0; i < count; i++) {
#ifdef DO_PART_B
	myLb->deleteAt(0, kv);
#else
	myLb->deleteFirst(kv);
#endif
	if (kv.key != (count - i - 1)) {
	    cout << "deleteAt wrong answer with i = " << i << " kv.key = "
		    << kv.key << endl;
	    myLb->printIt(5);
#ifdef DO_PART_B
	    myLb->printItBackwards(5);
#endif
	    break;
	}
    }

    myLb->clear();


    for (kv.key = 0; kv.key < 1000; kv.key++) {
	kv.value = kv.key + 5000;
#ifdef DO_PART_B
 	myLb->insertAt(kv.key, kv);
#else
 	myLb->add(kv);
#endif
    }

    cout << endl;

    myLb->printIt(5);
    cout << endl;
#ifdef DO_PART_B
    myLb->printItBackwards(5);
#endif

#ifdef DO_PART_B
    // test copy of a list
    cout << endl;
    cout << "Testing the copying of a list" << endl;

    CHOSEN_STYLE *myLc = new CHOSEN_STYLE(myLb);

    cout << "Printing list b" << endl;
    myLb->printIt(5);
    myLb->printItBackwards(5);

    cout << endl << "Printing list c" << endl;
    myLc->printIt(5);
    myLc->printItBackwards(5);

    // check that the copy worked
    int capB = myLb->getCapacity();
    int capC = myLc->getCapacity();
    int countB = myLb->getCount();
    int countC = myLc->getCount();

    if (capB != capC) {
	cout << "ERROR: copied capacities are not the same" << endl;
	cerr << "ERROR: copied capacities are not the same" << endl;
    }
    if (countB != countC) {
	cout << "ERROR: copied counts are not the same" << endl;
	cerr << "ERROR: copied counts are not the same" << endl;
    }

    if (capB == capC && countB == countC) {
	for (unsigned int i = 0; i < myLb->getCount(); i++) {
	    KEY_VALUE kvB, kvC;
	    myLb->readAt(i, kvB);
	    myLc->readAt(i, kvC);
	    if ((kvB.key != kvC.key) || (kvB.value != kvC.value)) {
		cout << "ERROR: copied list does not match at entry: " << i << endl;
		cerr << "ERROR: copied list does not match at entry: " << i << endl;
	    }
	}
    }

    // test concatenating a list
    cout << endl;
    cout << "Testing concatentation" << endl;

    CHOSEN_STYLE *myLd = new CHOSEN_STYLE();
    CHOSEN_STYLE *myLe = new CHOSEN_STYLE();

    for (kv.key = 0; kv.key < 10; kv.key++) {
	kv.value = myRand();
	myLd->add(kv);
    }

    for (kv.key = 30; kv.key < 40; kv.key++) {
	kv.value = myRand();
	myLe->add(kv);
    }

    CHOSEN_STYLE *myLf = myLd->cat(myLe);

    if (myLf) {
	cout << "First list prints now:" << endl;
	myLd->printIt(-1);

	cout << "Second list prints now:" << endl;
	myLe->printIt(-1);

	cout << "Concatenated list prints now:" << endl;
	myLf->printIt(-1);
    } else {
	cout << "Error: myLf not created via the cat function." << endl;
    }

    cout << endl;

#ifndef CHOOSE_DLL
    cout << "Now testing for insert by key and shortening" << endl;

    CHOSEN_STYLE *myLg = new CHOSEN_STYLE(0, 2);

    cout << "ExpandSize was " << myLg->getExpandSize() << endl;
    myLg->setExpandSize(1);
    cout << "ExpandSize is " << myLg->getExpandSize() << endl;

    if (myLg->getCapacity() != 0) {
	cout << "listCapacity is not the correct value" << endl;
    }
    if (myLg->getExpandSize() != 1) {
	cout << "expandSize is not the correct value" << endl;
    }
#else
    cout << "Now testing for insert by key" << endl;

    CHOSEN_STYLE *myLg = new CHOSEN_STYLE();
#endif

    cout << "Entering phase1 on insertByKey" << endl;
    bool failureHappened = false;
    unsigned int i;
    for (kv.key = 100, i = 0; kv.key < 200 &&
	!failureHappened; kv.key += 2, i++) {
	kv.value = kv.key + 1000;
	myLg->insertByKey(kv);
	if ((myLg->getCapacity() != i+1) || (myLg->getCount() != i+1)) {
	    cout << "Failure on expand" << endl;
	    cout << "getCount returned " << myLg->getCount() << endl;
	    cout << "getCapicity returned " << myLg->getCapacity() << endl;
	    myLg->printIt(-1);
	    failureHappened = true;
	}
    }

    if (!failureHappened) {
	cout << "insertByKey phase1 passed" << endl;
	// use the value of i from the first phase as a starting point
	cout << "Entering phase2 on insertByKey" << endl;
	for (kv.key = 101; kv.key < 200 &&
	    !failureHappened; kv.key += 2, i++) {
	    kv.value = kv.key + 1000;
	    myLg->insertByKey(kv);
	    if ((myLg->getCapacity() != i+1) || (myLg->getCount() != i+1)) {
		cout << "Failure on expand" << endl;
		cout << "getCount returned " << myLg->getCount() << endl;
		cout << "getCapicity returned " << myLg->getCapacity() << endl;
		myLg->printIt(-1);
		failureHappened = true;
	    }
	}
    }

    if (!failureHappened) {
	cout << "insertByKey phase2 passed" << endl;
	cout << "Checking correctness of the list" << endl;
	int expectedKey;
	for (i = 0, expectedKey = 100; i < 100; i++, expectedKey++) {
	    bool rc = myLg->readAt(i, kv);
	    if (rc) {
		if (kv.key != expectedKey) {
		    cout << "read at index " << i << " got wrong value" << endl;
		    cout << "  expected " << expectedKey;
		    cout << " got " << kv.key;
		    myLg->printIt(-1);
		    failureHappened = true;
		    break;
		}
	    } else {
		cout << "read at index " << i << " failed" << endl;
		myLg->printIt(-1);
		failureHappened = true;
		break;
	    }
	}
    }

    if (!failureHappened) {
	cout << "insertByKey correctness test passed" << endl;
	cout << "Checking of delete with shortening of the list" << endl;

	unsigned int stop = 20;

#ifndef CHOOSE_DLL
	CHOSEN_STYLE *myLh = new CHOSEN_STYLE(0, 1);
	myLh->setShortenEnabled(true);
#else
	CHOSEN_STYLE *myLh = new CHOSEN_STYLE();
#endif

	for (i = 0; i < stop; i++) {
	    kv.key = i;
	    kv.value = i+1000;
	    myLh->add(kv);
	}
	for (i = 0; i < stop; i++) {
	    myLh->deleteFirst(kv);
	    if (myLh->getCapacity() != stop-i-1) {
		cout << "shortening with deleteFirst() did not work" << endl;
		myLh->printIt(-1);
		failureHappened = true;
		break;
	    }
	}

	if (!failureHappened) {
	    cout << "deleteFirst() with shortening test passed." << endl;
	} else {
	    cout << "deleteFirst() with shortening test did not pass." << endl;
	}

	delete myLh;

#ifndef CHOOSE_DLL
	myLh = new CHOSEN_STYLE(0, 1);
	myLh->setShortenEnabled(true);
#else
	myLh = new CHOSEN_STYLE();
#endif

	for (i = 0; i < stop; i++) {
	    kv.key = i;
	    kv.value = i+1000;
	    myLh->add(kv);
	}
	for (i = 0; i < stop; i++) {
	    myLh->deleteLast(kv);
	    if (myLh->getCapacity() != stop-i-1) {
		cout << "shortening with deleteLast() did not work" << endl;
		myLh->printIt(-1);
		failureHappened = true;
		break;
	    }
	}

	if (!failureHappened) {
	    cout << "deleteLast() with shortening test passed." << endl;
	} else {
	    cout << "deleteLast() with shortening test did not pass." << endl;
	}

	delete myLh;

#ifndef CHOOSE_DLL
	myLh = new CHOSEN_STYLE(0, 1);
	myLh->setShortenEnabled(true);
#else
	myLh = new CHOSEN_STYLE();
#endif

	for (i = 0; i < stop; i++) {
	    kv.key = i;
	    kv.value = i+1000;
	    myLh->add(kv);
	}
	for (i = 0; i < stop; i++) {
	    unsigned int index = myLh->getCount() / 2;
	    myLh->deleteAt(index, kv);
	    if (myLh->getCapacity() != stop-i-1) {
		cout << "shortening with deleteAt() did not work" << endl;
		myLh->printIt(-1);
		failureHappened = true;
		break;
	    }
	}

	if (!failureHappened) {
	    cout << "deleteAt() with shortening test passed." << endl;
	} else {
	    cout << "deleteAt() with shortening test did not pass." << endl;
	}

    }

#endif
    return 0;
}
