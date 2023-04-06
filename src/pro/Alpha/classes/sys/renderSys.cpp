#include "renderSys.hpp"
#include "../utils/math.hpp"
#include <cmath>





namespace game
{
        RenderSys::RenderSys(FVeng::GameManager& Gman)
        : gMan_(Gman), window_(gMan_.getWindow())
        {
        }
        RenderSys::~RenderSys()
        {
            window_.close();
        }

        void RenderSys::iniRenderSys()
        {
            
        }

        // template<typename T>
        void RenderSys::draw(sf::Sprite& Sprite)
        {
            window_.draw(Sprite);
        }

        void RenderSys::drawFV(sfml_util::FVSprite& Sprite)
        {
            std::cout << "Inicio de inputmanager";
            window_.draw(Sprite);
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
        }

        void RenderSys::update(double percentTick)
        {

            auto& EM = gMan_.getEntityManager();

            window_.clear();

            for(auto& ent : EM)
            {
                if(ent.map) drawFV(ent.map->FVSprite);
                if(ent.render && ent.physics)
                {
                    iniSprite(ent,percentTick);
                    draw(ent.render->Sprite);
                    //draw(ent.render->FVSprite);

                }
            }

            window_.display();    

        }


}
