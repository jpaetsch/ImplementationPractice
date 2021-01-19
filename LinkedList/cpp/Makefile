CC = g++ -std=c++17
CFLAGS = -O

all: linkedlist-simple linkedlist

debug: CFLAGS = -g -Wall -Wextra
debug: all

clean:
	rm -f *.o linkedlist-simple linkedlist

linkedlist-simple: linkedlist-simple.o
	$(CC) $(CFLAGS) -o $@ linkedlist-simple.o

linkedlist-simple.o: linkedlist-simple.cpp linkedlist-simple.h
	$(CC) $(CFLAGS) -c linkedlist-simple.cpp

linkedlist: linkedlist.o
	$(CC) $(CFLAGS) -o $@ linkedlist.o

linkedlist.o: linkedlist.cpp linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist.cpp