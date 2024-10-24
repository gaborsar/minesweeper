#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include "board.h"

int main() {
    const int board_width { 10 };
    const int board_height { 10 };
    const int number_of_mines { 10 };

    const int window_width { board_width * Minesweeper::block_size };
    const int window_height { board_height * Minesweeper::block_size };

    // INIT SDL

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto window { SDL_CreateWindow(
            "Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            window_width, window_height, SDL_WINDOW_SHOWN) };

    if (!window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto renderer { SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) };

    if (!renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto tiles_img { SDL_LoadBMP("tiles.bmp") };

    if (!tiles_img) {
        std::cerr << "Error loading tiles: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto tiles_texture { SDL_CreateTextureFromSurface(renderer, tiles_img) };
    if (!tiles_texture) {
        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_FreeSurface(tiles_img);
    tiles_img = nullptr;

    auto board { std::make_unique<Minesweeper::Board>(
            renderer, tiles_texture,
            board_width, board_height, number_of_mines) };


    auto running { true };
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    board->HandleClick(event.button.x, event.button.y);
                    continue;
            }
        }
        board->Render();
        SDL_Delay(10);
    }

    SDL_DestroyTexture(tiles_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
