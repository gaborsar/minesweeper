#pragma once

#include "Sprite.h"
#include <SDL2/SDL.h>

namespace Minesweeper {
class Renderer {
public:
  Renderer(SDL_Renderer *renderer, SDL_Texture *texture);
  void RenderSprite(int px, int py, const Sprite& sprite);

private:
  SDL_Renderer *m_renderer;
  SDL_Texture *m_texture;
};
} // namespace Minesweeper
