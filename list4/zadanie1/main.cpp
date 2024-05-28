#include "bst.hpp"

int main(void) 
{
    clear();
    BST tree;
    tree.insert(517);
    tree.printTree(517);
    tree.insert(665);
    tree.printTree(665);
    tree.insert(713);
    tree.printTree(713);
    tree.insert(725);
    tree.printTree(725);
    tree.insert(736);
    tree.printTree(736);
    tree.insert(788);
    tree.printTree(788);
    tree.insert(924);
    tree.printTree(924);
    tree.insert(939);
    tree.printTree(939);
    tree.insert(978);
    tree.printTree(978);
    tree.insert(370);
    tree.printTree(370);
    tree.insert(372);
    tree.printTree(372);
    tree.insert(484);
    tree.printTree(484);
    tree.insert(352);
    tree.printTree(352);
    tree.insert(310);
    tree.printTree(310);
    tree.insert(282);
    tree.printTree(282);
    tree.insert(257);
    tree.printTree(257);
    tree.insert(54);
    tree.printTree(54);
    tree.insert(48);
    tree.printTree(48);

    std::cout << "Binary Search Tree:\n";
    tree.printTree(48);

    tree.deleteKey(370);
    std::cout << "\nBinary Search Tree after deleting 370:\n";
    tree.printTree(54);

    std::cout << "comparisons " << comparisons << std::endl;
    std::cout << "reads " << reads << std::endl;
    std::cout << "writes " << writes << std::endl;


    // FILE* file = fopen("data.csv", "r");

    // if (file == NULL)
    // {
    //     std::cout << "Error: file not found" << std::endl;
    //     return 1;
    // }

    // BST tree;



    

    return 0;
}