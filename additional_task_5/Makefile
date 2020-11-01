TARGET = main
FLAGS = -O0 -Wall -Werror
CC = g++

all: main

main: main.cpp intrusive_ptr.h
	$(CC) -g $^ -o $@ $(FLAGS)

clean:
	rm -rf *~ *.o main
