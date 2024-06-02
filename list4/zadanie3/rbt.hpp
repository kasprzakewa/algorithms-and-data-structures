#ifndef RBT_HPP
#define RBT_HPP

#include <iostream>
#include <algorithm>
#include "../include/lib.hpp"

class RBT 
{
private:
    RBTNode* root;

    RBTNode* insert(RBTNode* root, RBTNode* node) 
    {
        if (root == nullptr) 
        {
            return node;
        }

        if (compare_nodes(node->key, root->key)) 
        {
            root->left = write_node(insert(read_node(root->left), node));
            root->left->parent = write_node(root);
        } 
        else 
        {
            root->right = write_node(insert(read_node(root->right), node));
            root->right->parent = write_node(root);
        }

        return root;
    }

    void fixAfterInsertion(RBTNode* node) 
    {
        RBTNode *parent = nullptr, *grandparent = nullptr, *uncle = nullptr;

        while ((node != root) && (node->color != BLACK) && (read_node(node->parent)->color == RED)) 
        {
            parent = write_node(read_node(node->parent));
            grandparent = write_node(read_node(parent->parent));

            /*  Case : A
                Parent of node is left child of Grand-parent of node */
            if (parent == read_node(grandparent->left)) 
            {
                uncle = write_node(read_node(grandparent->right));

                /* Case : 1
                The uncle of node is also red. Only Recoloring required */
                if (uncle != nullptr && uncle->color == RED) 
                {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = write_node(grandparent);
                } 
                else 
                {
                    /* Case : 2
                    node is right child of its parent. Left-rotation required */
                    if (node == read_node(parent->right)) 
                    {
                        rotateLeft(parent);
                        node = write_node(parent);
                        parent = write_node(read_node(node->parent));
                    }

                    /* Case : 3
                    node is left child of its parent. Right-rotation required */
                    rotateRight(grandparent);
                    std::swap(parent->color, grandparent->color);
                    node = write_node(parent);
                }
            }

            /* Case : B
            Parent of node is right child of Grand-parent of node */
            else 
            {
                uncle = write_node(read_node(grandparent->left));

                /*  Case : 1
                    The uncle of node is also red. Only Recoloring required */
                if ((uncle != nullptr) && (uncle->color == RED)) 
                {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = write_node(grandparent);
                } 
                else 
                {
                    /* Case : 2
                    node is left child of its parent. Right-rotation required */
                    if (node == read_node(parent->left)) 
                    {
                        rotateRight(parent);
                        node = write_node(parent);
                        parent = write_node(read_node(node->parent));
                    }

                    /* Case : 3
                    node is right child of its parent. Left-rotation required */
                    rotateLeft(grandparent);
                    std::swap(parent->color, grandparent->color);
                    node = write_node(parent);
                }
            }
        }

        root->color = BLACK;
    }

    void rotateLeft(RBTNode* node) 
    {
        RBTNode* right = write_node(read_node(node->right));
        node->right = write_node(read_node(right->left));

        if (read_node(right->left) != nullptr) 
        {
            right->left->parent = write_node(node);
        }

        right->parent = write_node(read_node(node->parent));

        if (read_node(node->parent) == nullptr) 
        {
            root = write_node(right);
        } 
        else if (node == read_node(read_node(node->parent)->left)) 
        {
            node->parent->left = write_node(right);
        } 
        else 
        {
            node->parent->right = write_node(right);
        }

        right->left = write_node(node);
        node->parent = write_node(right);
    }

    void rotateRight(RBTNode* node) 
    {
        RBTNode* left = write_node(read_node(node->left));
        node->left = write_node(read_node(left->right));

        if (read_node(left->right) != nullptr) 
        {
            left->right->parent = write_node(node);
        }

        left->parent = write_node(read_node(node->parent));

        if (read_node(node->parent) == nullptr) 
        {
            root = write_node(left);
        } 
        else if (node == read_node(read_node(node->parent)->right)) 
        {
            node->parent->right = write_node(left);
        } 
        else 
        {
            node->parent->left = write_node(left);
        }

        left->right = write_node(node);
        node->parent = write_node(left);
    }

    RBTNode* findNode(RBTNode* root, int key) 
    {
        while (root != nullptr) 
        {
            if (compare_nodes(key, root->key)) 
            {
                root = write_node(read_node(root->left));
            } 
            else if (compare_nodes(root->key, key)) 
            {
                root = write_node(read_node(root->right));
            } 
            else 
            {
                return root;
            }
        }

        return nullptr;
    }

    RBTNode* minimum(RBTNode* node) 
    {
        while (read_node(node->left) != nullptr) 
        {
            node = write_node(read_node(node->left));
        }

        return node;
    }

