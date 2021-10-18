//------------------------------------------------------------------------------
//! @author Nikita Mochalov (github.com/tralf-strues)
//! @file id.cpp
//! @date 2021-10-18
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#include "utils/id.h"

id128_t getStringId128(const char* str)
{
    assert(str);

    uint64_t curByte = 0;
    id128_t  id      = {};

    while (*str != 0 && curByte < sizeof(id128_t))
    {
        if (curByte < sizeof(uint64_t))
        {
            id.low += static_cast<uint64_t>(*str);

            if (curByte < sizeof(uint64_t) - 1)
            {
                id.low <<= 8;
            }
        }
        else
        {
            id.high += static_cast<uint64_t>(*str);

            if ((curByte % sizeof(uint64_t)) < sizeof(uint64_t) - 1)
            {
                id.high <<= 8;
            }
        }

        ++curByte;
    }

    return id;
}