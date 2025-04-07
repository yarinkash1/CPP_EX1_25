# Graph Algorithms in C++

This project implements several graph algorithms in C++, including:
- Prim's Algorithm (Minimum Spanning Tree)
- Kruskal's Algorithm (Minimum Spanning Tree)
- Depth-First Search (DFS)
- Breadth-First Search (BFS)
- Dijkstra's Algorithm (Shortest Path)

The program is designed to allow users to run these algorithms on a given graph and return the resulting tree graph
(for example spanning tree, shortest path, etc.).

## Table of Contents
- [Description](#description)
- [Installation](#installation)
- [Usage](#usage)
- [Algorithms Implemented](#algorithms-implemented)
- [Contributing](#contributing)
- [License](#license)

## Description

This program is a C++ implementation of popular graph algorithms.
Users can input a graph (defined by vertices and edges through adjacency list),
and the program will execute one of the algorithms on the graph and output the result.
The output will be in the form of a spanning tree or weighted tree graph, depending on the algorithm used.

### Algorithms Implemented:
- **Prim's Algorithm**: Finds the Minimum Spanning Tree (MST) of a weighted, undirected graph.
- **Kruskal's Algorithm**: Another algorithm to find the MST, but uses edge sorting and union-find.
- **DFS (Depth-First Search)**: Explores a graph by starting at the root node and exploring as far as possible along each branch.
- **BFS (Breadth-First Search)**: Explores a graph level by level, useful for finding the shortest path in an unweighted graph.
- **Dijkstra's Algorithm**: Finds the shortest path between nodes in a weighted graph.

## Installation

To use this program, you need to have a C++ compiler installed. The program has been tested with `g++`.

1. Clone the repository:
   ```bash
   git clone https://github.com/yarinkash1/CPP_EX1_25.git
   ```

2. Navigate to the project directory:
    ```bash
    cd /home/yarin/cpp/CPP_EX1_25
    ```

3. Build the project using Makefile:
    ```bash
    make all
    ```

4. The `main_exe` binary will be created. You can run the program using:
    ```bash
    make main
    ```
