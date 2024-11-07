#pragma once

#include "Rect.h"
#include "Texture.h"

namespace Game
{
  class SpriteRenderer
  {
  public:
    SpriteRenderer();
    static void RenderSprite(int x, int y, const Rect &sprite);

  private:
    SpriteRenderer(const SpriteRenderer &) = delete;
    SpriteRenderer &operator=(const SpriteRenderer &) = delete;
    Texture m_atlas;
  };
} // namespace Game
