#pragma once

#include <iostream>
#include "Graph.hpp"
#include "Queue.hpp"


using namespace std;

class Algorithms
{
private:
    int* parent;   // Array to store parent of each node in BFS tree
    bool* visited; // Array to track visited nodes
    int* distance; // Array to store shortest path distances
    int num_vertices; // Store the graph size
public:
    Algorithms(int num_vertices);
    ~Algorithms();

    Graph Bfs(const Graph& G, int src_vtx); //pass by reference
};


