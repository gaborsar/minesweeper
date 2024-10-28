cmake_minimum_required(VERSION 3.30)
project(minesweeper)

find_package(SDL2 REQUIRED)
include_directories(minesweeper ${SDL2_INCLUDE_DIRS})

add_executable(minesweeper
    src/Board.cpp
    src/Board.h
    src/Entity.h
    src/Game.cpp
    src/Game.h
    src/Main.cpp
    src/Mouse.h
    src/Rect.h
    src/Renderer.cpp
    src/Renderer.h
    src/Sprite.h
)

target_link_libraries(minesweeper ${SDL2_LIBRARIES})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
