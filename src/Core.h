#pragma once

namespace Minesweeper
{
    struct Size
    {
        int w;
        int h;
    };

    struct Rect
    {
        int x, y;
        int w, h;
    };

    inline constexpr bool IsPointWithinRect(const Rect &rect, int px, int py)
    {
        return px >= rect.x && px < rect.x + rect.w && py >= rect.y && py < rect.y + rect.w;
    }
}
