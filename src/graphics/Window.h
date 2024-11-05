#pragma once

#include <SDL.h>

namespace Game
{
  class Window
  {
  public:
    Window(const char *title, int w, int h);
    ~Window();
    friend class Renderer;
    static Window &Get();
    static void Resize(int w, int h);
    static void SetIcon(const char *file);

  private:
    SDL_Window *m_window{nullptr};
  };

} // namespace Game
