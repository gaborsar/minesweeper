#pragma once

#include <random>
#include <memory>
#include <vector>
#include "renderer.h"
#include "block.h"

namespace Minesweeper
{
    class Board
    {
    public:
        Board(std::shared_ptr<Renderer> renderer, const int board_width, const int board_height, const int mines);
        void HandleClick(const int px, const int py);
        void Render();

    private:
        std::shared_ptr<Renderer> m_renderer;
        int m_board_width{0};
        int m_board_height{0};
        std::vector<std::shared_ptr<Block>> m_blocks{};
        void PlaceMine(const int x, const int y);
        void CreateGroups();
        inline void MergeGroups(const int a, const int b);
        inline int PosToIndex(const int x, const int y);
    };
}
