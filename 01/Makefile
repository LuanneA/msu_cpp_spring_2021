CC=g++
FLAGS=-std=c++17 -Wall -Werror -fsanitize=address -Wextra

hello: main.cpp
	$(CC) $(FLAGS) main.cpp -o test
	./test

.PHONY: clean
clean:
	rm test