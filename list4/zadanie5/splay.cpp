#include <iostream>

class SplayTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;

        Node(int key) : key(key), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Node* splay(Node* root, int key) {
        if (root == nullptr || root->key == key) return root;

        if (key < root->key) {
            if (root->left == nullptr) return root;
            if (key < root->left->key) {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            } else if (key > root->left->key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr) root->left = leftRotate(root->left);
            }

            return (root->left == nullptr) ? root : rightRotate(root);
        } else {
            if (root->right == nullptr) return root;
            if (key > root->right->key) {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            } else if (key < root->right->key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr) root->right = rightRotate(root->right);
            }

            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }

    Node* insert(Node* root, int key) {
        if (root == nullptr) return new Node(key);

        root = splay(root, key);

        if (key < root->key) {
            Node* newNode = new Node(key);
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
            return newNode;
        } else if (key > root->key) {
            Node* newNode = new Node(key);
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
            return newNode;
        } else {
            return root; // Key already exists
        }
    }

    Node* findMax(Node* root) {
        while (root->right != nullptr) root = root->right;
        return root;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) return nullptr;

        root = splay(root, key);

        if (root->key != key) return root; // Key not found

        Node* temp;
        if (root->left == nullptr) {
            temp = root;
            root = root->right;
        } else {
            temp = root;
            root = splay(root->left, key);
            root->right = temp->right;
        }

        delete temp;
        return root;
    }

    void printTree(Node* node, std::string indent, bool isLeft) {
        if (node != nullptr) {
            std::cout << indent;
            if (isLeft) {
                std::cout << "/-- ";
                indent += "|   ";
            } else {
                std::cout << "\\-- ";
                indent += "    ";
            }

            std::cout << node->key << std::endl;
            printTree(node->left, indent, true);
            printTree(node->right, indent, false);
        }
    }

public:
    SplayTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    bool search(int key) {
        root = splay(root, key);
        return (root != nullptr && root->key == key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    void printTree() {
        printTree(root, "", true);
    }
};

int main() {
    SplayTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);

    std::cout << "Tree structure:" << std::endl;
    tree.printTree();

    std::cout << "Search for 20: " << (tree.search(20) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search for 25: " << (tree.search(25) ? "Found" : "Not Found") << std::endl;

    tree.remove(20);
    std::cout << "Tree structure after removal:" << std::endl;
    tree.printTree();

    return 0;
}