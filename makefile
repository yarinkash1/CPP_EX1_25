# yarinkash1@gmail.com
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++2a
TARGET = main_exe
TEST_TARGET = test_exe

all: $(TARGET)

test: $(TEST_TARGET)

$(TARGET): main.o Graph.o Node.o Queue.o Stack.o Algorithms.o MinHeap.o Pair.o UnionFind.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o Graph.o Node.o Queue.o Stack.o Algorithms.o MinHeap.o Pair.o UnionFind.o

$(TEST_TARGET): algoTests.o Graph.o Node.o Queue.o Stack.o Algorithms.o MinHeap.o Pair.o UnionFind.o
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) algoTests.o Graph.o Node.o Queue.o Stack.o Algorithms.o MinHeap.o Pair.o UnionFind.o


main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Graph.o: Graph.cpp Graph.hpp Node.hpp
	$(CXX) $(CXXFLAGS) -c Graph.cpp

Node.o: Node.cpp Node.hpp
	$(CXX) $(CXXFLAGS) -c Node.cpp

Queue.o: Queue.cpp Queue.hpp
	$(CXX) $(CXXFLAGS) -c Queue.cpp

Stack.o: Stack.cpp Stack.hpp
	$(CXX) $(CXXFLAGS) -c Stack.cpp

Algorithms.o: Algorithms.cpp Algorithms.hpp Graph.hpp Queue.hpp Stack.hpp MinHeap.hpp UnionFind.hpp
	$(CXX) $(CXXFLAGS) -c Algorithms.cpp

MinHeap.o: MinHeap.cpp MinHeap.hpp Pair.hpp
	$(CXX) $(CXXFLAGS) -c MinHeap.cpp

Pair.o: Pair.cpp Pair.hpp
	$(CXX) $(CXXFLAGS) -c Pair.cpp

UnionFind.o: UnionFind.cpp UnionFind.hpp
	$(CXX) $(CXXFLAGS) -c UnionFind.cpp

algoTests.o: algoTests.cpp Graph.hpp Algorithms.hpp doctest.h
	$(CXX) $(CXXFLAGS) -c algoTests.cpp

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET)



clean:
	rm -f *.o main_exe test_exe

.PHONY: all clean valgrind