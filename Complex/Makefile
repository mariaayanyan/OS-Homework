CXX = g++
CXXFLAGS = -c

all: main

main: main.o complex.o
	$(CXX) main.o complex.o -o main

main.o: main.cpp complex.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.o

complex.o: complex.cpp
	$(CXX) $(CXXFLAGS) complex.cpp -o complex.o

clean:
	rm *.o main