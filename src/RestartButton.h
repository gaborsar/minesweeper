#pragma once

#include "Input.h"
#include <memory>

namespace Minesweeper
{
    class RestartButton
    {
    public:
        RestartButton(int x, int y);
        bool OnInput(UserCommand &command);
        void OnRender();

    private:
        int m_x{0};
        int m_y{0};
    };
}
