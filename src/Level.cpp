#include "Level.h"
#include <algorithm>
#include <cassert>
#include <random>

namespace Minesweeper
{
    Level::Level(std::shared_ptr<Renderer> renderer, int levelWidth, int levelHeight, int numberOfMines)
        : m_renderer{renderer}, m_levelWidth{levelWidth}, m_levelHeight{levelHeight}, m_numberOfMines{numberOfMines}
    {
        m_mt = static_cast<std::mt19937>(std::random_device{}());
        OnRestart();
    }

    void Level::OnRestart()
    {
        int l{m_levelWidth * m_levelHeight};

        std::uniform_int_distribution<int> randX{0, m_levelWidth - 1};
        std::uniform_int_distribution<int> randY{0, m_levelHeight - 1};

        m_blocks = std::vector<std::shared_ptr<Block>>(l);
        for (int i{0}; i < l; ++i)
        {
            m_blocks[i] = std::make_shared<Block>();
        }

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

    void Level::PlaceMine(int x, int y)
    {
        int i1{PosToIndex(x, y)};
        m_blocks[i1]->IsMine = true;
        for (int y2{y - 1}; y2 <= y + 1; ++y2)
        {
            if (y2 < 0 || y2 > m_levelHeight - 1)
            {
                continue;
            }
            for (int x2{x - 1}; x2 <= x + 1; ++x2)
            {
                if (x2 < 0 || x2 > m_levelWidth - 1)
                {
                    continue;
                }
                int i2{PosToIndex(x2, y2)};
                ++m_blocks[i2]->NearMineCount;
            }
        }
    }

    void Level::CreateGroups()
    {
        for (int i{0}; i < m_levelWidth * m_levelHeight; ++i)
        {
            if (!m_blocks[i]->IsMine && m_blocks[i]->NearMineCount == 0)
            {
                m_blocks[i]->Groups.first = i + 1;
            }
        }

        for (int y1{0}; y1 < m_levelHeight; ++y1)
        {
            for (int x1{0}; x1 < m_levelWidth; ++x1)
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
                    if (y2 < 0 || y2 > m_levelHeight - 1)
                    {
                        continue;
                    }
                    for (int x2{x1 - 1}; x2 <= x1 + 1; ++x2)
                    {
                        if (x2 < 0 || x2 > m_levelWidth - 1)
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

        for (int y1{0}; y1 < m_levelHeight; ++y1)
        {
            for (int x1{0}; x1 < m_levelWidth; ++x1)
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
                    if (y2 < 0 || y2 > m_levelHeight - 1)
                    {
                        continue;
                    }
                    for (int x2{x1 - 1}; x2 <= x1 + 1; ++x2)
                    {
                        if (x2 < 0 || x2 > m_levelWidth - 1)
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

    inline void Level::MergeGroups(int g1, int g2)
    {
        for (int i{0}; i < m_levelWidth * m_levelHeight; ++i)
        {
            auto &block{m_blocks[i]};
            if (block->Groups.first != g2)
            {
                continue;
            }
            block->Groups.first = g1;
        }
    }

    Rect Level::GetBoundingRect()
    {
        int x{20};
        int y{20 + 60 + 20};
        int w{m_levelWidth * 30};
        int h{m_levelHeight * 30};
        return {x, y, w, h};
    }

    bool Level::OnLeftClick(int px, int py)
    {
        int x{px / 30};
        if (x < 0 || x > m_levelWidth - 1)
        {
            return false;
        }
        int y{py / 30};
        if (y < 0 || y > m_levelHeight - 1)
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
        }
        return true;
    }

    bool Level::OnRightClick(int px, int py)
    {
        int x{px / 30};
        if (x < 0 || x > m_levelWidth - 1)
        {
            return false;
        }
        int y{py / 30};
        if (y < 0 || y > m_levelHeight - 1)
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

    void Level::OnRender()
    {
        for (int y{0}; y < m_levelHeight; ++y)
        {
            for (int x{0}; x < m_levelWidth; ++x)
            {
                int i{PosToIndex(x, y)};
                int px{20 + x * 30};
                int py{20 + 60 + 20 + y * 30};
                auto &block{m_blocks[i]};
                if (block->IsOpen)
                {
                    if (block->IsExploded)
                    {
                        m_renderer->RenderSprite(px, py, Sprites::BlockMineExploded);
                        continue;
                    }
                    if (block->IsMine)
                    {
                        m_renderer->RenderSprite(px, py, Sprites::BlockMine);
                        continue;
                    }
                    m_renderer->RenderSprite(px, py, Sprites::BlockDigits[block->NearMineCount]);
                    continue;
                }
                if (block->IsFlagged)
                {
                    m_renderer->RenderSprite(px, py, Sprites::BlockFlagged);
                    continue;
                }
                m_renderer->RenderSprite(px, py, Sprites::BlockClosed);
            }
        }
    }

    int Level::CountFlags()
    {
        return std::count_if(m_blocks.begin(), m_blocks.end(), [](const auto &block)
                             { return block->IsFlagged; });
    }

    bool Level::HasWon()
    {
        return std::all_of(m_blocks.begin(), m_blocks.end(), [](const auto &block)
                           { return block->IsMine ? !block->IsOpen : block->IsOpen; });
    }

    bool Level::HasLost()
    {
        return std::any_of(m_blocks.begin(), m_blocks.end(), [](const auto &block)
                           { return block->IsExploded; });
    }
} // namespace Minesweeper
