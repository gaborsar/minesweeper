#pragma once

#include <SDL.h>

namespace Minesweeper {
class RestartButton {
public:
  bool OnInput(const SDL_Event &event);
  void OnRender();
  void Move(int x, int y);

private:
  int m_x{0};
  int m_y{0};
};
} // namespace Minesweeper
