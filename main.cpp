#include <iostream>
#include "Graph.hpp"
using namespace std;

int main()
{
    cout<<"Hello World!\n";

    Graph graph(5); // Create a graph with 5 vertices

    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 4, 10);
    graph.addEdge(1, 2, 25);
    graph.addEdge(1, 3, -2);
    graph.addEdge(1, 4, 10);
    graph.addEdge(2, 3, 11);
    graph.addEdge(3, 4, -5);
    graph.addEdge(4, 2, -22);

    graph.print_graph();

    return 0;

    return 0;
}