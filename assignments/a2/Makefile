CC=g++
REL_FLAGS=-O3 -DNDEBUG
DBG_FLAGS=-g -O0 -DDEBUG

# Set current compiler flags
CFLAGS=$(DEBUG_FLAGS)

a2: bin
	$(CC) $(CFLAGS) a2.cpp -o bin/a2

all: a2

bin:
	mkdir bin

clean:
	rm -r bin
