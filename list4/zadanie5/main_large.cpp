#include "spt.hpp"
#include "../generators/ascending.hpp"
#include "../generators/random.hpp"
#include <vector>
#include <chrono>
#include <cstdlib>

int main(void)
{
    FILE* file_insert = fopen("spt_insert_asc.csv", "w");
    FILE* file_delete = fopen("spt_delete_asc.csv", "w");

    for (int n = 10000; n <= 100000; n+=10000)
    {
        std::cout << n << std::endl;

        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::srand(static_cast<unsigned int>(seed));

        for (int k = 0; k < 20; k++)
        {
            clear();
            std::vector<int> keys = ascending(n);

            SPT spt;

            for (int key : keys)
            {
                spt.insert(key);
            }

            int height = spt.height();
            fprintf(file_insert, "%d %ld %ld %ld %d\n", n, comparisons, reads, writes, height);

            clear();
            std::vector<int> keysToDelete = random(n);

            for (int key : keysToDelete)
            {
                spt.remove(key);
            }

            int height2 = spt.height();

            fprintf(file_delete, "%d %ld %ld %ld %d\n", n, comparisons, reads, writes, height2);
        }
    }

    fclose(file_insert);
    fclose(file_delete);

    system("echo -e '\a'"); // since the simulations takes some time, this will make a sound when it's done

    return 0;
}