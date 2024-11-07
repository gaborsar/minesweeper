#pragma once

#include <SDL_mixer.h>

namespace Game
{
  class Sound
  {
  public:
    Sound(const char *file);
    ~Sound();
    void Play();

  private:
    Sound(const Sound &) = delete;
    Sound &operator=(const Sound &) = delete;
    Mix_Chunk *m_chunk{nullptr};
  };
} // namespace Game
