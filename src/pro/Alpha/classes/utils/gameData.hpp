#pragma once

#include <iostream>
#include <fstream>
#include <string>

#define COINS_DATA_PATH "../gameData/coins.data"
namespace FVData
{
    [[nodiscard]] int getCoins();
    void writeCoins(int numCoins);
}