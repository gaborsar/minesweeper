#pragma once

namespace Minesweeper
{
    struct Block
    {
        bool is_open{false};
        bool is_flagged{false};
        bool is_mine{false};
        bool is_exploded{false};
        int near_mine_count{0};
        int group{0};
    };
}
