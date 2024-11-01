#pragma once

#include <SDL2/SDL.h>

namespace Minesweeper
{
    class Window
    {
    public:
        Window(SDL_Window *window);
        void Resize(int w, int h);
        static Window &Get();

    private:
        SDL_Window *m_window;
    };
}
