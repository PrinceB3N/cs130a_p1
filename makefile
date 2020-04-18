# Makefile

all: prog1.out
test: test
prog1.out: prog1.out.o
	clang++ -g prog1.cpp BST.cpp HashTable.cpp -o prog1.out
prog1.out.o: prog1.cpp
	clang++ -g -c prog1.cpp
test: test.o
	clang++ -g test.cpp BST.cpp HashTable.cpp -o test
clean:
	rm -f prog1.out test *.o
