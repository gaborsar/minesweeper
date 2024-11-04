#include "Texture.h"
#include "Renderer.h"
#include "Surface.h"
#include <sstream>

namespace Game {
Texture::Texture(const char *file, ImageType type) {
  Renderer &renderer{Renderer::Get()};
  Surface surface{file, type};
  SDL_Texture *texture{
      SDL_CreateTextureFromSurface(renderer.m_renderer, surface.m_surface)};
  if (!texture) {
    std::stringstream msg{};
    msg << "failed to load SDL texture: " << SDL_GetError();
    throw std::runtime_error(msg.str());
  }
  m_texture = texture;
}

Texture::~Texture() { SDL_DestroyTexture(m_texture); }

} // namespace Game
