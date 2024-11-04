#include "Engine.h"
#include <cassert>

namespace Engine {
static Window *s_window{nullptr};
static Renderer *s_renderer{nullptr};

Window::Window(const char *title, int w, int h) {
  SDL_Window *window{SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, w, h,
                                      SDL_WINDOW_SHOWN)};
  assert(window);
  m_window = window;
  s_window = this;
}

Window::~Window() { SDL_DestroyWindow(m_window); }

void Window::Resize(int w, int h) {
  SDL_SetWindowSize(s_window->m_window, w, h);
  SDL_SetWindowPosition(s_window->m_window, SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED);
}

Renderer::Renderer() {
  SDL_Renderer *renderer{
      SDL_CreateRenderer(s_window->m_window, -1, SDL_RENDERER_ACCELERATED)};
  assert(renderer);
  m_renderer = renderer;
  s_renderer = this;
}

Renderer::~Renderer() { SDL_DestroyRenderer(m_renderer); }

void Renderer::Clear() { SDL_RenderClear(s_renderer->m_renderer); }

void Renderer::Render() { SDL_RenderPresent(s_renderer->m_renderer); }

void Renderer::RenderSprite(Texture &texture, int x, int y,
                            const Rect &sprite) {
  SDL_Rect srcRect{sprite.x, sprite.y, sprite.w, sprite.h};
  SDL_Rect dstRect{x, y, sprite.w, sprite.h};
  SDL_RenderCopy(s_renderer->m_renderer, texture.m_texture, &srcRect, &dstRect);
}

Surface::Surface(const char *file, ImageType type) {
  SDL_Surface *surface{nullptr};
  switch (type) {
  case ImageType::BMP:
    surface = SDL_LoadBMP(file);
    break;
  }
  assert(surface);
  m_surface = surface;
}

Surface::~Surface() { SDL_FreeSurface(m_surface); }

Texture::Texture(const char *file, ImageType type) {
  Surface surface{file, type};
  SDL_Texture *texture{
      SDL_CreateTextureFromSurface(s_renderer->m_renderer, surface.m_surface)};
  assert(texture);
  m_texture = texture;
}

Texture::~Texture() { SDL_DestroyTexture(m_texture); }

Mixer::Mixer() {
  int result = Mix_OpenAudio(4410, MIX_DEFAULT_FORMAT, 2, 1024);
  assert(result >= 0);
}

Mixer::~Mixer() { Mix_Quit(); }

Sound::Sound(const char *file) {
  Mix_Chunk *chunk{Mix_LoadWAV(file)};
  assert(chunk);
  m_chunk = chunk;
}

Sound::~Sound() { Mix_FreeChunk(m_chunk); }

void Sound::Play(int channel) { Mix_PlayChannel(channel, m_chunk, 0); }
} // namespace Engine
