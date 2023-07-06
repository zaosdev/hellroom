#pragma once 
#include <array>

namespace game
{
    struct ShieldComponent
    {
        bool    active             {false};
        float   refreshTime        {10.f}; //seconds
        float   passedTime         {0.f};  //seconds 
        bool    autoActive         {false};//if true, doesnt need to press any key
        float   activatedTime      {0.f};  //time from activation
        float   max_ActivatedTime  {3.f};  //maximum time active
    };
}