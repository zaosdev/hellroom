#include "gameData.hpp"

namespace FVData
{
    [[nodiscard]] int getCoins()
    {
        std::ifstream inputFile(COINS_DATA_PATH);

        if (!inputFile) {
            std::cerr << "Error opening coins file." << std::endl;
            return -1;
        }

        std::string line;
        std::getline(inputFile, line);
        int numero = std::stoi(line);
        
        inputFile.close();

        return numero;
    }


    void writeCoins(int numCoins)
    {
        std::ofstream outputFile(COINS_DATA_PATH);

        // Write coins value
        outputFile << numCoins << "\n";

        outputFile.close();
    }
}