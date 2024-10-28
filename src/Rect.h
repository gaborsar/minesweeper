#pragma once

namespace Minesweeper {
struct Rect {
  int x, y;
  int w, h;
};

inline constexpr bool IsWithin(const Rect &rect, int px, int py) {
  return px >= rect.x && px < rect.x + rect.w && py >= rect.y &&
         py < rect.y + rect.w;
}
} // namespace Minesweeper
