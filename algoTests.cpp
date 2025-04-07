// yarinkash1@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>

// Helper function to check if two graphs have the same edges
bool areGraphsEqual(const Graph &g1, const Graph &g2)
{
    int n = g1.getNumVertices();
    if (n != g2.getNumVertices())
        return false;

    Node **adj1 = g1.getAdjLists();
    Node **adj2 = g2.getAdjLists();

    // Use simple arrays to track edges in both directions
    bool **visited1 = new bool *[n];
    bool **visited2 = new bool *[n];
    for (int i = 0; i < n; ++i)
    {
        visited1[i] = new bool[n]();
        visited2[i] = new bool[n]();
    }

    // Compare edges
    for (int i = 0; i < n; ++i)
    {
        Node *cur1 = adj1[i];
        while (cur1)
        {
            int u = i, v = cur1->getVertex();
            if (u > v)
                std::swap(u, v); // Always store smaller first
            visited1[u][v] = true;
            cur1 = cur1->getNext();
        }

        Node *cur2 = adj2[i];
        while (cur2)
        {
            int u = i, v = cur2->getVertex();
            if (u > v)
                std::swap(u, v); // Always store smaller first
            visited2[u][v] = true;
            cur2 = cur2->getNext();
        }
    }

    // Check if all edges in g1 are present in g2
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (visited1[i][j] != visited2[i][j])
            {
                delete[] visited1;
                delete[] visited2;
                return false;
            }
        }
    }

    delete[] visited1;
    delete[] visited2;
    return true;
}

TEST_CASE("BFS builds correct tree")
{
    Graph input(4);
    input.addEdge(0, 1, 1);
    input.addEdge(0, 2, 1);
    input.addEdge(1, 2, 1);
    input.addEdge(2, 3);

    Graph expected(4);
    expected.addEdge(0, 1, 1);
    expected.addEdge(0, 2, 1);
    expected.addEdge(2, 3, 1);

    Graph output = Algorithms::Bfs(input, 0);
    CHECK(areGraphsEqual(output, expected));
}

TEST_CASE("DFS build correct tree/forest")
{
    Graph input(6);

    input.addEdge(0, 1);
    input.addEdge(0, 2);
    input.addEdge(0, 3);
    input.addEdge(1, 3);
    input.addEdge(4, 5);

    // Adjust the expected edges based on DFS traversal order:
    Graph expected(6);
    expected.addEdge(0, 2); // DFS explores 0 -> 2 first
    expected.addEdge(0, 3); // DFS explores 0 -> 3 next
    expected.addEdge(1, 3); // DFS goes to 1 -> 3
    expected.addEdge(4, 5); // DFS visits 4 -> 5

    // Run DFS starting from vertex 0
    Algorithms algo;
    Graph dfs_output = algo.Dfs(input, 0);

    // Check if the output matches the expected graph
    CHECK(areGraphsEqual(dfs_output, expected));
}

TEST_CASE("Dijkstra builds correct tree")
{
    Graph input(4); // Create a graph with 4 vertices

    input.addEdge(0, 1, 2);

    input.addEdge(0, 3, 4);

    input.addEdge(1, 3, 1);

    input.addEdge(1, 2, 3);

    input.addEdge(3, 2, 6);

    Graph expected(4);
    expected.addEdge(0, 1, 2);
    expected.addEdge(1, 3, 1);
    expected.addEdge(1, 2, 3);

    // Create an instance of Algorithms
    Algorithms algo;
    Graph dijsktra_output = algo.dijkstra(input, 0);

    // Check if the output matches the expected graph
    CHECK(areGraphsEqual(dijsktra_output, expected));
}

TEST_CASE("Kruskal builds correct mst")
{
    Graph input(9);

    input.addEdge(0, 1, 4);
    input.addEdge(0, 2, 8);
    input.addEdge(1, 2, 11);

    input.addEdge(2, 3, 7);
    input.addEdge(3, 4, 6);
    input.addEdge(2, 4, 1);

    input.addEdge(1, 5, 8);
    input.addEdge(3, 5, 2);

    input.addEdge(4, 6, 2);
    input.addEdge(5, 6, 4);
    input.addEdge(5, 7, 7);

    input.addEdge(7, 6, 14);
    input.addEdge(6, 8, 10);
    input.addEdge(7, 8, 9);

    Graph expected(9);
    expected.addEdge(0, 1, 4);
    expected.addEdge(0, 2, 8);
    expected.addEdge(2, 4, 1);
    expected.addEdge(4, 6, 2);
    expected.addEdge(6, 5, 4);
    expected.addEdge(5, 3, 2);
    expected.addEdge(5, 7, 7);
    expected.addEdge(7, 8, 9);

    Graph kruskal_output = Algorithms::Kruskal(input);
    CHECK(areGraphsEqual(kruskal_output, expected));
}

