// yarinkash1@gmail.com
#include <iostream>
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace std;

void run_bfs()
{
    Graph graph(4); // Create a graph with 4 vertices

    graph.addEdge(0, 1, 1);

    graph.addEdge(0, 2, 1);

    graph.addEdge(1, 2, 1);

    graph.addEdge(2, 3);

    graph.print_graph();

    Graph bfs_output = Algorithms::Bfs(graph, 0);
    bfs_output.print_graph();
}

void run_dfs()
{
    Graph graph(6); // Create a graph with 6 vertices

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 3);
    graph.addEdge(4, 5);

    graph.print_graph();
    Algorithms algo;
    Graph dfs_output = algo.Dfs(graph, 0);
    dfs_output.print_graph();
}

void run_dijkstra()
{
    Graph graph(4); // Create a graph with 4 vertices

    graph.addEdge(0, 1, 2);

    graph.addEdge(0, 3, 4);

    graph.addEdge(1, 3, 1);

    graph.addEdge(1, 2, 3);

    graph.addEdge(3, 2, 6);

    graph.print_graph();

    // Create an instance of Algorithms
    Algorithms algo;

    Graph dijsktra_output = algo.dijkstra(graph, 0);
    dijsktra_output.print_graph();
}

void run_kruskal()
{
    Graph graph(9); // Create a graph with 9 vertices

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 8);
    graph.addEdge(1, 2, 11);

    graph.addEdge(2, 3, 7);
    graph.addEdge(3, 4, 6);
    graph.addEdge(2, 4, 1);

    graph.addEdge(1, 5, 8);
    graph.addEdge(3, 5, 2);

    graph.addEdge(4, 6, 2);
    graph.addEdge(5, 6, 4);
    graph.addEdge(5, 7, 7);

    graph.addEdge(7, 6, 14);
    graph.addEdge(6, 8, 10);
    graph.addEdge(7, 8, 9);

    graph.print_graph();

    Graph kruskal_output = Algorithms::Kruskal(graph);
    kruskal_output.print_graph();
}

void run_prim()
{
    Graph graph(9); // Create a graph with 9 vertices

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 8);
    graph.addEdge(1, 2, 11);

    graph.addEdge(2, 3, 7);
    graph.addEdge(3, 4, 6);
    graph.addEdge(2, 4, 1);

    graph.addEdge(1, 5, 8);
    graph.addEdge(3, 5, 2);

    graph.addEdge(4, 6, 2);
    graph.addEdge(5, 6, 4);
    graph.addEdge(5, 7, 7);

    graph.addEdge(7, 6, 14);
    graph.addEdge(6, 8, 10);
    graph.addEdge(7, 8, 9);

    graph.print_graph();

    Graph prim_output = Algorithms::Prim(graph);
    prim_output.print_graph();
}
int main()
{
    cout << "Program started!\n"
         << endl;
    
         int choice;

         cout << "Choose an algorithm to run:\n";
         cout << "1. BFS\n";
         cout << "2. DFS\n";
         cout << "3. Dijkstra\n";
         cout << "4. Kruskal\n";
         cout << "5. Prim\n";
         cout << "Enter your choice (1-5): ";
         cin >> choice;
     
         switch (choice)
         {
             case 1:
                 run_bfs();
                 break;
             case 2:
                 run_dfs();
                 break;
             case 3:
                 run_dijkstra();
                 break;
             case 4:
                 run_kruskal();
                 break;
             case 5:
                 run_prim();
                 break;
             default:
                 cout << "Invalid choice." << endl;
         }

    return 0;
}