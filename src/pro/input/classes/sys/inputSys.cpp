#include "inputSys.hpp"

namespace game
{
    InputSys::InputSys(FVeng::GameManager& gameMan, InputManager& inpMan)
    : gMan_(gameMan), inpRec_(inpMan)
    {
    }

    void InputSys::update()
    {
        gMan_.ent->physics->vel = {0,0};

        
        if(inpRec_.isWPressed())  gMan_.ent->physics->vel += {0,-5};
        if(inpRec_.isAPressed())  gMan_.ent->physics->vel += {-5,0};
        if(inpRec_.isSPressed())  gMan_.ent->physics->vel += {0,5};
        if(inpRec_.isDPressed())  gMan_.ent->physics->vel += {5,0};


    }

}

