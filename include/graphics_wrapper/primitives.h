/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file primitives.h
 * @date 2021-09-05s
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include "renderer.h"

namespace Sml
{
    struct Circle
    {
        Vec2<int32_t> center;
        int32_t       radius;
    };

    struct InfLine
    {
        Vec2<float> from;
        Vec2<float> direction;
    };

    void renderRect(const Rectangle<int32_t>& rect, uint8_t thickness = 1);
    void renderFilledRect(const Rectangle<int32_t>& rect);
    void renderCircle(const Circle& circle);
    void renderFilledCircle(const Circle& circle);
    void renderInfLine(const InfLine& infLine);
}
