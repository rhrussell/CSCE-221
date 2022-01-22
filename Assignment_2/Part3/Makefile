all: run-tminq

run-tminq: MinQueue-main.o 
	c++ -std=c++11 MinQueue-main.o -o run-tminq

MinQueue-main.o: MinQueue-main.cpp MinQueue.h
	c++ -std=c++11 -c MinQueue-main.cpp

clean:
	rm *.o run-tminq