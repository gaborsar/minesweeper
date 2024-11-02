cmake_minimum_required(VERSION 3.30)
project(minesweeper)

set(SDL2_INCLUDE_DIRS "/usr/local/Cellar/sdl2/2.30.8/include/SDL2;/usr/local/Cellar/sdl2_mixer/2.8.0/include/SDL2")
set(SDL2_LIBRARIES "/usr/local/Cellar/sdl2/2.30.8/lib/libSDL2.dylib;/usr/local/Cellar/sdl2_mixer/2.8.0/lib/libSDL2_mixer.dylib")

include_directories(minesweeper ${SDL2_INCLUDE_DIRS})

add_executable(minesweeper
    src/main.cpp
    src/Audio.cpp
    src/Board.cpp
    src/Game.cpp
    src/Renderer.cpp
    src/RestartButton.cpp
    src/Sound.cpp
    src/Window.cpp
)

target_link_libraries(minesweeper ${SDL2_LIBRARIES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/tiles.bmp DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/clicking.mp3 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/winning.mp3 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/losing.mp3 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
