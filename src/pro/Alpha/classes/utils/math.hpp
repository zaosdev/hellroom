#pragma once

#include <ostream>
#include <cmath>


namespace FVmath
{
    template<typename type>
    struct Point2Dt 
    {
        type x;
        type y;

               //Overload operator negation
        Point2Dt operator-() const 
        {
            Point2Dt result;
            result.x = -x;
            result.y = -y;
            return result;
        }

        //Overload scalar multiplication
        Point2Dt operator*(float scalar) const 
        {
            Point2Dt result;
            result.x = x * scalar;
            result.y = y * scalar;
            return result;
        }

        //Overload scalar division
        Point2Dt operator/(float scalar) const 
        {
            Point2Dt result;
            result.x = x/scalar;
            result.y = y/scalar;
            return result;
        }

        //non-Temporal version
        Point2Dt operator/(const Point2Dt& rhs)
        {
            Point2Dt res;
            res.x = x/rhs.x;
            res.y=  y/rhs.y;

            return res;
        }

        //Temporal version
        Point2Dt operator/(Point2Dt&& rhs)
        {
            Point2Dt res;
            res.x = x/rhs.x;
            res.y=  y/rhs.y;

            return res;
        }

        //non-Temporal version
        Point2Dt operator*(const Point2Dt& rhs)
        {
            Point2Dt res;
            res.x = x*rhs.x;
            res.y=  y*rhs.y;

            return res;
        }

        //Temporal version
        Point2Dt operator*(Point2Dt&& rhs)
        {
            Point2Dt res;
            res.x = x*rhs.x;
            res.y=  y*rhs.y;

            return res;
        }

        //Overload operator << 
        friend std::ostream& operator<<(std::ostream& os, const Point2Dt& point) 
        {
            os << "(" << point.x << ", " << point.y << ")";
            return os;
        }

        bool operator==(const Point2Dt& p2) const
        {
            return x == p2.x && y == p2.y;
        }

        //non-Temporal version
        Point2Dt operator+(const Point2Dt& rhs)
        {
            Point2Dt res;
            res.x = x+rhs.x;
            res.y=  y+rhs.y;

            return res;
        }

        //Temporal version
        Point2Dt operator+(Point2Dt&& rhs)
        {
            Point2Dt res;
            res.x = x+rhs.x;
            res.y=  y+rhs.y;

            return res;
        }

        //non-Temporal version
        Point2Dt operator-(const Point2Dt& rhs)
        {
            Point2Dt res;
            res.x = x-rhs.x;
            res.y=  y-rhs.y;

            return res;
        }

        //Temporal version
        Point2Dt operator-(Point2Dt&& rhs)
        {
            Point2Dt res;
            res.x = x-rhs.x;
            res.y=  y-rhs.y;

            return res;
        }

        Point2Dt operator+=(const Point2Dt& rhs)
        {
            x = x+rhs.x;
            y = y+rhs.y;

            return *this;
        }

        Point2Dt operator+=(Point2Dt&& rhs)
        {
            x = x+rhs.x;
            y = y+rhs.y;

            return *this;
        }



        float length()
        {
            return std::sqrt(x*x + y*y);
        }

        Point2Dt normaliye()
        {
            auto mag = length();

            if(mag>0)
                return *this/mag;
            else return {0,0};

        }
    };

    using Point2D = Point2Dt<float>;
    using Point2Di = Point2Dt<int>;
    
}