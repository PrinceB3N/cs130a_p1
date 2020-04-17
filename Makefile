# Makefile
CXX_FLAG = --std=c++11 -g

all: main

main: main.o
	clang++ $(CXX_FLAG) main.cpp BST.cpp HashTable.cpp -o main.o

clean:
	rm -f main *.o
