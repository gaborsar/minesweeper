#include "Application.h"
#include "Engine.h"
#include "Game.h"
#include <SDL.h>
#include <iostream>
#include <memory>

int main() {
  Minesweeper::GameConfig config{Minesweeper::BeginnerConfig};
  Engine::Size windowSize{Minesweeper::GetWindowSize(config)};

  // INIT SDL

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

  // INIT GAME

  auto application{std::make_unique<Minesweeper::Application>(
      "Minesweeper", windowSize.w, windowSize.h)};

  int startTime{static_cast<int>(SDL_GetTicks())};

  std::unique_ptr<Minesweeper::Game> game{
      std::make_unique<Minesweeper::Game>(config, startTime)};

  // MAIN LOOP

  bool running{true};
  bool shouldRender{true};

  SDL_Event event;
  Engine::UserCommand command;

  while (running) {
    Uint32 startTicks{SDL_GetTicks()};

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        switch (event.button.button) {
        case SDL_BUTTON_LEFT:
          command = {
              Engine::UserCommandType::MouseButtonDown,
              Engine::MouseButton::Left,
              event.button.x,
              event.button.y,
          };
          shouldRender = shouldRender || game->OnInput(command);
          break;
        case SDL_BUTTON_RIGHT:
          command = {
              Engine::UserCommandType::MouseButtonDown,
              Engine::MouseButton::Right,
              event.button.x,
              event.button.y,
          };
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

    Uint32 endTicks{SDL_GetTicks()};
    int elapsed = endTicks - startTicks;

    constexpr int targetDelay = 1000 / 60;
    if (elapsed < targetDelay) {
      SDL_Delay(targetDelay - elapsed);
    }
  }

  // CLEANUP SDL

  SDL_Quit();

  return 0;
}
