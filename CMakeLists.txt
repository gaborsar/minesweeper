cmake_minimum_required(VERSION 3.30)
project(minesweeper)

add_executable(minesweeper
    src/main.cpp
    src/board.cpp
    src/board.h
    src/pos.h
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
