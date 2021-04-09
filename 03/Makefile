all: matrix

test: matrix
	./matrix

matrix: matrix.o test.o
	g++ -std=c++17 -Wall -o matrix matrix.o test.o

matrix.o: matrix.cpp matrix.h
	g++ -std=c++17 -Wall matrix.cpp -c

test.o: test.cpp
	g++ -std=c++17 -Wall  test.cpp -c

clean:
	rm -rf matrix *.o