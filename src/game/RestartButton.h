#pragma once

#include <SDL.h>

namespace Game
{
  class RestartButton
  {
  public:
    void Move(int x, int y);
    bool OnInput(const SDL_Event &event);
    void OnRender();

  private:
    int m_x{0};
    int m_y{0};
  };
} // namespace Game
