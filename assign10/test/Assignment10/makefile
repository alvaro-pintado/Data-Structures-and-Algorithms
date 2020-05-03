# Make file for graphs assignment

CC	= g++ -pedantic -std=c++11 -g
OBJS	= graphs.o graphAlgorithms.cpp
DEPS	= graphAlgorithms.h priorityQueue.h

all: graphs

graphAlgorithms.o: graphAlgorithms.cpp $(DEPS)
	$(CC) -c graphAlgorithms.cpp

graphs.o: graphs.cpp $(DEPS)
	$(CC) -c graphs.cpp

graphs: graphs.o graphAlgorithms.o $(DEPS)
	$(CC) -o graphs $(OBJS)


# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

