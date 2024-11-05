#include "Renderer.h"
#include "Window.h"
#include <sstream>

namespace Game
{
  static Renderer *s_instance{nullptr};

  Renderer::Renderer()
  {
    Window &window{Window::Get()};
    SDL_Renderer *renderer{SDL_CreateRenderer(window.m_window, -1, SDL_RENDERER_ACCELERATED)};
    if (!renderer)
    {
      std::stringstream msg{};
      msg << "failed to create SDL renderer: " << SDL_GetError();
      throw std::runtime_error(msg.str());
    }
    m_renderer = renderer;
    s_instance = this;
  }

  Renderer::~Renderer()
  {
    SDL_DestroyRenderer(m_renderer);
  }

  Renderer &Renderer::Get()
  {
    return *s_instance;
  }

  void Renderer::Clear()
  {
    SDL_RenderClear(s_instance->m_renderer);
  }

  void Renderer::Render()
  {
    SDL_RenderPresent(s_instance->m_renderer);
  }
} // namespace Game
