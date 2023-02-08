#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../man/GameManager.hpp"



namespace game
{
    struct RenderSys
    {
        RenderSys(FVeng::GameManager& gameMan);
        ~RenderSys();

        void iniRenderSys();
        void drawSprite();
        void iniSprite();
        void update();


        private:
            FVeng::GameManager& gMan_;
            sf::RenderWindow& window_;
            Entity ent;
    };
}