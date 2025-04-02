#include "Graph.hpp"

Graph::Graph(int vertices) : numVertices(vertices)  // Initialize numVertices in the initializer list
{
    adjLists = new Node*[numVertices]; // Allocate array of pointers
    for (int i = 0; i < numVertices; i++) 
    {
        adjLists[i] = nullptr; // Initialize adjacency lists to nullptr
    }
}

void Graph::addEdge(int src, int dest,int weight=1) // Deafult is 1
{ 
        // Add an edge from src to dest
        Node* newNode = new Node(dest,weight);  // Step 1: Create a new node for 'dest'
        newNode->setNext(adjLists[src]); // Step 2: Point newNode to the current head of src's list
        adjLists[src] = newNode;         // Step 3: Update the head of src's list to newNode

    
        //Add an edge from dest to src for an undirected graph
        newNode = new Node(src,weight);         // Step 4: Create a new node for 'src'
        newNode->setNext(adjLists[dest]); // Step 5: Point newNode to the current head of dest's list
        adjLists[dest] = newNode;        // Step 6: Update the head of dest's list to newNode
}

void Graph::removeEdge(int src,int dest)
{
        // Remove dest from the adjacency list of src
        Node* current = adjLists[src];
        Node* prev = nullptr;
    
        while (current != nullptr)
        {
            if (current->getVertex() == dest) // Found the node to remove
            {
                if (prev == nullptr)  // If it's the first node
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

        //Remove src from the adjaceny list of dest
        current =adjLists[dest];
        prev=nullptr;

        while(current != nullptr)
        {
            if(current->getVertex() == src) // Found the node to remove
            {
                if(prev == nullptr) // If it's the first node
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
    for (int i=0;i<numVertices;i++)
    {
        cout << "Vertex " << i << ":";
        Node* temp = adjLists[i];
        while (temp!= nullptr) 
        {
            cout << "-> " << temp->getVertex() << " (weight: " << temp->getWeight() << ")";
            temp = temp->getNext();
        }
        cout << endl;
    }
}

Graph::~Graph()
{
    for (int i = 0; i < numVertices; i++) 
    {
        Node* temp = adjLists[i]; // Get the head of the linked list
        while (temp != nullptr) 
        {
            Node* toDelete = temp; // Store the current node to delete
            temp = temp->getNext(); // Move to the next node
            delete toDelete; // Free memory of the current node
        }
    }
    delete[] adjLists; // Free adjacency list array
}

int Graph::getNumVertices() const 
{
    return numVertices; 
}


Node** Graph::getAdjLists() const { return adjLists; }     // Getter for adjacency lists