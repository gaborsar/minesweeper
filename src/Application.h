#pragma once

#include "Engine.h"
#include "SoundManager.h"
#include "SpriteRenderer.h"

namespace Minesweeper {
class Application {
public:
  Application(const char *title, int w, int h);

private:
  Engine::SDLSubsystem m_sdl{};
  Engine::Window m_window;
  Engine::Renderer m_renderer{};
  Engine::Mixer m_mixer{};
  Minesweeper::SpriteRenderer m_spriteRenderer{};
  Minesweeper::SoundManager m_soundManager{};
};
} // namespace Minesweeper
