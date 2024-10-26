#pragma once

namespace Minesweeper
{
    struct Rect
    {
        int x, y;
        int w, h;
    };

    inline const bool IsWithin(const Rect& rect, const int px, const int py)
    {
        return px >= rect.x && px < rect.x + rect.w && py >= rect.y && py < rect.y + rect.w;
    }
}
