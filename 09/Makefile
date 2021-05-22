CC=g++ --std=c++17
CFLAGS = -c

all: assembly

test: assembly
	./main

assembly: sort.o main.o
	$(CC) sort.o main.o -o main 

sort.o: sort.cpp sort.h
	$(CC) $(CFLAGS) sort.cpp

main.o: sort.cpp sort.h
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *.o main output file