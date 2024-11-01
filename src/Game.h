#pragma once

#include "Board.h"
#include "Core.h"
#include "Input.h"
#include "RestartButton.h"
#include <memory>

namespace Minesweeper {
struct GameConfig {
  int boardWidth{0};
  int boardHeight{0};
  int numberOfMines{0};
};

constexpr GameConfig BeginnerConfig{9, 9, 10};
constexpr GameConfig IntermediateConfig{16, 16, 40};
constexpr GameConfig ExpertConfig{30, 16, 99};

inline constexpr Size GetWindowSize(const GameConfig &config) {
  return {20 * 2 + 30 * config.boardWidth,
          20 * 3 + 60 + 30 * config.boardHeight};
}

enum class GameStatus { Playing, Won, Lost };

class Game {
public:
  Game(const GameConfig &config, int time);
  static Game &Get();

  bool OnInput(UserCommand &cmd);
  bool OnUpdate(int time);
  void OnRender();

  GameStatus GetStatus() { return m_status; }
  void Restart();
  void Win();
  void Lose();

private:
  GameStatus m_status{GameStatus::Playing};
  GameConfig m_config{BeginnerConfig};

  int m_startTime{0};
  int m_updateTime{0};
  int m_elapsedTime{0};

  std::unique_ptr<RestartButton> m_restartButton;
  std::unique_ptr<Board> m_board;

private:
  void RenderBackground();
  void RenderCounter();
  void RenderTimer();
  void RenderNumber(int px, int py, int n);
  void RenderRestartButton();
};
} // namespace Minesweeper
