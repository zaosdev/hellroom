#include "HUDSys.hpp"
#include <string>
#include <iomanip>
#include <algorithm>

#define FONT_PATH "../media/font/Retro_Gaming.ttf"

//#include "../utils/math.hpp"
//#include <cmath>
namespace game
{
    static constexpr int lifeHeart = 100.f;

    HUDSys::HUDSys(FVeng::GameManager& Gman)
    : gMan_   (Gman),
     window_  (gMan_.getWindow())
    {
        if (!font_.loadFromFile(FONT_PATH)) {
            // manejar error de carga de fuente
            std::terminate();
        }
        //Configurate time text
        timeText_.setFillColor(sf::Color::Black);
        timeText_.setFont(font_);
        //timeText_.setCharacterSize(40);
        timeText_.setPosition({static_cast<float>(window_.getSize().x - 85), 0});

        //Configurate coins text
        coinText_.setFillColor(sf::Color::Black);
        coinText_.setFont(font_);
        //coinText_.setCharacterSize(40);
        coinText_.setPosition(34, 25);


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

    void HUDSys::setPlayer(Entity* player)
    {   
        player_ = player;
    }

    void HUDSys::setHeartID(size_t id)
    {
        heart_ = id;
    }

    void HUDSys::setCoinID(size_t id)
    {
        coin_ = id;
    }

    void HUDSys::setClockID(size_t id)
    {
        clocksp_ = id;
    }

    void HUDSys::setMaxTime(double newTime)
    {
        maxTime_ = newTime;
    }

    void HUDSys::renderHearts()
    {
        //Get the player's health
        auto& hc = player_->health;
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
        trueHeart.render->Sprite.setTextureRect(sf::IntRect{0, 0, static_cast<int> (semiHeart * sizeX), sizeY});
        //std::cout << "Deberia mostrar: "  << static_cast<int> (semiHeart * sizeX) << ", " << sizeY << std::endl;
        window_.draw(trueHeart.render->Sprite);
        
        //Return  sprite to normality
        trueHeart.render->Sprite.setTextureRect({0, 0, sizeX, sizeY});
    }

    void HUDSys::renderTimer()
    {
        //Get the clock sprite
        auto& EM = gMan_.getEntityManager();
        auto it = std::find_if(EM.begin(),EM.end(),[&](auto& e){ return e.id()==clocksp_;});
        auto& trueClock = *it.base();

        //Position the coin
        trueClock.render->Sprite.setPosition(
            600
        ,   0
        );

        //Add time to counter and restart clock
        accumulatedTime += clock_.getElapsedTime().asSeconds();
        clock_.restart();

        //Set the string to show
        timeText_.setString(std::to_string(int(maxTime_ - accumulatedTime)));  // int cast to avoid showing decimals

        //Draw
        window_.draw(timeText_);
        window_.draw(trueClock.render->Sprite);
    }

    void HUDSys::renderCoins()
    {
        //Get the player's coins data
        int coins = player_->data->coins;

        //Get the coin sprite
        auto& EM = gMan_.getEntityManager();
        auto it = std::find_if(EM.begin(),EM.end(),[&](auto& e){ return e.id()==coin_;});
        auto& trueCoin = *it.base();

        //Position the coin
        trueCoin.render->Sprite.setPosition(
            2
        ,   30
        );

        //Position the text
        coinText_.setString(std::to_string(coins)); 

    
        //Draw sprite and coin text
        window_.draw(trueCoin.render->Sprite);
        window_.draw(coinText_);
    }

    void HUDSys::update()
    {   
        //Render player's life
        renderHearts();

        //Render player's coins
        renderCoins();

        //Render the time passed
        renderTimer();
    }

}

