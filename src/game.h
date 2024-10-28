#pragma once

#include <cassert>
#include <memory>
#include "Rect.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Board.h"

namespace Minesweeper
{
    struct Size
    {
        int w;
        int h;
    };

    const Size GetWindowSize(const int boardWidth, const int boardHeight);

    class Game
    {
    public:
        Game(std::shared_ptr<Renderer> renderer, const int boardWidth, const int boardHeight, const int numberOfMines);
        const bool OnClick(const int px, const int py);
        const bool Update(const int time);
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
        std::unique_ptr<Board> m_board{};

    private:
        void RenderBackground();
        void RenderCounter();
        void RenderTimer();
        void RenderNumber(const int px, const int py, const int n);
        void RenderRestartButton();
    };
}
