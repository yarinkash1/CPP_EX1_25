// yarinkash1@gmail.com
#pragma once

#include <iostream>
#include "Pair.hpp"

using namespace std;

#define SIZE 100  // Max heap capacity

class MinHeap
{
private:
    Pair heap[SIZE]; // (distance, vertex) - Fixed-size array for heap storage
    int size; // Number of elements in the heap
    
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(Pair &a, Pair &b);

public:
    MinHeap(); // Constructor
    void insert(int distance, int vertex);
    Pair extractMin();
    Pair peek() const;
    bool isEmpty() const;
    bool isFull() const;
    void printHeap() const;
    
};

