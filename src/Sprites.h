#pragma once

#include "Core.h"
#include <array>

namespace Minesweeper {
namespace Sprites {
constexpr Rect BlockClosed{0, 0, 30, 30};
constexpr Rect BlockFlagged{30, 0, 30, 30};
constexpr Rect Block0{60, 0, 30, 30};
constexpr Rect Block1{90, 0, 30, 30};
constexpr Rect Block2{120, 0, 30, 30};
constexpr Rect Block3{150, 0, 30, 30};
constexpr Rect Block4{180, 0, 30, 30};
constexpr Rect Block5{210, 0, 30, 30};
constexpr Rect Block6{240, 0, 30, 30};
constexpr Rect Block7{270, 0, 30, 30};
constexpr Rect Block8{300, 0, 30, 30};
constexpr Rect BlockMine{330, 0, 30, 30};
constexpr Rect BlockMineExploded{360, 0, 30, 30};

constexpr Rect FrameTopLeftCorner{0, 30, 20, 20};
constexpr Rect FrameTopRightCorner{40, 30, 20, 20};
constexpr Rect FrameBottomLeftCorner{120, 30, 20, 20};
constexpr Rect FrameBottomRightCorner{140, 30, 20, 20};
constexpr Rect FrameLeftJoint{80, 30, 20, 20};
constexpr Rect FrameRightJoint{100, 30, 20, 20};
constexpr Rect FrameHorizontal{20, 30, 10, 20};
constexpr Rect FrameVertical{60, 30, 20, 10};
constexpr Rect FrameBase{2, 2, 10, 10};

constexpr Rect DigitBorder{0, 87, 64, 41};
constexpr Rect DigitNone{0, 50, 20, 37};
constexpr Rect Digit0{20, 50, 20, 37};
constexpr Rect Digit1{40, 50, 20, 37};
constexpr Rect Digit2{60, 50, 20, 37};
constexpr Rect Digit3{80, 50, 20, 37};
constexpr Rect Digit4{100, 50, 20, 37};
constexpr Rect Digit5{120, 50, 20, 37};
constexpr Rect Digit6{140, 50, 20, 37};
constexpr Rect Digit7{160, 50, 20, 37};
constexpr Rect Digit8{180, 50, 20, 37};
constexpr Rect Digit9{200, 50, 20, 37};

constexpr Rect RestartButtonHappy{64, 87, 36, 36};
constexpr Rect RestartButtonSad{100, 87, 36, 36};

constexpr std::array<Rect, 9> BlockDigits{
    Block0, Block1, Block2, Block3, Block4, Block5, Block6, Block7, Block8,
};

constexpr std::array<Rect, 10> LeftDigits{
    DigitNone, Digit1, Digit2, Digit3, Digit4,
    Digit5,    Digit6, Digit7, Digit8, Digit9,
};

constexpr std::array<Rect, 10> RightDigits{
    Digit0, Digit1, Digit2, Digit3, Digit4,
    Digit5, Digit6, Digit7, Digit8, Digit9,
};
} // namespace Sprites
} // namespace Minesweeper
