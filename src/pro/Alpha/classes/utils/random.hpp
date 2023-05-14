#pragma once

#include <random>

namespace FVmath
{
    [[nodiscard]] inline static int calculateRandom(int maxNum, int minNum = 0) noexcept
    {
        //example max 15, min = -5
        std::random_device rd;
        std::mt19937_64 gen(static_cast<unsigned>(rd()));
        std::uniform_int_distribution<int> dis(minNum, maxNum); //range = [0, 15-5] = [0, 10]
        
        int random = dis(gen);

        return random;
    }
}