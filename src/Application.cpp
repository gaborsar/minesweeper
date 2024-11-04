#include "Application.h"

namespace Minesweeper {
static Application *s_application{nullptr};

Application::Application(const char *title, int w, int h)
    : m_window{Engine::Window{title, w, h}}, m_renderer{Engine::Renderer{}},
      m_texture{Engine::Texture{"tiles.bmp", Engine::ImageType::BMP}},
      m_mixer{Engine::Mixer{}}, m_clickingSound{Engine::Sound{"clicking.mp3"}},
      m_winningSound{Engine::Sound{"winning.mp3"}},
      m_losingSound{Engine::Sound{"losing.mp3"}} {
  s_application = this;
}

void Application::ResizeWindow(int w, int h) {
  s_application->m_window.Resize(w, h);
}

void Application::RenderSprite(int x, int y, const Engine::Rect &sprite) {
  Engine::Renderer &renderer{s_application->m_renderer};
  Engine::Texture &texture{s_application->m_texture};
  renderer.RenderSprite(texture, x, y, sprite);
}

void Application::PlayClickingSound() { s_application->m_clickingSound.Play(); }

void Application::PlayWinningSound() { s_application->m_winningSound.Play(); }

void Application::PlayLosingSound() { s_application->m_losingSound.Play(); }
} // namespace Minesweeper
