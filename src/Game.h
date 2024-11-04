#pragma once

#include "Board.h"
#include "Engine.h"
#include "RestartButton.h"

namespace Minesweeper {
struct GameConfig {
  int boardWidth{0};
  int boardHeight{0};
  int numberOfMines{0};
};

enum class GameStatus { Playing, Won, Lost };

constexpr GameConfig BeginnerConfig{9, 9, 10};
constexpr GameConfig IntermediateConfig{16, 16, 40};
constexpr GameConfig ExpertConfig{30, 16, 99};

inline constexpr Engine::Size GetWindowSize(const GameConfig &config) {
  return {20 * 2 + 30 * config.boardWidth,
          20 * 3 + 60 + 30 * config.boardHeight};
}

class Game {
public:
  Game(const GameConfig &config, int time);

  bool OnInput(Engine::UserCommand &cmd);
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
} // namespace Minesweeper
