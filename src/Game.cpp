#include "Game.h"

namespace Minesweeper {
Game::Game(std::shared_ptr<Renderer> renderer, int boardWidth, int boardHeight,
           int numberOfMines)
    : m_renderer{renderer}, m_boardWidth{boardWidth},
      m_boardHeight{boardHeight}, m_numberOfMines{numberOfMines} {
  m_board =
      std::make_unique<Board>(renderer, boardWidth, boardHeight, numberOfMines);
}

void Game::SetStartTime(int startTime) {
  m_startTime = startTime;
  m_updateTime = startTime;
}

bool Game::OnClick(int px, int py, MouseButton button) {
  Rect box = m_board->GetBox();
  if (IsWithin(box, px, py)) {
    return m_board->OnClick(px - box.x, py - box.y, button);
  }
  return false;
}

bool Game::Update(int time) {
  m_updateTime = time;
  if (m_elapsedTime >= 999) {
    return false;
  }
  int elapsedTime = (m_updateTime - m_startTime) / 1000;
  if (elapsedTime > 999) {
    elapsedTime = 999;
  }
  if (elapsedTime == m_elapsedTime) {
    return false;
  }
  m_elapsedTime = elapsedTime;
  return true;
}

void Game::Render() {
  RenderBackground();
  RenderCounter();
  RenderTimer();
  RenderRestartButton();
  m_board->Render();
}

void Game::RenderBackground() {
  int x1{0};
  int x2{20 + m_boardWidth * 30};

  int y1{0};
  int y2{20 + 60};
  int y3{y2 + 20 + m_boardHeight * 30};

  m_renderer->RenderSprite(x1, y1, Sprites::FrameTopLeftCorner);
  m_renderer->RenderSprite(x2, y1, Sprites::FrameTopRightCorner);

  m_renderer->RenderSprite(x1, y3, Sprites::FrameBottomLeftCorner);
  m_renderer->RenderSprite(x2, y3, Sprites::FrameBottomRightCorner);

  m_renderer->RenderSprite(x1, y2, Sprites::FrameLeftJoint);
  m_renderer->RenderSprite(x2, y2, Sprites::FrameRightJoint);

  for (int i{0}; i < m_boardWidth * 3; ++i) {
    int x{20 + i * 10};
    m_renderer->RenderSprite(x, y1, Sprites::FrameHorizontal);
    m_renderer->RenderSprite(x, y2, Sprites::FrameHorizontal);
    m_renderer->RenderSprite(x, y3, Sprites::FrameHorizontal);
  }

  for (int i{0}; i < 6; ++i) {
    int y{20 + i * 10};
    m_renderer->RenderSprite(x1, y, Sprites::FrameVertical);
    m_renderer->RenderSprite(x2, y, Sprites::FrameVertical);
  }

  for (int i{0}; i < m_boardHeight * 3; ++i) {
    int y{y2 + 20 + i * 10};
    m_renderer->RenderSprite(x1, y, Sprites::FrameVertical);
    m_renderer->RenderSprite(x2, y, Sprites::FrameVertical);
  }

  for (int i{0}; i < 6; ++i) {
    for (int j{0}; j < m_boardWidth * 3; ++j) {
      int x{20 + j * 10};
      int y{20 + i * 10};
      m_renderer->RenderSprite(x, y, Sprites::FrameBase);
    }
  }
}

void Game::RenderCounter() {
  int x1{30};
  int y{30};
  int count = m_numberOfMines - m_board->CountFlags();
  if (count < 0) {
    count = 0;
  }
  RenderNumber(30, 30, count);
}

void Game::RenderTimer() {
  int x{20 + m_boardWidth * 30 - 64 - 10};
  int y{30};
  RenderNumber(x, y, m_elapsedTime);
}

void Game::RenderNumber(int px, int py, int n) {
  int d3 = n;

  int d1 = n / 100;
  d3 = d3 % 100;

  int d2 = d3 / 10;
  d3 = d3 % 10;

  assert(d1 >= 0 && d1 <= 9);
  assert(d2 >= 0 && d2 <= 9);
  assert(d3 >= 0 && d3 <= 9);

  m_renderer->RenderSprite(px, py, Sprites::DigitBorder);
  m_renderer->RenderSprite(px + 2, py + 2, Sprites::LeftDigits[d1]);
  if (d1 == 0) {
    m_renderer->RenderSprite(px + 2 + 20, py + 2, Sprites::LeftDigits[d2]);
  } else {
    m_renderer->RenderSprite(px + 2 + 20, py + 2, Sprites::RightDigits[d2]);
  }
  m_renderer->RenderSprite(px + 2 + 40, py + 2, Sprites::RightDigits[d3]);
}

void Game::RenderRestartButton() {
  int x{20 + m_boardWidth * 30 / 2 - 18};
  int y{20 + 12};
  m_renderer->RenderSprite(x, y, Sprites::RestartButtonHappy);
}
} // namespace Minesweeper
