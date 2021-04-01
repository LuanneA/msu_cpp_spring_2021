all: parser

test: parser
	./parser

parser: parser.o test.o
	g++ -std=c++17 -Wall -o parser parser.o test.o

parser.o: parser.cpp parser.h
	g++ -std=c++17 -Wall parser.cpp -c

test.o: test.cpp
	g++ -std=c++17 -Wall  test.cpp -c

clean:
	rm -rf parser *.o