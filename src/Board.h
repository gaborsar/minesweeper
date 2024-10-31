#pragma once

#include "Entity.h"
#include "Mouse.h"
#include "Renderer.h"
#include <memory>
#include <utility>
#include <vector>

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

    enum class BoardStatus
    {
        Playing,
        Lost,
        Won
    };

    class Board : public Entity
    {
    public:
        Board(std::shared_ptr<Renderer> renderer, int boardWidth, int boardHeight, int mines);
        virtual Rect GetBox() override;
        virtual bool OnClick(int px, int py, MouseButton button) override;
        void OnRender();
        BoardStatus GetStatus() { return m_status; }
        int CountFlags();

    private:
        std::shared_ptr<Renderer> m_renderer;
        BoardStatus m_status{BoardStatus::Playing};
        int m_boardWidth{0};
        int m_boardHeight{0};
        std::vector<std::shared_ptr<Block>> m_blocks;

    private:
        void PlaceMine(int x, int y);
        void CreateGroups();
        inline void MergeGroups(int a, int b);
        bool OnLeftClick(int i);
        bool OnRightClick(int i);
        inline int PosToIndex(int x, int y) { return y * m_boardWidth + x; }
    };
} // namespace Minesweeper
