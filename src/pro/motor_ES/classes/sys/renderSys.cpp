#include "renderSys.hpp"
#include "../utils/math.hpp"




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
        void RenderSys::iniSprite(game::Entity& ent)
        {
            ent.render->Sprite.setPosition(
                ent.physics->pos.x,
                ent.physics->pos.y
            );
        }

        void RenderSys::update()
        {

            auto& EM = gMan_.getEntityManager();

            window_.clear();

            for(auto& ent : EM)
            {
                if(ent.render)
                {
                    iniSprite(ent);
                    drawSprite(ent.render->Sprite);
                }
            }

            window_.display();    

        }


}
