#include "Renderer.h"

namespace Minesweeper {
Renderer::Renderer(SDL_Renderer *renderer, SDL_Texture *texture)
    : m_renderer{renderer}, m_texture{texture} {}

void Renderer::RenderSprite(const int px, const int py, const Sprite &sprite) {
  SDL_Rect srcRect;
  srcRect.x = sprite.x;
  srcRect.y = sprite.y;
  srcRect.w = sprite.w;
  srcRect.h = sprite.h;

  SDL_Rect dstRect;
  dstRect.x = px;
  dstRect.y = py;
  dstRect.w = sprite.w;
  dstRect.h = sprite.h;

  SDL_RenderCopy(m_renderer, m_texture, &srcRect, &dstRect);
}
} // namespace Minesweeper
