//------------------------------------------------------------------------------
//! @author Nikita Mochalov (github.com/tralf-strues)
//! @file id.cpp
//! @date 2021-10-18
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#include "utils/id.h"

namespace Sml
{

id64_t getStringId64(const char* str)
{
    assert(str);

    uint64_t curByte = 0;
    id64_t   id      = 0;

    while (*str != 0 && curByte < sizeof(id64_t))
    {
        id += static_cast<id64_t>(*str);

        if (curByte < sizeof(id64_t) - 1)
        {
            id <<= 8;
        }

        ++curByte;
    }

    return id;
}

id128_t getStringId128(const char* str)
{
    assert(str);

    id128_t id = {};
    id.low = getStringId64(str);

    uint64_t curByte = 0;
    while (str[curByte] != 0 && curByte < sizeof(id64_t)) 
    { 
        ++curByte;
    }

    if (curByte == sizeof(id64_t) && str[curByte] != 0)
    {
        id.high = getStringId64(str + curByte);
    }

    return id;
}

}