#include "lib.hpp"

long comparisons;
long reads;
long writes;

void clear()
{
    comparisons = 0;
    reads = 0;
    writes = 0;
}

bool compare_nodes(int a, int b)
{
    comparisons++;

    if (a < b)
        return true;

    return false;
}

Node* read_node(Node* node)
{
    reads++;
    return node;
}

int read_node(int node)
{
    reads++;
    return node;
}

RBTNode* read_node(RBTNode* node)
{
    reads++;
    return node;
}

SplayNode* read_node(SplayNode* node)
{
    reads++;
    return node;
}

Node* write_node(Node* node)
{
    writes++;
    return node;
}

RBTNode* write_node(RBTNode* node)
{
    writes++;
    return node;
}

SplayNode* write_node(SplayNode* node)
{
    writes++;
    return node;
}

void write_node()
{
    writes++;
}