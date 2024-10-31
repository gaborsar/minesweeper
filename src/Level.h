#pragma once

#include "Renderer.h"
#include "Rect.h"
#include <memory>
#include <utility>
#include <vector>
#include <random>

namespace Minesweeper
{
    struct Block
    {
        bool IsOpen{false};
        bool IsFlagged{false};
        bool IsMine{false};
        bool IsExploded{false};
        int NearMineCount{0};
        std::pair<int, int> Groups{0, 0};
    };

    class Level
    {
    public:
        Level(std::shared_ptr<Renderer> renderer, int levelWidth, int levelHeight, int numberOfMines);
        Rect GetBoundingRect();
        void OnRestart();
        bool OnLeftClick(int px, int py);
        bool OnRightClick(int px, int py);
        void OnRender();
        int CountFlags();
        bool HasWon();
        bool HasLost();

    private:
        std::shared_ptr<Renderer> m_renderer;
        std::mt19937 m_mt;
        int m_levelWidth{0};
        int m_levelHeight{0};
        int m_numberOfMines{0};
        std::vector<std::shared_ptr<Block>> m_blocks;

    private:
        void PlaceMine(int x, int y);
        void CreateGroups();
        inline void MergeGroups(int a, int b);
        inline int PosToIndex(int x, int y) { return y * m_levelWidth + x; }
    };
} // namespace Minesweeper
