# CS 302 Assignment #7
# Make file for zip codes project

OBJS	= checkZips.o zipCodes.o hashTable.o
CC	= g++ -Wall -pedantic -g -std=c++11
DEPS	= zipCodes.h hashTable.h
DEPS1	= hashTable.h

all: checkZips hashTest

hashTable.o: hashTable.cpp $(DEPS)
	$(CC) -c hashTable.cpp 

hashTest.o: hashTest.cpp $(DEPS1)
	$(CC) -c hashTest.cpp

hashTest: hashTest.o hashTable.o $(DEPS1)
	$(CC) -o hashTest hashTest.o hashTable.o

zipCodes.o: zipCodes.cpp $(DEPS)
	$(CC) -c zipCodes.cpp

checkZips.o: checkZips.cpp $(DEPS)
	$(CC) -c checkZips.cpp

checkZips: checkZips.o zipCodes.o hashTable.o $(DEPS)
	$(CC) -o checkZips $(OBJS)

# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

