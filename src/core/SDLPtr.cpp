#include "SDLPtr.h"
#include <SDL.h>
#include <sstream>

namespace Game {
SDLPtr::SDLPtr() {
  int result{SDL_Init(SDL_INIT_EVERYTHING)};
  if (result < 0) {
    std::stringstream msg{};
    msg << "failed to init SDL: " << SDL_GetError();
    throw std::runtime_error(msg.str());
  }
}

SDLPtr::~SDLPtr() { SDL_Quit(); }
} // namespace Game
