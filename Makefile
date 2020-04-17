# Makefile
CXX_FLAG = --std=c++11 -g

all: prog1

prog1: main.o
	clang++ $(CXX_FLAG) main.cpp BST.cpp HashTable.cpp -o prog1

clean:
	rm -f prog1 *.o
