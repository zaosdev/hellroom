#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../man/GameManager.hpp"


//display time, player health, player bullets...
#define spacing 35

namespace game
{
    struct HUDSys
    {
        HUDSys(FVeng::GameManager& Gman);
        ~HUDSys() = default;

        HUDSys (const HUDSys&) = delete;
        HUDSys (HUDSys&&) = delete;
        HUDSys& operator=(const HUDSys&)= delete;
        HUDSys& operator=(HUDSys&&)= delete;

        void iniRenderSys();
        void setPlayer  (Entity* player);
        void setHeartID (size_t id);
        void setCoinID  (size_t id);
        void setClockID (size_t id);
        void setShieldID(size_t id);
        // template<typename T>
        //void draw(sf::Sprite& Sprite);
        //void drawMap(MapComponent& Sprite);
        //void drawUpperMap(MapComponent& Sprite);
        //void drawFV(sfml_util::FVSprite& Sprite);

        //void iniSprite(game::Entity& ent, double pt);
        void update();
        FVmath::Point2Di renderHearts ();
        void renderShield(FVmath::Point2Di lastHeartPosition);
        void renderCoins();
        void renderTimer();
        void restartTime();
        void setMaxTime(double newTime);

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
            size_t              clocksp_;
            size_t              shieldsp_;
            double              accumulatedTime;    //time passed (seconds)
            double              maxTime_ = 99;
    };
}