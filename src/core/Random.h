#pragma once

#include <random>

namespace Game
{
  class Random
  {
  public:
    Random();
    static int Int(int u, int v);

  private:
    std::mt19937 m_mt;
  };
} // namespace Game
