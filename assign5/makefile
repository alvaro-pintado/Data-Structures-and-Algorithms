# CS 302 Assignment #5
# Make file for zip codes project

OBJS	= checkZips.o zipCodes.o
CC	= g++ -Wall -pedantic -g -std=c++11
DEPS	= zipCodes.h redBlackTree.h
DEPS1	= redBlackTree.h

all: checkZips treeTest

treeTest.o: treeTest.cpp $(DEPS1)
	$(CC) -c treeTest.cpp

treeTest: treeTest.o $(DEPS1)
	$(CC) -o treeTest treeTest.o


zipCodes.o: zipCodes.cpp $(DEPS)
	$(CC) -c zipCodes.cpp

checkZips.o: checkZips.cpp $(DEPS)
	$(CC) -c checkZips.cpp

checkZips: checkZips.o zipCodes.o $(DEPS)
	$(CC) -o checkZips $(OBJS)

# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

