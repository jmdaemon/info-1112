CC=g++
REL_FLAGS=-O3 -DNDEBUG
DBG_FLAGS=-g -O0 -DDEBUG

# Set current compiler flags
CFLAGS=$(DEBUG_FLAGS)

lab1: bin
	$(CC) $(CFLAGS) lab1.cpp -o bin/lab1

all: lab01

bin:
	mkdir bin

clean:
	rm -r bin
