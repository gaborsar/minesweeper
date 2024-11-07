#pragma once

#include "Image.h"
#include <SDL.h>

namespace Game
{
  class Surface
  {
  public:
    Surface(const char *file, ImageType type);
    ~Surface();
    friend class Window;
    friend class Texture;

  private:
    Surface(const Surface &) = delete;
    Surface &operator=(const Surface &) = delete;
    SDL_Surface *m_surface{nullptr};
  };
} // namespace Game
