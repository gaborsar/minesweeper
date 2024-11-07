#pragma once

#include "Image.h"
#include <SDL.h>

namespace Game
{
  class Texture
  {
  public:
    Texture(const char *file, ImageType type);
    ~Texture();
    friend class SpriteRenderer;

  private:
    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;
    SDL_Texture *m_texture{nullptr};
  };
} // namespace Game
