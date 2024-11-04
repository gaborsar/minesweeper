#include "Engine.h"
#include "Game.h"
#include "SoundManager.h"
#include "SpriteRenderer.h"
#include <memory>

int main() {
  // default difficulty and initial window size
  Minesweeper::GameConfig config{Minesweeper::BeginnerConfig};
  Engine::Size windowSize{Minesweeper::GetWindowSize(config)};

  // init shared static objects and resources
  auto sdl{std::make_unique<Engine::SDLSubsystem>()};
  auto window{std::make_unique<Engine::Window>("Minesweeper", windowSize.w,
                                               windowSize.h)};
  auto renderer{std::make_unique<Engine::Renderer>()};
  auto mixer{std::make_unique<Engine::Mixer>()};
  auto spriteRenderer{std::make_unique<Minesweeper::SpriteRenderer>()};
  auto soundManager{std::make_unique<Minesweeper::SoundManager>()};

  // init game session
  auto game{std::make_unique<Minesweeper::Game>(config, SDL_GetTicks())};

  bool running{true};
  bool shouldRender{true};
  SDL_Event event;

  while (running) {
    Uint32 startTicks{SDL_GetTicks()};

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;
      default:
        shouldRender = shouldRender || game->OnInput(event);
        break;
      }
    }

    shouldRender = shouldRender || game->OnUpdate(startTicks);

    if (shouldRender) {
      Engine::Renderer::Clear();
      game->OnRender();
      Engine::Renderer::Render();
      shouldRender = false;
    }

    Uint32 endTicks{SDL_GetTicks()};
    Uint32 elapsed{endTicks - startTicks};

    constexpr int targetDelay{1000 / 60};
    if (elapsed < targetDelay) {
      SDL_Delay(targetDelay - elapsed);
    }
  }

  return 0;
}