TEST_CASE("Prim builds correct mst")
{
    Graph input(9);

    input.addEdge(0, 1, 4);
    input.addEdge(0, 2, 8);
    input.addEdge(1, 2, 11);

    input.addEdge(2, 3, 7);
    input.addEdge(3, 4, 6);
    input.addEdge(2, 4, 1);

    input.addEdge(1, 5, 8);
    input.addEdge(3, 5, 2);

    input.addEdge(4, 6, 2);
    input.addEdge(5, 6, 4);
    input.addEdge(5, 7, 7);

    input.addEdge(7, 6, 14);
    input.addEdge(6, 8, 10);
    input.addEdge(7, 8, 9);

    Graph expected(9);
    expected.addEdge(0, 1, 4);
    expected.addEdge(0, 2, 8);
    expected.addEdge(2, 4, 1);
    expected.addEdge(4, 6, 2);
    expected.addEdge(5, 3, 2);
    expected.addEdge(6, 5, 4);
    expected.addEdge(5, 7, 7);
    expected.addEdge(7, 8, 9);

    Graph prim_output = Algorithms::Prim(input);
    CHECK(areGraphsEqual(prim_output, expected));
}

TEST_CASE("Pair default constructor")
{
    Pair p;
    CHECK(p.first == 0);
    CHECK(p.second == 0);
}

TEST_CASE("Pair parameterized constructor")
{
    Pair p(7, 42);
    CHECK(p.first == 7);
    CHECK(p.second == 42);
}

TEST_CASE("Pair comparison operators")
{
    Pair a(3, 1);
    Pair b(5, 9);
    Pair c(3, 99);

    CHECK(a < b);       // 3 < 5
    CHECK(b > a);       // 5 > 3
    CHECK_FALSE(a < c); // 3 is not < 3
    CHECK_FALSE(a > c); // 3 is not > 3
}

TEST_CASE("Stack basic push/pop/peek")
{
    Stack s;

    // Test pushing and peeking
    CHECK(s.isEmpty());
    CHECK_FALSE(s.isFull());

    s.push(10);
    CHECK_FALSE(s.isEmpty());
    CHECK(s.peek() == 10);

    s.push(20);
    CHECK(s.peek() == 20);

    // Test popping
    int val1 = s.pop();
    CHECK(val1 == 20);
    CHECK(s.peek() == 10);

    int val2 = s.pop();
    CHECK(val2 == 10);
    CHECK(s.isEmpty());
}

TEST_CASE("Stack error messages on invalid operations")
{
    Stack s;
    std::stringstream buffer;                              // Create a stringstream buffer to capture cout
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf()); // Redirect cout to buffer

    // Test popping from an empty stack
    s.pop();
    CHECK(buffer.str() == "Stack is empty, Cannot pop.\n");

    // Clear the buffer before the next test
    buffer.str("");
    buffer.clear();

    // Test peeking from an empty stack
    s.peek();
    CHECK(buffer.str() == "Stack is empty, Cannot peek.\n");

    // Test pushing to a full stack
    for (int i = 0; i < SIZE; ++i)
    {
        s.push(i);
    }
    buffer.str(""); // Clear the buffer before the next test
    s.push(100);
    CHECK(buffer.str() == "Stack is full, Cannot insert value.\n");

    // Restore the original cout stream
    std::cout.rdbuf(old);
}

TEST_CASE("Queue basic enqueue/dequeue/peek") 
{
    Queue q;

    // Test enqueue and peek
    CHECK(q.isEmpty());
    CHECK_FALSE(q.isFull());

    q.enqueue(10);
    CHECK_FALSE(q.isEmpty());
    CHECK(q.peek() == 10);

    q.enqueue(20);
    CHECK(q.peek() == 10);  // The first element should still be 10

    // Test dequeue
    int val1 = q.dequeue();
    CHECK(val1 == 10);  // Dequeue should return 10, the first element
    CHECK(q.peek() == 20);  // Now the front of the queue is 20

    int val2 = q.dequeue();
    CHECK(val2 == 20);  // Dequeue should return 20
    CHECK(q.isEmpty());  // The queue should now be empty
}

