#include "renderSys.hpp"
#include "../utils/math.hpp"
#include <cmath>
#include <numeric>
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
            cameraOnPlayerCenter(centerX, centerY);
            view_.setCenter(sf::Vector2f(centerX, centerY));
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

        void RenderSys::moveCameraOnDirection(float& centerX, float& centerY) //add a little value acorrding to where you looking at
        {
            game::Entity& player = gMan_.getPlayer();
            auto& playerPos      = player.physics->pos;
            auto& playerPrevPos  = player.physics->prevPos;

            //lambdas definition
            auto isMovingRight = [&playerPos, &playerPrevPos]() {
                return playerPos.x > playerPrevPos.x;
            };

            auto isMovingLeft = [&playerPos, &playerPrevPos]() {
                return playerPos.x < playerPrevPos.x;
            };

            auto isMovingUp = [&playerPos, &playerPrevPos]() {
                return playerPos.y < playerPrevPos.y;
            };

            auto isMovingDown = [&playerPos, &playerPrevPos]() {
                return playerPos.y > playerPrevPos.y;
            };

            //X Axis
            if(isMovingRight())
            {
                centerX += tileSize * plusTilesOnDirection;
            }
            else if (isMovingLeft())
            {
                centerX -= tileSize * plusTilesOnDirection;
            }

            //Y Axis
            if(isMovingUp())
            {
                centerY -= tileSize * plusTilesOnDirection;
            }
            else if(isMovingDown())
            {
                centerY += tileSize * plusTilesOnDirection;
            }


        }

        void RenderSys::cameraOnPlayerCenter(float& centerX, float& centerY)
        {
            //get the real player center
            game::Entity& player = gMan_.getPlayer();
            auto& playerSprite   = player.render->Sprite;
            sf::FloatRect bounds = playerSprite.getGlobalBounds();
            centerX = bounds.left + bounds.width / 2.0f;
            centerY = bounds.top + bounds.height / 2.0f;
        }

        void RenderSys::getViewSize(float& viewWidth, float& viewHeight)
        {
            //Get the view size according to thw window and player life
            game::Entity& player = gMan_.getPlayer();
            auto originalViewWidth  = window_.getSize().x;
            auto originalViewHeight = window_.getSize().y;
            auto maximumHeight  =  tileSize * maxHeightTiles; //we want to see 20 tiles tall
            auto appliedScale   =  originalViewHeight / maximumHeight; //scale in height
            auto maximumWidth   =  originalViewWidth  / appliedScale;  //apply the same scale to avoid deformation
            auto lifeProportion = player.health->currentLife / player.health->maxLife;
            auto viewProportion = std::max(0.5f,  lifeProportion);
            viewWidth      = maximumWidth  * viewProportion;
            viewHeight     = maximumHeight * viewProportion;
        }

        void RenderSys::setCameraCenter(float newCenterX, float newCenterY)
        {
            // Calculate the velocity of the camera
            float cameraSpeedX = newCenterX - centerX;
            float cameraSpeedY = newCenterY - centerY;

            // If velocity is exceeded
            float cameraSpeedMagnitude = std::sqrt(cameraSpeedX * cameraSpeedX + cameraSpeedY * cameraSpeedY);
            if (cameraSpeedMagnitude > maxCameraSpeed) {
                // Reduce velocity proporcionally
                float reductionFactor = maxCameraSpeed / cameraSpeedMagnitude;
                cameraSpeedX *= reductionFactor;
                cameraSpeedY *= reductionFactor;
            }

            // Update
            centerX += cameraSpeedX;
            centerY += cameraSpeedY;

             view_.setCenter(sf::Vector2f(centerX, centerY));
        }


        void RenderSys::setVisibleArea()
        {
            game::Entity& player = gMan_.getPlayer();
            auto& playerPos      = player.physics->pos;
            auto& playerPrevPos  = player.physics->prevPos;
            auto playerMoved = [&playerPos, &playerPrevPos]() {
                return  (
                            playerPos.x != playerPrevPos.x
                        ||  playerPos.y != playerPrevPos.y 
                        );
            };

            //Get and apply the center of the view
            if(playerMoved())
            {
                float newCenterX {}; float newCenterY {};
                cameraOnPlayerCenter(newCenterX, newCenterY);
                moveCameraOnDirection(newCenterX, newCenterY);
                setCameraCenter(newCenterX, newCenterY);
            }
            
            //Get and apply the size of the view
            float viewWidth {}; float viewHeight {};
            getViewSize(viewWidth, viewHeight);
            view_.setSize(sf::Vector2f(viewWidth, viewHeight));

            //Set the viewport
            view_.setViewport({0.f, 0.15f, 1.f, 1.f});
            // activate it
            window_.setView(view_);
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
            setVisibleArea();

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
