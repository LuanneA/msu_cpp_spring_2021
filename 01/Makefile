
all: my_prog

my_prog: test.o allocator.o 
		g++ -o my_prog test.o allocator.o

allocator.o: allocator.cpp allocator.h
		g++ -c allocator.cpp

test.o: test.cpp allocator.h
		g++ -c test.cpp

clean:
		rm -rf *.o my_prog