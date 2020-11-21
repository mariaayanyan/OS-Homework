CXX = g++
CXXFLAGS = -c

all: main

main: main.o ParallelScheduler.o
	$(CXX) main.o ParallelScheduler.o -lpthread -o main

main.o: main.cpp ParallelScheduler.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.o

ParallelScheduler.o: ParallelScheduler.cpp
	$(CXX) $(CXXFLAGS) ParallelScheduler.cpp -o ParallelScheduler.o

clean:
	rm *.o main