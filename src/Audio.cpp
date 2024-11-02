#include "Audio.h"
#include <cassert>

namespace Minesweeper {
Audio::Audio() {
  int result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
  assert(result >= 0);
}

Audio::~Audio() { Mix_Quit(); }
} // namespace Minesweeper
