#pragma once

#include <random>

namespace Amb
{
    namespace Utils
    {
        namespace Random
        {
            struct RandomBetween
            {
                size_t min, max;

                size_t get() const
                {
                    static std::random_device rd;
                    static std::mt19937 mt(rd());
                    std::uniform_int_distribution<size_t> dist(min, max);

                    return dist(mt);
                }
            };
        }
    }
}
