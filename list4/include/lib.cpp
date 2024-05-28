#include "lib.hpp"

int comparisons;
int reads;
int writes;

void clear()
{
    comparisons = 0;
    reads = 0;
    writes = 0;
}

bool compare(int a, int b)
{
    comparisons++;

    if (a < b)
        return true;

    return false;
}

void read_node()
{
    reads++;
}

void write_node()
{
    writes++;
}