# Make file for maze generator assignment.

OBJS	= makeMaze.o mazeGenerator.o
OBJS1	= testDS.o
CC	= g++ -Wall -pedantic -std=c++11 -g
DEPS	= mazeGenerator.h linkedStack.h

all: makeMaze testDS

makeMaze: makeMaze.o mazeGenerator.o $(DEPS)
	$(CC) -o makeMaze $(OBJS)

makeMaze.o: makeMaze.cpp $(DEPS)
	$(CC) -c makeMaze.cpp

mazeGenerator.o: mazeGenerator.cpp $(DEPS)
	$(CC) -c mazeGenerator.cpp


testDS: testDS.o $(DEPS)
	$(CC) -o testDS $(OBJS1)

testDS.o: testDS.cpp $(DEPS)
	$(CC) -c testDS.cpp


# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

