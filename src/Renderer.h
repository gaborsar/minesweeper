#pragma once

#include "Core.h"
#include <SDL2/SDL.h>

namespace Minesweeper
{
    class Renderer
    {
    public:
        Renderer(SDL_Renderer *renderer, SDL_Texture *texture);
        static Renderer &Get();
        void RenderSprite(int px, int py, const Rect &sprite);

    private:
        SDL_Renderer *m_renderer;
        SDL_Texture *m_texture;
    };
} // namespace Minesweeper
