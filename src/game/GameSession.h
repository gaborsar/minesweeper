#pragma once

#include "Board.h"
#include "GameConfig.h"
#include "RestartButton.h"
#include <SDL.h>

namespace Game {
enum class GameStatus { Playing, Won, Lost };

class GameSession {
public:
  GameSession(const GameConfig &config, int time);

  bool OnInput(const SDL_Event &event);
  bool OnUpdate(int time);
  void OnRender();

  static bool IsPlaying();
  static bool HasWon();
  static bool HasLost();
  static void Restart();
  static void Win();
  static void Lose();

private:
  GameConfig m_config{BeginnerConfig};
  GameStatus m_status{GameStatus::Playing};

  int m_startTime{0};
  int m_updateTime{0};
  int m_elapsedTime{0};

  RestartButton m_restartButton;
  Board m_board;

private:
  void RenderBackground();
  void RenderCounter();
  void RenderTimer();
  void RenderNumber(int px, int py, int n);
};
} // namespace Game
