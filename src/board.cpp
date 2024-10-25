#include "board.h"

namespace Minesweeper
{

    Board::Board(std::shared_ptr<Renderer> renderer, const int board_width, const int board_height, const int number_of_mines)
        : m_renderer{renderer}, m_board_width{board_width}, m_board_height{board_height}
    {
        const int l{board_width * board_height};

        std::mt19937 mt{std::random_device{}()};
        std::uniform_int_distribution<int> gx{0, board_width - 1};
        std::uniform_int_distribution<int> gy{0, board_height - 1};

        m_blocks = std::vector<std::shared_ptr<Block>>();
        for (int i{0}; i < l; ++i)
        {
            m_blocks.push_back(std::make_shared<Block>());
        }

        for (int i{0}; i < number_of_mines; ++i)
        {
            int x{gx(mt)};
            int y{gy(mt)};
            int j{PosToIndex(x, y)};
            while (m_blocks[j]->is_mine)
            {
                x = gx(mt);
                y = gy(mt);
                j = PosToIndex(x, y);
            }
            PlaceMine(x, y);
        }

        CreateGroups();
    }

    void Board::HandleClick(const int px, const int py)
    {
        const int x { (px - 20) / 30 };
        if (x < 0 || x > m_board_width - 1)
        {
            return;
        }
        const int y { (py - 20 * 2 - 60) / 30 };
        if (y < 0 || y > m_board_height - 1)
        {
            return;
        }
        const int i { PosToIndex(x, y) };
        m_blocks[i]->is_open = true;
    }

    void Board::Render()
    {
        for (int y{0}; y < m_board_height; ++y)
        {
            for (int x{0}; x < m_board_width; ++x)
            {
                const int i{PosToIndex(x, y)};
                const int px{20 + x * 30};
                const int py{20 + 60 + 20 + y * 30};
                if (m_blocks[i]->is_open)
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
        m_blocks[i1]->is_mine = true;
        for (int y2{y - 1}; y2 <= y + 1; ++y2)
        {
            if (y2 < 0 || y2 > m_board_height - 1)
            {
                continue;
            }
            for (int x2{x - 1}; x2 <= x + 1; ++x2)
            {
                if (x2 < 0 || x > m_board_width - 1)
                {
                    continue;
                }
                const int i2{PosToIndex(x2, y2)};
                m_blocks[i2]->near_mine_count++;
            }
        }
    }

    void Board::CreateGroups()
    {
        for (int i{0}; i < m_board_width * m_board_height; ++i)
        {
            if (!m_blocks[i]->is_mine && m_blocks[i]->near_mine_count == 0)
            {
                m_blocks[i]->group = i + 1;
            }
            else
            {
                m_blocks[i]->group = 0;
            }
        }
        for (int y1{0}; y1 < m_board_height; ++y1)
        {
            for (int x1{0}; x1 < m_board_width; ++x1)
            {
                const int i1{PosToIndex(x1, y1)};
                if (m_blocks[i1]->is_mine || m_blocks[i1]->near_mine_count != 0)
                {
                    continue;
                }
                for (int y2{y1 - 1}; y2 <= y1 + 1; ++y2)
                {
                    if (y2 < 0 || y2 > m_board_height - 1)
                    {
                        continue;
                    }
                    for (int x2{x1 - 1}; x2 <= x1 + 1; ++x2)
                    {
                        if (x2 < 0 || x2 > m_board_width - 1)
                        {
                            continue;
                        }
                        const int i2{PosToIndex(x2, y2)};
                        if (m_blocks[i2]->is_mine || m_blocks[i2]->near_mine_count != 0)
                        {
                            continue;
                        }
                        const int g1 { m_blocks[i1]->group };
                        const int g2 { m_blocks[i2]->group };
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
        for (int i{0}; i < m_board_width * m_board_height; ++i)
        {
            if (m_blocks[i]->group != b)
            {
                continue;
            }
            m_blocks[i]->group = a;
        }
    }

    inline int Board::PosToIndex(const int x, const int y)
    {
        return y * m_board_width + x;
    }

}
