#pragma once

#include "Sound.h"

namespace Game
{
  class SoundManager
  {
  public:
    SoundManager();
    static void PlayClickingSound();
    static void PlayWinningSound();
    static void PlayLosingSound();

  private:
    Sound m_clickingSound;
    Sound m_winningSound;
    Sound m_losingSound;
  };
} // namespace Game
