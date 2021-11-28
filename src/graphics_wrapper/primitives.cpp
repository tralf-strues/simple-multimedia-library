/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file primitives.cpp
 * @date 2021-09-05
 * 
 * @copyright Copyright (c) 2021
 */

#include "graphics_wrapper/primitives.h"

namespace Sml
{
    void renderRect(const Rectangle<int32_t>& rect, uint8_t thickness)
    {
        Vec2<int32_t> upperLeftCorner(rect.pos.x, rect.pos.y);
        Vec2<int32_t> upperRightCorner(rect.pos.x + rect.width - 1, rect.pos.y);
        
        Vec2<int32_t> bottomLeftCorner(rect.pos.x, rect.pos.y + rect.height - 1);
        Vec2<int32_t> bottomRightCorner(rect.pos.x + rect.width - 1, rect.pos.y + rect.height - 1);

        for (int32_t step = 0; static_cast<uint8_t>(step) < thickness; ++step)
        {
            // Top line
            renderLine(upperLeftCorner, upperRightCorner);

            // Bottom line
            renderLine(bottomLeftCorner, bottomRightCorner);

            // Left line
            renderLine(upperLeftCorner, bottomLeftCorner);

            // Right line
            renderLine(upperRightCorner, bottomRightCorner);

            upperLeftCorner   += Vec2<int32_t>{  1,  1 };
            upperRightCorner  += Vec2<int32_t>{ -1,  1 };
            bottomLeftCorner  += Vec2<int32_t>{  1, -1 };
            bottomRightCorner += Vec2<int32_t>{ -1, -1 };
        }
    }

    void renderFilledRect(const Rectangle<int32_t>& rect)
    {
        for (int32_t row = 0; row < rect.height; ++row)
        {
            renderLine(Vec2<int32_t>{rect.pos.x, rect.pos.y + row}, 
                       Vec2<int32_t>{rect.pos.x + rect.width - 1, rect.pos.y + row});
        }
    }

    void renderCircle(const Circle& circle)
    {
        int32_t diameter = 2 * circle.radius;

        int32_t x     = (circle.radius - 1);
        int32_t y     = 0;
        int32_t tx    = 1;
        int32_t ty    = 1;
        int32_t error = (tx - diameter);

        while (x >= y)
        {
            renderPoint({circle.center.x + x, circle.center.y - y});
            renderPoint({circle.center.x + x, circle.center.y + y});
            renderPoint({circle.center.x - x, circle.center.y - y});
            renderPoint({circle.center.x - x, circle.center.y + y});
            renderPoint({circle.center.x + y, circle.center.y - x});
            renderPoint({circle.center.x + y, circle.center.y + x});
            renderPoint({circle.center.x - y, circle.center.y - x});
            renderPoint({circle.center.x - y, circle.center.y + x});

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty    += 2;
            }

            if (error > 0)
            {
                --x;
                tx    += 2;
                error += (tx - diameter);
            }
        }
    }

    void renderFilledCircle(const Circle& circle)
    {
        for (int w = 0; w < 2 * circle.radius; w++)
        {
            for (int h = 0; h < 2 * circle.radius; h++)
            {
                int dx = circle.radius - w;
                int dy = circle.radius - h;

                if ((dx * dx + dy * dy) <= (circle.radius * circle.radius))
                {
                    renderPoint(Vec2<int32_t>{circle.center.x + dx, circle.center.y + dy});
                }
            }
        }
    }

    bool intersectInfLines(const InfLine& line1, const InfLine& line2, Vec2<float>* intersection)
    {
        assert(intersection);

        const Vec2<float>& firstFrom       = line1.from;
        const Vec2<float>& secondFrom      = line2.from;
        const Vec2<float>& firstDirection  = line1.direction;
        const Vec2<float>& secondDirection = line2.direction;

        float det = firstDirection.y * secondDirection.x - firstDirection.x * secondDirection.y;
        if (cmpFloat(det, 0) == 0)
        {
            return false;
        }

        float t = secondDirection.x * (secondFrom.y - firstFrom.y) - 
                secondDirection.y * (secondFrom.x - firstFrom.x);

        t /= det;
        *intersection = firstFrom + t * firstDirection;

        return true;
    }

    void renderInfLine(const InfLine& infLine)
    {
        float width  = Renderer::getInstance().getTargetWidth();
        float height = Renderer::getInstance().getTargetHeight();

        InfLine topLine    = {Vec2<float>{0,     0     }, Vec2<float>{1, 0}};
        InfLine bottomLine = {Vec2<float>{0,     height}, Vec2<float>{1, 0}};
        InfLine rightLine  = {Vec2<float>{width, 0     }, Vec2<float>{0, 1}};
        InfLine leftLine   = {Vec2<float>{0,     0     }, Vec2<float>{0, 1}};

        Vec2<float> intersections[4] = {};
        int32_t intersectionsCount = 0;

        if (intersectInfLines(infLine, topLine, &intersections[intersectionsCount]))
        {
            ++intersectionsCount;
        }

        if (intersectInfLines(infLine, bottomLine, &intersections[intersectionsCount]))
        {
            ++intersectionsCount;
        }

        if (intersectInfLines(infLine, rightLine, &intersections[intersectionsCount]))
        {
            ++intersectionsCount;
        }

        if (intersectInfLines(infLine, leftLine, &intersections[intersectionsCount]))
        {
            ++intersectionsCount;
        }

        if (intersectionsCount > 1)
        {
            renderLine(intersections[0], intersections[1]);
        }
    }
}