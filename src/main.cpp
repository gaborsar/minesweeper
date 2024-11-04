#include "./core/Random.h"
#include "./core/SDLPtr.h"
#include "./game/GameSession.h"
#include "./graphics/Renderer.h"
#include "./graphics/SpriteRenderer.h"
#include "./graphics/Window.h"
#include "./sound/Mixer.h"
#include "./sound/SoundManager.h"
#include <memory>

int main() {
  // default difficulty and initial window size
  Game::GameConfig config{Game::BeginnerConfig};
  Game::Size windowSize{Game::GetWindowSize(config)};

  // init shared static objects and resources
  auto random{std::make_unique<Game::Random>()};
  auto sdl{std::make_unique<Game::SDLPtr>()};
  auto window{
      std::make_unique<Game::Window>("Game", windowSize.w, windowSize.h)};
  auto renderer{std::make_unique<Game::Renderer>()};
  auto mixer{std::make_unique<Game::Mixer>()};
  auto spriteRenderer{std::make_unique<Game::SpriteRenderer>()};
  auto soundManager{std::make_unique<Game::SoundManager>()};

  // init game session
  auto game{std::make_unique<Game::GameSession>(config, SDL_GetTicks())};

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
      Game::Renderer::Clear();
      game->OnRender();
      Game::Renderer::Render();
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
