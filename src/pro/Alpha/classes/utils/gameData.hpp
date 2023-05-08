#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define COINS_DATA_PATH         "../gameData/coins.data"
#define BOUGHT_PETS_DATA_PATH   "../gameData/boughtPets.data"
#define SELECTED_PET_DATA_PATH  "../gameData/selectedPet.data"
namespace FVData
{
    [[nodiscard]] int getCoins();
    void writeCoins(int numCoins);
    [[nodiscard]] std::vector<bool> getBoughtPets();
    void writeBoughtPets(std::vector<bool>);
    [[nodiscard]] int getSelectedPet();
    void writeSelectedPet(int selectedPet);
}