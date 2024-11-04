#include "RestartButton.h"
#include "../graphics/SpriteRenderer.h"
#include "GameSession.h"

namespace Game {
void RestartButton::Move(int x, int y) {
  m_x = x;
  m_y = y;
}

bool RestartButton::OnInput(const SDL_Event &event) {
  if (event.type != SDL_MOUSEBUTTONDOWN) {
    return false;
  }
  if (event.button.button != SDL_BUTTON_LEFT) {
    return false;
  }
  if (event.button.x < m_x || event.button.x > m_x + 36) {
    return false;
  }
  if (event.button.y < m_y || event.button.y > m_y + 36) {
    return false;
  }
  GameSession::Restart();
  return true;
}

void RestartButton::OnRender() {
  if (GameSession::HasLost()) {
    SpriteRenderer::RenderSprite(m_x, m_y, Sprites::RestartButtonSad);
  } else {
    SpriteRenderer::RenderSprite(m_x, m_y, Sprites::RestartButtonHappy);
  }
}
} // namespace Game
