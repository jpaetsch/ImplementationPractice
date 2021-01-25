CC = g++ -std=c++17
CFLAGS = -O

all: tree-binary

debug: CFLAGS = -g -Wall -Wextra
debug: all

clean:
	rm -f *.o tree-binary

tree-binary: tree-binary.o
	$(CC) $(CFLAGS) -o $@ tree-binary.o

tree-binary.o: tree-binary.cpp tree-binary.h
	$(CC) $(CFLAGS) -c tree-binary.cpp