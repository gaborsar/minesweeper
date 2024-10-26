#include "Game.h"

namespace Minesweeper
{
    const Size GetWindowSize(const int boardWidth, const int boardHeight)
    {
        return {20 * 2 + 30 * boardWidth, 20 * 3 + 60 + 30 * boardHeight};
    }

    Game::Game(std::shared_ptr<Renderer> renderer, const int boardWidth, const int boardHeight, const int numberOfMines)
        : m_renderer{renderer}, m_boardWidth{boardWidth}, m_boardHeight{boardHeight}, m_numberOfMines{numberOfMines}
    {
        m_board = std::make_unique<Board>(renderer, boardWidth, boardHeight, numberOfMines);
    }

    void Game::OnClick(const int px, const int py)
    {
        const Rect box = m_board->GetBox();
        if (IsWithin(box, px, py))
        {
            m_board->OnClick(px - box.x, py - box.y);
        }
    }

    void Game::Render()
    {
        RenderBackground();
        m_board->Render();
    }

    void Game::RenderBackground()
    {
        const int x1{0};
        const int x2{20 + m_boardWidth * 30};

        const int y1{0};
        const int y2{20 + 60};
        const int y3{y2 + 20 + m_boardHeight * 30};

        m_renderer->RenderSprite(x1, y1, Sprites::FrameTopLeftCorner);
        m_renderer->RenderSprite(x2, y1, Sprites::FrameTopRightCorner);

        m_renderer->RenderSprite(x1, y3, Sprites::FrameBottomLeftCorner);
        m_renderer->RenderSprite(x2, y3, Sprites::FrameBottomRightCorner);

        m_renderer->RenderSprite(x1, y2, Sprites::FrameLeftJoint);
        m_renderer->RenderSprite(x2, y2, Sprites::FrameRightJoint);

        for (int i{0}; i < m_boardWidth * 3; ++i)
        {
            const int x{20 + i * 10};
            m_renderer->RenderSprite(x, y1, Sprites::FrameHorizontal);
            m_renderer->RenderSprite(x, y2, Sprites::FrameHorizontal);
            m_renderer->RenderSprite(x, y3, Sprites::FrameHorizontal);
        }

        for (int i{0}; i < 6; ++i)
        {
            const int y{20 + i * 10};
            m_renderer->RenderSprite(x1, y, Sprites::FrameVertical);
            m_renderer->RenderSprite(x2, y, Sprites::FrameVertical);
        }

        for (int i{0}; i < m_boardHeight * 3; ++i)
        {
            const int y{y2 + 20 + i * 10};
            m_renderer->RenderSprite(x1, y, Sprites::FrameVertical);
            m_renderer->RenderSprite(x2, y, Sprites::FrameVertical);
        }

        for (int i{0}; i < 6; ++i)
        {
            for (int j{0}; j < m_boardWidth * 3; ++j)
            {
                const int x{20 + j * 10};
                const int y{20 + i * 10};
                m_renderer->RenderSprite(x, y, Sprites::FrameBase);
            }
        }
    }
}
