#pragma once
#include <iostream>

namespace FVmath
{
    template<typename type>
    struct Point2D_t
    {
        type x{};
        type y{};

        //Overload operator negation
        Point2D_t operator-() const 
        {
            Point2D_t result;
            result.x = -x;
            result.y = -y;
            return result;
        }

        //Overload scalar multiplication
        Point2D_t operator*(type scalar) const 
        {
            Point2D_t result;
            result.x = x * scalar;
            result.y = y * scalar;
            return result;
        }

        //Overload operator << 
        friend std::ostream& operator<<(std::ostream& os, const Point2D_t& point) 
        {
            os << "(" << point.x << ", " << point.y << ")";
            return os;
        }

        //non-Temporal version
        Point2D_t operator+(const Point2D_t& rhs)
        {
            Point2D_t res;
            res.x = x+rhs.x;
            res.y=  y+rhs.y;

            return res;
        }

        bool operator==(const Point2D_t& p2) 
        {
            return x == p2.x && y == p2.y;
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


    //Dim2D sprite dimensions

    struct Dim2D{
        uint32_t w{}, h{};
        uint32_t size() const noexcept { return w*h; }
    };
    

    //Rect2D

    struct Rect2D{

        struct Segment { 
            int32_t min{}, max{};
        };

        int32_t left{}, right{};
        int32_t up{}, down{};


        [[nodiscard]]  constexpr bool segmentsCollide(Segment const A, Segment const B) const noexcept {
            return not (A.max < B.min || B.max < A.min);
        }


        [[nodiscard]]  constexpr bool collidesWith(Rect2D const& B) const noexcept {

            return (segmentsCollide({left, right}, {B.left, B.right}) && segmentsCollide({up, down}, {B.up, B.down}));

        }

        //constexpr bool operator<=>(Rect2D const&) const noexcept = default;


        static Rect2D from(Dim2D const dim, int32_t const dw, int32_t const dh) {

           return{
                .left   = dw,
                .right  = int32_t(dim.w) - dw,
                .up     = dh, 
                .down   = int32_t(dim.h) - dh,

           };

        }
    };



}