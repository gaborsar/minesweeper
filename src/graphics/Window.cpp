#include "Window.h"
#include "Image.h"
#include "Surface.h"
#include <sstream>

namespace Game {
static Window *s_instance{nullptr};

Window::Window(const char *title, int w, int h) {
  SDL_Window *window{SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, w, h,
                                      SDL_WINDOW_SHOWN)};
  if (!window) {
    std::stringstream msg{};
    msg << "failed to create SDL window: " << SDL_GetError();
    throw std::runtime_error(msg.str());
  }
  m_window = window;
  s_instance = this;
}

Window::~Window() { SDL_DestroyWindow(m_window); }

Window &Window::Get() { return *s_instance; }

void Window::Resize(int w, int h) {
  SDL_SetWindowSize(s_instance->m_window, w, h);
  SDL_SetWindowPosition(s_instance->m_window, SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED);
}

void Window::SetIcon(const char *file) {
  Surface icon{file, ImageType::ICO};
  SDL_SetWindowIcon(s_instance->m_window, icon.m_surface);
}
} // namespace Game
