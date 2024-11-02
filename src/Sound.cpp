#include "Sound.h"
#include <cassert>

namespace Minesweeper {
Sound::Sound(const char *file) : m_file{file} {}

Sound::~Sound() {
  if (m_chunk != nullptr) {
    Mix_FreeChunk(m_chunk);
  }
}

void Sound::Load() {
  if (m_ready) {
    return;
  }
  Mix_Chunk *chunk = Mix_LoadWAV(m_file);
  assert(chunk != nullptr);
  m_chunk = chunk;
}

void Sound::Play() {
  Load();
  Mix_PlayChannel(1, m_chunk, 0);
}
} // namespace Minesweeper
