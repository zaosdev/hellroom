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

    std::vector<bool> getBoughtPets()
    {
        std::vector<bool> petValues;

        std::ifstream inputFile(BOUGHT_PETS_DATA_PATH);

        if (inputFile) 
        {
            std::string line;
            while (std::getline(inputFile, line)) 
            {
                std::istringstream ss(line);
                std::string petName;
                int petValue;
                if (std::getline(ss, petName, ',') && (ss >> petValue)) 
                {
                    if (petValue == 0 || petValue == 1) 
                    {
                        petValues.push_back(petValue);
                    }
                }
            }
            inputFile.close();
            std::cout << "File read successfully." << std::endl;
        } 
        else 
        {
            std::cout << "Error opening file." << std::endl;
        }
        return petValues;
    }

    void writeBoughtPets(std::vector<bool> boughtPets)
    {
        std::ofstream outputFile(BOUGHT_PETS_DATA_PATH);
        std::cout << "me llega: " << std::endl;
        std::cout << boughtPets[0] << "," <<boughtPets[1]<< ","<< boughtPets[2]<< std::endl;

        if (outputFile.is_open())
        {
            for (size_t i = 0; i < boughtPets.size(); i++)
            {
                outputFile << "pet" << i+1 << "," << boughtPets[i] << "\n";
                std::cout << "pet" << i+1 << "," <<boughtPets[i] << std::endl;
            }
            
            outputFile.close();
            std::cout << "File saved successfully." << std::endl;
        }
        else
        {
            std::cout << "Error opening file." << std::endl;
        }
    }

    [[nodiscard]] int getSelectedPet()
    {
        std::ifstream inputFile(SELECTED_PET_DATA_PATH);

        if (!inputFile) {
            std::cerr << "Error opening selected pet file." << std::endl;
            return -1;
        }

        std::string line;
        std::getline(inputFile, line);
        int numero = std::stoi(line);
        
        inputFile.close();

        return numero;
    }

    void writeSelectedPet(int pet_number)
    {
        std::ofstream outputFile(SELECTED_PET_DATA_PATH);

        // Write selected pet value
        outputFile << pet_number << "\n";

        outputFile.close();
    }
}