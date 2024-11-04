#include "Engine.h"
#include <sstream>

namespace Engine {
static Window *s_window{nullptr};
static Renderer *s_renderer{nullptr};

SDLSubsystem::SDLSubsystem() {
  int result{SDL_Init(SDL_INIT_EVERYTHING)};
  if (result < 0) {
    std::stringstream msg{};
    msg << "failed to init SDL: " << SDL_GetError();
    throw std::runtime_error(msg.str());
  }
}

SDLSubsystem::~SDLSubsystem() { SDL_Quit(); }

Window::Window(const char *title, int w, int h) {
  SDL_Window *window{SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, w, h,
                                      SDL_WINDOW_SHOWN)};
  if (!window) {
    std::stringstream msg{};
    msg << "failed to create SDL window: " << SDL_GetError();
    throw std::runtime_error(msg.str());
  }
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
  if (!renderer) {
    std::stringstream msg{};
    msg << "failed to create SDL renderer: " << SDL_GetError();
    throw std::runtime_error(msg.str());
  }
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
  int result{SDL_RenderCopy(s_renderer->m_renderer, texture.m_texture, &srcRect,
                            &dstRect)};
  if (result < 0) {
    std::stringstream msg{};
    msg << "failed to render sprite: " << SDL_GetError();
    throw std::runtime_error(msg.str());
  }
}

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

Texture::Texture(const char *file, ImageType type) {
  Surface surface{file, type};
  SDL_Texture *texture{
      SDL_CreateTextureFromSurface(s_renderer->m_renderer, surface.m_surface)};
  if (!texture) {
    std::stringstream msg{};
    msg << "failed to load SDL texture: " << SDL_GetError();
    throw std::runtime_error(msg.str());
  }
  m_texture = texture;
}

Texture::~Texture() { SDL_DestroyTexture(m_texture); }

Mixer::Mixer() {
  int result{Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)};
  if (result < 0) {
    std::stringstream msg{};
    msg << "failed to open SDL audio" << Mix_GetError();
    throw std::runtime_error(msg.str());
  }
}

Mixer::~Mixer() { Mix_Quit(); }

Sound::Sound(const char *file) {
  Mix_Chunk *chunk{Mix_LoadWAV(file)};
  if (!chunk) {
    std::stringstream msg{};
    msg << "failed to load SDL audio chunk" << Mix_GetError();
    throw std::runtime_error(msg.str());
  }
  m_chunk = chunk;
}

Sound::~Sound() { Mix_FreeChunk(m_chunk); }

void Sound::Play() { Mix_PlayChannel(-1, m_chunk, 0); }
} // namespace Engine
