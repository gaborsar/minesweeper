#include "Board.h"

namespace Minesweeper
{
    Board::Board(std::shared_ptr<Renderer> renderer, const int boardWidth, const int boardHeight, const int numberOfMines)
        : m_renderer{renderer}, m_boardWidth{boardWidth}, m_boardHeight{boardHeight}
    {
        const int l{boardWidth * boardHeight};

        std::mt19937 mt{std::random_device{}()};
        std::uniform_int_distribution<int> randX{0, boardWidth - 1};
        std::uniform_int_distribution<int> randY{0, boardHeight - 1};

        m_blocks = std::vector<std::shared_ptr<Block>>();
        for (int i{0}; i < l; ++i)
        {
            m_blocks.push_back(std::make_shared<Block>());
        }

        for (int i{0}; i < numberOfMines; ++i)
        {
            int x{randX(mt)};
            int y{randY(mt)};
            int j{PosToIndex(x, y)};
            while (m_blocks[j]->IsMine)
            {
                x = randX(mt);
                y = randY(mt);
                j = PosToIndex(x, y);
            }
            PlaceMine(x, y);
        }

        CreateGroups();
    }

    const Rect Board::GetBox()
    {
        const int x = 20;
        const int y = 20 + 60 + 20;
        const int w = m_boardWidth * 30;
        const int h = m_boardHeight * 30;
        return { x, y, w, h };
    }

    const bool Board::OnClick(const int px, const int py)
    {
        const int x { px / 30 };
        if (x < 0 || x > m_boardWidth - 1)
        {
            return false;
        }
        const int y { py / 30 };
        if (y < 0 || y > m_boardHeight - 1)
        {
            return false;
        }
        const int i { PosToIndex(x, y) };
        if (m_blocks[i]->IsOpen)
        {
            return false;
        }
        m_blocks[i]->IsOpen = true;
        return true;
    }

    void Board::Render()
    {
        for (int y{0}; y < m_boardHeight; ++y)
        {
            for (int x{0}; x < m_boardWidth; ++x)
            {
                const int i{PosToIndex(x, y)};
                const int px{20 + x * 30};
                const int py{20 + 60 + 20 + y * 30};
                if (m_blocks[i]->IsOpen)
                {
                    m_renderer->RenderSprite(px, py, Sprites::BlockOpen);
                }
                else
                {
                    m_renderer->RenderSprite(px, py, Sprites::BlockClosed);
                }
            }
        }
    }

    void Board::PlaceMine(const int x, const int y)
    {
        const int i1{PosToIndex(x, y)};
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
                const int i2{PosToIndex(x2, y2)};
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
                m_blocks[i]->Group = i + 1;
            }
            else
            {
                m_blocks[i]->Group = 0;
            }
        }
        for (int y1{0}; y1 < m_boardHeight; ++y1)
        {
            for (int x1{0}; x1 < m_boardWidth; ++x1)
            {
                const int i1{PosToIndex(x1, y1)};
                if (m_blocks[i1]->IsMine || m_blocks[i1]->NearMineCount != 0)
                {
                    continue;
                }
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
                        const int i2{PosToIndex(x2, y2)};
                        if (m_blocks[i2]->IsMine || m_blocks[i2]->NearMineCount != 0)
                        {
                            continue;
                        }
                        const int g1 { m_blocks[i1]->Group };
                        const int g2 { m_blocks[i2]->Group };
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
    }

    inline void Board::MergeGroups(const int a, const int b)
    {
        for (int i{0}; i < m_boardWidth * m_boardHeight; ++i)
        {
            if (m_blocks[i]->Group != b)
            {
                continue;
            }
            m_blocks[i]->Group = a;
        }
    }

    inline int Board::PosToIndex(const int x, const int y)
    {
        return y * m_boardWidth + x;
    }
}
