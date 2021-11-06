/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file random.h
 * @date 2021-10-02
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <math.h>

namespace Sml
{
    template <typename T>
    T randomFromInterval(T from, T to)
    {
        return from + (to - from) * ((rand() % (uint32_t) 1e6) / 1e6);
    }

    bool randomTry(float probability);
}
