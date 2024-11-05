#include "GameSession.h"
#include "../graphics/SpriteManager.h"
#include "../graphics/SpriteRenderer.h"
#include "../graphics/Window.h"
#include <cassert>

namespace Game
{
  static GameSession *s_instance{nullptr};

  GameSession::GameSession(const GameConfig &config, int time)
      : m_config{config}, m_startTime{time}, m_updateTime{time},
        m_restartButton{RestartButton{}}, m_board{Board{}}
  {
    m_restartButton.Move(20 + m_config.boardWidth * 30 / 2 - 18, 20 + 12);
    m_board.Move(20, 20 + 60 + 20);
    m_board.Init(config.boardWidth, config.boardHeight, config.numberOfMines);
    s_instance = this;
  }

  bool GameSession::OnInput(const SDL_Event &event)
  {
    if (m_restartButton.OnInput(event))
    {
      return true;
    }
    if (m_status == GameStatus::Playing && m_board.OnInput(event))
    {
      return true;
    }
    return false;
  }

  bool GameSession::OnUpdate(int time)
  {
    if (m_status != GameStatus::Playing)
    {
      return false;
    }
    m_updateTime = time;
    if (m_elapsedTime >= 999)
    {
      return false;
    }
    int elapsedTime{(m_updateTime - m_startTime) / 1000};
    if (elapsedTime > 999)
    {
      elapsedTime = 999;
    }
    if (elapsedTime == m_elapsedTime)
    {
      return false;
    }
    m_elapsedTime = elapsedTime;
    return true;
  }

  void GameSession::OnRender()
  {
    RenderBackground();
    RenderCounter();
    RenderTimer();
    m_restartButton.OnRender();
    m_board.OnRender();
  }

  bool GameSession::IsPlaying()
  {
    return s_instance->m_status == GameStatus::Playing;
  }

  bool GameSession::HasWon()
  {
    return s_instance->m_status == GameStatus::Won;
  }

  bool GameSession::HasLost()
  {
    return s_instance->m_status == GameStatus::Lost;
  }

  void GameSession::Restart()
  {
    s_instance->m_status = GameStatus::Playing;
    s_instance->m_startTime = s_instance->m_updateTime;
    if (s_instance->m_board.HasChanged())
    {
      s_instance->m_board.Init(s_instance->m_config.boardWidth, s_instance->m_config.boardHeight, s_instance->m_config.numberOfMines);
    }
    else
    {
      if (s_instance->m_config.boardWidth == BeginnerConfig.boardWidth)
      {
        s_instance->m_config = IntermediateConfig;
      }
      else if (s_instance->m_config.boardWidth == IntermediateConfig.boardWidth)
      {
        s_instance->m_config = ExpertConfig;
      }
      else
      {
        s_instance->m_config = BeginnerConfig;
      }

      Size windowSize{GetWindowSize(s_instance->m_config)};
      Window::Resize(windowSize.w, windowSize.h);

      s_instance->m_restartButton.Move(20 + s_instance->m_config.boardWidth * 30 / 2 - 18, 20 + 12);
      s_instance->m_board.Init(s_instance->m_config.boardWidth, s_instance->m_config.boardHeight, s_instance->m_config.numberOfMines);
    }
  }

  void GameSession::Win()
  {
    s_instance->m_status = GameStatus::Won;
  }

  void GameSession::Lose()
  {
    s_instance->m_status = GameStatus::Lost;
  }

  void GameSession::RenderBackground()
  {
    int x1{0};
    int x2{20 + m_config.boardWidth * 30};

    int y1{0};
    int y2{20 + 60};
    int y3{y2 + 20 + m_config.boardHeight * 30};

    SpriteRenderer::RenderSprite(x1, y1, SpriteManager::FrameTopLeftCorner);
    SpriteRenderer::RenderSprite(x2, y1, SpriteManager::FrameTopRightCorner);

    SpriteRenderer::RenderSprite(x1, y3, SpriteManager::FrameBottomLeftCorner);
    SpriteRenderer::RenderSprite(x2, y3, SpriteManager::FrameBottomRightCorner);

    SpriteRenderer::RenderSprite(x1, y2, SpriteManager::FrameLeftJoint);
    SpriteRenderer::RenderSprite(x2, y2, SpriteManager::FrameRightJoint);

    for (int i{0}; i < m_config.boardWidth * 3; ++i)
    {
      int x{20 + i * 10};
      SpriteRenderer::RenderSprite(x, y1, SpriteManager::FrameHorizontal);
      SpriteRenderer::RenderSprite(x, y2, SpriteManager::FrameHorizontal);
      SpriteRenderer::RenderSprite(x, y3, SpriteManager::FrameHorizontal);
    }

    for (int i{0}; i < 6; ++i)
    {
      int y{20 + i * 10};
      SpriteRenderer::RenderSprite(x1, y, SpriteManager::FrameVertical);
      SpriteRenderer::RenderSprite(x2, y, SpriteManager::FrameVertical);
    }

    for (int i{0}; i < m_config.boardHeight * 3; ++i)
    {
      int y{y2 + 20 + i * 10};
      SpriteRenderer::RenderSprite(x1, y, SpriteManager::FrameVertical);
      SpriteRenderer::RenderSprite(x2, y, SpriteManager::FrameVertical);
    }

    for (int i{0}; i < 6; ++i)
    {
      for (int j{0}; j < m_config.boardWidth * 3; ++j)
      {
        int x{20 + j * 10};
        int y{20 + i * 10};
        SpriteRenderer::RenderSprite(x, y, SpriteManager::FrameBase);
      }
    }
  }

  void GameSession::RenderCounter()
  {
    int count{m_config.numberOfMines - m_board.GetNumberOfFlags()};
    if (count < 0)
    {
      count = 0;
    }
    RenderNumber(30, 30, count);
  }

  void GameSession::RenderTimer()
  {
    RenderNumber(20 + m_config.boardWidth * 30 - 64 - 10, 30, m_elapsedTime);
  }

  void GameSession::RenderNumber(int px, int py, int n)
  {
    int d3{n};

    int d1{n / 100};
    d3 = d3 % 100;

    int d2{d3 / 10};
    d3 = d3 % 10;

    assert(d1 >= 0 && d1 <= 9);
    assert(d2 >= 0 && d2 <= 9);
    assert(d3 >= 0 && d3 <= 9);

    SpriteRenderer::RenderSprite(px, py, SpriteManager::DigitBorder);
    SpriteRenderer::RenderSprite(px + 2, py + 2, SpriteManager::LeftDigits[d1]);
    if (d1 == 0)
    {
      SpriteRenderer::RenderSprite(px + 2 + 20, py + 2, SpriteManager::LeftDigits[d2]);
    }
    else
    {
      SpriteRenderer::RenderSprite(px + 2 + 20, py + 2, SpriteManager::RightDigits[d2]);
    }
    SpriteRenderer::RenderSprite(px + 2 + 40, py + 2, SpriteManager::RightDigits[d3]);
  }
} // namespace Game
