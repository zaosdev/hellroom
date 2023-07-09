#include "leverSys.hpp"

namespace game
{
    LeverSys::LeverSys(FVeng::GameManager& gameMan, game::SoundSys& soundSys)
    : gMan_(gameMan), soundSys_(soundSys)
    {
    }

    LeverSys::~LeverSys() = default;

    void LeverSys::update()
    {
        for(auto& e : gMan_.getEntityManager())
        {
            if(e.hasTag(game::Entity::TAG::LEVER))
            {
                auto& pos = e.physics->pos; //posicion cofre
                //std::cout << "pos: " << pos << std::endl;
                int posxmin = pos.x -65;
                int posxmax = pos.x +40;
                int posymin = pos.y -70;
                int posymax = pos.y +40;

                if(e.lever->pressed && (gMan_.getPlayer().physics->pos.x < posxmax) && (gMan_.getPlayer().physics->pos.x > posxmin) && (gMan_.getPlayer().physics->pos.y < posymax) && (gMan_.getPlayer().physics->pos.y > posymin))
                {
                    soundSys_.setLoop(false, soundSys_.soundLever);
                    soundSys_.playSound(soundSys_.soundLever, soundSys_.isLever);

                    gMan_.initEntityRender(e, {0,0},SFMLeng::SpriteManager::rect_i_type(6*gMan_.getMapManager().getTileSize().x,12*gMan_.getMapManager().getTileSize().y,16,16));

                    for(auto& ent : gMan_.getEntityManager())
                    {
                        if(ent.lever && ent.lever->ownerID == e.id())
                        {
                            ent.mark4destruction();
                        }
                    }
                }
                else{
                    soundSys_.stopSound(soundSys_.soundLever, soundSys_.isLever);
                }

                e.lever->pressed=false;



            }
        } 
    } 
} // namespace game

