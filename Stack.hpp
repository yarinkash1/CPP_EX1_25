// yarinkash1@gmail.com
#pragma once

#include <iostream>
using namespace std;

#define SIZE 100

class Stack 
{
private:
    int top;
    int arr[SIZE];

public:
    Stack();

    bool isEmpty() const;
    bool isFull() const;
    int peek() const;

    void push(int value);
    int pop();
};