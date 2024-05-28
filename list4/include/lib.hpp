#ifndef LIB_HPP
#define LIB_HPP

#include <iostream>


extern int comparisons;
extern int reads;
extern int writes;

struct Node
{
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

void clear();
bool compare(int a, int b);
void read_node();
void write_node();

#endif