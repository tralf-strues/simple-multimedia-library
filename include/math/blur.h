/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file blur.h
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include "../graphics_wrapper/renderer.h"
#include "../graphics_wrapper/color.h"
#include "vec2.h"

namespace Sml
{
    class Kernel
    {
    public:
        Kernel(int32_t radius = 1);
        ~Kernel();

        int32_t getRadius() const;
        int32_t getSize() const;

        float* operator[](int32_t row);
        const float* operator[](int32_t row) const;

    private:
        int32_t m_Size   = 0;
        float*  m_Matrix = nullptr;
    };

    Kernel* createGaussianBlurKernel(int32_t radius);
    Kernel* createSharpenKernel();
    void applyKernel(const Kernel* kernel, const Rectangle<int32_t>& targetRegion);
    void applyKernel(const Kernel* kernel, const Color* srcPixels, Color* dstPixels, int32_t width, int32_t height);
}