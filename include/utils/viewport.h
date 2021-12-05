/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file viewport.h
 * @date 2021-09-27
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include "../sml_graphics_wrapper.h"

namespace Sml
{
    struct Viewport
    {
        Viewport(const Vec2f& axesMin, const Vec2f& axesMax, const Rectangle<int32_t>& windowArea);

        Vec2f axesMin;
        Vec2f axesMax;

        Rectangle<int32_t> windowArea;

        float getRelativeWidth()  const;
        float getRelativeHeight() const;

        Vec2f toPixels(const Vec2f& point) const;
        float       toPixels(float distance) const;
    };
}
