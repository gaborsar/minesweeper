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

    void Game::SetStartTime(int startTime)
    {
        m_startTime = startTime;
        m_updateTime = startTime;
    }

    const bool Game::OnClick(const int px, const int py)
    {
        const Rect box = m_board->GetBox();
        if (IsWithin(box, px, py))
        {
            return m_board->OnClick(px - box.x, py - box.y);
        }
        return false;
    }

    const bool Game::Update(int time)
    {
        m_updateTime = time;
        if (m_elapsedTime >= 999)
        {
            return false;
        }
        int elapsedTime = (m_updateTime - m_startTime) / 1000;
        if (elapsedTime > 999)
        {
            elapsedTime = 999;
        }
        if (elapsedTime == m_elapsedTime)
        {
            return false;
        }
        m_elapsedTime = elapsedTime;
        return true;
    }

    void Game::Render()
    {
        RenderBackground();
        RenderCounter();
        RenderTimer();
        RenderRestartButton();
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

    void Game::RenderCounter()
    {
        const int x1{30};
        const int y{30};
        m_renderer->RenderSprite(x1, y, Sprites::DigitBorder);
        m_renderer->RenderSprite(x1 + 2, y + 2, Sprites::DigitNone);
        m_renderer->RenderSprite(x1 + 2 + 20, y + 2, Sprites::Digit0);
        m_renderer->RenderSprite(x1 + 2 + 40, y + 2, Sprites::Digit1);
    }

    void Game::RenderTimer()
    {
        const int x{20 + m_boardWidth * 30 - 64 - 10};
        const int y{30};
        RenderNumber(x, y, m_elapsedTime);
    }

    void Game::RenderNumber(const int px, const int py, const int n)
    {
        int d3 = n;

        int d1 = n / 100;
        d3 = d3 % 100;

        int d2 = d3 / 10;
        d3 = d3 % 10;

        assert(d1 >= 0 && d1 <= 9);
        assert(d2 >= 0 && d2 <= 9);
        assert(d3 >= 0 && d3 <= 9);

        m_renderer->RenderSprite(px, py, Sprites::DigitBorder);
        m_renderer->RenderSprite(px + 2, py + 2, Sprites::LeftDigits[d1]);
        if (d1 == 0)
        {
            m_renderer->RenderSprite(px + 2 + 20, py + 2, Sprites::LeftDigits[d2]);
        }
        else
        {
            m_renderer->RenderSprite(px + 2 + 20, py + 2, Sprites::RightDigits[d2]);
        }
        m_renderer->RenderSprite(px + 2 + 40, py + 2, Sprites::RightDigits[d3]);
    }

    void Game::RenderRestartButton()
    {
        const int x{20 + m_boardWidth * 30 / 2 - 15};
        const int y{35};
        m_renderer->RenderSprite(x, y, Sprites::RestartButtonHappy);
    }
}
