.PHONY: clean

CC=g++
FLAGS=-Wall -Wextra -Werror -g
BUILD=../build/

main: main.o
	$(CC) $(FLAGS) -o $(BUILD)program main.o 

main.o: main.cpp ArraySequence.hpp Graph.hpp
	$(CC) $(FLAGS) -c main.cpp

clean:
	rm -Rfv *.o *.gch *.out $(BUILD)program
