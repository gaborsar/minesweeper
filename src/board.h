#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "pos.h"

namespace Minesweeper {

class Board {
public:
    Board(const int w, const int h, const int m);
    void PrintMinesAndCounts();
    void PrintGroups();
private:
    int m_w {};
    int m_h {};
    std::vector<bool> m_mines{};
    std::vector<int> m_counts{};
    std::vector<int> m_groups{};
    void PlaceMine(const Pos& pos);
    void CreateGroups();
    inline void MergeGroups(const int a, const int b);
    inline std::size_t PosToIndex(const Pos& pos);
};

}
