#include "Game.h"

namespace Minesweeper
{
    Game::Game(std::shared_ptr<Renderer> renderer, int levelWidth, int levelHeight, int numberOfMines, int time)
        : m_renderer{renderer}, m_levelWidth{levelWidth}, m_levelHeight{levelHeight}, m_numberOfMines{numberOfMines}, m_startTime{time}, m_updateTime{time}
    {
        m_restartButton = std::make_unique<RestartButton>(renderer, levelWidth, levelHeight);
        m_level = std::make_unique<Level>(renderer, levelWidth, levelHeight, numberOfMines);
    }

    bool Game::OnLeftClick(int px, int py)
    {
        Rect btnRect{m_restartButton->GetBoundingRect()};
        if (IsPointWithinRect(btnRect, px, py))
        {
            m_status = GameStatus::Playing;
            m_startTime = m_updateTime;
            m_restartButton->MakeHappy();
            m_level->OnRestart();
            return true;
        }

        if (m_status != GameStatus::Playing)
        {
            return false;
        }

        Rect levelRect{m_level->GetBoundingRect()};
        if (IsPointWithinRect(levelRect, px, py))
        {
            bool hasChanged{m_level->OnLeftClick(px - levelRect.x, py - levelRect.y)};
            if (!hasChanged)
            {
                return false;
            }
            if (m_level->HasWon())
            {
                m_status = GameStatus::Won;
            }
            else if (m_level->HasLost())
            {
                m_status = GameStatus::Lost;
                m_restartButton->MakeSad();
            }
            return true;
        }

        return false;
    }

    bool Game::OnRightClick(int px, int py)
    {
        if (m_status != GameStatus::Playing)
        {
            return false;
        }

        Rect levelRect{m_level->GetBoundingRect()};
        if (IsPointWithinRect(levelRect, px, py))
        {
            return m_level->OnRightClick(px - levelRect.x, py - levelRect.y);
        }

        return false;
    }

    bool Game::OnUpdate(int time)
    {
        if (m_status != GameStatus::Playing)
        {
            return false;
        }
        m_updateTime = time;
        if (m_elapsedTime >= 999)
        {
            return false;
        }
        int elapsedTime{(m_updateTime - m_startTime) / 1000};
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

    void Game::OnRender()
    {
        RenderBackground();
        RenderCounter();
        RenderTimer();
        m_restartButton->OnRender();
        m_level->OnRender();
    }

    void Game::RenderBackground()
    {
        int x1{0};
        int x2{20 + m_levelWidth * 30};

        int y1{0};
        int y2{20 + 60};
        int y3{y2 + 20 + m_levelHeight * 30};

        m_renderer->RenderSprite(x1, y1, Sprites::FrameTopLeftCorner);
        m_renderer->RenderSprite(x2, y1, Sprites::FrameTopRightCorner);

        m_renderer->RenderSprite(x1, y3, Sprites::FrameBottomLeftCorner);
        m_renderer->RenderSprite(x2, y3, Sprites::FrameBottomRightCorner);

        m_renderer->RenderSprite(x1, y2, Sprites::FrameLeftJoint);
        m_renderer->RenderSprite(x2, y2, Sprites::FrameRightJoint);

        for (int i{0}; i < m_levelWidth * 3; ++i)
        {
            int x{20 + i * 10};
            m_renderer->RenderSprite(x, y1, Sprites::FrameHorizontal);
            m_renderer->RenderSprite(x, y2, Sprites::FrameHorizontal);
            m_renderer->RenderSprite(x, y3, Sprites::FrameHorizontal);
        }

        for (int i{0}; i < 6; ++i)
        {
            int y{20 + i * 10};
            m_renderer->RenderSprite(x1, y, Sprites::FrameVertical);
            m_renderer->RenderSprite(x2, y, Sprites::FrameVertical);
        }

        for (int i{0}; i < m_levelHeight * 3; ++i)
        {
            int y{y2 + 20 + i * 10};
            m_renderer->RenderSprite(x1, y, Sprites::FrameVertical);
            m_renderer->RenderSprite(x2, y, Sprites::FrameVertical);
        }

        for (int i{0}; i < 6; ++i)
        {
            for (int j{0}; j < m_levelWidth * 3; ++j)
            {
                int x{20 + j * 10};
                int y{20 + i * 10};
                m_renderer->RenderSprite(x, y, Sprites::FrameBase);
            }
        }
    }

    void Game::RenderCounter()
    {
        int x1{30};
        int y{30};
        int count{m_numberOfMines - m_level->CountFlags()};
        if (count < 0)
        {
            count = 0;
        }
        RenderNumber(30, 30, count);
    }

    void Game::RenderTimer()
    {
        int x{20 + m_levelWidth * 30 - 64 - 10};
        int y{30};
        RenderNumber(x, y, m_elapsedTime);
    }

    void Game::RenderNumber(int px, int py, int n)
    {
        int d3{n};

        int d1{n / 100};
        d3 = d3 % 100;

        int d2{d3 / 10};
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
        int x{20 + m_levelWidth * 30 / 2 - 18};
        int y{20 + 12};
        m_renderer->RenderSprite(x, y, Sprites::RestartButtonHappy);
    }
} // namespace Minesweeper
