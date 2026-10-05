#
# CSC 255 Fall 2026 - Dr. Wheat
# Assignment: P6 minHeap and PQ
# Team 9 - Chukwuemeka Obinna and Ojonimi Edime
#

CXX      = g++
CXXFLAGS = -Wall -Wextra -O2

all: minHeap PQ

minHeap: minHeap.o minHeapMain.o
	$(CXX) $(CXXFLAGS) minHeap.o minHeapMain.o -o minHeap

PQ: minHeap.o PQ.o PQMain.o
	$(CXX) $(CXXFLAGS) minHeap.o PQ.o PQMain.o -o PQ

minHeap.o: minHeap.cpp minheap.h common.h
	$(CXX) $(CXXFLAGS) -c minHeap.cpp -o minHeap.o

minHeapMain.o: minHeapMain.cpp minheap.h common.h
	$(CXX) $(CXXFLAGS) -c minHeapMain.cpp -o minHeapMain.o

PQ.o: PQ.cpp PQ.h minheap.h common.h
	$(CXX) $(CXXFLAGS) -c PQ.cpp -o PQ.o

PQMain.o: PQmain.cpp PQ.h minheap.h common.h
	$(CXX) $(CXXFLAGS) -c PQmain.cpp -o PQMain.o

clean:
	rm -f *.o minHeap PQ

.PHONY: all clean
