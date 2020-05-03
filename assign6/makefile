CC = g++
CFLAGS = -g -Wall -pedantic -std=c++11 -pthread

TARGET = amicableNumes

all:$(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	rm $(TARGET)
