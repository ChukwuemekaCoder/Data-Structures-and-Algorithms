#
# CSC 255 Fall 2026 - Dr. Wheat
# Assignment: P2 cList
# Team 9 - Chukwuemeka Obinna and Ojonimi Edime
#
#

CWFLAGS=-Wall -Wextra -D CHOOSE_CLIST

all: cListA cListB

cListA.o:	cList.cpp cList.h common.h
	g++ $(CWFLAGS) -O2 -c cList.cpp -o cListA.o

cListB.o:	cList.cpp cList.h common.h
	g++ $(CWFLAGS) -O2 -D DO_PART_B -c cList.cpp -o cListB.o

listMainA.o:	listMain.cpp cList.h common.h
	g++ $(CWFLAGS) -O2 -c listMain.cpp -o listMainA.o

listMainB.o:	listMain.cpp cList.h common.h
	g++ $(CWFLAGS) -D DO_PART_B -O2 -c listMain.cpp -o listMainB.o

cListA:		listMainA.o cListA.o
	g++ $(CWFLAGS) -O2 listMainA.o cListA.o -o cListA

cListB:		listMainB.o cListB.o
	g++ $(CWFLAGS) -O2 listMainB.o cListB.o -o cListB

clean:
	rm -f *.o cListA.exe cListB.exe cListA cListB
