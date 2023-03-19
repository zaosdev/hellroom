#include "AISys.hpp"
#include "utils/AI.hpp"
#include <iostream>

namespace game
{
    AISys::AISys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
    }

    void AISys::update()
    {
        auto& EM = gMan_.getEntityManager();

        for(auto& ent : EM)
        {
            if(ent.AI && ent.physics)
            {
                FVmath::Point2D addPos;
                switch(ent.AI->behaviour)
                {
                    case FVAI::SB::ARRIVE:
                    {
                        addPos = FVAI::arrive(ent.physics->pos, ent.AI->targetCoord, ent.physics->mov_speed, ent.AI->friction);
                        break;
                    }
                    case FVAI::SB::SEEK:
                    {
                        addPos = FVAI::seek(ent.physics->pos, ent.AI->targetCoord, ent.physics->mov_speed);
                        break;
                    }
                    case FVAI::SB::PURSUE:
                    {
                        auto* Target = EM.getEntityByID(ent.AI->targetID);
                        if(Target!=nullptr && Target->physics)
                        {
                            //Precalculate position
                            FVmath::Point2D proxTargetPos = Target->physics->pos + Target->physics->vel;
                            //Send to the AI
                            addPos = FVAI::pursue(ent.physics->pos, proxTargetPos, ent.physics->mov_speed);
                        }
                        break;
                    }
                    case FVAI::SB::FLEE:
                    {
                        addPos = FVAI::flee(ent.physics->pos, ent.AI->targetCoord, ent.physics->mov_speed);
                        break;
                    }
                    default:break;
                }
                std::cout << "position adding: " << addPos.x << ", "<< addPos.y << std::endl;
                ent.physics->vel = addPos;
            }

        }  
    }
}