#pragma once

#include <SDL_mixer.h>

namespace Minesweeper {
class Sound {
public:
  Sound(const char *file);
  ~Sound();
  void Load();
  void Play();

private:
  const char *m_file{};
  const bool m_ready{false};

private:
  Mix_Chunk *m_chunk;
};

namespace Sounds {
inline Sound ClickingSound{"clicking.mp3"};
inline Sound WinningSound{"winning.mp3"};
inline Sound LosingSound{"losing.mp3"};
} // namespace Sounds
} // namespace Minesweeper
