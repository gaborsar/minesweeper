#include "Audio.h"
#include "Core.h"
#include "Game.h"
#include "Input.h"
#include "Renderer.h"
#include "Sound.h"
#include "Window.h"
#include <SDL.h>
#include <iostream>
#include <memory>

int main() {
  Minesweeper::GameConfig config{Minesweeper::BeginnerConfig};
  Minesweeper::Size windowSize{Minesweeper::GetWindowSize(config)};

  auto audio{std::make_unique<Minesweeper::Audio>()};
  Minesweeper::Sounds::ClickingSound.Load();
  Minesweeper::Sounds::WinningSound.Load();
  Minesweeper::Sounds::LosingSound.Load();

  // INIT SDL

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *sdlWindow{SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED, windowSize.w,
                                         windowSize.h, SDL_WINDOW_SHOWN)};
  if (!sdlWindow) {
    std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Renderer *sdlRenderer{
      SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED)};
  if (!sdlRenderer) {
    std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Surface *sdlImg{SDL_LoadBMP("tiles.bmp")};
  if (!sdlImg) {
    std::cerr << "Error loading tiles: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Texture *sdlTexture{SDL_CreateTextureFromSurface(sdlRenderer, sdlImg)};
  if (!sdlTexture) {
    std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_FreeSurface(sdlImg);
  sdlImg = nullptr;

  // INIT GAME

  int startTime{static_cast<int>(SDL_GetTicks())};

  std::unique_ptr<Minesweeper::Window> window{
      std::make_unique<Minesweeper::Window>(sdlWindow, windowSize.w,
                                            windowSize.h)};
  std::unique_ptr<Minesweeper::Renderer> renderer{
      std::make_unique<Minesweeper::Renderer>(sdlRenderer, sdlTexture)};
  std::unique_ptr<Minesweeper::Game> game{
      std::make_unique<Minesweeper::Game>(config, startTime)};

  // MAIN LOOP

  bool running{true};
  bool shouldRender{true};

  SDL_Event event;
  Minesweeper::UserCommand command;

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
              Minesweeper::UserCommandType::MouseButtonDown,
              Minesweeper::MouseButton::Left,
              event.button.x,
              event.button.y,
          };
          shouldRender = shouldRender || game->OnInput(command);
          break;
        case SDL_BUTTON_RIGHT:
          command = {
              Minesweeper::UserCommandType::MouseButtonDown,
              Minesweeper::MouseButton::Right,
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
      SDL_RenderClear(sdlRenderer);
      game->OnRender();
      SDL_RenderPresent(sdlRenderer);
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

  SDL_DestroyTexture(sdlTexture);
  SDL_DestroyRenderer(sdlRenderer);
  SDL_DestroyWindow(sdlWindow);
  SDL_Quit();

  return 0;
}
