#pragma once

#include <iostream>
#include "Node.hpp"

using namespace std;


class Graph 
{
    private:
    const int numVertices;
    Node** adjLists; // Array of adjacency lists
    
    public:
    Graph(int vertices);
    void addEdge(int src, int dest, int weight);
    void removeEdge(int src,int dest);
    void print_graph();
    ~Graph();  // Destructor declaration
    int getNumVertices() const;
    Node** getAdjLists() const;
};