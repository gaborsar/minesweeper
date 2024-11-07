#pragma once

#include <SDL.h>

namespace Game
{
  class Window
  {
  public:
    Window(const char *title, int w, int h);
    ~Window();
    static Window &Get();
    static void Resize(int w, int h);
    static void SetIcon(const char *file);
    friend class Renderer;

  private:
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;
    SDL_Window *m_window{nullptr};
  };

} // namespace Game
