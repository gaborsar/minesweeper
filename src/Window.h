#pragma once

#include <SDL2/SDL.h>

namespace Minesweeper {
class Window {
public:
  Window(SDL_Window *window, int w, int h);
  static Window &Get();
  void Resize(int w, int h);

private:
  SDL_Window *m_window;
  int m_w{0};
  int m_h{0};
};
} // namespace Minesweeper
