#include "RestartButton.h"

namespace Minesweeper
{
    RestartButton::RestartButton(std::shared_ptr<Renderer> renderer, int boardWidth, int boardHeight)
        : m_renderer{renderer}, m_boardWidth{boardWidth}, m_boardHeight{boardHeight}
    {
    }

    Rect RestartButton::GetBoundingRect()
    {
        int x{20 + m_boardWidth * 30 / 2 - 18};
        int y{20 + 12};
        int w{36};
        int h{36};
        return {x, y, w, h};
    };

    void RestartButton::OnRender()
    {
        int x{20 + m_boardWidth * 30 / 2 - 18};
        int y{20 + 12};
        m_renderer->RenderSprite(x, y, m_isHappy ? Sprites::RestartButtonHappy : Sprites::RestartButtonSad);
    }
}
