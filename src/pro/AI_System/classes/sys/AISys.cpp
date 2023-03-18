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
            if(ent.AI)
            {
                switch(ent.AI->behaviour)
                {
                    case FVAI::SB::ARRIVE:
                    {
                        FVAI::arrive();
                        break;
                    }
                    default:break;
                }
                

            }

        }  
    }
}