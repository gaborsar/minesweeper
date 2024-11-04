#include "Game.h"
#include "SpriteRenderer.h"
#include <cassert>

namespace Minesweeper {
static Game *s_instance{nullptr};

Game::Game(const GameConfig &config)
    : m_config{config}, m_restartButton{RestartButton{
                            20 + m_config.boardWidth * 30 / 2 - 18, 20 + 12}},
      m_board{Board{20, 20 + 60 + 20, config.boardWidth, config.boardHeight,
                    config.numberOfMines}} {
  m_startTime = Engine::Timer::GetTicks();
  m_updateTime = m_startTime;
  s_instance = this;
}

bool Game::OnInput(Engine::UserCommand &cmd) {
  if (m_restartButton.OnInput(cmd)) {
    return true;
  }
  if (m_status == GameStatus::Playing && m_board.OnInput(cmd)) {
    return true;
  }
  return false;
}

bool Game::OnUpdate(int time) {
  if (m_status != GameStatus::Playing) {
    return false;
  }
  m_updateTime = time;
  if (m_elapsedTime >= 999) {
    return false;
  }
  int elapsedTime{(m_updateTime - m_startTime) / 1000};
  if (elapsedTime > 999) {
    elapsedTime = 999;
  }
  if (elapsedTime == m_elapsedTime) {
    return false;
  }
  m_elapsedTime = elapsedTime;
  return true;
}

void Game::OnRender() {
  RenderBackground();
  RenderCounter();
  RenderTimer();
  m_restartButton.OnRender();
  m_board.OnRender();
}

bool Game::IsPlaying() { return s_instance->m_status == GameStatus::Playing; }

bool Game::HasWon() { return s_instance->m_status == GameStatus::Won; }

bool Game::HasLost() { return s_instance->m_status == GameStatus::Lost; }

void Game::Restart() {
  s_instance->m_status = GameStatus::Playing;
  s_instance->m_startTime = s_instance->m_updateTime;
  if (s_instance->m_board.HasChanged()) {
    s_instance->m_board.Init();
  } else {
    if (s_instance->m_config.boardWidth == BeginnerConfig.boardWidth) {
      s_instance->m_config = IntermediateConfig;
    } else if (s_instance->m_config.boardWidth ==
               IntermediateConfig.boardWidth) {
      s_instance->m_config = ExpertConfig;
    } else {
      s_instance->m_config = BeginnerConfig;
    }

    Engine::Size windowSize{Minesweeper::GetWindowSize(s_instance->m_config)};
    Engine::Window::Resize(windowSize.w, windowSize.h);

    int btnX{20 + s_instance->m_config.boardWidth * 30 / 2 - 18};
    int btnY{20 + 12};
    s_instance->m_restartButton.Move(btnX, btnY);

    int boardX{20};
    int boardY{20 + 60 + 20};
    s_instance->m_board = Board{boardX, boardY, s_instance->m_config.boardWidth,
                                s_instance->m_config.boardHeight,
                                s_instance->m_config.numberOfMines};
  }
}

void Game::Win() { s_instance->m_status = GameStatus::Won; }

void Game::Lose() { s_instance->m_status = GameStatus::Lost; }

void Game::RenderBackground() {
  int x1{0};
  int x2{20 + m_config.boardWidth * 30};

  int y1{0};
  int y2{20 + 60};
  int y3{y2 + 20 + m_config.boardHeight * 30};

  SpriteRenderer::RenderSprite(x1, y1, Sprites::FrameTopLeftCorner);
  SpriteRenderer::RenderSprite(x2, y1, Sprites::FrameTopRightCorner);

  SpriteRenderer::RenderSprite(x1, y3, Sprites::FrameBottomLeftCorner);
  SpriteRenderer::RenderSprite(x2, y3, Sprites::FrameBottomRightCorner);

  SpriteRenderer::RenderSprite(x1, y2, Sprites::FrameLeftJoint);
  SpriteRenderer::RenderSprite(x2, y2, Sprites::FrameRightJoint);

  for (int i{0}; i < m_config.boardWidth * 3; ++i) {
    int x{20 + i * 10};
    SpriteRenderer::RenderSprite(x, y1, Sprites::FrameHorizontal);
    SpriteRenderer::RenderSprite(x, y2, Sprites::FrameHorizontal);
    SpriteRenderer::RenderSprite(x, y3, Sprites::FrameHorizontal);
  }

  for (int i{0}; i < 6; ++i) {
    int y{20 + i * 10};
    SpriteRenderer::RenderSprite(x1, y, Sprites::FrameVertical);
    SpriteRenderer::RenderSprite(x2, y, Sprites::FrameVertical);
  }

  for (int i{0}; i < m_config.boardHeight * 3; ++i) {
    int y{y2 + 20 + i * 10};
    SpriteRenderer::RenderSprite(x1, y, Sprites::FrameVertical);
    SpriteRenderer::RenderSprite(x2, y, Sprites::FrameVertical);
  }

  for (int i{0}; i < 6; ++i) {
    for (int j{0}; j < m_config.boardWidth * 3; ++j) {
      int x{20 + j * 10};
      int y{20 + i * 10};
      SpriteRenderer::RenderSprite(x, y, Sprites::FrameBase);
    }
  }
}

void Game::RenderCounter() {
  int count{m_config.numberOfMines - m_board.GetNumberOfFlags()};
  if (count < 0) {
    count = 0;
  }
  RenderNumber(30, 30, count);
}

void Game::RenderTimer() {
  RenderNumber(20 + m_config.boardWidth * 30 - 64 - 10, 30, m_elapsedTime);
}

void Game::RenderNumber(int px, int py, int n) {
  int d3{n};

  int d1{n / 100};
  d3 = d3 % 100;

  int d2{d3 / 10};
  d3 = d3 % 10;

  assert(d1 >= 0 && d1 <= 9);
  assert(d2 >= 0 && d2 <= 9);
  assert(d3 >= 0 && d3 <= 9);

  SpriteRenderer::RenderSprite(px, py, Sprites::DigitBorder);
  SpriteRenderer::RenderSprite(px + 2, py + 2, Sprites::LeftDigits[d1]);
  if (d1 == 0) {
    SpriteRenderer::RenderSprite(px + 2 + 20, py + 2, Sprites::LeftDigits[d2]);
  } else {
    SpriteRenderer::RenderSprite(px + 2 + 20, py + 2, Sprites::RightDigits[d2]);
  }
  SpriteRenderer::RenderSprite(px + 2 + 40, py + 2, Sprites::RightDigits[d3]);
}
} // namespace Minesweeper
