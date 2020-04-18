# Makefile

all: prog1.out

prog1.out: main.o
	clang++ -g main.cpp BST.cpp HashTable.cpp -o prog1.out
main.o: main.cpp
	clang++ -g -c main.cpp
clean:
	rm -f prog1.out *.o
