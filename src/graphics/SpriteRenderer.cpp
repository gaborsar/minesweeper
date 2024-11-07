#include "SpriteRenderer.h"
#include "Renderer.h"
#include <SDL.h>
#include <sstream>

namespace Game
{
  static SpriteRenderer *s_instance{nullptr};

  SpriteRenderer::SpriteRenderer() : m_atlas{Texture{"tiles.bmp", ImageType::BMP}}
  {
    s_instance = this;
  }

  void SpriteRenderer::RenderSprite(int x, int y, const Rect &sprite)
  {
    Renderer &renderer{Renderer::Get()};
    SDL_Rect srcRect{sprite.x, sprite.y, sprite.w, sprite.h};
    SDL_Rect dstRect{x, y, sprite.w, sprite.h};
    int result{SDL_RenderCopy(renderer.m_renderer, s_instance->m_atlas.m_texture, &srcRect, &dstRect)};
    if (result < 0)
    {
      std::stringstream msg{};
      msg << "failed to render sprite: " << SDL_GetError();
      throw std::runtime_error(msg.str());
    }
  }
} // namespace Game
