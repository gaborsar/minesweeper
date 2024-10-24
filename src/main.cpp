#include <iostream>
#include <memory>
#include "board.h"

int main() {
    auto board { std::make_unique<Minesweeper::Board>(10, 10, 10) };

    std::cout << '\n';
    board->PrintMinesAndCounts();
    std::cout << '\n';

    std::cout << '\n';
    board->PrintGroups();
    std::cout << '\n';

    return 0;
}
