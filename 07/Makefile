CC=g++
FLAGS=--std=c++20
all: main
main: test.o
	$(CC) $(FLAGS) -o main test.o
test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp
clean:
	rm -rf *.o main
test:
	valgrind -s ./main