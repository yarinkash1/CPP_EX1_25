#include "Node.hpp"

Node::Node(int vertex, int weight = 1) : vertex(vertex), weight(weight), next(nullptr) {} // Initializer List Constructor

int Node::getVertex() const
{
    return vertex; 
}

Node* Node::getNext() const 
{
    return next;
}

void Node::setNext(Node* newNext) 
{
    next = newNext;
}

int Node::getWeight() const 
{
     return weight; 
}

void Node::setWeight(int w)
{
    weight = w; 
}