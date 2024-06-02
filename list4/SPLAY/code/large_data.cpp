#include "splay.hpp"
#include "../generators/ascending.hpp"
#include "../generators/random.hpp"
#include <vector>
#include <chrono>
#include <cstdlib>

int main(void)
{
    FILE* file_insert = fopen("insert_random.csv", "w");
    FILE* file_delete = fopen("delete_random.csv", "w");

    for (int n = 10000; n <= 100000; n+=10000)
    {
        std::cout << n << std::endl;

        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::srand(static_cast<unsigned int>(seed));

        for (int k = 0; k < 20; k++)
        {
            clear();
            std::vector<int> keys = random(n);

            Splay splay;

            for (int key : keys)
            {
                splay.insert(key);
            }

            int height = splay.height();
            fprintf(file_insert, "%d %ld %ld %ld %d\n", n, comparisons, reads, writes, height);

            clear();
            std::vector<int> keysToDelete = random(n);

            for (int key : keysToDelete)
            {
                splay.remove(key);
            }

            int height2 = splay.height();

            fprintf(file_delete, "%d %ld %ld %ld %d\n", n, comparisons, reads, writes, height2);
        }
    }

    fclose(file_insert);
    fclose(file_delete);

    system("echo -e '\a'"); // since the simulations takes some time, this will make a sound when it's done

    return 0;
}