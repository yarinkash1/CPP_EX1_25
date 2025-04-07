// yarinkash1@gmail.com
#pragma once

#include <iostream>
#include "Node.hpp"

using namespace std;

// Edge is intended to be a simple data structure thus we are using a struct and not a class
struct Edge
{
    int src, dest, weight;  // Structure to store edge details
};

class Graph 
{
    private:
    const int num_vertices;
    Node** adjLists; // Array of adjacency lists
    
    public:
    Graph(int vertices);
////////////////////////////// Rule of 3 ///////////////////////////
    Graph(const Graph& other);  // Copy constructor
    Graph& operator=(const Graph &other);  // Copy assignment operator (not used)
    ~Graph();  // Destructor declaration
///////////////////////////////////////////////////////////////////
    void addEdge(int src, int dest, int weight = 1);
    void addDirectedEdge(int src, int dest, int weight);
    void removeEdge(int src,int dest);
    void print_graph();
    int getNumVertices() const;
    Node** getAdjLists() const;
    bool hasEdge(int u, int v);
    static int getEdgesFromGraph(const Graph& graph, Edge* edges);
    static void bubbleSort(Edge* edges, int numEdges);
};