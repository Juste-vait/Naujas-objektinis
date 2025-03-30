main: vector.o funkcijos.o
	g++ -std=c++17 -Wall -o main vector.o funkcijos.o

vector.o: vector.cpp funkcijos.h
	g++ -std=c++17 -Wall -c vector.cpp

funkcijos.o: funkcijos.cpp funkcijos.h
	g++ -std=c++17 -Wall -c funkcijos.cpp

run: main
	./main

clean:
	rm -f vector.o funkcijos.o main
