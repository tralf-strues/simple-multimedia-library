/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file ray.cpp
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 */

#include "math/ray.h"

namespace Sml
{
    Vec3<float> Ray::at(float rayParameter) const
    {
        return from + direction * rayParameter;
    }
}