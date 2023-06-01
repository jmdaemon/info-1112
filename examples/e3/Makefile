CC=g++
REL_FLAGS=-O3 -DNDEBUG
DBG_FLAGS=-g -O0 -DDEBUG

# Set current compiler flags
CFLAGS=$(DEBUG_FLAGS)

a1: bin
	$(CC) $(CFLAGS) a1.cpp -o bin/a1

all: a1

bin:
	mkdir bin

clean:
	rm -r bin
