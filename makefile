# Makefile
CXX_FLAG = --std=c++11 -g

all: prog1.out

prog1.out: main.o
	clang++ $(CXX_FLAG) main.cpp BST.cpp HashTable.cpp -o prog1.out

clean:
	rm -f prog1.out *.o
