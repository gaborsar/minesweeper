#pragma once

#include "Engine.h"

namespace Minesweeper {
class Application {
public:
  Application(const char *title, int w, int h);
  static void ResizeWindow(int w, int h);
  static void RenderSprite(int x, int y, const Engine::Rect &sprite);
  static void PlayClickingSound();
  static void PlayWinningSound();
  static void PlayLosingSound();

private:
  Engine::Window m_window;
  Engine::Renderer m_renderer;
  Engine::Texture m_texture;
  Engine::Mixer m_mixer;
  Engine::Sound m_clickingSound;
  Engine::Sound m_winningSound;
  Engine::Sound m_losingSound;
};
} // namespace Minesweeper
