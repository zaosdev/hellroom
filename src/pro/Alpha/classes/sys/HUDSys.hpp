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
        // template<typename T>
        //void draw(sf::Sprite& Sprite);
        //void drawMap(MapComponent& Sprite);
        //void drawUpperMap(MapComponent& Sprite);
        //void drawFV(sfml_util::FVSprite& Sprite);

        //void iniSprite(game::Entity& ent, double pt);
        void update();
        void renderHearts();

        void restartTime();


        private:
            FVeng::GameManager& gMan_;
            sf::RenderWindow&   window_;
            Entity&             player_;
            sf::Clock           clock_;
            sf::Text            text_;
            sf::Font            font_;
            Entity&             heart_;
            double    accumulatedTime;    //time passed (seconds)
    };
}