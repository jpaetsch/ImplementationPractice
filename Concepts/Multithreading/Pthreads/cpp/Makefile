CC = g++ -std=c++17
CFLAGS = -O2
LIBS = -pthread
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

.PHONY: all clean debug

all: produceNconsume

debug: CFLAGS = -g -Wall -Wextra
debug: all

clean:
	rm -f *.o *.log produceNconsume

%.o: %.cpp
	${CC} ${CFLAGS} -c $< -o $@

produceNconsume: $(OBJECTS)
	$(CC) -o produceNconsume $(OBJECTS) $(LIBS)