#pragma once

#include "Engine.h"

namespace Minesweeper {
class SoundManager {
public:
  SoundManager();
  static void PlayClickingSound();
  static void PlayWinningSound();
  static void PlayLosingSound();

private:
  Engine::Sound m_clickingSound;
  Engine::Sound m_winningSound;
  Engine::Sound m_losingSound;
};
} // namespace Minesweeper
