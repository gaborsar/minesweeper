#pragma once

#include "Engine.h"
#include <array>

namespace Minesweeper {
namespace Sprites {
constexpr Engine::Rect BlockClosed{0, 0, 30, 30};
constexpr Engine::Rect BlockFlagged{30, 0, 30, 30};
constexpr Engine::Rect Block0{60, 0, 30, 30};
constexpr Engine::Rect Block1{90, 0, 30, 30};
constexpr Engine::Rect Block2{120, 0, 30, 30};
constexpr Engine::Rect Block3{150, 0, 30, 30};
constexpr Engine::Rect Block4{180, 0, 30, 30};
constexpr Engine::Rect Block5{210, 0, 30, 30};
constexpr Engine::Rect Block6{240, 0, 30, 30};
constexpr Engine::Rect Block7{270, 0, 30, 30};
constexpr Engine::Rect Block8{300, 0, 30, 30};
constexpr Engine::Rect BlockMine{330, 0, 30, 30};
constexpr Engine::Rect BlockMineExploded{360, 0, 30, 30};

constexpr Engine::Rect FrameTopLeftCorner{0, 30, 20, 20};
constexpr Engine::Rect FrameTopRightCorner{40, 30, 20, 20};
constexpr Engine::Rect FrameBottomLeftCorner{120, 30, 20, 20};
constexpr Engine::Rect FrameBottomRightCorner{140, 30, 20, 20};
constexpr Engine::Rect FrameLeftJoint{80, 30, 20, 20};
constexpr Engine::Rect FrameRightJoint{100, 30, 20, 20};
constexpr Engine::Rect FrameHorizontal{20, 30, 10, 20};
constexpr Engine::Rect FrameVertical{60, 30, 20, 10};
constexpr Engine::Rect FrameBase{2, 2, 10, 10};

constexpr Engine::Rect DigitBorder{0, 87, 64, 41};
constexpr Engine::Rect DigitNone{0, 50, 20, 37};
constexpr Engine::Rect Digit0{20, 50, 20, 37};
constexpr Engine::Rect Digit1{40, 50, 20, 37};
constexpr Engine::Rect Digit2{60, 50, 20, 37};
constexpr Engine::Rect Digit3{80, 50, 20, 37};
constexpr Engine::Rect Digit4{100, 50, 20, 37};
constexpr Engine::Rect Digit5{120, 50, 20, 37};
constexpr Engine::Rect Digit6{140, 50, 20, 37};
constexpr Engine::Rect Digit7{160, 50, 20, 37};
constexpr Engine::Rect Digit8{180, 50, 20, 37};
constexpr Engine::Rect Digit9{200, 50, 20, 37};

constexpr Engine::Rect RestartButtonHappy{64, 87, 36, 36};
constexpr Engine::Rect RestartButtonSad{100, 87, 36, 36};

constexpr std::array<Engine::Rect, 9> BlockDigits{
    Block0, Block1, Block2, Block3, Block4, Block5, Block6, Block7, Block8,
};

constexpr std::array<Engine::Rect, 10> LeftDigits{
    DigitNone, Digit1, Digit2, Digit3, Digit4,
    Digit5,    Digit6, Digit7, Digit8, Digit9,
};

constexpr std::array<Engine::Rect, 10> RightDigits{
    Digit0, Digit1, Digit2, Digit3, Digit4,
    Digit5, Digit6, Digit7, Digit8, Digit9,
};
} // namespace Sprites
} // namespace Minesweeper
