#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <iomanip>
#include "../../include/lib.hpp"

class BST
{
private:
    Node* root;

    Node* insert(Node* node, int key)
    {
        if (node == nullptr)
        {
            return new Node(key);
        }

        if (compare_nodes(key, read_node(node->key)))
        {
            node->left = write_node(insert(read_node(node->left), key));
        }
        else
        {
            node->right = write_node(insert(read_node(node->right), key));
        }

        return node;
    }

    Node* findMin(Node* node)
    {
        while (read_node(node->left) != nullptr)
        {
            node = write_node(read_node(node->left));
        }

        return node;
    }

    Node* deleteNode(Node* node, int key)
    {
        if (node == nullptr)
        {
            return node;
        }

        if (compare_nodes(key, node->key))
        {
            node->left = deleteNode(node->left, key);
            writes++;
            reads++;
        }
        else if (compare_nodes(node->key, key))
        {
            node->right = deleteNode(node->right, key);
            writes++;
            reads++;
        }
        else
        {
            if (node->left == nullptr)
            {
                reads++;
                Node* temp = node->right;
                writes++;
                reads++;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                reads++;
                Node* temp = node->left;
                writes++;
                reads++;
                delete node;
                return temp;
            }
            else
            {
                Node* temp = findMin(node->right);
                reads++;
                node->key = temp->key;
                node->right = deleteNode(node->right, temp->key);
                writes++;
                reads++;
            }
        }

        return node;
    }

    int height(Node* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return std::max(leftHeight, rightHeight) + 1;
    }

    void printTree(Node* node, std::string indent, bool isLeft)
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

public:
    BST(void) : root(nullptr) {}

    void insert(int key)
    {
        root = insert(root, key);
    }

    void deleteKey(int key)
    {
        root = deleteNode(root, key);
    }

    int height(void)
    {
        return height(root);
    }

    Node* getRoot(void)
    {
        return root;
    }

    void printTree(void)
    {
        printTree(root, "", false);
        std::cout << std::endl;
    }
};

#endif 
