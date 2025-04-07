// yarinkash1@gmail.com
#include "Stack.hpp"

    Stack::Stack()
    {
        top = -1;
    }

    bool Stack::isEmpty() const
    {
        if (top == -1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Stack::isFull() const
    {
        if (top == SIZE -1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int Stack::peek() const
    {
        if(isEmpty()==false)
        {
            return arr[top];
        }
        else
        {
            cout << "Stack is empty, Cannot peek.\n";
            return -1;
        }
    }
    void Stack::push(int value)
    {
        if(isFull()==false)
        {
            top++;
            arr[top]=value;
        }
        else
        {
            cout << "Stack is full, Cannot insert value.\n";
        }
    }

    int Stack::pop()
    {
        if(isEmpty()==false)
        {
            int val = arr[top];
            top--;
            return val;
        }
        else
        {
            cout << "Stack is empty, Cannot pop.\n";
            return -1;
        }
    }
