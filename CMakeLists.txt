cmake_minimum_required(VERSION 3.30)
project(minesweeper)

set(SDL2_INCLUDE_DIRS "/usr/local/Cellar/sdl2/2.30.8/include/SDL2;/usr/local/Cellar/sdl2_mixer/2.8.0/include/SDL2")
set(SDL2_LIBRARIES "/usr/local/Cellar/sdl2/2.30.8/lib/libSDL2.dylib;/usr/local/Cellar/sdl2_mixer/2.8.0/lib/libSDL2_mixer.dylib")

include_directories(minesweeper ${SDL2_INCLUDE_DIRS})

add_executable(minesweeper
    src/main.cpp
    src/core/SDLPtr.cpp
    src/game/Board.cpp
    src/game/GameSession.cpp
    src/game/RestartButton.cpp
    src/graphics/Renderer.cpp
    src/graphics/SpriteRenderer.cpp
    src/graphics/Surface.cpp
    src/graphics/Texture.cpp
    src/graphics/Window.cpp
    src/Sound/Mixer.cpp
    src/Sound/Sound.cpp
    src/Sound/SoundManager.cpp
)

target_link_libraries(minesweeper ${SDL2_LIBRARIES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/tiles.bmp DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/clicking.mp3 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/winning.mp3 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/losing.mp3 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
