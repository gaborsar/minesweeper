#include "Game.h"
#include "Input.h"
#include "Renderer.h"
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>

int main()
{
    int boardWidth{10};
    int boardHeight{10};
    int numberOfMines{10};

    auto windowSize{Minesweeper::GetWindowSize(boardWidth, boardHeight)};

    // INIT SDL

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto sdlWindow{SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.w, windowSize.h, SDL_WINDOW_SHOWN)};
    if (!sdlWindow)
    {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto sdlRenderer{SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED)};
    if (!sdlRenderer)
    {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto sdlImg{SDL_LoadBMP("tiles.bmp")};
    if (!sdlImg)
    {
        std::cerr << "Error loading tiles: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto sdlTexture{SDL_CreateTextureFromSurface(sdlRenderer, sdlImg)};
    if (!sdlTexture)
    {
        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_FreeSurface(sdlImg);
    sdlImg = nullptr;

    // INIT GAME

    int startTime{static_cast<int>(SDL_GetTicks())};

    auto renderer{std::make_shared<Minesweeper::Renderer>(sdlRenderer, sdlTexture)};
    auto game{std::make_unique<Minesweeper::Game>(boardWidth, boardHeight, numberOfMines, startTime)};

    // MAIN LOOP

    bool running{true};
    bool shouldRender{true};
    int frameCount{0};

    SDL_Event event;
    Minesweeper::UserCommand command;

    while (running)
    {
        Uint32 startTicks{SDL_GetTicks()};

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    command = {Minesweeper::UserCommandType::MouseButtonDown, Minesweeper::MouseButton::Left, event.button.x, event.button.y};
                    shouldRender = shouldRender || game->OnInput(command);
                    break;
                case SDL_BUTTON_RIGHT:
                    command = {Minesweeper::UserCommandType::MouseButtonDown, Minesweeper::MouseButton::Right, event.button.x, event.button.y};
                    shouldRender = shouldRender || game->OnInput(command);
                    break;
                }
                continue;
            }
        }

        shouldRender = shouldRender || game->OnUpdate(startTicks);

        if (shouldRender)
        {
            SDL_RenderClear(sdlRenderer);
            game->OnRender();
            SDL_RenderPresent(sdlRenderer);
            shouldRender = false;
        }

        SDL_Delay(15);

        Uint32 endTicks{SDL_GetTicks()};
        float fps{1.0f / ((endTicks - startTicks) / 1000.0f)};

        if (++frameCount == 60)
        {
            frameCount = 0;
            std::cout << "fps: " << fps << std::endl;
        }
    }

    // CLEANUP SDL

    SDL_DestroyTexture(sdlTexture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();

    return 0;
}
