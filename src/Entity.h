#pragma once

#include "Mouse.h"
#include "Rect.h"

namespace Minesweeper
{
    class Entity
    {
    public:
        virtual ~Entity() = default;
        virtual Rect GetBox() = 0;
        virtual bool OnClick(int px, int py, MouseButton button) = 0;
    };
} // namespace Minesweeper
