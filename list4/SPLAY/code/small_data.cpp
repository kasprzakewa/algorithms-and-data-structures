#include "splay.hpp"
#include "../generators/ascending.hpp"
#include "../generators/random.hpp"
#include <vector>

#define RESET   "\033[0m"
#define MAGENTA "\033[1;35m"
#define PINK "\033[1;38;5;161m"

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
        return 1;
    }

    clear();
    std::cout << std::endl;

    int n = std::stoi(argv[1]);

    std::cout << PINK << "SPLAY TREE" << RESET << " n = " << n << std::endl;
    std::cout << std::endl;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<int> keys = random(n);

    std::cout << "Keys: ";
    for (int key : keys) 
    {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    Splay splay;

    for (int key : keys) 
    {
        splay.insert(key);
        std::cout << "insert " << MAGENTA << key << RESET << std::endl;
        splay.printTree();
    }

    int height = splay.height();
    std::cout << "comparisons: " << comparisons << std::endl;
    std::cout << "reads: " << reads << std::endl;
    std::cout << "writes: " << writes << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << std::endl;

    clear();

    std::vector<int> keysToDelete = random(n);

    std::cout << "Keys to delete: ";
    for (int key : keysToDelete) 
    {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    for (int key : keysToDelete) 
    {
        splay.remove(key);
        std::cout << "delete " << MAGENTA << key << RESET << std::endl;
        splay.printTree();
    }

    int height2 = splay.height();

    std::cout << "comparisons: " << comparisons << std::endl;
    std::cout << "reads: " << reads << std::endl;
    std::cout << "writes: " << writes << std::endl;
    std::cout << "height: " << height2 << std::endl;
    std::cout << std::endl;

    return 0;
}