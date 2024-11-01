#pragma once

#include "Core.h"
#include <SDL2/SDL.h>

namespace Minesweeper {
class Window {
public:
  Window(SDL_Window *window);
  static Window &Get();
  void ScheduleResize(int w, int h);
  void ApplyUpdates();
  Size GetSize() { return {m_w, m_h}; }

private:
  SDL_Window *m_window;
  bool m_shouldUpdate{false};
  int m_w{0};
  int m_h{0};
};
} // namespace Minesweeper
