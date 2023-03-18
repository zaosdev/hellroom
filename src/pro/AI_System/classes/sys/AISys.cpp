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
                        addPos = FVAI::arrive(ent.physics->pos, ent.AI->targetCoord);
                        break;
                    }
                    default:break;
                }
                ent.physics->pos+= addPos;
            }

        }  
    }
}