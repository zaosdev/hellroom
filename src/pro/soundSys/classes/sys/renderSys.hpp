#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../man/GameManager.hpp"




namespace game
{
    struct RenderSys
    {
        RenderSys(FVeng::GameManager& Gman);
        ~RenderSys();

        RenderSys (const RenderSys&) = delete;
        RenderSys (RenderSys&&) = delete;
        RenderSys& operator=(const RenderSys&)= delete;
        RenderSys& operator=(RenderSys&&)= delete;

        void iniRenderSys();
        void drawSprite(sf::Sprite& Sprite);
        void iniSprite();
        void update();


        private:
            FVeng::GameManager& gMan_;
            sf::RenderWindow& window_;
    };
}