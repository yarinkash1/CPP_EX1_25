#pragma once

#include <iostream>
#include <utility> // For std::pair

using namespace std;

#define SIZE 100  // Max heap capacity

class MinHeap
{
private:
    pair<int, int> heap[SIZE]; //  (distance, vertex) - Fixed-size array for heap storage
    int size;       // Number of elements in the heap
    
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(pair<int, int> &a, pair<int, int> &b);

public:
    MinHeap(); // Constructor
    void insert(int distance, int vertex);
    pair<int, int> extractMin();
    pair<int, int> peek() const;
    bool isEmpty() const;
    bool isFull() const;
    void printHeap() const;
    
};

