CXX = g++
CXXFLAGS = -c

all : silentshell

silentshell : silentshell.o
	$(CXX) silentshell.o -lpthread -o silentshell

silentshell.o : silentshell.cpp
	$(CXX) $(CXXFLAGS) silentshell.cpp -o silentshell.o

clean :
	rm *.o silentshell