#pragma once

#include "Board.h"
#include "Mouse.h"
#include "Renderer.h"
#include <cassert>
#include <memory>

namespace Minesweeper
{
    struct Size
    {
        int w;
        int h;
    };

    inline constexpr Size GetWindowSize(int boardWidth, int boardHeight)
    {
        return {20 * 2 + 30 * boardWidth, 20 * 3 + 60 + 30 * boardHeight};
    }

    class Game
    {
    public:
        Game(std::shared_ptr<Renderer> renderer, int boardWidth, int boardHeight, int numberOfMines);
        bool OnClick(int px, int py, MouseButton button);
        bool Update(int time);
        void Render();
        void SetStartTime(int startTime);

    private:
        std::shared_ptr<Renderer> m_renderer;
        int m_boardWidth{0};
        int m_boardHeight{0};
        int m_numberOfMines{0};
        int m_startTime{0};
        int m_updateTime{0};
        int m_elapsedTime{0};
        std::unique_ptr<Board> m_board;

    private:
        void RenderBackground();
        void RenderCounter();
        void RenderTimer();
        void RenderNumber(int px, int py, int n);
        void RenderRestartButton();
    };
} // namespace Minesweeper
