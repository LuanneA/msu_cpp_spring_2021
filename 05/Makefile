CC=g++ --std=c++17

all: tests

tests: test.cpp serializer.h
	$(CC) test.cpp -o tests

test: tests
	./tests

clean:
	rm tests