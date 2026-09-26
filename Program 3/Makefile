#
# CSC 255 Fall 2026 - Dr. Wheat
# Assignment: P3 dll
# Team 9 - Chukwuemeka Obinna and Ojonimi Edime
#
#

CWFLAGS=-Wall -Wextra -D CHOOSE_DLL -D DO_PART_B

all: dll

dll.o:	dll.cpp dll.h common.h
	g++ $(CWFLAGS) -O2 -c dll.cpp -o dll.o

listMain.o:	listMain.cpp dll.h common.h
	g++ $(CWFLAGS) -O2 -c listMain.cpp -o listMain.o

dll:	listMain.o dll.o
	g++ $(CWFLAGS) -O2 listMain.o dll.o -o dll

clean:
	rm -f *.o dll.exe dll
