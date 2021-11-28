/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file window.cpp
 * @date 2021-09-01
 * 
 * @copyright Copyright (c) 2021
 */

#include <assert.h>
#include <SDL_ttf.h>
#include "graphics_wrapper/window.h"
#include "graphics_wrapper/texture.h"

namespace Sml
{
    Window::Window(size_t width, size_t height, const char* title)
        : m_Width(width), m_Height(height), m_Title(title) 
    {
        assert(m_Width);
        assert(m_Height);

        m_NativeWindow = SDL_CreateWindow(title, 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          m_Width, m_Height, 0);

        if (m_NativeWindow == nullptr)
        {
            setError(CREATE_ERROR);
            return;
        }
    }

    Window::~Window()
    {
        SDL_DestroyWindow(m_NativeWindow);
    }

    size_t Window::getWidth() const 
    { 
        return m_Width;       
    }

    size_t Window::getHeight() const 
    { 
        return m_Height;      
    }

    const char* Window::getTitle() const 
    { 
        return m_Title;       
    }

    uint32_t Window::getError() const 
    { 
        return m_ErrorStatus; 
    }

    SDL_Window* Window::getNativeWindow() const
    {
        return m_NativeWindow;
    }

    Texture* Window::getSurface() const
    {
        return m_Surface;
    }

    void Window::setSurface(Texture* surface)
    {
        assert(surface);
        
        if (m_Surface != nullptr)
        {
            delete m_Surface;
        }

        m_Surface = surface;
    }

    // Color* Window::readPixels(const Rectangle<int32_t>* region) const
    // {
    //     int32_t width  = (region != nullptr) ? region->width  : getWidth();
    //     int32_t height = (region != nullptr) ? region->height : getHeight();

    //     if (width <= 0 || height <= 0)
    //     {
    //         return nullptr;
    //     }

    //     Color* pixels = new Color[width * height];
    //     readPixelsTo(pixels, region);

    //     return pixels;
    // }

    // void Window::readPixelsTo(Color* dst, const Rectangle<int32_t>* region) const
    // {
    //     assert(dst);

    //     SDL_Surface* surface = SDL_GetWindowSurface(getNativeWindow());
    //     if (surface == nullptr)
    //     {
    //         printf("%s\n", SDL_GetError());
    //     }

    //     Rectangle<int32_t> realRegion = (region != nullptr) ?
    //                                     *region :
    //                                     Rectangle<int32_t>{{0, 0},
    //                                                        static_cast<int32_t>(getWidth()),
    //                                                        static_cast<int32_t>(getHeight())};

    //     if (region != nullptr)
    //     {
    //         for (int32_t row = 0; row < realRegion.height; ++row)
    //         {
    //             Color*       dstStart = dst + realRegion.width * row;
    //             const Color* srcStart = static_cast<const Color*>(surface->pixels) +
    //                                     getWidth() * (realRegion.pos.y + row) + realRegion.pos.x;
    //             memcpy(dstStart, srcStart, realRegion.width * sizeof(Color));
    //         }
    //     }
    //     else
    //     {
    //         memcpy(dst, surface->pixels, getWidth() * getHeight() * sizeof(Color));
    //     }
    // }

    // void Window::updatePixels(const Color* src, const Rectangle<int32_t>* region)
    // {
    //     SDL_Surface* surface = SDL_GetWindowSurface(getNativeWindow());
    //     if (surface == nullptr)
    //     {
    //         printf("%s\n", SDL_GetError());
    //     }

    //     Rectangle<int32_t> realRegion = (region != nullptr) ?
    //                                     *region :
    //                                     Rectangle<int32_t>{{0, 0},
    //                                                        static_cast<int32_t>(getWidth()),
    //                                                        static_cast<int32_t>(getHeight())};

    //     if (region != nullptr)
    //     {
    //         for (int32_t row = 0; row < realRegion.height; ++row)
    //         {
    //             const Color* srcStart     = src + realRegion.width * row;
    //             Color*       surfaceStart = static_cast<Color*>(surface->pixels) +
    //                                         getWidth() * (realRegion.pos.y + row) + realRegion.pos.x;
    //             memcpy(surfaceStart, srcStart, realRegion.width * sizeof(Color));
    //         }
    //     }
    //     else
    //     {
    //         memcpy(surface->pixels, src, getWidth() * getHeight() * sizeof(Color));
    //     }
    // }

    void Window::updateTitle(const char* title)
    {
        m_Title  = (title == nullptr) ? WINDOW_DEFAULT_TITLE : title;

        SDL_SetWindowTitle(m_NativeWindow, m_Title);
    }

    void Window::setBorderless(bool borderless)
    {
        SDL_SetWindowBordered(m_NativeWindow, static_cast<SDL_bool>(!borderless));
    }

    void Window::resizeWindow(size_t width, size_t height)
    {
        assert(width);
        assert(height);

        if (m_Surface != nullptr && (m_Width != width || m_Height != height))
        {
            delete m_Surface;
            m_Surface = new Texture(width, height);
        }

        SDL_SetWindowSize(m_NativeWindow, (int) m_Width, (int) m_Height);

        m_Width  = width;
        m_Height = height;
    }

    void Window::setError(uint32_t error)
    {
        m_ErrorStatus |= error;
    }

    bool initGraphics()
    {
        if (SDL_Init(SDL_INIT_VIDEO) == -1)
        {
            return false;
        }

        if (TTF_Init() == -1)
        {
            return false;
        }

        return true;
    }

    void quitGraphics()
    {
        SDL_Quit();
    }
}