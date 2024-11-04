#pragma once

#include "Image.h"
#include <SDL.h>

namespace Game {
class Texture {
public:
  Texture(const char *file, ImageType type);
  ~Texture();
  friend class SpriteRenderer;

private:
  SDL_Texture *m_texture{nullptr};
};
} // namespace Game