    void deleteNode(RBTNode* node) 
    {
        if (read_node(node->left) != nullptr && read_node(node->right) != nullptr) 
        {
            RBTNode* successor = write_node(minimum(read_node(node->right)));
            node->key = successor->key;
            node = write_node(successor);
        }

        RBTNode* replacement = (read_node(node->left) != nullptr) ? read_node(node->left) : read_node(node->right);
        writes++;

        if (replacement != nullptr) 
        {
            replacement->parent = write_node(read_node(node->parent));

            if (read_node(node->parent) == nullptr) 
            {
                root = write_node(replacement);
            } 
            else if (node == read_node(read_node(node->parent)->left)) 
            {
                node->parent->left = write_node(replacement);
            } 
            else 
            {
                node->parent->right = write_node(replacement);
            }

            node->left = node->right = node->parent = nullptr;

            if (node->color == BLACK) 
            {
                fixAfterDeletion(replacement);
            }
        } 
        else if (read_node(node->parent) == nullptr) 
        {
            root = nullptr;
        } 
        else 
        {
            if (node->color == BLACK) 
            {
                fixAfterDeletion(node);
            }

            if (read_node(node->parent) != nullptr) 
            {
                if (node == read_node(read_node(node->parent)->left)) 
                {
                    node->parent->left = nullptr;
                } 
                else if (node == read_node(read_node(node->parent)->right)) 
                {
                    node->parent->right = nullptr;
                }

                node->parent = nullptr;
            }
        }
    }

    void fixAfterDeletion(RBTNode* node) 
    {
        while (node != root && colorOf(node) == BLACK) 
        {
            if (node == leftOf(parentOf(node))) 
            {
                RBTNode* sibling = write_node(rightOf(parentOf(node)));

                if (colorOf(sibling) == RED) 
                {
                    setColor(sibling, BLACK);
                    setColor(parentOf(node), RED);
                    rotateLeft(parentOf(node));
                    sibling = write_node(rightOf(parentOf(node)));
                }

                if (colorOf(leftOf(sibling)) == BLACK && colorOf(rightOf(sibling)) == BLACK) 
                {
                    setColor(sibling, RED);
                    node = write_node(parentOf(node));
                } 
                else 
                {
                    if (colorOf(rightOf(sibling)) == BLACK) 
                    {
                        setColor(leftOf(sibling), BLACK);
                        setColor(sibling, RED);
                        rotateRight(sibling);
                        sibling = write_node(rightOf(parentOf(node)));
                    }

                    setColor(sibling, colorOf(parentOf(node)));
                    setColor(parentOf(node), BLACK);
                    setColor(rightOf(sibling), BLACK);
                    rotateLeft(parentOf(node));
                    node = write_node(root);
                }
            } 
            else 
            {
                RBTNode* sibling = leftOf(parentOf(node));

                if (colorOf(sibling) == RED) 
                {
                    setColor(sibling, BLACK);
                    setColor(parentOf(node), RED);
                    rotateRight(parentOf(node));
                    sibling = write_node(leftOf(parentOf(node)));
                }

                if (colorOf(rightOf(sibling)) == BLACK && colorOf(leftOf(sibling)) == BLACK) 
                {
                    setColor(sibling, RED);
                    node = write_node(parentOf(node));
                } 
                else 
                {
                    if (colorOf(leftOf(sibling)) == BLACK) 
                    {
                        setColor(rightOf(sibling), BLACK);
                        setColor(sibling, RED);
                        rotateLeft(sibling);
                        sibling = write_node(leftOf(parentOf(node)));
                    }

                    setColor(sibling, colorOf(parentOf(node)));
                    setColor(parentOf(node), BLACK);
                    setColor(leftOf(sibling), BLACK);
                    rotateRight(parentOf(node));
                    node = write_node(root);
                }
            }
        }

        setColor(node, BLACK);
    }

    bool colorOf(RBTNode* node) 
    {
        return node == nullptr ? BLACK : node->color;
    }

    RBTNode* parentOf(RBTNode* node) 
    {
        return node == nullptr ? nullptr : node->parent;
    }

    RBTNode* leftOf(RBTNode* node) 
    {
        return node == nullptr ? nullptr : node->left;
    }

    RBTNode* rightOf(RBTNode* node) 
    {
        return node == nullptr ? nullptr : node->right;
    }

    void setColor(RBTNode* node, bool color) 
    {
        if (node != nullptr) 
        {
            node->color = color;
        }
    }

    int height(RBTNode* node) 
    {
        if (node == nullptr) 
        {
            return -1;
        }

        return 1 + std::max(height(node->left), height(node->right));
    }

    void printTree(RBTNode* node, std::string indent, bool isLeft) 
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

            if (node->color == RED)
                std::cout << "\033[1;31m" << node->key << "\033[0m" << std::endl; 
            else
                std::cout << "\033[1;37m" << node->key << "\033[0m" << std::endl;

            printTree(node->left, indent, true);
            printTree(node->right, indent, false);
        }
    }

    

public:
    RBT() : root(nullptr) {}

    void insert(int key) 
    {
        RBTNode* node = new RBTNode(key);
        root = insert(root, node);
        fixAfterInsertion(node);
    }

    void deleteKey(int key) 
    {
        RBTNode* node = findNode(root, key);

        if (node == nullptr) return;

        deleteNode(node);
    }

    int height() 
    {
        return height(root);
    }

    void printTree() 
    {
        printTree(root, "", true);
    }

    RBTNode* getRoot() 
    {
        return root;
    }
};

#endif