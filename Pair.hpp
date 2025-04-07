// yarinkash1@gmail.com
#pragma once

class Pair
{
public:
    int first;   // distance
    int second;  // vertex

    Pair() : first(0), second(0) {} // Default constructor

    Pair(int f, int s) : first(f), second(s) {} // Parameterized constructor

    // Operator overloading for comparisons (used in heap operations):
    bool operator<(const Pair &other) const 
    {
        return first < other.first;
    }

    bool operator>(const Pair &other) const 
    {
        return first > other.first;
    }
};