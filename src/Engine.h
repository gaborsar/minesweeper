#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

namespace Engine {
class Texture;

struct Size {
  int w;
  int h;
};

struct Rect {
  int x, y;
  int w, h;
};

enum class ImageType { BMP };

inline constexpr bool IsPointWithinRect(const Rect &rect, int px, int py) {
  return px >= rect.x && px < rect.x + rect.w && py >= rect.y &&
         py < rect.y + rect.w;
}

class SDLSubsystem {
public:
  SDLSubsystem();
  ~SDLSubsystem();
};

class Timer {
public:
  static int GetTicks();
  static void Delay(int ms);
};

class Window {
public:
  Window(const char *title, int w, int h);
  ~Window();
  friend class Renderer;
  static void Resize(int w, int h);

private:
  SDL_Window *m_window{nullptr};
};

class Renderer {
public:
  Renderer();
  ~Renderer();
  friend class Texture;
  static void Clear();
  static void Render();
  static void RenderSprite(Texture &texture, int x, int y, const Rect &sprite);

private:
  SDL_Renderer *m_renderer{nullptr};
};

class Surface {
public:
  Surface(const char *file, ImageType type);
  ~Surface();
  friend class Texture;

private:
  SDL_Surface *m_surface{nullptr};
};

class Texture {
public:
  Texture(const char *file, ImageType type);
  ~Texture();
  friend class Renderer;

private:
  SDL_Texture *m_texture{nullptr};
};

class Mixer {
public:
  Mixer();
  ~Mixer();
};

class Sound {
public:
  Sound(const char *file);
  ~Sound();
  void Play();

private:
  Mix_Chunk *m_chunk{nullptr};
};
} // namespace Engine
