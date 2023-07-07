#include "AI.hpp"
#include "math.hpp"
#include <cmath>
#include <algorithm>

#include <iostream>

FVmath::Point2D FVAI::arrive(FVmath::Point2D origin, FVmath::Point2D target, double MaxSpeed, double arrivalRadius = 2, double friction = 0, bool decreaseVelocity = false, double time2arrive = 1)
{
    //Calculate distance to the target
    double distance = std::hypot(origin.x - target.x, origin.y - target.y);
    
    if(distance <= arrivalRadius)
    {
        //std::cout << "No enough distance to do arrive" << std::endl;
        return {};
    }
    else
    {
        // std::cout << "Distance: " << distance<< std::endl;
        // std::cout << "Arrival radius:" << arrivalRadius << std::endl;
    }
    
    //Calculate the desired direction and angle
    double dirX = target.x - origin.x;
    double dirY = target.y - origin.y;
    double angle = atan2(dirY, dirX);

    //To simulate velocity reducction of arrive
    double currentSpeed;
    if(decreaseVelocity) currentSpeed = distance / time2arrive;
    else                 currentSpeed = MaxSpeed;
    currentSpeed = std::clamp(currentSpeed - friction * currentSpeed, 0.0, MaxSpeed);

    //Calculate movement using the angle
    double xMovement = currentSpeed * cos(angle);
    double yMovement = currentSpeed * sin(angle);

    return {float(xMovement), float(yMovement)};
}


FVmath::Point2D FVAI::seek(FVmath::Point2D origin, FVmath::Point2D target, double speed, double arrivalRadius = 2)
{
    return arrive(origin, target, speed, arrivalRadius);
}

FVmath::Point2D FVAI::pursue(FVmath::Point2D origin, FVmath::Point2D target, double speed, double arrivalRadius = 2)
{
    return seek(origin, target, speed, arrivalRadius); 
}

FVmath::Point2D FVAI::stay()
{
    return {};
}

FVmath::Point2D FVAI::flee(FVmath::Point2D origin, FVmath::Point2D target, double speed)
{
    return -seek(origin, target, speed); 
}

FVmath::Point2D FVAI::cross(FVAI::PriotiryCross priority, double speed)
{
    if(priority == FVAI::PriotiryCross::FIRSTX) return {float(speed), 0};
    else                                        return {0, float(speed)};
}

FVmath::Point2D FVAI::followPath(FVmath::Point2D origin, circularIterator& path, double speed)
{
    auto addPos = seek(origin, path.getCurrent(), speed);
    if(addPos == FVmath::Point2D{}) path.getNext();
    return addPos;
}