#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <random>
#include <SDL2/SDL.h>

namespace Minesweeper {

inline constexpr int block_size = 30;

enum class TileId {
    Closed,
    Open,
};

struct RenderingJob {
    TileId id;
    int x;
    int y;
};

class Board {
public:
    Board(SDL_Renderer* renderer, SDL_Texture* tiles,
        const int w, const int h, const int mines);
    void Render();
    void HandleClick(const int x, const int y);
private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_tiles;
    int m_w {};
    int m_h {};
    std::vector<bool> m_mines{};
    std::vector<int> m_counts{};
    std::vector<int> m_groups{};
    std::vector<RenderingJob> m_rendering_queue{};
    void PlaceMine(const int x, const int y);
    void CreateGroups();
    inline void MergeGroups(const int a, const int b);
    inline int PosToIndex(const int x, const int y);
};

}
