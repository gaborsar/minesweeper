#include "board.h"

namespace Minesweeper {

Board::Board(SDL_Renderer* renderer, SDL_Texture* tiles,
        const int w, const int h, const int mines)
        : m_renderer{ renderer }, m_tiles{ tiles }, m_w{ w }, m_h{ h } {
    const auto l { w * h };

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<int> gx{ 0, w - 1 };
    std::uniform_int_distribution<int> gy{ 0, h - 1 };

    m_mines = std::vector<bool>(l);
    m_counts = std::vector<int>(l);
    m_groups = std::vector<int>(l);

    for (int i { 0 }; i < mines; ++i) {
        auto x { gx(mt) };
        auto y { gy(mt) };
        auto j { PosToIndex(x, y) };
        while (m_mines[j]) {
            x = gx(mt);
            y = gy(mt);
            j = PosToIndex(x, y);
        }
        PlaceMine(x, y);
    }

    CreateGroups();

    for (int y { 0}; y < m_h; ++y) {
        for (int x { 0 }; x < m_w; ++x) {
            m_rendering_queue.push_back({ TileId::Closed, x, y });
        }
    }
}

void Board::Render() {
    SDL_Rect src_rect;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = block_size;
    src_rect.h = block_size;

    SDL_Rect dst_rect;
    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.w = block_size;
    dst_rect.h = block_size;

    for (const auto& job : m_rendering_queue) {
        dst_rect.x = job.x * block_size;
        dst_rect.y = job.y * block_size;
        switch (job.id) {
            case TileId::Closed:
                src_rect.x = 0;
                break;
            case TileId::Open:
                src_rect.x = block_size;
                break;
        }
        SDL_RenderCopy(m_renderer, m_tiles, &src_rect, &dst_rect);
    }
    SDL_RenderPresent(m_renderer);
}

void Board::HandleClick(const int x, const int y) {
    const int xi = x / block_size;
    if (xi < 0 || xi > m_w - 1) {
        return;
    }
    const int yi = y / block_size;
    if (yi < 0 || yi > m_h - 1) {
        return;
    }
    m_rendering_queue.push_back({ TileId::Open, xi, yi });
}

void Board::PlaceMine(const int x, const int y) {
    const auto i1 { PosToIndex(x, y) };
    m_mines[i1] = true;
    for (int y2 { y - 1 }; y2 <= y + 1; ++y2) {
        if (y2 < 0 || y2 > m_h - 1) {
            continue;
        }
        for (int x2 { x - 1 }; x2 <= x + 1; ++x2) {
            if (x2 < 0 || x > m_w - 1) {
                continue;
            }
            const auto i2 { PosToIndex(x2, y2) };
            m_counts[i2]++;
        }
    }
}

void Board::CreateGroups() {
    for (int i { 0 }; i < m_w * m_h; ++i) {
        if (!m_mines[i] && m_counts[i] == 0) {
            m_groups[i] = i + 1;
        } else {
            m_groups[i] = 0;
        }
    }
    for (int y1 { 0 }; y1 < m_h; ++y1) {
        for (int x1 { 0 }; x1 < m_w; ++x1) {
            const auto i1 { PosToIndex(x1, y1) };
            if (m_mines[i1] || m_counts[i1] != 0) {
                continue;
            }
            for (int y2 { y1 - 1 }; y2 <= y1 + 1; ++y2) {
                if (y2 < 0 || y2 > m_h - 1) {
                    continue;
                }
                for (int x2 { x1 - 1 }; x2 <= x1 + 1; ++x2) {
                    if (x2 < 0 || x2 > m_w - 1) {
                        continue;
                    }
                    const auto i2 { PosToIndex(x2, y2) };
                    if (m_mines[i2] || m_counts[i2] != 0) {
                        continue;
                    }
                    const auto g1 = m_groups[i1];
                    const auto g2 = m_groups[i2];
                    if (g1 == g2) {
                        continue;
                    }
                    if (g1 < g2) {
                        MergeGroups(g1, g2);
                    } else {
                        MergeGroups(g2, g1);
                    }
                }
            }
        }
    }
}

inline void Board::MergeGroups(const int a, const int b) {
    for (int i { 0 }; i < m_w * m_h; ++i) {
        if (m_groups[i] != b) {
            continue;
        }
        m_groups[i] = a;
    }
}

inline int Board::PosToIndex(const int x, const int y) {
    return y * m_w + x;
}

}
