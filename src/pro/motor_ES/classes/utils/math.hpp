#pragma once

namespace FVmath
{
    struct vec2D
    {
        float x{};
        float y{};

        //non-Temporal version
        vec2D operator+(const vec2D& vec)
        {
            vec2D res;
            res.x = x+vec.x;
            res.y=  y+vec.y;

            return res;
        }

        //Temporal version
        vec2D operator+(vec2D&& vec)
        {
            vec2D res;
            res.x = x+vec.x;
            res.y=  y+vec.y;

            return res;
        }

        vec2D operator+=(const vec2D& vec)
        {
            x = x+vec.x;
            y = y+vec.y;

            return *this;
        }

        vec2D operator+=(vec2D&& vec)
        {
            x = x+vec.x;
            y = y+vec.y;

            return *this;
        }


    };
}