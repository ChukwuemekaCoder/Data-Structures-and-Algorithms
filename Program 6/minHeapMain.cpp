#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "minheap.h"

using namespace std;

//******************************************************************************

void part1(minHeap &myHeap, unsigned int count) {
    bool rc;
    KEY_VALUE kv, kv2;

    cout << "Starting Part 1 ********************" << endl;
    for (kv.key = count - 1; kv.key > 0; kv.key -= 2) {
	kv.value = kv.key + 100;
	myHeap.insert(kv);

	if (!myHeap.integrity()) {
	    cout << "WARNING: The integrity of the heap is broken." << endl;
	}
    }

    for (kv.key = 0; kv.key < (int)count; kv.key += 2) {
	kv.value = kv.key + 100;
	myHeap.insert(kv);

	if (!myHeap.integrity()) {
	    cout << "WARNING: The integrity of the heap is broken." << endl;
	}
    }

    cout << "Heap contents are: \n";
    myHeap.printIt();

    for (unsigned int index = 0; index < 10; index += 2) {
	rc = myHeap.readByIndex(index, kv2);

	if (!rc) {
	    cout << "WARNING: readyByIndex at " << index << "failed." << endl;
	} else {
	    if (index % 2) {
		rc = myHeap.removeByKey(kv2.key, kv);
		if (kv.key != kv2.key) {
		    cout << "WARNING: RBK returned the incorrect kv" << endl;
		}

		cout << index << ": RBK got " << "(" << kv.key << "," << kv.value;
		cout  << ") and " << (rc ? "TRUE" : "FALSE") << endl;
	    } else {
		rc = myHeap.removeByIndex(index, kv);
		if (kv.key != kv2.key) {
		    cout << "WARNING: RBI returned the incorrect kv" << endl;
		}

		cout << index << ": RBI got " << "(" << kv.key << "," << kv.value;
		cout  << ") and " << (rc ? "TRUE" : "FALSE") << endl;
	    }
	}

	if (!myHeap.integrity()) {
	    cout << "WARNING: The integrity of the heap is broken after remove."
			<< endl;
	}
    }

    cout << endl << "Done with removing KVs." << endl;
    cout << "Heap contents are: \n";
    myHeap.printIt();


    myHeap.clear();
    cout << "Heap count after clear is now " << myHeap.getCount() << endl;
}

//******************************************************************************

int main() {
    minHeap myHeap(200);

    part1(myHeap, 100);

    cout << "Doing Part 1 again *************" << endl;

    part1(myHeap, 200);
    cout << "all done \n";
}
