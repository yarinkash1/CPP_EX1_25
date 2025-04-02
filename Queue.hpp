#pragma once

#include <iostream>
using namespace std;

#define SIZE 100

class Queue 
{
private:
    int front;
    int rear;
    int arr[SIZE];

public:
    Queue();

    bool isEmpty() const;
    bool isFull() const;
    int peek() const;

    void enqueue(int value);
    int dequeue();
};