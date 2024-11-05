#pragma once

#include "../graphics/Size.h"

namespace Game
{
  struct GameConfig
  {
    int boardWidth{0};
    int boardHeight{0};
    int numberOfMines{0};
  };

  constexpr GameConfig BeginnerConfig{9, 9, 10};
  constexpr GameConfig IntermediateConfig{16, 16, 40};
  constexpr GameConfig ExpertConfig{30, 16, 99};

  inline constexpr Size GetWindowSize(const GameConfig &config)
  {
    return {20 * 2 + 30 * config.boardWidth, 20 * 3 + 60 + 30 * config.boardHeight};
  }
} // namespace Game
