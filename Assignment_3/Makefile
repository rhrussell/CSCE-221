all: run-bstree

run-bstree: BSTree.o BSTree_main.o 
	c++ -std=c++11 BSTree.o BSTree_main.o -o run-bstree

BSTree.o: BSTree.cpp BSTree.h
	c++ -g -std=c++11 -c BSTree.cpp

BSTree_main.o: BSTree_main.cpp BSTree.h
	c++ -std=c++11 -c BSTree_main.cpp

clean:
	rm *.o run-bstree