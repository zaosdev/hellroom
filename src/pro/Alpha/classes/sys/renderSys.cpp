#include "renderSys.hpp"
#include "../utils/math.hpp"
#include <cmath>
#include "../define.h"




namespace game
{
        RenderSys::RenderSys(FVeng::GameManager& Gman, HUDSys& hud)
        : gMan_(Gman), 
          window_(gMan_.getWindow()),
          HUD_ (hud)
        {
        }
        // RenderSys::~RenderSys()
        // {
        //     if(window_.isOpen()) window_.close();
        // }

        void RenderSys::iniRenderSys()
        {
         
        }

        // template<typename T>
        void RenderSys::draw(sf::Sprite& Sprite)
        {
            window_.draw(Sprite);
        }

        void RenderSys::drawMap(MapComponent& Map)
        {
            //std::cout << "Inicio de inputmanager";
            window_.draw(Map.FVSprite);

            for(int i{1}; i<Map.maxLowerLayer;i++)
            {
                gMan_.setRenderNextLayer(Map);
                window_.draw(Map.FVSprite);

            }

        }

        void RenderSys::drawUpperMap(MapComponent& Map)
        {
            //std::cout << "Inicio de inputmanager";
            for(int i{gMan_.getMapManager().getActiveLayer()+1}; i<gMan_.getMapManager().getTotalLayerCount();i++)
            {
                gMan_.setRenderNextLayer(Map);
                window_.draw(Map.FVSprite);
            }

            gMan_.resetMap(Map);

        }


        //recover world position and change it to screen position
        void RenderSys::iniSprite(game::Entity& ent, double pt)
        {
            //render sprite position according to the changes
            FVmath::Point2D newState = ent.physics->pos;
            FVmath::Point2D oldState = ent.physics->prevPos;
            

            ent.render->window_Pos.x = oldState.x * (1 - pt) + newState.x * pt;
            ent.render->window_Pos.y = oldState.y * (1 - pt) + newState.y * pt;
            //std::cout << "newstate: " << newState  << "oldstate" << oldState <<  "rendered position: " <<  ent.render->window_Pos << std::endl;

            ent.render->Sprite.setPosition(
              ent.render->window_Pos.x ,
              ent.render->window_Pos.y
            );

            if(ent.health && !ent.hasTag(game::Entity::TAG::Player))
            {
                float percentLife   = ent.health->currentLife / ent.health->maxLife;
                int   colorquantity = percentLife * 255;
                sf::Color color(255, colorquantity, colorquantity, 255);
                ent.render->Sprite.setColor(color);
            }

            else if(ent.hasTag(game::Entity::TAG::Player))
            {
                if(ent.shield->active)
                {
                    sf::Color color(255, 215, 0, 255);
                    ent.render->Sprite.setColor(color);
                }
                else
                {
                    sf::Color color(255, 255, 255, 255);
                    ent.render->Sprite.setColor(color);
                }
            }
            
        }

        void RenderSys::setVisibleArea(double pt)
        {
            //create a default view to use
            sf::View view {};

            //get the real player center
            game::Entity& player = gMan_.getPlayer();
            auto& playerSprite   = player.render->Sprite;
            sf::FloatRect bounds = playerSprite.getGlobalBounds();
            float centerX = bounds.left + bounds.width / 2.0f;
            float centerY = bounds.top + bounds.height / 2.0f;

            //Get the view size according to thw window and player life
            auto originalViewWidth  = window_.getSize().x;
            auto originalViewHeight = window_.getSize().y;
            auto lifeProportion = player.health->currentLife / player.health->maxLife;
            auto viewProportion = std::max(0.5f,  lifeProportion);
            auto viewWidth      = originalViewWidth  * viewProportion;
            auto viewHeight     = originalViewHeight * viewProportion;

            //apply the view center (player) and size 
            view.setCenter(sf::Vector2f(centerX, centerY));
            view.setSize(sf::Vector2f(viewWidth, viewHeight));
            view.zoom(screenScale);

            view.setViewport({0.f, 0.15f, 1.f, 1.f});
            // activate it
            window_.setView(view);
        }

        void RenderSys::lowLifeEffect()
        {
            game::Entity& player = gMan_.getPlayer();
            auto windowWidth     = window_.getSize().x;
            auto windowHeight    = window_.getSize().y;
            
            if(player.health->currentLife < 300)
            {
                sf::RectangleShape square {};
                float normalizedLife = 1.0f - static_cast<float>(player.health->currentLife) / 300.0f;
                auto transparency = std::lerp(redTransparencyMin, redTransparencyMax, normalizedLife);
                sf::Color redWithAlpha(255, 0, 0, transparency);
                square.setSize(sf::Vector2f(windowWidth, windowHeight));
                square.setFillColor(redWithAlpha); // Puedes cambiar el color según tus preferencias
                square.setPosition(0, 0);
                window_.draw(square);
            }
        }

        void RenderSys::update(double percentTick)
        {
            auto& EM = gMan_.getEntityManager();

            window_.clear();

            //Define and set the visible area according to the player
            setVisibleArea(percentTick);

            game::Entity* mapEnt{};
            
            for(auto& ent : EM)
            {
                if(ent.alive() && ent.map && ent.map->object_type & map_object_t::MAP)
                {
                    drawMap(*ent.map);
                    mapEnt = &ent;
                }
                if(ent.render && ent.physics)
                {
                    iniSprite(ent,percentTick);
                    draw(ent.render->Sprite);

                }
            }

            if(mapEnt)
                drawUpperMap(*mapEnt->map);

            HUD_.update();

            //Set the low life effect
            lowLifeEffect();
            
            window_.display();    

        }


}
