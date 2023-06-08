CC=g++
REL_FLAGS=-O3 -DNDEBUG
DBG_FLAGS=-g -O0 -DDEBUG

# Set current compiler flags
CFLAGS=$(DEBUG_FLAGS)

l2: bin
	$(CC) $(CFLAGS) l2.cpp -o bin/l2

all: l2

bin:
	mkdir bin

clean:
	rm -r bin
