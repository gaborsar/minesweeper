#pragma once

namespace Game
{
  class Mixer
  {
  public:
    Mixer();
    ~Mixer();

  private:
    Mixer(const Mixer &) = delete;
    Mixer &operator=(const Mixer &) = delete;
  };
} // namespace Game
