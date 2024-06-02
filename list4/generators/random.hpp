#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<int> random(int n)
{
    std::vector<int> randomValues;
    randomValues.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        randomValues.push_back(std::rand() % (2 * n));
    }

    return randomValues;
}

#endif // RANDOM_HPP

