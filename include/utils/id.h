//------------------------------------------------------------------------------
//! @author Nikita Mochalov (github.com/tralf-strues)
//! @file id.h
//! @date 2021-10-18
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#ifndef ID_H
#define ID_H

#include <assert.h>
#include <stdint.h>

#define SID(str) getStringId128(str)

struct id128_t
{
    uint64_t low  = 0;
    uint64_t high = 0;
};

id128_t getStringId128(const char* str);

#endif // ID_H