#pragma once

namespace FVmath
{
    template<typename type>
    struct Point2D_t
    {
        type x{};
        type y{};

        //Overload operator negation
        Point2D_t operator-() const {
            Point2D_t result;
            result.x = -x;
            result.y = -y;
            return result;
        }

        //non-Temporal version
        Point2D_t operator+(const Point2D_t& rhs)
        {
            Point2D_t res;
            res.x = x+rhs.x;
            res.y=  y+rhs.y;

            return res;
        }

        //Temporal version
        Point2D_t operator+(Point2D_t&& rhs)
        {
            Point2D_t res;
            res.x = x+rhs.x;
            res.y=  y+rhs.y;

            return res;
        }

        Point2D_t operator+=(const Point2D_t& rhs)
        {
            x = x+rhs.x;
            y = y+rhs.y;

            return *this;
        }

        Point2D_t operator+=(Point2D_t&& rhs)
        {
            x = x+rhs.x;
            y = y+rhs.y;

            return *this;
        }

    };

    using Point2D  =  Point2D_t<double>;
    using Point2Di =  Point2D_t<int>;

}