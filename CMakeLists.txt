cmake_minimum_required(VERSION 3.30)
project(minesweeper)

find_package(SDL2 REQUIRED)
include_directories(minesweeper ${SDL2_INCLUDE_DIRS})

add_executable(minesweeper
    src/main.cpp
    src/board.h src/board.cpp 
)

target_link_libraries(minesweeper ${SDL2_LIBRARIES})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
