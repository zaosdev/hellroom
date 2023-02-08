#include "renderSys.hpp"
#include "../utils/math.hpp"




namespace game
{
        RenderSys::RenderSys(FVeng::GameManager& gMan)
        : gMan_(gMan), window_(gMan_.getWindow())
        {
        }
        RenderSys::~RenderSys()
        {
            window_.close();
        }

        void RenderSys::iniRenderSys()
        {
            
        }
        void RenderSys::drawSprite()
        {
            if(ent.render)
            {
                window_.draw(ent.render->Sprite);
            }

        }
        void RenderSys::iniSprite()
        {

        }

        void RenderSys::update()
        {
            window_.clear();
            drawSprite();
            window_.display();    

        }


}
