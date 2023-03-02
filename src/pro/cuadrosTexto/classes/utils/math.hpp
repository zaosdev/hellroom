#pragma once

namespace FVmath
{
    template<typename type>
    struct vec2Dt
    {
        type x{};
        type y{};

        //non-Temporal version
        vec2Dt operator+(const vec2Dt& rhs)
        {
            vec2Dt res;
            res.x = x+rhs.x;
            res.y=  y+rhs.y;

            return res;
        }

        //Temporal version
        vec2Dt operator+(vec2Dt&& rhs)
        {
            vec2Dt res;
            res.x = x+rhs.x;
            res.y=  y+rhs.y;

            return res;
        }

        vec2Dt operator+=(const vec2Dt& rhs)
        {
            x = x+rhs.x;
            y = y+rhs.y;

            return *this;
        }

        vec2Dt operator+=(vec2Dt&& rhs)
        {
            x = x+rhs.x;
            y = y+rhs.y;

            return *this;
        }

    };

    using vec2D = vec2Dt<float>;
    using vec2Di = vec2Dt<int>;

}