/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file blur.cpp
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 */

#include <assert.h>
#include <vector>
#include "math/blur.h"

namespace Sml
{
    Kernel::Kernel(int32_t size)
    {
        assert((size % 2) == 1);

        m_Size   = size;
        m_Matrix = new float[m_Size * m_Size];
    }

    Kernel::~Kernel()
    {
        m_Size = 0;
        delete[] m_Matrix;
    }

    int32_t Kernel::getRadius() const { return (m_Size - 1) / 2; }
    int32_t Kernel::getSize() const { return m_Size; }

    float* Kernel::operator[](int32_t row)
    {
        assert(row < getSize());
        return &m_Matrix[row * getSize()];
    }

    const float* Kernel::operator[](int32_t row) const
    {
        assert(row < getSize());
        return &m_Matrix[row * getSize()];
    }

    Kernel* createGaussianBlurKernel(int32_t radius)
    {
        assert(radius >= 0);

        int32_t kernelSize = 2 * radius + 1;
        Kernel* kernel     = new Kernel(kernelSize);
        float   sigma      = std::max(static_cast<float>(radius) / 2.f, 1.f);

        float kernelSum        = 0;
        float kernelConstant   = 1 / (2 * M_PI * sigma * sigma);
        float exponentConstant = - 2 / (3 * sigma * sigma);

        for (int32_t y = -radius; y <= radius; ++y)
        {
            for (int32_t x = -radius; x <= radius; ++x)
            {
                float exponent    = (x * x + y * y) * exponentConstant;
                float kernelValue = kernelConstant * expf(exponent);

                (*kernel)[y + radius][x + radius] = kernelValue;
                kernelSum += kernelValue;
            }
        }

        for (int32_t y = 0; y < kernelSize; ++y)
        {
            for (int32_t x = 0; x < kernelSize; ++x)
            {
                (*kernel)[y][x] /= kernelSum;
            }
        }

        return kernel;
    }

    void applyKernel(const Kernel* kernel, const Rectangle<int32_t>& targetRegion)
    {
        assert(kernel);
        assert(targetRegion.width  > 0);
        assert(targetRegion.height > 0);

        Color* src = Renderer::getInstance().readTargetPixels(&targetRegion);
        assert(src);

        Color* newPixels = new Color[targetRegion.width * targetRegion.height];

        int32_t kernelRadius = kernel->getRadius();

        for (int32_t y = 0; y < targetRegion.height; ++y)
        {
            for (int32_t x = 0; x < targetRegion.width; ++x)
            {
                Vec4<float> normalizedColor = {0, 0, 0, 0};

                for (int32_t kernelY = -kernelRadius; kernelY <= kernelRadius; ++kernelY)
                {
                    for (int32_t kernelX = -kernelRadius; kernelX <= kernelRadius; ++kernelX)
                    {
                        int32_t targetY = y + kernelY;
                        int32_t targetX = x + kernelX;

                        targetX = std::max(targetX, 0);
                        targetX = std::min(targetX, targetRegion.width - 1);

                        targetY = std::max(targetY, 0);
                        targetY = std::min(targetY, targetRegion.height - 1);

                        normalizedColor += colorToNormalized(src[targetX + targetY * targetRegion.width]) *
                                           (*kernel)[kernelY + kernelRadius][kernelX + kernelRadius];
                    }
                }
                
                newPixels[x + y * targetRegion.width] = colorFromNormalized(normalizedColor);
            }
        }

        Renderer::getInstance().updateTargetPixels(newPixels, &targetRegion);

        delete[] src;
        delete[] newPixels;
    }
}