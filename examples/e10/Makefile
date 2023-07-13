CC=g++
REL_FLAGS=-O3 -DNDEBUG
DBG_FLAGS=-g -O0 -DDEBUG

# Set current compiler flags
CFLAGS=$(DEBUG_FLAGS)

e10: bin
	$(CC) $(CFLAGS) e10.cpp -o bin/e10

all: e10

bin:
	mkdir bin

clean:
	rm -r bin
