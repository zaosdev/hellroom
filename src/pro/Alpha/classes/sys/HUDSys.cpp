#include "HUDSys.hpp"
#include <string>
#include <iomanip>
#include <algorithm>

//#include "../utils/math.hpp"
//#include <cmath>
namespace game
{
    static constexpr int lifeHeart = 100.f;

    HUDSys::HUDSys(FVeng::GameManager& Gman)
    : gMan_   (Gman),
     window_  (gMan_.getWindow()),
     player_  (gMan_.getPlayer()),
     heart_   (gMan_.createHeart().id())
    {
        if (!font_.loadFromFile("../media/font/Retro_Gaming.ttf")) {
            // manejar error de carga de fuente
            std::terminate();
        }
        text_.setFillColor(sf::Color::Red);
        text_.setFont(font_);
        text_.setCharacterSize(40);
        text_.setPosition({static_cast<float>(window_.getSize().x - 150), 0});
        restartTime();
    }

    HUDSys::~HUDSys()
    {
        if(window_.isOpen()) window_.close();
    }

    void HUDSys::restartTime()
    {
        accumulatedTime = 0;
        clock_.restart();
    }

    void HUDSys::renderHearts()
    {
        //Get the player's health
        auto& hc = player_.health;
        float ch = hc->currentLife;
        //Every 100 hp, render one heart
        int   fullHearts   = static_cast<int>(ch / lifeHeart); //5
        float semiHeart    = (static_cast<int>(ch) % lifeHeart) / 100.f;
        //std::cout << "SemiHeart: " << semiHeart << std::endl;
        //Render the full hearts
        int spacing = 35;

        auto& EM = gMan_.getEntityManager();

        auto it = std::find_if(EM.begin(),EM.end(),[&](auto& e){ return e.id()==heart_;});

        auto& trueHeart = *it.base();
        for(int i = 0; i <= fullHearts; i++)
        {
            trueHeart.render->Sprite.setPosition(
              0 + i * spacing,
              0
            );
            if(i < fullHearts) window_.draw(trueHeart.render->Sprite);
        }
        //Render the heart semi filled
        int sizeX = trueHeart.render->Sprite.getTexture()->getSize().x;
        int sizeY = trueHeart.render->Sprite.getTexture()->getSize().y;
        //trueHeart.render->Sprite.setTextureRect(sf::IntRect{0, 0, static_cast<int> (semiHeart * sizeX), sizeY});
        //std::cout << "Deberia mostrar: "  << static_cast<int> (semiHeart * sizeX) << ", " << sizeY << std::endl;
        window_.draw(trueHeart.render->Sprite);
        
        //Return  sprite to normality
        //heart_.render->Sprite.setTextureRect({0, 0, sizeX, sizeY});
    }

    void HUDSys::update()
    {
        //Add time to counter and restart clock
        accumulatedTime += clock_.getElapsedTime().asSeconds();
        clock_.restart();

        //Set the string to show
        text_.setString(std::to_string(int(accumulatedTime)));  // int cast to avoid showing decimals
        
        //Render player's life
        renderHearts();

        //Draw
        window_.draw(text_);
    }

}

