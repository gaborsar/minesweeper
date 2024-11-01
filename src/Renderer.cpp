#include "Renderer.h"

namespace Minesweeper {
static Renderer *m_instance{nullptr};

Renderer::Renderer(SDL_Renderer *renderer, SDL_Texture *texture)
    : m_renderer{renderer}, m_texture{texture} {
  m_instance = this;
}

Renderer &Renderer::Get() { return *m_instance; }

void Renderer::RenderSprite(int px, int py, const Rect &sprite) {
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
