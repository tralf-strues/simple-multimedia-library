/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file id.h
 * @date 2021-10-18
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <assert.h>
#include <stdint.h>

namespace Sml
{
    #define SID(str) getStringId128(str)

    typedef uint64_t id64_t;

    struct id128_t
    {
        uint64_t low  = 0;
        uint64_t high = 0;

        id128_t() = default;
        id128_t(id64_t low) : low(low) {}
        id128_t(id64_t high, id64_t low) : low(low), high(high) {}
    };

    id64_t  getStringId64  (const char* str);
    id128_t getStringId128 (const char* str);
}
