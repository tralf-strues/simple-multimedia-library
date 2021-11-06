/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file window.h
 * @date 2021-09-01
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <assert.h>
#include <stdio.h>
#include <SDL.h>

namespace Sml
{
    static const char* WINDOW_DEFAULT_TITLE = "Untitled";

    class Window
    {
    public:
        enum Error
        {
            NO_ERROR     = 0,
            CREATE_ERROR = (1u << 0),
            RESIZE_ERROR = (1u << 1)
        };

    public:
        /**
         * @brief Construct a new Window object.
         * 
         * @param width 
         * @param height 
         * @param title Can be nullptr in which case title is set to DEFAULT_TITLE.
         */
        Window(size_t width, size_t height, const char* title);

        /**
         * @brief Destroy the Window object.
         */
        ~Window();

        /**
         * @return Window's width.
         */
        size_t getWidth() const;

        /**
         * @return Window's height.
         */
        size_t getHeight() const;

        /**
         * @return Window's title.
         */
        const char* getTitle() const;

        /**
         * Get Window's error status, which is represented as bit-mask of all possible Error codes.
         * 
         * @return Window's error status. 
         */
        uint32_t getError() const;

        /**
         * @return Low-level native window.
         */
        SDL_Window* getNativeWindow() const;

        /**
         * @brief Update Window's title.
         * 
         * @param title New title, can be nullptr (then DEFAULT_TITLE is used).
         */
        void updateTitle(const char* title);

        /**
         * @brief Add or remove Window's borders.
         * 
         * @param borderless 
         */
        void setBorderless(bool borderless = true);

        /**
         * @brief Resize Window.
         * 
         * @param width  New Window's width.
         * @param height New Window's height.
         */
        void resizeWindow(size_t width, size_t height);

    private:
        size_t      m_Width        = 0;
        size_t      m_Height       = 0;
        const char* m_Title        = nullptr;
        uint32_t    m_ErrorStatus  = NO_ERROR;

        SDL_Window* m_NativeWindow = nullptr;

        /**
         * @brief Set the error.
         * 
         * @note New Window's error status = (prev error status) OR (error).
         * 
         * @param error Bit-mask based on Error codes.
         */
        void setError(uint32_t error);
    };

    /**
     * @brief Initialize graphics.
     * 
     * @warning Supposed to be called only once prior to using any graphics functionality.
     * 
     * @return true  Successfully initialized.
     * @return false Failed to initialize. 
     */
    bool initGraphics();

    /**
     * @brief Quit graphics.
     * 
     * @warning Supposed to be called only once after using graphics functionality.
     */
    void quitGraphics();
}
