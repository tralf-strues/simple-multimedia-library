/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file renderer.cpp
 * @date 2021-09-11
 * 
 * @copyright Copyright (c) 2021
 */

#include <assert.h>
#include "sml_log.h"
#include "graphics_wrapper/renderer.h"

namespace Sml
{
    Renderer* Renderer::s_Instance;

    void Renderer::init(Window* window)
    {
        assert(window);

        if (s_Instance != nullptr) { return; }

        s_Instance = new Renderer(window);

        s_Instance->m_Window->setSurface(new Texture(s_Instance->m_Window->getWidth(),
                                                     s_Instance->m_Window->getHeight()));

        s_Instance->setTarget(WINDOW_TARGET);
    }

    Renderer& Renderer::getInstance()
    {
        return *s_Instance;
    }

    bool Renderer::isInitialized()
    {
        return s_Instance != nullptr;
    }

    Renderer::Renderer(Window* window) : m_Window(window)
    {
        assert(window);

        m_NativeRenderer = SDL_CreateRenderer(m_Window->getNativeWindow(),
                                              -1, 
                                              SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
        if (m_NativeRenderer == nullptr)
        {
            setError(Renderer::CREATE_ERROR);
            return;
        }

        m_WindowSpecificNativeRenderers[m_Window] = m_NativeRenderer;

        setBlendMode(BlendMode::BLEND);
    }

    Renderer::~Renderer()
    {
        for (auto nativeRenderer : m_WindowSpecificNativeRenderers)
        {
            SDL_DestroyRenderer(nativeRenderer.second);
        }
    }

    Color Renderer::getColor() const
    {
        return m_Color;
    }

    void Renderer::setColor(Color color)
    {
        m_Color = color;
        SDL_SetRenderDrawColor(m_NativeRenderer, colorGetR(color), 
                                                 colorGetG(color), 
                                                 colorGetB(color), 
                                                 colorGetA(color));
    }

    Renderer::BlendMode Renderer::getBlendMode() const
    {
        return m_BlendMode;
    }

    void Renderer::setBlendMode(BlendMode mode)
    {
        m_BlendMode = mode;

        switch (mode)
        {
            case BlendMode::NONE:
            {
                SDL_SetRenderDrawBlendMode(getNativeRenderer(), SDL_BLENDMODE_NONE);
                break;
            }

            case BlendMode::BLEND:
            {
                SDL_SetRenderDrawBlendMode(getNativeRenderer(), SDL_BLENDMODE_BLEND);
                break;
            }

            case BlendMode::ADD:
            {
                SDL_SetRenderDrawBlendMode(getNativeRenderer(), SDL_BLENDMODE_ADD);
                break;
            }
            
            default:
            {
                LOG_LIB_ERROR("Invalid BlendMode");
            }
        }
    }

    uint32_t Renderer::getError() const
    {
        return m_ErrorStatus;  
    }

    Window& Renderer::getWindow() const
    {
        return *m_Window;
    }

    SDL_Renderer* Renderer::getNativeRenderer() const
    {
        return m_NativeRenderer;
    }

    void Renderer::setError(uint32_t error)
    {
        m_ErrorStatus |= error;
    }

    void Renderer::present()
    {
        if (m_TargetTexture == m_Window->getSurface())
        {
            pushTarget();

            SDL_SetRenderTarget(m_NativeRenderer, nullptr);
            renderTexture(*m_Window->getSurface(), nullptr, nullptr);

            SDL_RenderPresent(m_NativeRenderer);

            popTarget();
        }
    }

    void Renderer::clear()
    {
        if (m_TargetTexture == m_Window->getSurface())
        {
            pushTarget();

            SDL_SetRenderTarget(m_NativeRenderer, nullptr);
            SDL_RenderClear(m_NativeRenderer);

            popTarget();
        }

        SDL_RenderClear(m_NativeRenderer);
    }

    void Renderer::pushTarget()
    {
        m_TargetStack.push(m_TargetTexture);
    }

    void Renderer::popTarget()
    {
        assert(!m_TargetStack.empty());

        m_TargetTexture = m_TargetStack.top();
        m_TargetStack.pop();

        setTarget(m_TargetTexture);
    }

    void Renderer::pushSetTarget(Texture* targetTexture)
    {
        pushTarget();
        setTarget(targetTexture);
    }

    void Renderer::setTarget(Texture* targetTexture)
    {
        m_TargetTexture = (targetTexture == WINDOW_TARGET) ? m_Window->getSurface() : targetTexture;

        SDL_SetRenderTarget(m_NativeRenderer, m_TargetTexture->getNativeTexture());
    }

    Texture* Renderer::getTarget()
    {
        return m_TargetTexture;
    }

    size_t Renderer::getTargetWidth() const
    {
        return static_cast<int32_t>(m_TargetTexture->getWidth());
    }

    size_t Renderer::getTargetHeight() const
    {
        return static_cast<int32_t>(m_TargetTexture->getHeight());
    }

    Color* Renderer::readTargetPixels(const Rectangle<int32_t>* targetRegion) const
    {
        Rectangle<int32_t> realRegion = (targetRegion != nullptr) ?
                                        *targetRegion :
                                        Rectangle<int32_t>{{0, 0},
                                                           static_cast<int32_t>(getTargetWidth()),
                                                           static_cast<int32_t>(getTargetHeight())};

        if (realRegion.width <= 0 || realRegion.height <= 0)
        {
            return nullptr;
        }

        Color* pixels = new Color[realRegion.width * realRegion.height];
        readTargetPixelsTo(pixels, targetRegion);

        return pixels;
    }

    void Renderer::readTargetPixelsTo(Color* dst, const Rectangle<int32_t>* targetRegion) const
    {
        assert(dst);

        SDL_Rect rect;
        if (targetRegion != nullptr)
        {
            rect = {targetRegion->pos.x, targetRegion->pos.y, targetRegion->width, targetRegion->height};
        }

        SDL_RenderReadPixels(getNativeRenderer(),
                             targetRegion == nullptr ? nullptr : &rect,
                             SDL_PIXELFORMAT_RGBA8888,
                             dst,
                             (targetRegion == nullptr ? getTargetWidth() : rect.w) * sizeof(Color));
    }

    void Renderer::updateTargetPixels(const Color* src, const Rectangle<int32_t>* targetRegion)
    {
        assert(src);

        getTarget()->updatePixels(src, targetRegion);
    }

    void Renderer::setClipRegion(const Rectangle<int32_t>& clipRegion) const
    {
        SDL_Rect rect = {clipRegion.pos.x, clipRegion.pos.y, clipRegion.width, clipRegion.height};

        SDL_RenderSetClipRect(m_NativeRenderer, &rect);
    }

    void Renderer::resetClipRegion() const
    {
        SDL_RenderSetClipRect(m_NativeRenderer, nullptr);
    }

    void Renderer::renderPoint(const Vec2i& pos)
    {
        SDL_RenderDrawPoint(m_NativeRenderer, pos.x, pos.y);
    }

    void Renderer::renderLine(const Vec2i& start, const Vec2i& end)
    {
        SDL_RenderDrawLine(m_NativeRenderer, start.x, start.y, end.x, end.y);
    }

    void Renderer::renderTexture(const Texture& texture,
                                 const Rectangle<int32_t>* targetRegion,
                                 const Rectangle<int32_t>* sourceRegion)
    {
        SDL_Rect targetRect;
        SDL_Rect sourceRect;

        SDL_Rect* pTargetRect = nullptr;
        SDL_Rect* pSourceRect = nullptr;

        if (targetRegion != nullptr)
        {
            targetRect = toNativeRectangle(*targetRegion);
            pTargetRect = &targetRect;
        }

        if (sourceRegion != nullptr)
        {
            sourceRect = toNativeRectangle(*sourceRegion);
            pSourceRect = &sourceRect;
        }

        SDL_RenderCopy(m_NativeRenderer, texture.getNativeTexture(), pSourceRect, pTargetRect);
    }

    void Renderer::renderTexture(const Texture& texture, const Vec2i& pos)
    {
        Rectangle<int32_t> targetRegion{pos, static_cast<int32_t>(texture.getWidth()),
                                            static_cast<int32_t>(texture.getHeight())};

        renderTexture(texture, &targetRegion, nullptr);
    }

    void renderPoint(const Vec2i& pos)
    {
        Renderer::getInstance().renderPoint(pos);
    }

    void renderLine(const Vec2i& start, const Vec2i& end)
    {
        Renderer::getInstance().renderLine(start, end);
    }

    void renderTexture(const Texture& source,
                    const Rectangle<int32_t>* targetRegion,
                    const Rectangle<int32_t>* sourceRegion)
    {
        Renderer::getInstance().renderTexture(source, targetRegion, sourceRegion);
    }

    void renderTexture(const Texture& texture, const Vec2i& pos)
    {
        Renderer::getInstance().renderTexture(texture, pos);
    }
}