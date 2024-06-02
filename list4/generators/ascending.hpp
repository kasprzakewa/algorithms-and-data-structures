#ifndef ASCENDING_HPP
#define ASCENDING_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

std::vector<int> ascending(int n)
{
    std::vector<int> ascendingValues;
    ascendingValues.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        ascendingValues.push_back(std::rand() % (2 * n));
    }

    std::sort(ascendingValues.begin(), ascendingValues.end());

    return ascendingValues;
}

#endif // ASCENDING_HPP