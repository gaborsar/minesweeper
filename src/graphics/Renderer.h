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

    static Renderer &Get();
    static void Clear();
    static void Render();

    friend class Texture;
    friend class SpriteRenderer;

  private:
    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;

    SDL_Renderer *m_renderer{nullptr};
  };
} // namespace Game
