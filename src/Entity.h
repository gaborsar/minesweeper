#pragma once

#include "Mouse.h"
#include "Rect.h"

namespace Minesweeper {
class Entity {
public:
  virtual ~Entity() = default;
  virtual const Rect GetBox() = 0;
  virtual const bool OnClick(const int px, const int py,
                             const MouseButton button) = 0;
};
} // namespace Minesweeper
