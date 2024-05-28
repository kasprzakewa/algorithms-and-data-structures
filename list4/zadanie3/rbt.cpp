#include <iostream>
#include <algorithm>

class RedBlackBST 
{
private:
    static const bool RED = true;
    static const bool BLACK = false;

    struct Node 
    {
        int key;
        Node* left;
        Node* right;
        Node* parent;
        bool color;

        Node(int key) : key(key), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
    };

    Node* root;

    Node* insert(Node* root, Node* node) 
    {
        if (root == nullptr) 
        {
            return node;
        }

        if (node->key < root->key) 
        {
            root->left = insert(root->left, node);
            root->left->parent = root;
        } 
        else 
        {
            root->right = insert(root->right, node);
            root->right->parent = root;
        }

        return root;
    }

    void fixAfterInsertion(Node* node) 
{
    Node *parent = nullptr, *grandparent = nullptr, *uncle = nullptr;

    while ((node != root) && (node->color != BLACK) && (node->parent->color == RED)) 
    {
        parent = node->parent;
        grandparent = parent->parent;

        /*  Case : A
            Parent of node is left child of Grand-parent of node */
        if (parent == grandparent->left) 
        {
            uncle = grandparent->right;

            /* Case : 1
            The uncle of node is also red. Only Recoloring required */
            if (uncle != nullptr && uncle->color == RED) 
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } 
            else 
            {
                /* Case : 2
                node is right child of its parent. Left-rotation required */
                if (node == parent->right) 
                {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }

                /* Case : 3
                node is left child of its parent. Right-rotation required */
                rotateRight(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }

        /* Case : B
        Parent of node is right child of Grand-parent of node */
        else 
        {
            uncle = grandparent->left;

            /*  Case : 1
                The uncle of node is also red. Only Recoloring required */
            if ((uncle != nullptr) && (uncle->color == RED)) 
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } 
            else 
            {
                /* Case : 2
                node is left child of its parent. Right-rotation required */
                if (node == parent->left) 
                {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }

                /* Case : 3
                node is right child of its parent. Left-rotation required */
                rotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }

    root->color = BLACK;
}

    void rotateLeft(Node* node) 
    {
        Node* right = node->right;
        node->right = right->left;

        if (right->left != nullptr) 
        {
            right->left->parent = node;
        }

        right->parent = node->parent;

        if (node->parent == nullptr) 
        {
            root = right;
        } 
        else if (node == node->parent->left) 
        {
            node->parent->left = right;
        } 
        else 
        {
            node->parent->right = right;
        }

        right->left = node;
        node->parent = right;
    }

    void rotateRight(Node* node) 
    {
        Node* left = node->left;
        node->left = left->right;

        if (left->right != nullptr) 
        {
            left->right->parent = node;
        }

        left->parent = node->parent;

        if (node->parent == nullptr) 
        {
            root = left;
        } 
        else if (node == node->parent->right) 
        {
            node->parent->right = left;
        } 
        else 
        {
            node->parent->left = left;
        }

        left->right = node;
        node->parent = left;
    }

    Node* findNode(Node* root, int key) 
    {
        while (root != nullptr) 
        {
            if (key < root->key) 
            {
                root = root->left;
            } 
            else if (key > root->key) 
            {
                root = root->right;
            } 
            else 
            {
                return root;
            }
        }

        return nullptr;
    }

    Node* minimum(Node* node) 
    {
        while (node->left != nullptr) 
        {
            node = node->left;
        }

        return node;
    }

    void deleteNode(Node* node) 
    {
        if (node->left != nullptr && node->right != nullptr) 
        {
            Node* successor = minimum(node->right);
            node->key = successor->key;
            node = successor;
        }

        Node* replacement = (node->left != nullptr) ? node->left : node->right;

        if (replacement != nullptr) 
        {
            replacement->parent = node->parent;

            if (node->parent == nullptr) 
            {
                root = replacement;
            } 
            else if (node == node->parent->left) 
            {
                node->parent->left = replacement;
            } 
            else 
            {
                node->parent->right = replacement;
            }

            node->left = node->right = node->parent = nullptr;

            if (node->color == BLACK) 
            {
                fixAfterDeletion(replacement);
            }
        } 
        else if (node->parent == nullptr) 
        {
            root = nullptr;
        } 
        else 
        {
            if (node->color == BLACK) 
            {
                fixAfterDeletion(node);
            }

            if (node->parent != nullptr) 
            {
                if (node == node->parent->left) 
                {
                    node->parent->left = nullptr;
                } 
                else if (node == node->parent->right) 
                {
                    node->parent->right = nullptr;
                }

                node->parent = nullptr;
            }
        }
    }

    void fixAfterDeletion(Node* node) 
    {
        while (node != root && colorOf(node) == BLACK) 
        {
            if (node == leftOf(parentOf(node))) 
            {
                Node* sibling = rightOf(parentOf(node));

                if (colorOf(sibling) == RED) 
                {
                    setColor(sibling, BLACK);
                    setColor(parentOf(node), RED);
                    rotateLeft(parentOf(node));
                    sibling = rightOf(parentOf(node));
                }

                if (colorOf(leftOf(sibling)) == BLACK && colorOf(rightOf(sibling)) == BLACK) 
                {
                    setColor(sibling, RED);
                    node = parentOf(node);
                } 
                else 
                {
                    if (colorOf(rightOf(sibling)) == BLACK) 
                    {
                        setColor(leftOf(sibling), BLACK);
                        setColor(sibling, RED);
                        rotateRight(sibling);
                        sibling = rightOf(parentOf(node));
                    }

                    setColor(sibling, colorOf(parentOf(node)));
                    setColor(parentOf(node), BLACK);
                    setColor(rightOf(sibling), BLACK);
                    rotateLeft(parentOf(node));
                    node = root;
                }
            } 
            else 
            {
                Node* sibling = leftOf(parentOf(node));

                if (colorOf(sibling) == RED) 
                {
                    setColor(sibling, BLACK);
                    setColor(parentOf(node), RED);
                    rotateRight(parentOf(node));
                    sibling = leftOf(parentOf(node));
                }

                if (colorOf(rightOf(sibling)) == BLACK && colorOf(leftOf(sibling)) == BLACK) 
                {
                    setColor(sibling, RED);
                    node = parentOf(node);
                } 
                else 
                {
                    if (colorOf(leftOf(sibling)) == BLACK) 
                    {
                        setColor(rightOf(sibling), BLACK);
                        setColor(sibling, RED);
                        rotateLeft(sibling);
                        sibling = leftOf(parentOf(node));
                    }

                    setColor(sibling, colorOf(parentOf(node)));
                    setColor(parentOf(node), BLACK);
                    setColor(leftOf(sibling), BLACK);
                    rotateRight(parentOf(node));
                    node = root;
                }
            }
        }

        setColor(node, BLACK);
    }

    bool colorOf(Node* node) 
    {
        return node == nullptr ? BLACK : node->color;
    }

    Node* parentOf(Node* node) 
    {
        return node == nullptr ? nullptr : node->parent;
    }

    Node* leftOf(Node* node) 
    {
        return node == nullptr ? nullptr : node->left;
    }

    Node* rightOf(Node* node) 
    {
        return node == nullptr ? nullptr : node->right;
    }

    void setColor(Node* node, bool color) 
    {
        if (node != nullptr) 
        {
            node->color = color;
        }
    }

    int height(Node* node) 
    {
        if (node == nullptr) 
        {
            return -1;
        }

        return 1 + std::max(height(node->left), height(node->right));
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

        // If the node color is RED, print the key in red, otherwise print in white
        if (node->color == RED)
            std::cout << "\033[1;31m" << node->key << "\033[0m" << std::endl; // Red color
        else
            std::cout << "\033[1;37m" << node->key << "\033[0m" << std::endl; // White color

        printTree(node->left, indent, true);
        printTree(node->right, indent, false);
    }
}

public:
    RedBlackBST() : root(nullptr) {}

    void insert(int key) 
    {
        Node* node = new Node(key);
        root = insert(root, node);
        fixAfterInsertion(node);
    }

    void deleteKey(int key) 
    {
        Node* node = findNode(root, key);

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
};

int main() 
{
    RedBlackBST tree;

    tree.insert(7);
    tree.insert(0);
    tree.insert(6);
    tree.insert(2);
    tree.insert(1);

    std::cout << "Tree structure:" << std::endl;
    tree.printTree();

    tree.deleteKey(7);
    tree.deleteKey(1);
    tree.deleteKey(4);

    std::cout << "Tree structure after deletions:" << std::endl;
    tree.printTree();

    return 0;
}
