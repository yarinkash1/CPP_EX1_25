// yarinkash1@gmail.com
#include "Algorithms.hpp"
#include <climits>

Algorithms::Algorithms() {}

Algorithms::~Algorithms() {}

Graph Algorithms::Bfs(const Graph &g, int src_vtx)
{
    Queue q;                               // Create a new queue for the BFS algo.
    int num_vertices = g.getNumVertices(); // Get the number of vertives form the graph g we got as an input.

    // Allocate and initialize tracking arrays
    int *parent = new int[num_vertices];
    bool *visited = new bool[num_vertices];
    int *distance = new int[num_vertices];

    for (int i = 0; i < num_vertices; i++)
    {
        parent[i] = -1;        // Default parent is -1 (no parent)
        visited[i] = false;    // Default is unvisited
        distance[i] = INT_MAX; // Default is "infinity"
    }

    // Start BFS from the source vertex
    q.enqueue(src_vtx);
    visited[src_vtx] = true;
    distance[src_vtx] = 0;
    parent[src_vtx] = -1;

    while (q.isEmpty() == false)
    {
        int node = q.dequeue();             // Dequeue current vertex
        Node *temp = g.getAdjLists()[node]; // Get adjacency list of vertex

        while (temp != nullptr) // Iterate over each neighbor
        {
            int neighbor = temp->getVertex();
            if (visited[neighbor]==false) // If neighbor isn't visited
            {
                visited[neighbor] = true;
                parent[neighbor] = node;
                distance[neighbor] = distance[node] + 1; // BFS assumes unit weights
                q.enqueue(neighbor);
            }
            temp = temp->getNext(); // Move to next neighbor
        }
    }

    // Construct BFS tree
    Graph bfsTree(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        if (parent[i] != -1) // If vertex has a parent, add it to the tree
        {
            bfsTree.addEdge(parent[i], i, 1);
        }
    }

    // Clean up
    delete[] parent;
    delete[] visited;
    delete[] distance;

    return bfsTree;
}

Graph Algorithms::Dfs(const Graph &g, int src_vtx)
{
    int num_vertices = g.getNumVertices(); // Get the number of vertives form the graph g we got as an input.
    Graph dfsTree(num_vertices);           // Create an empty graph for the DFS tree
    Stack my_stack;                        // Create a new stack for the DFS algo.

    // Allocate and initialize tracking arrays
    int *parent = new int[num_vertices];
    int *color = new int[num_vertices]; // WHITE (0), GRAY (1), BLACK (2)
    int *discovery_time = new int[num_vertices];
    int *finish_time = new int[num_vertices];

    int time = 0; // Global time counter

    // Initialize arrays
    for (int i = 0; i < num_vertices; i++)
    {
        parent[i] = -1;         // Default parent is -1
        color[i] = WHITE;       // Default is WHITE (unvisited)
        discovery_time[i] = 0; // Defult discovery-time is -1
        finish_time[i] = 0;    // Deafult finish-time is -1
    }

    my_stack.push(src_vtx);           // Add the source vertex to the queue
    color[src_vtx] = GRAY;            // Mark source as GRAY (discovered)
    discovery_time[src_vtx] = ++time; // Add 1 unit of time and assign it to the discovery-time of the source vertex

    // Start DFS from the given source
    DFSVisit(g, my_stack, parent, color, discovery_time, finish_time, time, dfsTree);

    // Handle any disconnected components
    for (int i = 0; i < num_vertices; i++)
    {
        if (color[i] == WHITE)
        {
            my_stack.push(i);
            color[i] = GRAY;            // Mark source as GRAY (discovered)
            discovery_time[i] = ++time; // Add 1 unit of time and assign it to the discovery-time of the source vertex
            DFSVisit(g, my_stack, parent, color, discovery_time, finish_time, time, dfsTree);
        }
    }

    // Print discovery and finish times
    std::cout << "Vertex Discovery Time Finish Time\n";
    for (int i = 0; i < num_vertices; i++)
    {
        std::cout << i << "        " << discovery_time[i] << "                " << finish_time[i] << "\n";
    }

    delete[] parent;
    delete[] color;
    delete[] discovery_time;
    delete[] finish_time;

    return dfsTree;
}

