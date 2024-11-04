#pragma once

#include "Rect.h"
#include "Texture.h"

namespace Game {
class SpriteRenderer {
public:
  SpriteRenderer();
  static void RenderSprite(int x, int y, const Rect &sprite);

private:
  Texture m_atlas;
};
} // namespace Game
