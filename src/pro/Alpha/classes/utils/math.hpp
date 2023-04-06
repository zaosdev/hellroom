#pragma once

#include <ostream>

namespace FVmath
{
    template<typename type>
    struct Point2Dt
    {
        type x{};
        type y{};

        //Overload operator negation
        Point2Dt operator-() const 
        {
            Point2Dt result;
            result.x = -x;
            result.y = -y;
            return result;
        }

        //Overload scalar multiplication
        Point2Dt operator*(type scalar) const 
        {
            Point2Dt result;
            result.x = x * scalar;
            result.y = y * scalar;
            return result;
        }

        //Overload operator << 
        friend std::ostream& operator<<(std::ostream& os, const Point2Dt& point) 
        {
            os << "(" << point.x << ", " << point.y << ")";
            return os;
        }

        //non-Temporal version
        Point2Dt operator+(const Point2Dt& rhs)
        {
            Point2Dt res;
            res.x = x+rhs.x;
            res.y=  y+rhs.y;

            return res;
        }

        bool operator==(const Point2Dt& p2) const
        {
            return x == p2.x && y == p2.y;
        }

        //Temporal version
        Point2Dt operator+(Point2Dt&& rhs)
        {
            Point2Dt res;
            res.x = x+rhs.x;
            res.y=  y+rhs.y;

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

    };

    using Point2D = Point2Dt<float>;
    using Point2Di = Point2Dt<int>;

}