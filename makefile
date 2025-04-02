CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = main_exe
SRC = main.cpp Graph.cpp Node.cpp Queue.cpp Algorithms.cpp

all: $(TARGET)

$(TARGET): main.o Graph.o Node.o Queue.o Algorithms.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o Graph.o Node.o Queue.o Algorithms.o

main.o: main.cpp
	$(CXX) -c main.cpp

Graph.o: Graph.cpp Graph.hpp
	$(CXX) -c Graph.cpp

Node.o: Node.cpp Node.hpp
	$(CXX) -c Node.cpp

Queue.o: Queue.cpp Queue.hpp
	$(CXX) -c Queue.cpp

Algorithms.o: Algorithms.cpp Algorithms.hpp
	$(CXX) -c Algorithms.cpp

clean:
	rm -f *.o main_exe

.PHONY: all clean