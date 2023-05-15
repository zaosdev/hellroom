#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../man/GameManager.hpp"
#include "HUDSys.hpp"



namespace game
{
    struct RenderSys
    {
        RenderSys(FVeng::GameManager& Gman, HUDSys& HUD);
        ~RenderSys() = default;

        RenderSys (const RenderSys&) = delete;
        RenderSys (RenderSys&&) = delete;
        RenderSys& operator=(const RenderSys&)= delete;
        RenderSys& operator=(RenderSys&&)= delete;

        void iniRenderSys();
        // template<typename T>
        void draw(sf::Sprite& Sprite);
        void drawMap(MapComponent& Sprite);
        void drawUpperMap(MapComponent& Sprite);
        //void drawFV(sfml_util::FVSprite& Sprite);

        void iniSprite(game::Entity& ent, double pt);
        void update(double percentTick);
       // void addHUD(HUDSys& hud);

        private:
            FVeng::GameManager& gMan_;
            sf::RenderWindow& window_;
            HUDSys&              HUD_;
    };
}