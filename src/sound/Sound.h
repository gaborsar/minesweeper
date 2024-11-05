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
    Mix_Chunk *m_chunk{nullptr};
  };
} // namespace Game