TEST_CASE("Queue error messages on invalid operations") 
{
    Queue q;
    
    // Test dequeuing from an empty queue
    {
        std::streambuf* old_buf = std::cout.rdbuf(); // Save old buffer
        std::stringstream buffer;
        std::cout.rdbuf(buffer.rdbuf()); // Redirect std::cout to stringstream

        q.dequeue();
        CHECK(buffer.str() == "Queue is empty, cannot dequeue");

        buffer.str("");  // Clear the buffer before the next test
        buffer.clear();

        // Test peeking from an empty queue
        q.peek();
        CHECK(buffer.str() == "Queue is empty, cannot peek.");

        // Test enqueueing to a full queue
        for (int i = 0; i < SIZE; ++i) 
        {
            q.enqueue(i);
        }
        buffer.str("");  // Clear the buffer before the next test
        q.enqueue(555);
        CHECK(buffer.str() == "Queue is full, cannot enqueue");

        std::cout.rdbuf(old_buf); // Restore the original std::cout buffer
    }
}

TEST_CASE("Node constructor and getters") 
{
    // Create a Node with vertex 1 and weight 10
    Node node(1, 10);

    // Test getters
    CHECK(node.getVertex() == 1);
    CHECK(node.getWeight() == 10);
}

TEST_CASE("Node setters") 
{
    // Create a Node with initial vertex 1 and weight 10
    Node node(1, 10);

    // Test setter for weight
    node.setWeight(20);
    CHECK(node.getWeight() == 20);  // The weight should be updated to 20

    // Test setter for next node
    Node* nextNode = new Node(2, 30);
    node.setNext(nextNode);
    CHECK(node.getNext() == nextNode);  // The next node should now be set to nextNode
}

TEST_CASE("Node next pointer") 
{
    // Create two nodes and link them using the next pointer
    Node node1(1, 10);
    Node node2(2, 20);

    // Initially, node1's next should be nullptr
    CHECK(node1.getNext() == nullptr);

    // Set node1's next to node2 and check the link
    node1.setNext(&node2);
    CHECK(node1.getNext() == &node2);  // node1's next should point to node2
}

TEST_CASE("UnionFind initialization and find") 
{
    // Create a UnionFind instance with 5 elements
    UnionFind uf(5);

    // Initially, all elements should be their own parent
    CHECK(uf.find(0) == 0);
    CHECK(uf.find(1) == 1);
    CHECK(uf.find(2) == 2);
    CHECK(uf.find(3) == 3);
    CHECK(uf.find(4) == 4);
}

TEST_CASE("UnionFind union and find") 
{
    UnionFind uf(5);

    // Union sets 0 and 1, and 2 and 3
    uf.union_sets(0, 1);
    uf.union_sets(2, 3);

    // After union, 0 and 1 should be in the same set
    CHECK(uf.find(0) == uf.find(1));

    // 2 and 3 should also be in the same set
    CHECK(uf.find(2) == uf.find(3));

    // But 0 and 2 should be in different sets
    CHECK(uf.find(0) != uf.find(2));
}

TEST_CASE("UnionFind path compression") 
{
    UnionFind uf(5);

    // Union sets 0, 1, and 2
    uf.union_sets(0, 1);
    uf.union_sets(1, 2);

    // Path compression should have occurred
    // After union, find(2) should directly lead to 0
    CHECK(uf.find(2) == uf.find(0));

    // Ensuring find works after compression
    CHECK(uf.find(1) == uf.find(0));
}

TEST_CASE("UnionFind with multiple unions") 
{
    UnionFind uf(6);

    // Union different sets
    uf.union_sets(0, 1);
    uf.union_sets(2, 3);
    uf.union_sets(4, 5);

    // After multiple unions, 0 and 1 should be in the same set
    CHECK(uf.find(0) == uf.find(1));

    // 2 and 3 should be in the same set
    CHECK(uf.find(2) == uf.find(3));

    // 4 and 5 should be in the same set
    CHECK(uf.find(4) == uf.find(5));

    // But 0 and 2 should be in different sets
    CHECK(uf.find(0) != uf.find(2));

    // 2 and 4 should also be in different sets
    CHECK(uf.find(2) != uf.find(4));
}

