// yarinkash1@gmail.com
#pragma once

#include <iostream>
#include "Graph.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "MinHeap.hpp"
#include "UnionFind.hpp"

enum Color { WHITE, GRAY, BLACK };

using namespace std;

class Algorithms
{
private:
    int* parent;
    bool* visited;
    int* distance;
    // Helper functions:
    void DFSVisit(const Graph &g, Stack &my_stack, int *parent, int *color, int *discovery_time, int *finish_time, int &time, Graph &dfsTree);
    bool hasNegativeWeight(const Graph& g);
    void relax(int u, int v, int weight, int* distance, int* parent, MinHeap &heap);
    void printShortestPathTree(int src, const int *parent, const int *distance, const Graph &g);

public:
    Algorithms();
    ~Algorithms();

    // Pass by reference:
    static Graph Bfs(const Graph& G, int src_vtx);
    Graph Dfs(const Graph& G,int src_vtx);
    Graph dijkstra(const Graph& g, int src_vtx);

    static Graph Prim(const Graph& g);
    static Graph Kruskal(const Graph& g);
};


