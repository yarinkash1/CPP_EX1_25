// yarinkash1@gmail.com
#pragma once

#include <iostream>

class Node 
{
private:
    int vertex;
    int weight;
    Node* next;

public:
    Node(int vtx,int weight);

    int getVertex() const;
    
    Node* getNext() const;

    int getWeight() const;

    void setWeight(int w);

    void setNext(Node* newNext);
};