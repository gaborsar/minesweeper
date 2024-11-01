#pragma once

#include "Input.h"

namespace Minesweeper
{
    class RestartButton
    {
    public:
        RestartButton(int x, int y);
        bool OnInput(UserCommand &cmd);
        void OnRender();
        void Move(int x, int y);

    private:
        int m_x{0};
        int m_y{0};
    };
}
