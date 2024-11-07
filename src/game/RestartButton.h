#pragma once

#include <SDL.h>

namespace Game
{
  class RestartButton
  {
  public:
    RestartButton() {};
    void Move(int x, int y);
    bool OnInput(const SDL_Event &event);
    void OnRender();

  private:
    RestartButton(const RestartButton &) = delete;
    RestartButton &operator=(const RestartButton &) = delete;
    int m_x{0};
    int m_y{0};
  };
} // namespace Game
