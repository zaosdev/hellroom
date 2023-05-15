
#include "savingSys.hpp"
#include "../man/SpriteManager.hpp"
#include "../sys/renderSys.hpp"
#include "../utils/gameData.hpp"
#include <iostream>
#include <fstream>

namespace game
{
    SavingSys::SavingSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
        clock_.restart();
    }

    SavingSys::~SavingSys() = default;

    //save every 5 seconds to prevent overwritting
    void SavingSys::update()
    {
        if (clock_.getElapsedTime().asSeconds() > saveTime_)
        {
            DataComponent& data = *gMan_.getPlayer().data;

            FVData::writeCoins(data.coins);

            clock_.restart();
        }
    }

}