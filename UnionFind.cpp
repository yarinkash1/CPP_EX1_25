// yarinkash1@gmail.com
#include "UnionFind.hpp"

UnionFind::UnionFind(int n)
{
    size = n;
    parent = new int[n];
    rank = new int[n];

    for (int i = 0; i < n; i++)
    {
        parent[i]=i; // Each node is its own parent initially
        rank[i]=0; // All ranks start at 0
    }
    
}

UnionFind::~UnionFind()
{
    delete[] parent;
    delete[] rank;
}

int UnionFind::find(int x)
{
    if(parent[x] != x)
    {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
    
}

void UnionFind::union_sets(int x,int y)
{
    // up stands for ultimate-parent
    int up_x = find(x);
    int up_y = find(y);

    if(up_x == up_y) // Nothing to do when we union the same vertex to itself
    {
        return;
    }

    int rank_up_x = rank[up_x];
    int rank_up_y = rank[up_y];

    // Union by rank:
    if(rank_up_x > rank_up_y)
    {
        parent[up_y] = up_x;
    }
    else if(rank_up_x < rank_up_y)
    {
        parent[up_x] = up_y;
    }
    else // Ranks are equal
    {
        parent[up_y] = up_x;
        rank[up_x]++;
    }
}