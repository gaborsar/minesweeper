#include "game.h"

namespace Minesweeper
{

    const Size GetWindowSize(const int board_width, const int board_height)
    {
        return {20 * 2 + 30 * board_width, 20 * 3 + 60 + 30 * board_height};
    }

    Game::Game(std::shared_ptr<Renderer> renderer, const int board_width, const int board_height, const int number_of_mines)
        : m_renderer{renderer}, m_board_width{board_width}, m_board_height{board_height}, m_number_of_mines{number_of_mines}
    {
        m_board = std::make_unique<Board>(renderer, board_width, board_height, number_of_mines);
    }

    void Game::HandleClick(const int px, const int py)
    {
        m_board->HandleClick(px, py);
    }

    void Game::Render()
    {
        RenderBackground();
        m_board->Render();
    }

    void Game::RenderBackground()
    {
        const int x1{0};
        const int x2{20 + m_board_width * 30};

        const int y1{0};
        const int y2{20 + 60};
        const int y3{y2 + 20 + m_board_height * 30};

        m_renderer->RenderSprite(x1, y1, Sprites::FrameTopLeftCorner);
        m_renderer->RenderSprite(x2, y1, Sprites::FrameTopRightCorner);

        m_renderer->RenderSprite(x1, y3, Sprites::FrameBottomLeftCorner);
        m_renderer->RenderSprite(x2, y3, Sprites::FrameBottomRightCorner);

        m_renderer->RenderSprite(x1, y2, Sprites::FrameLeftJoint);
        m_renderer->RenderSprite(x2, y2, Sprites::FrameRightJoint);

        for (int i{0}; i < m_board_width * 3; ++i)
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

        for (int i{0}; i < m_board_height * 3; ++i)
        {
            const int y{y2 + 20 + i * 10};
            m_renderer->RenderSprite(x1, y, Sprites::FrameVertical);
            m_renderer->RenderSprite(x2, y, Sprites::FrameVertical);
        }
    }

}
