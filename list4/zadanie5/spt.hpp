#ifndef SPT_HPP
#define SPT_HPP

#include <iostream>
#include "../include/lib.hpp"

class SPT
{
private:

    SPTNode* root;

    SPTNode* rightRotate(SPTNode* x) 
    {
        SPTNode* y = write_node(read_node(x->left));
        x->left = write_node(read_node(y->right));
        y->right = write_node(x);

        return y;
    }

    SPTNode* leftRotate(SPTNode* x) 
    {
        SPTNode* y = write_node(read_node(x->right));
        x->right = write_node(read_node(y->left));
        y->left = write_node(x);

        return y;
    }

    SPTNode* splay(SPTNode* root, int key) 
    {
        if (root == nullptr || root->key == key) 
            return root;

        if (compare_nodes(key, root->key)) 
        {
            if (read_node(root->left) == nullptr) 
                return root;

            if (compare_nodes(key, read_node(root->left)->key)) 
            {
                root->left->left = write_node(splay(read_node(read_node(root->left)->left), key));
                root = rightRotate(root);
            } 
            else if (compare_nodes(read_node(root->left)->key, key)) 
            {
                root->left->right = write_node(splay(read_node(read_node(root->left)->right), key));

                if (read_node(read_node(root->left)->right) != nullptr) 
                    root->left = write_node(leftRotate(read_node(root->left)));
            }

            return (read_node(root->left) == nullptr) ? root : rightRotate(root);
        } 
        else 
        {
            if (read_node(root->right) == nullptr) 
                return root;

            if (compare_nodes(read_node(root->right)->key, key)) 
            {
                root->right->right = write_node(splay(read_node(read_node(root->right)->right), key));
                root = leftRotate(root);
            } 
            else if (compare_nodes(key, read_node(root->right)->key)) 
            {
                root->right->left = write_node(splay(read_node(read_node(root->right)->left), key));

                if (read_node(read_node(root->right)->left) != nullptr) 
                    root->right = write_node(rightRotate(read_node(root->right)));
            }

            return (read_node(root->right) == nullptr) ? root : leftRotate(root);
        }
    }

    SPTNode* insert(SPTNode* root, int key) 
    {
        if (root == nullptr) 
            return new SPTNode(key);

        root = write_node(splay(root, key));

        if (compare_nodes(key, root->key)) 
        {
            SPTNode* newNode = new SPTNode(key);

            newNode->right = write_node(root);
            newNode->left = write_node(read_node(root->left));
            root->left = nullptr;

            return newNode;
        } 
        else if (compare_nodes(root->key, key)) 
        {
            SPTNode* newNode = new SPTNode(key);

            newNode->left = write_node(root);
            newNode->right = write_node(read_node(root->right));
            root->right = nullptr;

            return newNode;
        } 
        else 
        {
            return root;
        }
    }

    SPTNode* findMax(SPTNode* root) 
    {
        while (read_node(root->right) != nullptr) 
            root = write_node(read_node(root->right));

        return root;
    }

    SPTNode* deleteNode(SPTNode* root, int key) 
    {
        if (root == nullptr) return nullptr;

        root = write_node(splay(root, key));

        if (root->key != key) 
            comparisons++;
            return root;

        SPTNode* temp;
        if (read_node(root->left) == nullptr) 
        {
            temp = write_node(root);
            root = write_node(read_node(root->right));
        } 
        else 
        {
            temp = write_node(root);
            root = write_node(splay(read_node(root->left), key));
            root->right = write_node(read_node(temp->right));
        }

        delete temp;
        return root;
    }

    void printTree(SPTNode* node, std::string indent, bool isLeft) 
    {
        if (node != nullptr) 
        {
            std::cout << indent;

            if (isLeft) 
            {
                std::cout << "/-- ";
                indent += "|   ";
            } 
            else 
            {
                std::cout << "\\-- ";
                indent += "    ";
            }

            std::cout << node->key << std::endl;
            printTree(node->left, indent, true);
            printTree(node->right, indent, false);
        }
    }

    int height(SPTNode* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return std::max(leftHeight, rightHeight) + 1;
    }

public:
    SPT() : root(nullptr) {}

    void insert(int key) 
    {
        root = insert(root, key);
    }

    bool search(int key) 
    {
        root = splay(root, key);
        return (root != nullptr && root->key == key);
    }

    void remove(int key) 
    {
        root = deleteNode(root, key);
    }

    void printTree() 
    {
        printTree(root, "", true);
    }

    int height(void)
    {
        return height(root);
    }
};

#endif