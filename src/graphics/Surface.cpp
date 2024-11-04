#include "Surface.h"
#include <sstream>

namespace Game {
Surface::Surface(const char *file, ImageType type) {
  SDL_Surface *surface{nullptr};
  switch (type) {
  case ImageType::BMP:
    surface = SDL_LoadBMP(file);
    break;
  }
  if (!surface) {
    std::stringstream msg{};
    msg << "failed to load SDL surface: " << SDL_GetError();
    throw std::runtime_error(msg.str());
  }
  m_surface = surface;
}

Surface::~Surface() { SDL_FreeSurface(m_surface); }
} // namespace Game
