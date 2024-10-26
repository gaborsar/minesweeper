#pragma once

#include <random>
#include <memory>
#include <vector>
#include "Renderer.h"
#include "Entity.h"

namespace Minesweeper
{
    struct Block
    {
        bool IsOpen{false};
        bool IsFlagged{false};
        bool IsMine{false};
        bool IsExploded{false};
        int NearMineCount{0};
        int Group{0};
    };

    class Board : public Entity
    {
    public:
        Board(std::shared_ptr<Renderer> renderer, const int boardWidth, const int boardHeight, const int mines);
        const Rect GetBox() override;
        const bool OnClick(const int px, const int py) override;
        void Render();

    private:
        std::shared_ptr<Renderer> m_renderer;
        int m_boardWidth{0};
        int m_boardHeight{0};
        std::vector<std::shared_ptr<Block>> m_blocks{};

    private:
        void PlaceMine(const int x, const int y);
        void CreateGroups();
        inline void MergeGroups(const int a, const int b);
        inline int PosToIndex(const int x, const int y);
    };
}
