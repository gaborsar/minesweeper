#include "SpriteRenderer.h"

namespace Minesweeper {
static SpriteRenderer *s_instance{nullptr};

SpriteRenderer::SpriteRenderer()
    : m_atlas{Engine::Texture{"tiles.bmp", Engine::ImageType::BMP}} {
  s_instance = this;
}

void SpriteRenderer::RenderSprite(int x, int y, const Engine::Rect &sprite) {
  Engine::Renderer::RenderSprite(s_instance->m_atlas, x, y, sprite);
}
} // namespace Minesweeper
