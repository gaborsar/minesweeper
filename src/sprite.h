#pragma once

#include "Rect.h"
#include <array>

namespace Minesweeper {
using Sprite = Rect;

namespace Sprites {
inline constexpr Sprite BlockClosed{0, 0, 30, 30};
inline constexpr Sprite BlockFlagged{30, 0, 30, 30};
inline constexpr Sprite Block0{60, 0, 30, 30};
inline constexpr Sprite Block1{90, 0, 30, 30};
inline constexpr Sprite Block2{120, 0, 30, 30};
inline constexpr Sprite Block3{150, 0, 30, 30};
inline constexpr Sprite Block4{180, 0, 30, 30};
inline constexpr Sprite Block5{210, 0, 30, 30};
inline constexpr Sprite Block6{240, 0, 30, 30};
inline constexpr Sprite Block7{270, 0, 30, 30};
inline constexpr Sprite Block8{300, 0, 30, 30};
inline constexpr Sprite BlockMine{330, 0, 30, 30};
inline constexpr Sprite BlockMineExploded{360, 0, 30, 30};

inline constexpr Sprite FrameTopLeftCorner{0, 30, 20, 20};
inline constexpr Sprite FrameTopRightCorner{40, 30, 20, 20};
inline constexpr Sprite FrameBottomLeftCorner{120, 30, 20, 20};
inline constexpr Sprite FrameBottomRightCorner{140, 30, 20, 20};
inline constexpr Sprite FrameLeftJoint{80, 30, 20, 20};
inline constexpr Sprite FrameRightJoint{100, 30, 20, 20};
inline constexpr Sprite FrameHorizontal{20, 30, 10, 20};
inline constexpr Sprite FrameVertical{60, 30, 20, 10};
inline constexpr Sprite FrameBase{2, 2, 10, 10};

inline constexpr Sprite DigitBorder{0, 87, 64, 41};
inline constexpr Sprite DigitNone{0, 50, 20, 37};
inline constexpr Sprite Digit0{20, 50, 20, 37};
inline constexpr Sprite Digit1{40, 50, 20, 37};
inline constexpr Sprite Digit2{60, 50, 20, 37};
inline constexpr Sprite Digit3{80, 50, 20, 37};
inline constexpr Sprite Digit4{100, 50, 20, 37};
inline constexpr Sprite Digit5{120, 50, 20, 37};
inline constexpr Sprite Digit6{140, 50, 20, 37};
inline constexpr Sprite Digit7{160, 50, 20, 37};
inline constexpr Sprite Digit8{180, 50, 20, 37};
inline constexpr Sprite Digit9{200, 50, 20, 37};

inline constexpr Sprite RestartButtonHappy{64, 87, 36, 36};
inline constexpr Sprite RestartButtonHappyActive{136, 87, 36, 36};
inline constexpr Sprite RestartButtonSad{100, 87, 36, 36};
inline constexpr Sprite RestartButtonSadActive{172, 87, 36, 36};

inline constexpr std::array<Sprite, 9> BlockDigits{
    Block0, Block1, Block2, Block3, Block4, Block5, Block6, Block7, Block8};

inline constexpr std::array<Sprite, 10> LeftDigits{
    DigitNone, Digit1, Digit2, Digit3, Digit4,
    Digit5,    Digit6, Digit7, Digit8, Digit9};

inline constexpr std::array<Sprite, 10> RightDigits{
    Digit0, Digit1, Digit2, Digit3, Digit4,
    Digit5, Digit6, Digit7, Digit8, Digit9};
} // namespace Sprites
} // namespace Minesweeper
