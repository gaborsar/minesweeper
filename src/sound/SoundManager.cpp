#include "SoundManager.h"

namespace Game {
static SoundManager *s_instance{nullptr};

SoundManager::SoundManager()
    : m_clickingSound{Sound{"clicking.mp3"}},
      m_winningSound{Sound{"winning.mp3"}}, m_losingSound{Sound{"losing.mp3"}} {
  s_instance = this;
}

void SoundManager::PlayClickingSound() { s_instance->m_clickingSound.Play(); }
void SoundManager::PlayWinningSound() { s_instance->m_winningSound.Play(); }
void SoundManager::PlayLosingSound() { s_instance->m_losingSound.Play(); }
} // namespace Game
