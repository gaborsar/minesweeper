#include "board.h"

namespace Minesweeper {

Board::Board(const int w, const int h, const int m) : m_w{ w }, m_h{ h } {
    const std::size_t l { static_cast<std::size_t>(w * h) };

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<int> gx{ 0, w - 1 };
    std::uniform_int_distribution<int> gy{ 0, h - 1 };

    m_mines = std::vector<bool>(l);
    m_counts = std::vector<int>(l);
    m_groups = std::vector<int>(l);

    for (std::size_t i { 0 }; i < m; ++i) {
        auto x { gx(mt) };
        auto y { gy(mt) };
        auto j { PosToIndex({ x, y }) };
        while (m_mines[j]) {
            x = gx(mt);
            y = gy(mt);
            j = PosToIndex({ x, y });
        }
        PlaceMine({ x, y });
    }

    CreateGroups();
}

void Board::PrintMinesAndCounts() {
    for (int y { 0 }; y < m_h; ++y) {
        for (int x { 0 }; x < m_w; ++x) {
            const auto i { PosToIndex({ x, y }) };
            std::cout << '\t';
            if (m_mines[i]) {
                std::cout << 'X';
            } else if (m_counts[i] == 0) {
                std::cout << '.';
            } else {
                std::cout << m_counts[i];
            }
        }
        std::cout << '\n';
    }
}

void Board::PrintGroups() {
    for (int y { 0 }; y < m_h; ++y) {
        for (int x { 0 }; x < m_w; ++x) {
            const auto i { PosToIndex({ x, y }) };
            std::cout << '\t';
            if (m_groups[i] == 0) {
                std::cout << '.';
            } else {
                std::cout << m_groups[i];
            }
        }
        std::cout << '\n';
    }
}

void Board::PlaceMine(const Pos& pos) {
    const auto i1 { PosToIndex(pos) };
    m_mines[i1] = true;
    for (int y { pos.y - 1 }; y <= pos.y + 1; ++y) {
        if (y < 0 || y > m_h - 1) {
            continue;
        }
        for (int x { pos.x - 1 }; x <= pos.x + 1; ++x) {
            if (x < 0 || x > m_w - 1) {
                continue;
            }
            const auto i2 { PosToIndex({ x, y }) };
            m_counts[i2]++;
        }
    }
}

void Board::CreateGroups() {
    for (std::size_t i { 0 }; i < m_w * m_h; ++i) {
        if (!m_mines[i] && m_counts[i] == 0) {
            m_groups[i] = i + 1;
        } else {
            m_groups[i] = 0;
        }
    }
    for (int y1 { 0 }; y1 < m_h; ++y1) {
        for (int x1 { 0 }; x1 < m_w; ++x1) {
            const auto i1 { PosToIndex({ x1, y1 }) };
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
                    const auto i2 { PosToIndex({ x2, y2 }) };
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
    for (std::size_t i { 0 }; i < m_w * m_h; ++i) {
        if (m_groups[i] != b) {
            continue;
        }
        m_groups[i] = a;
    }
}

inline std::size_t Board::PosToIndex(const Pos& pos) {
    return pos.y * m_w + pos.x;
}

}
