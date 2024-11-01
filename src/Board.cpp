#include "Board.h"
#include "Game.h"
#include "Renderer.h"
#include "Sprites.h"
#include <algorithm>
#include <cassert>
#include <random>

namespace Minesweeper
{
    Board::Board(int x, int y, int boardWidth, int boardHeight, int numberOfMines)
        : m_x{x}, m_y{y}, m_boardWidth{boardWidth}, m_boardHeight{boardHeight}, m_numberOfMines{numberOfMines}
    {
        m_mt = static_cast<std::mt19937>(std::random_device{}());
        Init();
    }

    void Board::Init()
    {
        int l{m_boardWidth * m_boardHeight};

        m_blocks = std::vector<std::shared_ptr<Block>>(l);
        for (int i{0}; i < l; ++i)
        {
            m_blocks[i] = std::make_shared<Block>();
        }

        std::uniform_int_distribution<int> randX{0, m_boardWidth - 1};
        std::uniform_int_distribution<int> randY{0, m_boardHeight - 1};

        for (int i{0}; i < m_numberOfMines; ++i)
        {
            int x{randX(m_mt)};
            int y{randY(m_mt)};
            int j{PosToIndex(x, y)};
            while (m_blocks[j]->IsMine)
            {
                x = randX(m_mt);
                y = randY(m_mt);
                j = PosToIndex(x, y);
            }
            PlaceMine(x, y);
        }

        CreateGroups();
    }

    bool Board::OnInput(UserCommand &cmd)
    {
        if (cmd.type != UserCommandType::MouseButtonDown)
        {
            return false;
        }
        if (cmd.mouseX < m_x || cmd.mouseX > m_x + m_boardWidth * 30)
        {
            return false;
        }
        if (cmd.mouseY < m_y || cmd.mouseY > m_y + m_boardHeight * 30)
        {
            return false;
        }

        int x{cmd.mouseX - m_x};
        int y{cmd.mouseY - m_y};

        if (cmd.mouseButton == MouseButton::Left)
        {
            return OnLeftClick(x, y);
        }
        if (cmd.mouseButton == MouseButton::Right)
        {
            return OnRightClick(x, y);
        }

        return false;
    }

    void Board::OnRender()
    {
        Renderer &renderer{Renderer::Get()};
        for (int y{0}; y < m_boardHeight; ++y)
        {
            for (int x{0}; x < m_boardWidth; ++x)
            {
                int i{PosToIndex(x, y)};
                int px{20 + x * 30};
                int py{20 + 60 + 20 + y * 30};
                auto &block{m_blocks[i]};
                if (block->IsOpen)
                {
                    if (block->IsExploded)
                    {
                        renderer.RenderSprite(px, py, Sprites::BlockMineExploded);
                        continue;
                    }
                    if (block->IsMine)
                    {
                        renderer.RenderSprite(px, py, Sprites::BlockMine);
                        continue;
                    }
                    renderer.RenderSprite(px, py, Sprites::BlockDigits[block->NearMineCount]);
                    continue;
                }
                if (block->IsFlagged)
                {
                    renderer.RenderSprite(px, py, Sprites::BlockFlagged);
                    continue;
                }
                renderer.RenderSprite(px, py, Sprites::BlockClosed);
            }
        }
    }

    int Board::GetNumberOfFlags()
    {
        return std::count_if(m_blocks.begin(), m_blocks.end(), [](const auto &block)
                             { return block->IsFlagged; });
    }

    void Board::PlaceMine(int x, int y)
    {
        int i1{PosToIndex(x, y)};
        m_blocks[i1]->IsMine = true;
        for (int y2{y - 1}; y2 <= y + 1; ++y2)
        {
            if (y2 < 0 || y2 > m_boardHeight - 1)
            {
                continue;
            }
            for (int x2{x - 1}; x2 <= x + 1; ++x2)
            {
                if (x2 < 0 || x2 > m_boardWidth - 1)
                {
                    continue;
                }
                int i2{PosToIndex(x2, y2)};
                ++m_blocks[i2]->NearMineCount;
            }
        }
    }

