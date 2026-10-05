#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "PQ.h"

using namespace std;

//******************************************************************************

void part1(PQ &myPQ) {
    bool rc;
    KEY_VALUE kv;

    for (kv.key = myPQ.getCapacity() - 1; kv.key > 0; kv.key -= 2) {
	kv.value = kv.key + 100;
	myPQ.enq(kv);
    }

    for (kv.key = 0; kv.key < (int)(myPQ.getCapacity()); kv.key += 2) {
	kv.value = kv.key + 100;
	myPQ.enq(kv);
    }

    cout << "PQ count is " << myPQ.getCount() << endl;
    cout << "PQ contents are: \n";

    myPQ.printIt();

    for (int i = 0; i < 10; i++) {
	rc = myPQ.deq(kv);
	cout << i << ": deq got " << "(" << kv.key << "," << kv.value;
	cout  << ") and " << (rc ? "TRUE" : "FALSE") << endl;
    }

    myPQ.clear();
    cout << "PQ Clear completed." << endl;
    myPQ.printIt();
}

//******************************************************************************

int main() {
    PQ myPQ(200);

    part1(myPQ);
    cout << "all done \n";
}
