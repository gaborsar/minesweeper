cmake_minimum_required(VERSION 3.30)
project(minesweeper)

find_package(SDL2 REQUIRED)
include_directories(minesweeper ${SDL2_INCLUDE_DIRS})

add_executable(minesweeper
    src/Game.cpp
    src/Game.h
    src/Level.cpp
    src/Level.h
    src/main.cpp
    src/Rect.h
    src/Renderer.cpp
    src/Renderer.h
    src/RestartButton.cpp
    src/RestartButton.h
    src/Size.h
    src/Sprite.h
)

target_link_libraries(minesweeper ${SDL2_LIBRARIES})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
