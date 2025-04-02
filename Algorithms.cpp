#include "Algorithms.hpp"
#include <climits>

Algorithms::Algorithms(int num_vertices)
{
    parent = new int[num_vertices];
    visited = new bool[num_vertices];
    distance = new int[num_vertices];

    for(int i=0;i<num_vertices;i++)
    {
        parent[i]=-1; // Deafult is -1
        visited[i]=false; // Deafult is false
        distance[i] = INT_MAX; // Deafult is infinity
    }
}

Algorithms::~Algorithms()
{
    delete[] parent;
    delete[] visited;
    delete[] distance;
}

Graph Algorithms::Bfs(const Graph& g,int src_vtx)
{
    Queue q;// Create a new queue for the BFS algo.
    int num_vertices = g.getNumVertices(); // Get the number of vertives form the graph g we got as an input.

    //Add the source vertex to the queue and set it's values accordingly.
    q.enqueue(src_vtx);
    parent[src_vtx]=-1;
    visited[src_vtx]=true;
    distance[src_vtx]=0;

    while(q.isEmpty()==false)
    {
        int node = q.dequeue(); // Dequeue the current vertex
        Node* temp = g.getAdjLists()[node]; // Get adjacency list of vertex

        while(temp!=nullptr) // Iterate over each neighbor
        {
            int neighbor = temp->getVertex();
            if(visited[neighbor]==false) // If the neighbor isn't visited
            {
                visited[neighbor]=true; // Set the neighbor to visited
                parent[neighbor]=node; // Set the parent of the neighbor to the vertex we got to it from
                distance[neighbor]=distance[node] + 1; // All the weights in BFS are 1 so we add only one to the distance
                q.enqueue(neighbor); // Add the neighbor to the queue
            }
            temp=temp->getNext(); // Move to the next vertex in the adjacency list
        }
    }

        // Construct BFS tree:
        Graph bfsTree(num_vertices); // Create another graph with the number of vertices from the original graph
        for (int i = 0; i < num_vertices; i++) // Iterate over all of the vertices
        {
            if (parent[i] != -1)  // if the vertex has a parent
            {
                bfsTree.addEdge(parent[i], i, 1); // Add edge to BFS tree. Format: (source,destination,weight)
            }
        }

        return bfsTree;
}

