#include "HUDSys.hpp"
#include <string>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include "../define.h"

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
        timeText_.setFillColor(sf::Color::White);
        timeText_.setFont(font_);
        //timeText_.setCharacterSize(40);
        timeText_.setPosition({static_cast<float>(window_.getSize().x - 85), 0});

        //Configurate coins text
        coinText_.setFillColor(sf::Color::White);
        coinText_.setFont(font_);
        //coinText_.setCharacterSize(40);
        coinText_.setPosition(34, 25);

        //create the viewport and set the position
        view_.setViewport({0.f, 0.f, 1.f, 0.2f});


        restartTime();
    }

    // HUDSys::~HUDSys()
    // {
    //     if(window_.isOpen()) window_.close();
    // }

    void HUDSys::restartTime()
    {
        accumulatedTime_ = 0;
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

    void HUDSys::setShieldID(size_t id)
    {
        shieldsp_ = id;
    }

    void HUDSys::setMaxTime(double newTime)
    {
        maxTime_ = newTime;
    }

    FVmath::Point2Di HUDSys::renderHearts()
    {
        FVmath::Point2Di lastHeartPosition {};
        //Get the player's health
        auto& hc = player_->health;
        float ch = hc->currentLife;
        //Every 100 hp, render one heart
        int   fullHearts   = static_cast<int>(ch / lifeHeart); //5
        float semiHeart    = (static_cast<int>(ch) % lifeHeart) / 100.f;
        //std::cout << "SemiHeart: " << semiHeart << std::endl;
        //Render the full hearts
        auto& EM = gMan_.getEntityManager();

        auto it = std::find_if(EM.begin(),EM.end(),[&](auto& e){ return e.id()==heart_;});

        auto& trueHeart = *it.base();
        for(int i = 0; i <= fullHearts; i++)
        {
            trueHeart.render->Sprite.setPosition(
              0 + i * spacing,
              0
            );
            if(semiHeart == 0) lastHeartPosition = {0 + (i-1) * spacing, 0};
            else               lastHeartPosition = {0 + i   * spacing, 0}; 
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

        return lastHeartPosition;
    }

    void HUDSys::renderShield(FVmath::Point2Di lastHeartPosition)
    {
        //Get the player's shield
        auto& sh = player_->shield;

        auto& EM = gMan_.getEntityManager();

        auto it = std::find_if(EM.begin(),EM.end(),[&](auto& e){ return e.id()==shieldsp_;});

        //set shield position
        auto& trueShield = *it.base();
        trueShield.render->Sprite.setPosition(
          lastHeartPosition.x + spacing,
          lastHeartPosition.y
        );
 
        //Render the shield semi filled according to refresh time
        FVmath::Point2D shieldSize = {    (float) trueShield.render->Sprite.getTexture()->getSize().x
                                     ,    (float) trueShield.render->Sprite.getTexture()->getSize().y };
        float refreshPropotion      = sh->passedTime / sh->refreshTime;

        sf::Color color(refreshPropotion * 255, refreshPropotion * 255, refreshPropotion * 255, 255);
        trueShield.render->Sprite.setColor(color);

        trueShield.render->Sprite.setTextureRect({0, 0, (int) (shieldSize.x * refreshPropotion), (int) shieldSize.y});
        window_.draw(trueShield.render->Sprite);
    }


    void HUDSys::renderTimer()
    {
        //Get the clock sprite
        auto& EM = gMan_.getEntityManager();
        auto it = std::find_if(EM.begin(),EM.end(),[&](auto& e){ return e.id()==clocksp_;});
        auto& trueClock = *it.base();

        //Position the clock
        trueClock.render->Sprite.setPosition(
            600
        ,   0
        );

        //Add time to counter and restart clock
        accumulatedTime_ += clock_.getElapsedTime().asSeconds();
        clock_.restart();

        //Set the string to show
        timeText_.setString(std::to_string(int(maxTime_ - accumulatedTime_)));  // int cast to avoid showing decimals

        //Draw
        window_.draw(timeText_);
        window_.draw(trueClock.render->Sprite);
    }

    void HUDSys::renderCoins()
    {
        //Get the player's coins data
        int coins = player_->data->coins;

        //Get the coin sprite COPIAR ESTO
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

    void HUDSys::renderGunType(){
        //Get the gun type
        auto& EM = gMan_.getEntityManager();
        std::vector<game::Entity>::iterator it;
        //game::Entity &trueGun;

        game::Entity& player = gMan_.getPlayer();
        auto tipo = player.weapon->especial;
        switch(tipo){
            case 1:
                std::cout << "tipo disparo: "<<player.weapon->especial << std::endl;
                it = std::find_if(EM.begin(),EM.end(),[&](auto& e){ return e.id()==gunEscopeta_;});
            break;
            case 2:
                std::cout << "tipo disparo: "<<player.weapon->especial << std::endl;
                it = std::find_if(EM.begin(),EM.end(),[&](auto& e){ return e.id()==gunCruz_;});
            break;
            case 3:
                std::cout << "tipo disparo: "<<player.weapon->especial << std::endl;
                it = std::find_if(EM.begin(),EM.end(),[&](auto& e){ return e.id()==gunRafaga_;});
            break;
        }
        auto& trueGun = *it.base();
        trueGun.render->Sprite.setPosition(100,100);
        window_.draw(trueGun.render->Sprite);
        
        //auto it = std::find_if(EM.begin(),EM.end(),[&](auto& e){ return e.id()==coin_;});
    }

    void HUDSys::update()
    {   
        player_ = &gMan_.getPlayer();

        //activate a view used only for the hud
        sf::View view({screenWidth / 2, screenHeight / 2}, {screenWidth, screenHeight});
        window_.setView(view);


        //Get the initial positions for rendering the hud
        //auto viewPort  = window_.getView().getViewport();
      //  viewPortTop_   = viewPort.top;
      //  viewPortLeft_  = viewPort.left;

        //Render player's life
        auto lastPos = renderHearts();

        //Render the shield indicator
        renderShield(lastPos);

        //Render player's coins
        renderCoins();

        //Render the time passed
        renderTimer();

        //render the type of special shot obtained
        renderGunType();
    }

}

