// yarinkash1@gmail.com
#pragma once

class UnionFind
{
private:
    int* parent;
    int* rank;
    int size;
public:
    UnionFind(int n);
    ~UnionFind();

    int find(int x);
    void union_sets(int x, int y);
};

