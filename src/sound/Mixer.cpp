#include "Mixer.h"
#include <SDL_mixer.h>
#include <sstream>

namespace Game
{
  Mixer::Mixer()
  {
    int result{Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)};
    if (result < 0)
    {
      std::stringstream msg{};
      msg << "failed to open SDL audio" << Mix_GetError();
      throw std::runtime_error(msg.str());
    }
  }

  Mixer::~Mixer()
  {
    Mix_Quit();
  }
} // namespace Game
