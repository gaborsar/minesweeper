#pragma once

#include "Image.h"
#include <SDL.h>

namespace Game {
class Surface {
public:
  Surface(const char *file, ImageType type);
  ~Surface();
  friend class Window;
  friend class Texture;

private:
  SDL_Surface *m_surface{nullptr};
};
} // namespace Game
