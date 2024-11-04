#include "Application.h"
#include "Engine.h"
#include "Game.h"
#include <memory>

int main() {
  Minesweeper::GameConfig config{Minesweeper::BeginnerConfig};
  Engine::Size windowSize{Minesweeper::GetWindowSize(config)};

  // INIT

  auto application{std::make_unique<Minesweeper::Application>(
      "Minesweeper", windowSize.w, windowSize.h)};

  std::unique_ptr<Minesweeper::Game> game{
      std::make_unique<Minesweeper::Game>(config)};

  // MAIN LOOP

  bool running{true};
  bool shouldRender{true};

  SDL_Event event;
  Engine::UserCommand command;

  while (running) {
    int startTicks{Engine::Timer::GetTicks()};

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        switch (event.button.button) {
        case SDL_BUTTON_LEFT:
          command = {Engine::UserCommandType::MouseButtonDown,
                     Engine::MouseButton::Left, event.button.x, event.button.y};
          shouldRender = shouldRender || game->OnInput(command);
          break;
        case SDL_BUTTON_RIGHT:
          command = {Engine::UserCommandType::MouseButtonDown,
                     Engine::MouseButton::Right, event.button.x,
                     event.button.y};
          shouldRender = shouldRender || game->OnInput(command);
          break;
        }
        continue;
      }
    }

    shouldRender = shouldRender || game->OnUpdate(startTicks);

    if (shouldRender) {
      Engine::Renderer::Clear();
      game->OnRender();
      Engine::Renderer::Render();
      shouldRender = false;
    }

    int endTicks{Engine::Timer::GetTicks()};
    int elapsed = endTicks - startTicks;

    constexpr int targetDelay = 1000 / 60;
    if (elapsed < targetDelay) {
      Engine::Timer::Delay(targetDelay - elapsed);
    }
  }

  return 0;
}
