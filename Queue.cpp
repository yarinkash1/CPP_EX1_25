#include "Queue.hpp"

    Queue::Queue()
    {
        front=-1;
        rear=-1;
    }

    bool Queue::isEmpty() const
    {
        if(front==-1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Queue::isFull() const
    {
        if(rear == SIZE -1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int Queue::peek() const
    {
        if(isEmpty()==false)
        {
            return arr[front];
        }
        else
        {
            cout << "Queue is empty, cannot peek.";
            return -1;
        }
    }

    void Queue::enqueue(int value)
    {
        if(isFull()==false)
        {
            if(isEmpty()==true)
            {
                front=0;
            }
            rear++;
            arr[rear]=value;
        }
        else
        {
            cout << "Queue is full, cannot enqueue";
        }
    }

    int Queue::dequeue()
    {
        if(isEmpty()==false)
        {
            int val = arr[front];
            if(front==rear) //Dequeueing last element
            { 
                front=-1;
                rear=-1;
                return val;
            }

            front++;
            return val;
        }
        else
        {
            cout << "Queue is empty, cannot dequeue";
            return -1;
        }

    }


