/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file float_compare.h
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include "inttypes.h"
#include <float.h>

namespace Sml
{
    int32_t cmpFloat(float first, float second, float epsilon = FLT_EPSILON);
}
