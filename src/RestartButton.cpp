#include "RestartButton.h"
#include "Game.h"
#include "SoundManager.h"
#include "SpriteRenderer.h"

namespace Minesweeper {
RestartButton::RestartButton(int x, int y) : m_x{x}, m_y{y} {}

bool RestartButton::OnInput(Engine::UserCommand &cmd) {
  if (cmd.type != Engine::UserCommandType::MouseButtonDown) {
    return false;
  }
  if (cmd.mouseButton != Engine::MouseButton::Left) {
    return false;
  }
  if (cmd.mouseX < m_x || cmd.mouseX > m_x + 36) {
    return false;
  }
  if (cmd.mouseY < m_y || cmd.mouseY > m_y + 36) {
    return false;
  }
  SoundManager::PlayClickingSound();
  Game::Restart();
  return true;
}

void RestartButton::OnRender() {
  if (Game::HasLost()) {
    SpriteRenderer::RenderSprite(m_x, m_y, Sprites::RestartButtonSad);
  } else {
    SpriteRenderer::RenderSprite(m_x, m_y, Sprites::RestartButtonHappy);
  }
}

void RestartButton::Move(int x, int y) {
  m_x = x;
  m_y = y;
}
} // namespace Minesweeper
