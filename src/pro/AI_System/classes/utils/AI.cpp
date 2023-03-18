#include "AI.hpp"
#include "math.hpp"
#include <cmath>

#include <iostream>

FVmath::Point2D FVAI::arrive(FVmath::Point2D origin, FVmath::Point2D target, double speed)
{
    static int tolerance = 1;
    //std::cout << "Call to arrive from origin: " << origin.x << ", " << origin.y << ". To objective: " << target.x << ", " << target.y << std::endl;
    //Check if the distance isnt't high enough
    double distance = std::hypot(origin.x - target.x, origin.y - target.y);
    if(distance < tolerance)
    {
        std::cout << "No enough distance to do arrive" << std::endl;
        return {0,0};
    }
    
    //Calculate vector direction
    double dirX = target.x - origin.x;
    double dirY = target.y - origin.y;

    //Calculate rotation angle
    double angle = atan2(dirY, dirX);

    //Calculate movement using the angle
    double xMovement = cos(angle);
    double yMovement = sin(angle);
    return {speed * xMovement, speed * yMovement};
    
}