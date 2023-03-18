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
        void RenderSys::drawSprite(sf::Sprite& Sprite)
        {
            window_.draw(Sprite);
        }

        //recover world position and change it to screen position
        void RenderSys::iniSprite(game::Entity& ent)
        {
            ent.render->window_Pos.x = int( std::round(ent.physics->pos.x));
            ent.render->window_Pos.y = int( std::round(ent.physics->pos.y));

            ent.render->Sprite.setPosition(
              ent.render->window_Pos.x ,
              ent.render->window_Pos.y
            );
        }

        void RenderSys::update()
        {

            auto& EM = gMan_.getEntityManager();

            window_.clear();

            for(auto& ent : EM)
            {
                if(ent.render && ent.physics)
                {
                    iniSprite(ent);
                    drawSprite(ent.render->Sprite);
                }
            }

            window_.display();    

        }


}
