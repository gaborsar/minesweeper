#pragma once

namespace Minesweeper
{
    struct Sprite
    {
        int x;
        int y;
        int w;
        int h;
    };

    namespace Sprites
    {
        inline constexpr Sprite BlockClosed{0, 0, 30, 30};
        inline constexpr Sprite BlockOpen{30, 0, 30, 30};
        inline constexpr Sprite FrameTopLeftCorner{0, 30, 20, 20};
        inline constexpr Sprite FrameTopRightCorner{40, 30, 20, 20};
        inline constexpr Sprite FrameBottomLeftCorner{120, 30, 20, 20};
        inline constexpr Sprite FrameBottomRightCorner{140, 30, 20, 20};
        inline constexpr Sprite FrameLeftJoint{80, 30, 20, 20};
        inline constexpr Sprite FrameRightJoint{100, 30, 20, 20};
        inline constexpr Sprite FrameHorizontal{20, 30, 10, 20};
        inline constexpr Sprite FrameVertical{60, 30, 20, 10};
    }
}