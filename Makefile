all: avl bst

bst:
	g++ -std=c++11 -o bst bst.cpp
avl:
	g++ -std=c++11 -o avl avl.cpp
clean:
	rm -f avl bst.o
