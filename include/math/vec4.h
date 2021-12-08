/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file vec4.h
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <assert.h>
#include <math.h>
#include "vec3.h"

namespace Sml
{
    template <typename T>
    struct Vec4
    {
        T x;
        T y;
        T z;
        T w;

        Vec4(const Vec3<T>& vector) : x(vector.x), y(vector.y), z(vector.z), w(1) {}
        Vec4(const T& x = 0, const T& y = 0, const T& z = 0, const T& w = 0) : x(x), y(y), z(z), w(w) {}

        T& getCoord(uint8_t i)
        {
            assert(i < 4);

            switch (i)
            {
                case 0: { return x; }
                case 1: { return y; }
                case 2: { return z; }
                case 3: { return w; }
            }

            return x;
        }

        const T& getCoord(uint8_t i) const
        {
            assert(i < 4);

            switch (i)
            {
                case 0: { return x; }
                case 1: { return y; }
                case 2: { return z; }
                case 3: { return w; }
            }

            return x;
        }

        Vec4& operator+=(const Vec4& second)
        {
            x += second.x;
            y += second.y;
            z += second.z;
            w += second.w;

            return *this;
        }

        Vec4& operator-=(const Vec4& second)
        {
            x -= second.x;
            y -= second.y;
            z -= second.z;
            w -= second.w;

            return *this;
        }

        Vec4& operator*=(T scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;

            return *this;
        }

        Vec4& operator/=(T scalar)
        {
            assert(scalar != 0);

            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;

            return *this;
        }
    };

    template <typename T>
    Vec4<T> operator+(const Vec4<T>& first, const Vec4<T>& second)
    {
        Vec4<T> sum(first);
        sum += second;

        return sum;
    }

    template <typename T>
    Vec4<T> operator-(const Vec4<T>& first, const Vec4<T>& second)
    {
        Vec4<T> dif(first);
        dif -= second;

        return dif;
    }

    template <typename T>
    Vec4<T> operator*(const Vec4<T>& vector, T scalar)
    {
        Vec4<T> mul(vector);
        mul *= scalar;

        return mul;
    }

    template <typename T>
    Vec4<T> operator*(T scalar, const Vec4<T>& vector)
    {
        return vector * scalar;
    }

    template <typename T>
    Vec4<T> operator/(const Vec4<T>& vector, T scalar)
    {
        Vec4<T> ratio(vector);
        ratio /= scalar;

        return ratio;
    }

    template <typename T>
    Vec4<T> operator-(const Vec4<T>& vector)
    {
        return vector * (-1.0f);
    }

    template <typename T>
    Vec4<T> componentMultiply(const Vec4<T>& first, const Vec4<T>& second)
    {
        return {first.x * second.x, first.y * second.y, first.z * second.z, first.w * second.w};
    }

    template <typename T>
    float lengthSquare(const Vec4<T>& vector)
    {
        return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z + vector.w * vector.w;
    }

    template <typename T>
    float length(const Vec4<T>& vector)
    {
        return sqrtf(lengthSquare(vector));
    }

    template <typename T>
    Vec4<T> normalize(const Vec4<T>& vector)
    {
        float len = length(vector);
        assert(len != 0);

        return vector / len;
    }

    template <typename T>
    T dotProduct(const Vec4<T>& first, const Vec4<T>& second)
    {
        return first.x * second.x + 
               first.y * second.y +
               first.z * second.z +
               first.w * second.w;
    }

    // template <typename T>
    // Vec4<T> crossProduct(const Vec4<T>& first, const Vec4<T>& second)
    // {
    //     Vec4<T> product;

    //     product.x = first.y * second.z - first.z * second.y;
    //     product.y = first.z * second.x - first.x * second.z;
    //     product.z = first.x * second.y - first.y * second.x;

    //     return product;
    // }

    using Vec4i = Vec4<int32_t>;
    using Vec4f = Vec4<float>;
}
