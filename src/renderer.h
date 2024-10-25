#pragma once

#include <SDL2/SDL.h>
#include "sprite.h"

namespace Minesweeper
{
    class Renderer
    {
    public:
        Renderer(SDL_Renderer *renderer, SDL_Texture *texture);
        void RenderSprite(const int px, const int py, const Sprite sprite);

    private:
        SDL_Renderer *m_renderer;
        SDL_Texture *m_texture;
    };
}
