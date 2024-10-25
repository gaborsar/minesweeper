#include "renderer.h"

namespace Minesweeper
{
    Renderer::Renderer(SDL_Renderer *renderer, SDL_Texture *texture)
        : m_renderer{renderer}, m_texture{texture} {}

    void Renderer::RenderSprite(const int px, const int py, const Sprite sprite)
    {
        SDL_Rect src_rect;
        src_rect.x = sprite.x;
        src_rect.y = sprite.y;
        src_rect.w = sprite.w;
        src_rect.h = sprite.h;

        SDL_Rect dst_rect;
        dst_rect.x = px;
        dst_rect.y = py;
        dst_rect.w = sprite.w;
        dst_rect.h = sprite.h;

        SDL_RenderCopy(m_renderer, m_texture, &src_rect, &dst_rect);
    }
}
