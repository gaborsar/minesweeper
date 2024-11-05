#pragma once

#include <SDL.h>

namespace Game
{
  class Texture;

  class Renderer
  {
  public:
    Renderer();
    ~Renderer();
    friend class Texture;
    friend class SpriteRenderer;
    static Renderer &Get();
    static void Clear();
    static void Render();

  private:
    SDL_Renderer *m_renderer{nullptr};
  };
} // namespace Game
