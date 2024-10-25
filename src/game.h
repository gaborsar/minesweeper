#pragma once

#include <memory>
#include "renderer.h"
#include "sprite.h"
#include "board.h"

namespace Minesweeper
{

    struct Size
    {
        int width;
        int height;
    };

    const Size GetWindowSize(const int board_width, const int board_height);

    class Game
    {
    public:
        Game(std::shared_ptr<Renderer> renderer, const int board_width, const int board_height, const int number_of_mines);
        void HandleClick(const int px, const int py);
        void Render();

    private:
        std::shared_ptr<Renderer> m_renderer;
        int m_board_width{0};
        int m_board_height{0};
        int m_number_of_mines{0};
        std::unique_ptr<Board> m_board{};
        void RenderBackground();
        // void RenderCounter();
        // void RenderTimer();
        // void RenderPlayButton();
        // void RenderBeginnerButton();
        // void RenderIntermediateButton();
        // void RenderExpertButton();
    };

}
