#pragma once

namespace Minesweeper
{
    class Entity
    {
    public:
        virtual ~Entity() = default;
        virtual const Rect GetBox() = 0;
        virtual void OnClick(const int px, const int py) = 0;
    };
}
