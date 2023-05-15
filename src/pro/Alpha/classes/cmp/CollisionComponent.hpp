#pragma once 

namespace game
{
    
    struct CollisionComponent{

        FVmath::Point2D contactPoint{};
        FVmath::Point2D contactNormal{};
        float contactTime{};

    };
}