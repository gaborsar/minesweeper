#include "Random.h"

namespace Game
{
  static Random *s_instance{nullptr};

  Random::Random()
  {
    m_mt = static_cast<std::mt19937>(std::random_device{}());
    s_instance = this;
  }

  int Random::Int(int u, int v)
  {
    std::uniform_int_distribution<int> dist{u, v};
    return dist(s_instance->m_mt);
  }
} // namespace Game
