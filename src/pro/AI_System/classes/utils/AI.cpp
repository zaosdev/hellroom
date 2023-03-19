#include "AI.hpp"
#include "math.hpp"
#include <cmath>
#include <algorithm>

#include <iostream>

FVmath::Point2D FVAI::arrive(FVmath::Point2D origin, FVmath::Point2D target, double MaxSpeed, double friction)
{
    static int tolerance = 1;
    //std::cout << "Call to arrive from origin: " << origin.x << ", " << origin.y << ". To objective: " << target.x << ", " << target.y << std::endl;
    //Check if the distance isnt't high enough
    double distance = std::hypot(origin.x - target.x, origin.y - target.y);
    if(distance < tolerance)
    {
        //std::cout << "No enough distance to do arrive" << std::endl;
        return {};
    }
    
    //Calculate vector direction
    double dirX = target.x - origin.x;
    double dirY = target.y - origin.y;

    //Calculate rotation angle
    double angle = atan2(dirY, dirX);

    //Calculate movement using the angle
    double xMovement = cos(angle);
    double yMovement = sin(angle);

    //To simulate velocity reducction of arrive
    double reductedspeed =  std::clamp(MaxSpeed, MaxSpeed, distance / (pow(MaxSpeed, friction)));

    return {reductedspeed * xMovement, reductedspeed * yMovement};
}


FVmath::Point2D FVAI::seek(FVmath::Point2D origin, FVmath::Point2D target, double speed)
{
    return arrive(origin, target, speed, 0);
}

FVmath::Point2D FVAI::pursue(FVmath::Point2D origin, FVmath::Point2D target, double speed)
{
    return seek(origin, target, speed); 
}

FVmath::Point2D FVAI::flee(FVmath::Point2D origin, FVmath::Point2D target, double speed)
{
    return -seek(origin, target, speed); 
}