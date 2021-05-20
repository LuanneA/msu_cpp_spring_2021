CC=g++ -std=c++17

all: main

main: test.o 
	$(CC) -o main test.o 
 
test: main
	./main
	
test.o: test.cpp ThreadPool.h  
	$(CC) -c test.cpp  
  
clean:  
	rm -rf *.o main