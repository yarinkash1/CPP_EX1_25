// yarinkash1@gmail.com
#include "MinHeap.hpp"

    MinHeap::MinHeap()
    {
        size=0;
    }
    
    void MinHeap::heapifyUp(int index)
    {
        while (index > 0) // Continue until root
        { 
            int parentIndex = (index - 1) / 2;
    
            if (heap[index].first < heap[parentIndex].first) // Swap if child is smaller in distance
            { 
                swap(heap[index], heap[parentIndex]);
                index = parentIndex; // Move up
            }
            else
            {
                break; // Heap property restored
            }
        }
    }

    void MinHeap::heapifyDown(int index)
    {
        int smallest = index; 
        int leftChild = 2 * index + 1; 
        int rightChild = 2 * index + 2; 
    
        // Check if left child is smaller than current smallest in terms of distance
        if ( (leftChild < size) && (heap[leftChild].first < heap[smallest].first) ) 
        {
            smallest = leftChild;
        }
    
        // Check if right child is smaller than the current smallest in terms of distance
        if ( (rightChild < size) && (heap[rightChild].first < heap[smallest].first) ) 
        {
            smallest = rightChild;
        }
    
        // If the smallest element is not the parent, swap and continue heapifying down
        if (smallest != index)
        {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest); // Recursively fix the subtree
        }
    }

    void MinHeap::swap(Pair &a, Pair &b)
    {
        Pair temp = a;
        a=b;
        b=temp;
    }

    void MinHeap::insert(int distance, int vertex)
    {
        if (isFull()==true) 
        {
            cout << "Heap is full" << endl;
        }
    
        heap[size] = {distance, vertex}; // Store pair (distance, vertex)
        heapifyUp(size);    // Restore heap property
        size++;             // Increase heap size
    }

    Pair MinHeap::extractMin()
    {
        if (isEmpty()) 
        {
            cout << "Heap is empty" << endl; // Handle empty heap
        }
    
        Pair minValue = heap[0]; // Get min element (smallest distance)
        heap[0] = heap[size - 1]; // Move the last element to the root
        size--; // Decrease the size of the heap
    
        heapifyDown(0); // Restore the heap property
    
        return minValue;
    }

    Pair MinHeap::peek() const
    {
        if (isEmpty()==true) 
        {
            cout << "Heap is empty" << endl;
        }
        return heap[0];
    }

    bool MinHeap::isEmpty() const
    {
        return size<=0;
    }

    bool MinHeap::isFull() const
    {
        return size>=SIZE;
    }

    void MinHeap::printHeap() const
    {
        if (isEmpty())
         {
            cout << "Heap is empty." << endl;
            return;
        }
    
        for (int i = 0; i < size; i++) 
        {
            cout << "(" << heap[i].first << ", " << heap[i].second << ") ";
        }
        cout << endl;
    }
