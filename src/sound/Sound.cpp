#include "Sound.h"
#include <sstream>

namespace Game {
Sound::Sound(const char *file) {
  Mix_Chunk *chunk{Mix_LoadWAV(file)};
  if (!chunk) {
    std::stringstream msg{};
    msg << "failed to load SDL audio chunk" << Mix_GetError();
    throw std::runtime_error(msg.str());
  }
  m_chunk = chunk;
}

Sound::~Sound() { Mix_FreeChunk(m_chunk); }

void Sound::Play() { Mix_PlayChannel(-1, m_chunk, 0); }
} // namespace Game
