#include "Window.h"

namespace Minesweeper
{
    static Window *m_instance{nullptr};

    Window::Window(SDL_Window *window) : m_window{window}
    {
        m_instance = this;
    }

    void Window::ScheduleResize(int w, int h) {
        m_shouldUpdate = true;
        m_w = w;
        m_h = h;
    }

    void Window::ApplyUpdates()
    {
        m_shouldUpdate = false;
        SDL_SetWindowSize(m_window, m_w, m_h);
        SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }

    Window &Window::Get()
    {
        return *m_instance;
    }
}
