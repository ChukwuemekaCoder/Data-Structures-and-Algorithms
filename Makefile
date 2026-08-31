#
# CSC 255 Fall 2026 - Dr. Wheat
# Assignment: P1 List
# Team 9 - Chukwuemeka Obinna and Ojonimi Edime
#
#

CWFLAGS=-Wall -Wextra -D CHOOSE_LIST

all: listA listB simpleA simpleB

listA.o:	list.cpp list.h common.h
	g++ $(CWFLAGS) -O2 -c list.cpp -o listA.o

listB.o:	list.cpp list.h common.h
	g++ $(CWFLAGS) -O2 -D DO_PART_B -c list.cpp -o listB.o

simpleMainA.o:	simpleMain.cpp list.h common.h
	g++ $(CWFLAGS) -O2 -c simpleMain.cpp -o simpleMainA.o
	
simpleMainB.o:	simpleMain.cpp list.h common.h
	g++ $(CWFLAGS) -D DO_PART_B -O2 -c simpleMain.cpp -o simpleMainB.o
	
listMainA.o:	listMain.cpp list.h common.h
	g++ $(CWFLAGS) -O2 -c listMain.cpp -o listMainA.o
	
listMainB.o:	listMain.cpp list.h common.h
	g++ $(CWFLAGS) -D DO_PART_B -O2 -c listMain.cpp -o listMainB.o
	
simpleA:	simpleMainA.o listA.o
	g++ $(CWFLAGS) -O2 simpleMainA.o listA.o -o simpleA

simpleB:	simpleMainB.o listB.o
	g++ $(CWFLAGS) -O2 simpleMainB.o listB.o -o simpleB

listA:	listMainA.o listA.o
	g++ $(CWFLAGS) -O2 listMainA.o listA.o -o listA

listB:	listMainB.o listB.o
	g++ $(CWFLAGS) -O2 listMainB.o listB.o -o listB

clean:
	rm -f *.o listA.exe listB.exe listA listB simpleA.exe simpleB.exe simpleA simpleB
