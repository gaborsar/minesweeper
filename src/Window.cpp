#include "Window.h"

namespace Minesweeper
{
    static Window *m_instance{nullptr};

    Window::Window(SDL_Window *window) : m_window{window} {}

    void Window::Resize(int w, int h) {
        SDL_SetWindowSize(m_window, w, h);
    }

    Window &Window::Get()
    {
        return *m_instance;
    }
}
