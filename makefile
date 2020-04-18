# Makefile

all: prog1.out
test: test
prog1.out: main.o
	clang++ -g main.cpp BST.cpp HashTable.cpp -o prog1.out
main.o: main.cpp
	clang++ -g -c main.cpp
test: test.o
	clang++ -g test.cpp BST.cpp HashTable.cpp -o test
clean:
	rm -f prog1.out test *.o
