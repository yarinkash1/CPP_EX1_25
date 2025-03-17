#include "graph.hpp"
#include "algorithms.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace graph;
int main() {
    graph::Graph g(5); 
    g.addEdge(0, 1, 1);
    g.addEdge(0, 4, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 1);

    g.printGraph(); // Should print something like:
    /*
    Adjacency list of vertex 0: (4, 1) -> (1, 1) -> NULL
    Adjacency list of vertex 1: (4, 1) -> (3, 1) -> (2, 1) -> (0, 1) -> NULL
    Adjacency list of vertex 2: (3, 1) -> (1, 1) -> NULL
    Adjacency list of vertex 3: (4, 1) -> (2, 1) -> (1, 1) -> NULL
    Adjacency list of vertex 4: (3, 1) -> (1, 1) -> (0, 1) -> NULL
    */
    
    cout << "BFS starting from vertex 0:" << endl;
    graph::Graph* bfs = Algorithms::bfs_scan(g, 0); 
    bfs->print_graph() // Should print 0 4 1 3 2 
    
    cout << "DFS starting from vertex 0:" << endl;
    graph::Graph* dfs = Algorithms::dfs_scan(g, 0); 
    dfs->print_graph() // Should print 0 4 3 2 1
    
    cout << "Dijkstra from 0 to 3:" << endl;
    graph::Graph* dijkstra = Algorithms::dijkstra_path(g, 0, 3); 
    dijkstra->print_graph() // Should print something like: Shortest path from 0 to 3 is: 0->4->3 with weight 2
        
    cout << Algorithms::has_cycle(g) << endl; // Should print true

    delete bfs;
    delete dfs;
    delete dijkstra;
    return 0;
}
