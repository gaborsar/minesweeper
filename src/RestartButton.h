#pragma once

#include "Renderer.h"
#include <memory>

namespace Minesweeper
{
    class RestartButton
    {
    public:
        RestartButton(std::shared_ptr<Renderer> renderer, int boardWidth, int boardHeight);
        Rect GetBoundingRect();
        void OnRender();
        void MakeHappy() { m_isHappy = true; }
        void MakeSad() { m_isHappy = false; }

    private:
        std::shared_ptr<Renderer> m_renderer;
        int m_boardWidth{0};
        int m_boardHeight{0};
        bool m_isHappy{true};
    };
}
