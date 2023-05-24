CC=g++
REL_FLAGS=-O3 -DNDEBUG
DBG_FLAGS=-g -O0 -DDEBUG

# Set current compiler flags
CFLAGS=$(DEBUG_FLAGS)

q1: bin
	$(CC) $(CFLAGS) q1.cpp -o bin/q1

q2: bin
	$(CC) $(CFLAGS) q2.cpp -o bin/q2

q3: bin
	$(CC) $(CFLAGS) q3.cpp -o bin/q3

q4: bin
	$(CC) $(CFLAGS) q4.cpp -o bin/q4

q5: bin
	$(CC) $(CFLAGS) q5.cpp -o bin/q5

q6: bin
	$(CC) $(CFLAGS) q6.cpp -o bin/q6

q7: bin
	$(CC) $(CFLAGS) q7.cpp -o bin/q7


all: q1 q2 q3 q4 q5 q6 q7

bin:
	mkdir bin

clean:
	rm -r bin
