#pragma once

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
        void OnClick(const int px, const int py);
        void Render();

    private:
        std::shared_ptr<Renderer> m_renderer;
        int m_boardWidth{0};
        int m_boardHeight{0};
        int m_numberOfMines{0};
        std::unique_ptr<Board> m_board{};

    private:
        void RenderBackground();
        // void RenderCounter();
        // void RenderTimer();
        // void RenderPlayButton();
        // void RenderBeginnerButton();
        // void RenderIntermediateButton();
        // void RenderExpertButton();
    };
}
