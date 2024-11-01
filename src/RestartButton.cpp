#include "RestartButton.h"
#include "Game.h"
#include "Renderer.h"
#include "Sprites.h"

namespace Minesweeper {
RestartButton::RestartButton(int x, int y) : m_x{x}, m_y{y} {}

bool RestartButton::OnInput(UserCommand &cmd) {
  if (cmd.type != UserCommandType::MouseButtonDown ||
      cmd.mouseButton != MouseButton::Left) {
    return false;
  }
  if (cmd.mouseX < m_x || cmd.mouseX > m_x + 36) {
    return false;
  }
  if (cmd.mouseY < m_y || cmd.mouseY > m_y + 36) {
    return false;
  }

  Game &game{Game::Get()};
  game.Restart();

  return true;
}

void RestartButton::OnRender() {
  Game &game{Game::Get()};
  bool isSad{game.GetStatus() == GameStatus::Lost};

  Renderer &renderer{Renderer::Get()};
  renderer.RenderSprite(m_x, m_y,
                        isSad ? Sprites::RestartButtonSad
                              : Sprites::RestartButtonHappy);
}

void RestartButton::Move(int x, int y) {
  m_x = x;
  m_y = y;
}
} // namespace Minesweeper
