CC=g++
FLAGS=--std=c++17

all: my_prog

my_prog: test.o allocator.o 
		$(CC) $(FLAGS) -o my_prog test.o allocator.o

allocator.o: allocator.cpp allocator.h
		$(CC) $(FLAGS) -c allocator.cpp

test.o: test.cpp allocator.h
		$(CC) $(FLAGS) -c test.cpp

clean:
		rm -rf *.o my_prog
test: 
	valgrind ./my_prog