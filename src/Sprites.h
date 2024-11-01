#pragma once

#include "Core.h"
#include <array>

namespace Minesweeper
{
    namespace Sprites
    {
        inline constexpr Rect BlockClosed{0, 0, 30, 30};
        inline constexpr Rect BlockFlagged{30, 0, 30, 30};
        inline constexpr Rect Block0{60, 0, 30, 30};
        inline constexpr Rect Block1{90, 0, 30, 30};
        inline constexpr Rect Block2{120, 0, 30, 30};
        inline constexpr Rect Block3{150, 0, 30, 30};
        inline constexpr Rect Block4{180, 0, 30, 30};
        inline constexpr Rect Block5{210, 0, 30, 30};
        inline constexpr Rect Block6{240, 0, 30, 30};
        inline constexpr Rect Block7{270, 0, 30, 30};
        inline constexpr Rect Block8{300, 0, 30, 30};
        inline constexpr Rect BlockMine{330, 0, 30, 30};
        inline constexpr Rect BlockMineExploded{360, 0, 30, 30};

        inline constexpr Rect FrameTopLeftCorner{0, 30, 20, 20};
        inline constexpr Rect FrameTopRightCorner{40, 30, 20, 20};
        inline constexpr Rect FrameBottomLeftCorner{120, 30, 20, 20};
        inline constexpr Rect FrameBottomRightCorner{140, 30, 20, 20};
        inline constexpr Rect FrameLeftJoint{80, 30, 20, 20};
        inline constexpr Rect FrameRightJoint{100, 30, 20, 20};
        inline constexpr Rect FrameHorizontal{20, 30, 10, 20};
        inline constexpr Rect FrameVertical{60, 30, 20, 10};
        inline constexpr Rect FrameBase{2, 2, 10, 10};

        inline constexpr Rect DigitBorder{0, 87, 64, 41};
        inline constexpr Rect DigitNone{0, 50, 20, 37};
        inline constexpr Rect Digit0{20, 50, 20, 37};
        inline constexpr Rect Digit1{40, 50, 20, 37};
        inline constexpr Rect Digit2{60, 50, 20, 37};
        inline constexpr Rect Digit3{80, 50, 20, 37};
        inline constexpr Rect Digit4{100, 50, 20, 37};
        inline constexpr Rect Digit5{120, 50, 20, 37};
        inline constexpr Rect Digit6{140, 50, 20, 37};
        inline constexpr Rect Digit7{160, 50, 20, 37};
        inline constexpr Rect Digit8{180, 50, 20, 37};
        inline constexpr Rect Digit9{200, 50, 20, 37};

        inline constexpr Rect RestartButtonHappy{64, 87, 36, 36};
        inline constexpr Rect RestartButtonSad{100, 87, 36, 36};

        inline constexpr std::array<Rect, 9> BlockDigits{
            Block0, Block1, Block2, Block3, Block4,
            Block5, Block6, Block7, Block8};

        inline constexpr std::array<Rect, 10> LeftDigits{
            DigitNone, Digit1, Digit2, Digit3, Digit4,
            Digit5, Digit6, Digit7, Digit8, Digit9};

        inline constexpr std::array<Rect, 10> RightDigits{
            Digit0, Digit1, Digit2, Digit3, Digit4,
            Digit5, Digit6, Digit7, Digit8, Digit9};
    } // namespace Rects
} // namespace Minesweeper