TEST_CASE("UnionFind destruction") 
{
    // Ensure that the UnionFind instance is properly destroyed
    CHECK_NOTHROW({
        UnionFind uf(10);  // Create a UnionFind instance with 10 elements
    });  // It should not throw anything during destruction
}

TEST_CASE("MinHeap Initialization and Insertion") 
{
    MinHeap minHeap;

    // Inserting pairs (5, 0), (3, 1), and (8, 2)
    minHeap.insert(5, 0);
    minHeap.insert(3, 1);
    minHeap.insert(8, 2);

    // Check the size of the heap (should be 3 after 3 insertions)
    CHECK(minHeap.isFull() == false);

    // Peek should return the minimum element (3, 1) after insertion
    Pair p = minHeap.peek();
    CHECK(p.first == 3);
    CHECK(p.second == 1);
}

TEST_CASE("MinHeap Extract Min") 
{
    MinHeap minHeap;

    // Insert some elements
    minHeap.insert(5, 0);
    minHeap.insert(3, 1);
    minHeap.insert(8, 2);
    minHeap.insert(1, 3);

    // Extract the minimum element (should be (1, 3))
    Pair minPair = minHeap.extractMin();
    CHECK(minPair.first == 1);
    CHECK(minPair.second == 3);

    // After extraction, the next minimum should be (3, 1)
    minPair = minHeap.extractMin();
    CHECK(minPair.first == 3);
    CHECK(minPair.second == 1);
}

TEST_CASE("MinHeap Peek Empty") 
{
    MinHeap minHeap;

    // Peek into an empty heap
    Pair p = minHeap.peek();
    CHECK(p.first == 0); // Assuming that empty heap returns a Pair with distance 0
    CHECK(p.second == 0); // and vertex 0
}

TEST_CASE("MinHeap Insert and Heapify") 
{
    MinHeap minHeap;

    // Insert elements in reverse order
    minHeap.insert(10, 0);
    minHeap.insert(20, 1);
    minHeap.insert(5, 2);
    minHeap.insert(15, 3);

    // The minimum element should be (5, 2) after heapifying
    Pair minPair = minHeap.extractMin();
    CHECK(minPair.first == 5);
    CHECK(minPair.second == 2);

    // The next minimum should be (10, 0)
    minPair = minHeap.extractMin();
    CHECK(minPair.first == 10);
    CHECK(minPair.second == 0);
}

TEST_CASE("MinHeap Print Heap") 
{
    MinHeap minHeap;
    
    // Insert some elements
    minHeap.insert(5, 0);
    minHeap.insert(3, 1);
    minHeap.insert(8, 2);

    // Here we just check that printHeap doesn't crash
    // For more detailed tests, you would check the actual output using a stringstream
    CHECK_NOTHROW(minHeap.printHeap());
}

TEST_CASE("MinHeap prints correct error messages when full or empty") 
{
    MinHeap minHeap;

    // Redirect std::cout to a stringstream to capture output
    std::ostringstream output;

    // Save the original std::cout buffer
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    
    // Set std::cout to the stringstream buffer
    std::cout.rdbuf(output.rdbuf());

    // Try inserting elements until heap is full
    for (int i = 0; i < SIZE; i++) 
    {
        minHeap.insert(i, i);
    }

    // At this point, the heap should be full
    minHeap.insert(100, 100);
    
    // Check if the appropriate error message was printed
    CHECK(output.str() == "Heap is full\n");

    // Clear the output stream
    output.str("");
    output.clear();

    // Try extracting from an empty heap
    while (!minHeap.isEmpty()) 
    {
        minHeap.extractMin();
    }

    // The heap is now empty, so let's try to extract again
    minHeap.extractMin();
    
    // Check if the appropriate error message was printed
    CHECK(output.str() == "Heap is empty\n");

    // Clear the output stream
    output.str("");
    output.clear();

    // Try peeking into an empty heap
    minHeap.peek();
    
    // Check if the appropriate error message was printed
    CHECK(output.str() == "Heap is empty\n");

    // Restore the original std::cout buffer
    std::cout.rdbuf(originalCoutBuffer);
}

