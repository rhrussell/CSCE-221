all: test

test: Stress_ball.o Collection.o collection_test.o
	c++ -std=c++11 Stress_ball.o Collection.o collection_test.o -o test

Stress_ball.o: Stress_ball.cpp Stress_ball.h
	c++ -std=c++11 -c Stress_ball.cpp

Collection.o: Collection.cpp Collection.h Stress_ball.h
	c++ -std=c++11 -c Collection.cpp

collection_test.o: collection_test.cpp Stress_ball.h Collection.h
	c++ -std=c++11 -c collection_test.cpp

clean:
	rm -f *.o test