void Algorithms::DFSVisit(const Graph &g, Stack &my_stack, int *parent, int *color, int *discovery_time, int *finish_time, int &time, Graph &dfsTree)
{
    while (my_stack.isEmpty() == false)
    {
        int v = my_stack.pop();
        Node *temp = g.getAdjLists()[v];

        while (temp != nullptr)
        {
            int neighbor = temp->getVertex();

            if (color[neighbor] == WHITE) // If WHITE, it's a tree edge
            {
                color[neighbor] = GRAY;            // Mark as GRAY
                discovery_time[neighbor] = ++time; // Add 1 unit of time and assign it to the discovery-time of the neighbor vertex
                parent[neighbor] = v;
                dfsTree.addEdge(v, neighbor, 1);
                my_stack.push(neighbor);
                DFSVisit(g,my_stack,parent,color,discovery_time,finish_time,time,dfsTree);
            }
            temp=temp->getNext();
        }
        color[v] = BLACK;        // Mark node as BLACK (fully explored)
        finish_time[v] = ++time; // Add 1 unit of time and assign it to the finish-time of a vertex we finished exploring
    }
}

Graph Algorithms::dijkstra(const Graph &g, int src_vtx)
{
    int num_vertices = g.getNumVertices();
    Graph weighted_tree_of_shortest_paths(num_vertices);
    MinHeap my_min_heap; // Create a new min heap for the Dijsktra's algo.

    if (hasNegativeWeight(g) == true)
    {
        cout << "Error: Graph contains negative weight edges. Dijkstra's algorithm cannot be used." << endl;
        return Graph(g.getNumVertices()); // Return an empty graph
    }

    // Allocate and initialize tracking arrays
    int *parent = new int[num_vertices];    // Parent array for path reconstruction
    bool *visited = new bool[num_vertices]; // Visited array
    int *distance = new int[num_vertices];  // Distance array

    for (int i = 0; i < num_vertices; i++)
    {
        parent[i] = -1;        // Default parent is -1 (no parent)
        visited[i] = false;    // Default is unvisited
        distance[i] = INT_MAX; // Default is "infinity"
    }

    distance[src_vtx] = 0;          // Distance to source is 0
    my_min_heap.insert(0, src_vtx); // Insert the source with distance 0

    // Main loop:
    while (my_min_heap.isEmpty() == false)
    {
        Pair min = my_min_heap.extractMin();
        int u = min.second;

        if (visited[u] == true)
            continue; // Skip if already processed(enter the loop again with the next u in the minheap)
        visited[u] = true;

        // Explore all neighbors of u
        Node *temp = g.getAdjLists()[u];
        while (temp != nullptr)
        {
            int v = temp->getVertex();
            int weight = temp->getWeight();

            // Call the relax function to update distances and parents if needed
            relax(u, v, weight, distance, parent, my_min_heap);

            temp = temp->getNext();
        }
    }


    for (int v = 0; v < num_vertices; v++)
    {
        if (parent[v] != -1)
        {
            int u = parent[v];
            // Find weight of edge (u, v) from original graph:
            Node *temp = g.getAdjLists()[u];
            while (temp != nullptr && temp->getVertex() != v) // Traverse the adjacency list of u until we find v:
            {
                temp = temp->getNext();
            }
            if (temp != nullptr) // Found the the node v in u's adjaceny list:
            {
                int weight = temp->getWeight();                        // Extract the weight
                weighted_tree_of_shortest_paths.addDirectedEdge(u, v, weight);  // Add the edge (u, v) with that weight into the new shortest-path tree.
            }
        }
    }

    // Print the shortest-path tree (after Dijkstra has finished)
    printShortestPathTree(src_vtx, parent, distance, g);

    // Clean up
    delete[] parent;
    delete[] visited;
    delete[] distance;

    return weighted_tree_of_shortest_paths;
}

bool Algorithms::hasNegativeWeight(const Graph &g)
{
    int num_vertices = g.getNumVertices();

    for (int i = 0; i < num_vertices; i++) // Iterate over all adjacency lists
    {
        Node *temp = g.getAdjLists()[i]; // Get adjacency list of vertex i
        while (temp != nullptr)          // Traverse edges (nodes in adjacency list)
        {
            if (temp->getWeight() < 0) // Check if weight is negative
            {
                return true; // Found a negative weight, return true
            }
            temp = temp->getNext(); // Move to next edge
        }
    }

    return false; // No negative weights found
}

