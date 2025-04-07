// yarinkash1@gmail.com
#include "Graph.hpp"

Graph::Graph(int vertices) : num_vertices(vertices) // Initialize numVertices in the initializer list
{
    adjLists = new Node *[num_vertices]; // Allocate array of pointers
    for (int i = 0; i < num_vertices; i++)
    {
        adjLists[i] = nullptr; // Initialize adjacency lists to nullptr
    }
}

////////////////////////////////////////////////////// Rule of 3: ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// Copy constructor //////////////////////////////////////////////////////
Graph::Graph(const Graph& other) : num_vertices(other.num_vertices) 
{
    adjLists = new Node*[num_vertices];
    for (int i = 0; i < num_vertices; i++) 
    {
        Node* current = other.adjLists[i];
        Node* newHead = nullptr;
        Node* tail = nullptr;
        while (current != nullptr) 
        {
            Node* copy = new Node(current->getVertex(), current->getWeight());
            if (newHead == nullptr) 
            {
                newHead = copy;
                tail = copy;
            } else 
            {
                tail->setNext(copy);
                tail = copy;
            }
            current = current->getNext();
        }
        adjLists[i] = newHead;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////// Copy assignment operator (not used) //////////////////////////////////
Graph& Graph::operator=(const Graph &other)
{
    // Self-assignment check
    if (this == &other)
        return *this;

    // First, deallocate the existing adjacency list to prevent memory leaks
    for (int i = 0; i < num_vertices; i++)
    {
        Node *temp = adjLists[i];
        while (temp != nullptr)
        {
            Node *toDelete = temp;
            temp = temp->getNext();
            delete toDelete;
        }
    }
    delete[] adjLists;

    // Allocate new adjacency list for the current object based on the 'other' graph's size
    adjLists = new Node*[other.num_vertices];
    for (int i = 0; i < other.num_vertices; i++)
    {
        adjLists[i] = nullptr;
    }

    // Copy the edges from the 'other' graph
    for (int i = 0; i < other.num_vertices; i++)
    {
        Node *temp = other.adjLists[i];
        while (temp != nullptr)
        {
            addEdge(i, temp->getVertex(), temp->getWeight());
            temp = temp->getNext();
        }
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////// Destructor ////////////////////////////////////////////////////////////////////////
Graph::~Graph()
{
    for (int i = 0; i < num_vertices; i++)
    {
        Node *temp = adjLists[i]; // Get the head of the linked list
        while (temp != nullptr)
        {
            Node *toDelete = temp;  // Store the current node to delete
            temp = temp->getNext(); // Move to the next node
            delete toDelete;        // Free memory of the current node
        }
    }
    delete[] adjLists; // Free adjacency list array
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Graph::addEdge(int src, int dest, int weight) // Deafult of weight is 1
{
    // Add an edge from src to dest
    Node *newNode = new Node(dest, weight); // Step 1: Create a new node for 'dest'
    newNode->setNext(adjLists[src]);        // Step 2: Point newNode to the current head of src's list
    adjLists[src] = newNode;                // Step 3: Update the head of src's list to newNode

    // Add an edge from dest to src for an undirected graph:
    newNode = new Node(src, weight);  // Step 4: Create a new node for 'src'
    newNode->setNext(adjLists[dest]); // Step 5: Point newNode to the current head of dest's list
    adjLists[dest] = newNode;         // Step 6: Update the head of dest's list to newNode
}

void Graph::addDirectedEdge(int src, int dest, int weight) // Deafult of weight is 1
{
    // Add an edge from src to dest
    Node *newNode = new Node(dest, weight); // Step 1: Create a new node for 'dest'
    newNode->setNext(adjLists[src]);        // Step 2: Point newNode to the current head of src's list
    adjLists[src] = newNode;                // Step 3: Update the head of src's list to newNode
}

void Graph::removeEdge(int src, int dest)
{
    // Remove dest from the adjacency list of src
    Node *current = adjLists[src];
    Node *prev = nullptr;

    while (current != nullptr)
    {
        if (current->getVertex() == dest) // Found the node to remove
        {
            if (prev == nullptr) // If it's the first node
            {
                adjLists[src] = current->getNext();
            }
            else // Otherwise, bypass it
            {
                prev->setNext(current->getNext());
            }
            delete current;
            break;
        }
        prev = current;
        current = current->getNext();
    }

    // Remove src from the adjaceny list of dest
    current = adjLists[dest];
    prev = nullptr;

    while (current != nullptr)
    {
        if (current->getVertex() == src) // Found the node to remove
        {
            if (prev == nullptr) // If it's the first node
            {
                adjLists[dest] = current->getNext();
            }
            else // otherwise, bypass it
            {
                prev->setNext(current->getNext());
            }
            delete current;
            break;
        }
        prev = current;
        current = current->getNext();
    }
}

void Graph::print_graph()
{
    for (int i = 0; i < num_vertices; i++)
    {
        cout << "Vertex " << i << ":";
        Node *temp = adjLists[i];
        while (temp != nullptr)
        {
            cout << "-> " << temp->getVertex() << " (weight: " << temp->getWeight() << ")";
            temp = temp->getNext();
        }
        cout << endl;
    }
    cout << "Print ended." << endl;
}

int Graph::getNumVertices() const
{
    return num_vertices;
}

Node **Graph::getAdjLists() const { return adjLists; } // Getter for adjacency lists

bool Graph::hasEdge(int u, int v) 
{
    Node* current = adjLists[u];
    while (current != nullptr) 
    {
        if (current->getVertex() == v) return true;
        current = current->getNext();
    }
    return false;
}

// Static method to extract edges from the graph
int Graph::getEdgesFromGraph(const Graph& graph, Edge* edges) 
{
    int index = 0;
    int numVertices = graph.getNumVertices();
    Node** adjLists = graph.getAdjLists();

    for (int i = 0; i < numVertices; i++) 
    {
        Node* current = adjLists[i];
        while (current != nullptr) 
        {
            if (i < current->getVertex()) // Avoid duplicate edges (undirected graph)
            {  
                edges[index++] = {i, current->getVertex(), current->getWeight()};
            }
            current = current->getNext();
        }
    }
    return index;  // Return the number of edges
}

// Static method for bubble sort
void Graph::bubbleSort(Edge* edges, int numEdges) 
{
    for (int i = 0; i < numEdges - 1; i++) 
    {
        for (int j = 0; j < numEdges - i - 1; j++) 
        {
            if (edges[j].weight > edges[j + 1].weight) 
            {
                // Swap the edges
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}