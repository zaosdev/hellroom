#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../man/GameManager.hpp"


//display time, player health, player bullets...

namespace game
{
    struct HUDSys
    {
        HUDSys(FVeng::GameManager& Gman);
        ~HUDSys();

        HUDSys (const HUDSys&) = delete;
        HUDSys (HUDSys&&) = delete;
        HUDSys& operator=(const HUDSys&)= delete;
        HUDSys& operator=(HUDSys&&)= delete;

        void iniRenderSys();
        void setPlayer  (Entity* player);
        void setHeartID (size_t id);
        void setCoinID  (size_t id);
        // template<typename T>
        //void draw(sf::Sprite& Sprite);
        //void drawMap(MapComponent& Sprite);
        //void drawUpperMap(MapComponent& Sprite);
        //void drawFV(sfml_util::FVSprite& Sprite);

        //void iniSprite(game::Entity& ent, double pt);
        void update();
        void renderHearts();
        void renderCoins();
        void renderTimer();
        void restartTime();


        private:
            FVeng::GameManager& gMan_;
            sf::RenderWindow&   window_;
            Entity*             player_;
            sf::Clock           clock_;
            sf::Text            timeText_;
            sf::Text            coinText_;
            sf::Font            font_;
            size_t              heart_;
            size_t              coin_;
            double    accumulatedTime;    //time passed (seconds)
    };
}