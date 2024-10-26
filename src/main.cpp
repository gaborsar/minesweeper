#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include "Renderer.h"
#include "Game.h"

int main()
{
    const int board_width{10};
    const int board_height{10};
    const int number_of_mines{10};

    const auto window_size = Minesweeper::GetWindowSize(board_width, board_height);

    // INIT SDL

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto sdl_window{SDL_CreateWindow(
        "Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        window_size.w, window_size.h, SDL_WINDOW_SHOWN)};

    if (!sdl_window)
    {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto sdl_renderer{SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED)};

    if (!sdl_renderer)
    {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto sdl_img{SDL_LoadBMP("tiles.bmp")};

    if (!sdl_img)
    {
        std::cerr << "Error loading tiles: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto sdl_texture{SDL_CreateTextureFromSurface(sdl_renderer, sdl_img)};
    if (!sdl_texture)
    {
        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_FreeSurface(sdl_img);
    sdl_img = nullptr;

    // INIT GAME

    auto renderer{std::make_shared<Minesweeper::Renderer>(sdl_renderer, sdl_texture)};
    auto game{std::make_unique<Minesweeper::Game>(renderer, board_width, board_height, number_of_mines)};

    bool running{true};
    bool should_render{true};

    // MAIN LOOP

    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                should_render = game->OnClick(event.button.x, event.button.y);
                continue;
            }
        }

        if (should_render)
        {
            SDL_RenderClear(sdl_renderer);
            game->Render();
            SDL_RenderPresent(sdl_renderer);
            should_render = false;
        }

        SDL_Delay(25);
    }

    // CLEANUP SDL

    SDL_DestroyTexture(sdl_texture);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();

    return 0;
}
