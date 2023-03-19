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
        void RenderSys::iniSprite()
        {
            gMan_.ent->render->Sprite.setPosition(
                gMan_.ent->physics->pos.x,
                gMan_.ent->physics->pos.y
            );
        }

        void RenderSys::update()
        {
            iniSprite();
            window_.clear();
            drawSprite(gMan_.ent->render->Sprite);
            window_.display();    

        }


}
