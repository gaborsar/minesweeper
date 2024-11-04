#pragma once

#include "Engine.h"

namespace Minesweeper {
class RestartButton {
public:
  RestartButton(int x, int y);
  bool OnInput(Engine::UserCommand &cmd);
  void OnRender();
  void Move(int x, int y);

private:
  int m_x{0};
  int m_y{0};
};
} // namespace Minesweeper
