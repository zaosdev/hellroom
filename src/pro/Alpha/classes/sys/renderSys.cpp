#include "renderSys.hpp"
#include "../utils/math.hpp"
#include <cmath>





namespace game
{
        RenderSys::RenderSys(FVeng::GameManager& Gman, HUDSys& hud)
        : gMan_(Gman), 
          window_(gMan_.getWindow()),
          HUD_ (hud)
        {
        }
        RenderSys::~RenderSys()
        {
            if(window_.isOpen()) window_.close();
        }

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

        void RenderSys::update(double percentTick)
        {
            auto& EM = gMan_.getEntityManager();

            window_.clear();

            game::Entity* mapEnt{};
            
            for(auto& ent : EM)
            {
                if(ent.map)
                {
                    drawMap(*ent.map);
                    mapEnt = &ent;
                }
                if(ent.render && ent.physics)
                {
                    iniSprite(ent,percentTick);
                    draw(ent.render->Sprite);
                    //draw(ent.render->FVSprite);

                }
            }


            drawUpperMap(*mapEnt->map);

            HUD_.update();

            window_.display();    

        }


}
