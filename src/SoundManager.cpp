#include "SoundManager.h"

namespace Minesweeper {
static SoundManager *s_instance{nullptr};

SoundManager::SoundManager()
    : m_clickingSound{Engine::Sound{"clicking.mp3"}},
      m_winningSound{Engine::Sound{"winning.mp3"}},
      m_losingSound{Engine::Sound{"losing.mp3"}} {
  s_instance = this;
}

void SoundManager::PlayClickingSound() { s_instance->m_clickingSound.Play(); }

void SoundManager::PlayWinningSound() { s_instance->m_winningSound.Play(); }

void SoundManager::PlayLosingSound() { s_instance->m_losingSound.Play(); }

} // namespace Minesweeper
