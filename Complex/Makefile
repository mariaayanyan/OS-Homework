all: main

main: main.o complex.o
	g++ main.o complex.o -o main

main.o: main.cpp
	g++ -c main.cpp -o main.o

complex.o: complex.cpp
	g++ -c complex.cpp -o complex.o

clean:
	rm *.o main
