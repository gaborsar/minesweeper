#include "Window.h"

namespace Minesweeper {
static Window *m_instance{nullptr};

Window::Window(SDL_Window *window, int w, int h)
    : m_window{window}, m_w{w}, m_h{h} {
  m_instance = this;
}

Window &Window::Get() { return *m_instance; }

void Window::Resize(int w, int h) {
  m_w = w;
  m_h = h;
  SDL_SetWindowSize(m_window, m_w, m_h);
  SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED);
}
} // namespace Minesweeper
