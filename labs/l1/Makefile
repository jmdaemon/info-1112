CC=g++
REL_FLAGS=-O3 -DNDEBUG
DBG_FLAGS=-g -O0 -DDEBUG

# Set current compiler flags
CFLAGS=$(DEBUG_FLAGS)

l1: bin
	$(CC) $(CFLAGS) l1.cpp -o bin/l1

all: l1

bin:
	mkdir bin

clean:
	rm -r bin
