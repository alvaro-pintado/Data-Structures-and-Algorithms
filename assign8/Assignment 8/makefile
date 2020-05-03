# CS 302 Assignment #8
# Make file for zip codes project

OBJS	= cubeSum.o pqTest.o
CC	= g++ -pedantic -g -std=c++11
DEPS	= priorityQueue.h

all: cubeSum pqTest

pqTest.o: pqTest.cpp $(DEPS)
	$(CC) -c pqTest.cpp 

pqTest: pqTest.o $(DEPS)
	$(CC) -o pqTest pqTest.o 	 

cubeSum.o: cubeSum.cpp $(DEPS)
	$(CC) -c cubeSum.cpp

cubeSum: cubeSum.o $(DEPS)
	$(CC) -o cubeSum cubeSum.o

# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

