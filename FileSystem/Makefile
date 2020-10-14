CXX = g++
CXXFLAGS = -c

all: copy

copy: copy.o 
	$(CXX) copy.o -o copy

copy.o: copy.cpp
	$(CXX) $(CXXFLAGS) copy.cpp -o copy.o

clean:
	rm *.o copy