void Algorithms::relax(int u, int v, int weight, int *distance, int *parent, MinHeap &heap)
{
    if (distance[u] + weight < distance[v])
    {
        distance[v] = distance[u] + weight;
        parent[v] = u;
        heap.insert(distance[v], v);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::printShortestPathTree(int src, const int *parent, const int *distance, const Graph &g)
{
    cout << "Weighted Shortest Path Tree from vertex " << src << ":\n";
    for (int i = 0; i < g.getNumVertices(); i++)
    {
        if (i != src && parent[i] != -1)
        {
            // Print the edge from parent[i] to i with the distance and weight
            cout << "Vertex " << i << " -> Distance: " << distance[i]
                 << " (Parent: " << parent[i] << ", Weight: ";
            
            Node *temp = g.getAdjLists()[parent[i]];
            while (temp != nullptr && temp->getVertex() != i)
            {
                temp = temp->getNext();
            }
            if (temp != nullptr)
            {
                cout << temp->getWeight();
            }

            cout << ")\n";
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Graph Algorithms::Prim(const Graph &g)
{
    int num_vertices = g.getNumVertices();
    // Create a result graph (MST)
    Graph mst(num_vertices);

    MinHeap my_min_heap; // Create a new min heap for the Prim's algo.

    // Allocate and initialize tracking arrays
    int *parent = new int[num_vertices];    // Parent array for path reconstruction
    bool *visited = new bool[num_vertices]; // Visited array
    int *distance = new int[num_vertices];  // Distance array

    for (int i = 0; i < num_vertices; i++)
    {
        parent[i] = -1;        // Default parent is -1 (no parent)
        visited[i] = false;    // Default is unvisited
        distance[i] = INT_MAX; // Default is "infinity"
    }

    int start_vertex = 0;       // Pick the first vertex
    distance[start_vertex] = 0; // Set the starting vertex's distance to 0
    // *The starting vertex's parent is -1 because of the initialization at the start
    my_min_heap.insert(0, start_vertex); // Insert the starting vertex into the min heap

    while (my_min_heap.isEmpty() == false)
    {
        Pair current = my_min_heap.extractMin(); // Extract the vertex with the minimum distance
        int u = current.second; // Get the vertex (u) from the extracted pair
        if (visited[u]) continue;
        visited[u] = true; // Mark the vertex as visited

        // Add the vertex to the MST:
        if (parent[u] != -1) // Avoid adding the first vertex (no parent)
        {
            if (!mst.hasEdge(parent[u], u)) 
            {
                mst.addEdge(parent[u], u, distance[u]);
            }
        }
        // Update the distances of adjacent vertices:
        Node *current_node = g.getAdjLists()[u]; // Get the adjacency list of u
        while (current_node != nullptr)          // Iterate the neighbors
        {
            int v = current_node->getVertex();      // Get the adjacent vertex v
            int weight = current_node->getWeight(); // Get the weight of the edge (u, v)

            // If vertex v is not visited and the weight is less than the current distance
            if (visited[v] == false && weight < distance[v])
            {
                // Update the distance and parent of vertex v:
                parent[v] = u;
                distance[v] = weight;

                my_min_heap.insert(distance[v], v); // Insert the vertex with updated distance
            }

            current_node = current_node->getNext();
        }
    }

        // Clean up dynamically allocated memory:
        delete[] parent;
        delete[] visited;
        delete[] distance;

        return mst; // Return the MST
    }

Graph Algorithms::Kruskal(const Graph &graph)
    {
        int numEdges = graph.getNumVertices() * (graph.getNumVertices() - 1) / 2;  // Maximum number of edges in a fully connected graph
        Edge* edges = new Edge[numEdges];  // Temporary array to hold edges
    
        // Extract edges from the graph using Graph's static function
        int edgeCount = Graph::getEdgesFromGraph(graph, edges);
    
        // Sort edges by weight using Graph's static bubbleSort function
        Graph::bubbleSort(edges, edgeCount);
    
        // Create a new Graph for the MST
        Graph mst(graph.getNumVertices());  // Initialize MST with the same number of vertices
    
        // Union-Find (or other algorithm) to form MST
        UnionFind uf(graph.getNumVertices());  // Assuming UnionFind class is implemented for Kruskal's algorithm
    
        for (int i = 0; i < edgeCount; i++) {
            int u = edges[i].src;
            int v = edges[i].dest;
            if (uf.find(u) != uf.find(v)) {
                uf.union_sets(u, v);
                mst.addEdge(u, v, edges[i].weight);  // Add the edge to the MST
            }
        }
    
        delete[] edges;  // Clean up dynamically allocated memory
    
        return mst;  // Return the MST
    }



