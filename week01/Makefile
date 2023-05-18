CC=g++
REL_FLAGS=-O3 -DNDEBUG
DBG_FLAGS=-g -O0 -DDEBUG

# Set current compiler flags
CFLAGS=$(DEBUG_FLAGS)

q1: bin
	$(CC) $(CFLAGS) q1.cpp -o bin/q1

q2: bin
	$(CC) $(CFLAGS) q2.cpp -o bin/q2

all: q1 q2

bin:
	mkdir bin

clean:
	rm -r bin
