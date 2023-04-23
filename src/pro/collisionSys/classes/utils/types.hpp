#pragma once

namespace FV_types
{

    //TAG definition
    struct not_valid_Type{};
    struct int_Type{};
    struct const_char_Type{};
    struct bool_Type{};


    //BASE TYPE
    template<typename T>
    struct queryTypes
    {
        typedef not_valid_Type Type;
    };

    //IMPLEMENTED TYPES
    template<>
    struct queryTypes<int*>
    {
        typedef int_Type Type;
    };
    template<>
    struct queryTypes<const char**>
    {
        typedef const_char_Type Type;
    };
    template<>
    struct queryTypes<bool*>
    {
        typedef bool_Type Type;
    };
}
        
