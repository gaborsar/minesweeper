#pragma once

namespace Game
{
  class SDLPtr
  {
  public:
    SDLPtr();
    ~SDLPtr();
    
  private:
    SDLPtr(const SDLPtr&) = delete;
    SDLPtr& operator=(const SDLPtr&) = delete;
  };
} // namespace Game
