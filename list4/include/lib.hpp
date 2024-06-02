#ifndef LIB_HPP
#define LIB_HPP

#include <iostream>


extern long comparisons;
extern long reads;
extern long writes;

static const bool RED = true;
static const bool BLACK = false;

struct Node
{
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

struct RBTNode 
{
    int key;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;
    bool color;

    RBTNode(int key) : key(key), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

struct SplayNode 
{
    int key;
    SplayNode* left;
    SplayNode* right;

    SplayNode(int key) : key(key), left(nullptr), right(nullptr) {}
};

void clear();
bool compare_nodes(int a, int b);
Node* read_node(Node* node);
int read_node(int node);
RBTNode* read_node(RBTNode* node);
SplayNode* read_node(SplayNode* node);
Node* write_node(Node* node);
RBTNode* write_node(RBTNode* node);
SplayNode* write_node(SplayNode* node);
void write_node();

#endif