    void Board::CreateGroups()
    {
        for (int i{0}; i < m_boardWidth * m_boardHeight; ++i)
        {
            if (!m_blocks[i]->IsMine && m_blocks[i]->NearMineCount == 0)
            {
                m_blocks[i]->Groups.first = i + 1;
            }
        }

        for (int y1{0}; y1 < m_boardHeight; ++y1)
        {
            for (int x1{0}; x1 < m_boardWidth; ++x1)
            {
                int i1{PosToIndex(x1, y1)};
                auto &block1{m_blocks[i1]};
                if (block1->IsMine || block1->NearMineCount != 0)
                {
                    continue;
                }
                int g1{block1->Groups.first};
                for (int y2{y1 - 1}; y2 <= y1 + 1; ++y2)
                {
                    if (y2 < 0 || y2 > m_boardHeight - 1)
                    {
                        continue;
                    }
                    for (int x2{x1 - 1}; x2 <= x1 + 1; ++x2)
                    {
                        if (x2 < 0 || x2 > m_boardWidth - 1)
                        {
                            continue;
                        }
                        int i2{PosToIndex(x2, y2)};
                        auto &block2{m_blocks[i2]};
                        if (block2->IsMine || block2->NearMineCount != 0)
                        {
                            continue;
                        }
                        int g2{block2->Groups.first};
                        if (g1 == g2)
                        {
                            continue;
                        }
                        if (g1 < g2)
                        {
                            MergeGroups(g1, g2);
                        }
                        else
                        {
                            MergeGroups(g2, g1);
                        }
                    }
                }
            }
        }

        for (int y1{0}; y1 < m_boardHeight; ++y1)
        {
            for (int x1{0}; x1 < m_boardWidth; ++x1)
            {
                int i1{PosToIndex(x1, y1)};
                auto &block1{m_blocks[i1]};
                if (block1->IsMine || block1->NearMineCount != 0)
                {
                    continue;
                }
                int g{block1->Groups.first};
                for (int y2{y1 - 1}; y2 <= y1 + 1; ++y2)
                {
                    if (y2 < 0 || y2 > m_boardHeight - 1)
                    {
                        continue;
                    }
                    for (int x2{x1 - 1}; x2 <= x1 + 1; ++x2)
                    {
                        if (x2 < 0 || x2 > m_boardWidth - 1)
                        {
                            continue;
                        }
                        int i2{PosToIndex(x2, y2)};
                        auto &block2{m_blocks[i2]};
                        if (block2->IsMine || block2->NearMineCount == 0)
                        {
                            continue;
                        }
                        if (block2->Groups.first == g || block2->Groups.second == g)
                        {
                            continue;
                        }
                        assert(block2->Groups.first == 0 || block2->Groups.second == 0);
                        if (block2->Groups.first == 0)
                        {
                            block2->Groups.first = g;
                        }
                        else
                        {
                            block2->Groups.second = g;
                        }
                    }
                }
            }
        }
    }

    inline void Board::MergeGroups(int g1, int g2)
    {
        for (int i{0}; i < m_boardWidth * m_boardHeight; ++i)
        {
            auto &block{m_blocks[i]};
            if (block->Groups.first != g2)
            {
                continue;
            }
            block->Groups.first = g1;
        }
    }

    bool Board::OnLeftClick(int px, int py)
    {
        int x{px / 30};
        if (x < 0 || x > m_boardWidth - 1)
        {
            return false;
        }
        int y{py / 30};
        if (y < 0 || y > m_boardHeight - 1)
        {
            return false;
        }
        int i{PosToIndex(x, y)};
        auto &block{m_blocks[i]};
        if (block->IsOpen || block->IsFlagged)
        {
            return false;
        }
        block->IsOpen = true;
        if (block->IsMine)
        {
            for (auto &block : m_blocks)
            {
                block->IsOpen = true;
                block->IsFlagged = false;
            }
            block->IsExploded = true;
            Game &game{Game::Get()};
            game.Lose();
        }
        else
        {
            if (block->NearMineCount == 0)
            {
                int g{block->Groups.first};
                for (auto &block : m_blocks)
                {
                    if (!block->IsFlagged && (block->Groups.first == g || block->Groups.second == g))
                    {
                        block->IsOpen = true;
                    }
                }
            }
            if (std::all_of(m_blocks.begin(), m_blocks.end(), [](const auto &block)
                            { return block->IsMine ? !block->IsOpen : block->IsOpen; }))
            {
                Game &game{Game::Get()};
                game.Win();
            }
        }
        return true;
    }

    bool Board::OnRightClick(int px, int py)
    {
        int x{px / 30};
        if (x < 0 || x > m_boardWidth - 1)
        {
            return false;
        }
        int y{py / 30};
        if (y < 0 || y > m_boardHeight - 1)
        {
            return false;
        }
        int i{PosToIndex(x, y)};
        auto &block{m_blocks[i]};
        if (block->IsOpen)
        {
            return false;
        }
        block->IsFlagged = !block->IsFlagged;
        return true;
    }
} // namespace Minesweeper
