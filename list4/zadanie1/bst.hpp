#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <iomanip>
#include "../include/lib.hpp"

class BST
{
private:
    Node* root;

    Node* insert(Node* node, int key)
    {
        if (node == nullptr)
        {
            read_node();
            return new Node(key);
        }

        if (compare(key, node->key))
        {
            read_node();
            node->left = insert(node->left, key);
            read_node();
            write_node();
        }
        else
        {
            node->right = insert(node->right, key);
            read_node();
            write_node();
        }

        return node;
    }

    Node* findMin(Node* node)
    {
        while (node->left != nullptr)
        {
            read_node();
            node = node->left;
            read_node();
            write_node();
        }
        read_node();

        return node;
    }

    Node* deleteNode(Node* node, int key)
    {
        if (node == nullptr)
        {
            read_node();
            return node;
        }

        if (compare(key, node->key))
        {
            read_node();
            node->left = deleteNode(node->left, key);
            read_node();
            write_node();
        }
        else if (compare(node->key, key))
        {
            read_node();
            node->right = deleteNode(node->right, key);
            read_node();
            write_node();
        }
        else
        {
            if (node->left == nullptr)
            {
                read_node();
                Node* temp = node->right;
                read_node();
                write_node();
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                read_node();
                Node* temp = node->left;
                read_node();
                write_node();
                delete node;
                return temp;
            }
            else
            {
                Node* temp = findMin(node->right);
                read_node();
                write_node();
                node->key = temp->key;
                read_node();
                write_node();
                node->right = deleteNode(node->right, temp->key);
                read_node();
                read_node();
                write_node();
            }
        }

        return node;
    }

    int height(Node* node)
    {
        if (node == nullptr)
        {
            read_node();
            return 0;
        }

        int leftHeight = height(node->left);
        read_node();
        int rightHeight = height(node->right);
        read_node();

        return std::max(leftHeight, rightHeight) + 1;
    }

    void printTree(Node* node, std::string indent, bool isLeft, int highlightKey = -1)
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

            if (node->key == highlightKey)
            {
                std::cout << "\033[1;32m" << node->key << "\033[0m" << std::endl; // Highlight the node in green
            }
            else
            {
                std::cout << node->key << std::endl;
            }

            printTree(node->left, indent, true, highlightKey);
            printTree(node->right, indent, false, highlightKey);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(int key)
    {
        root = insert(root, key);
    }

    void deleteKey(int key)
    {
        root = deleteNode(root, key);
    }

    int height()
    {
        return height(root);
    }

    void printTree(int highlightKey)
    {
        printTree(root, "", false, highlightKey);
        std::cout << std::endl;
    }
};

#endif /* BST_HPP */
