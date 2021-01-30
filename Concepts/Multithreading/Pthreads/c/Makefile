CC = gcc
CFLAGS = -std=c99 -O2
LIBS = -pthread -lm

.PHONY: all debug clean

all: main

debug: CFLAGS = -g -Wall -Wextra
debug: all

clean:
	rm -f *.o main

main: main.o IO.o
	$(CC) $(CFLAGS) -o $@ main.o IO.o $(LIBS)

main.o: main.c main.h 
	$(CC) $(CFLAGS) -c main.c 
	
IO.o: IO.c IO.h
	$(CC) $(CFLAGS) -c IO.c