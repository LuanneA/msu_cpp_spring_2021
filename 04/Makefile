all: BigInt

test: BigInt
	./BigInt

BigInt: BigInt.o test.o
	g++ -std=c++17 -Wall -o BigInt BigInt.o test.o

BigInt.o: BigInt.cpp BigInt.h
	g++ -std=c++17 -Wall BigInt.cpp -c

test.o: test.cpp
	g++ -std=c++17 -Wall  test.cpp -c

clean:
	rm -rf BigInt *.o