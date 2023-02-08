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

        }

        void RenderSys::update()
        {
            window_.clear();
            drawSprite(gMan_.ent->render->Sprite);
            window_.display();    

        }


}
