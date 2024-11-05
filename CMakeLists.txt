cmake_minimum_required(VERSION 3.30)
project(minesweeper)

find_path(SDL2_INCLUDE_DIR SDL2/SDL.h)
if (SDL2_INCLUDE_DIR)
    set(SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIR}/SDL2)
    message(STATUS "SDL2 include dir: ${SDL2_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "SDL2 include dir not found")
endif()

find_path(SDL2_IMAGE_INCLUDE_DIR SDL2/SDL_image.h)
if (SDL2_IMAGE_INCLUDE_DIR)
    set(SDL2_IMAGE_INCLUDE_DIR ${SDL2_IMAGE_INCLUDE_DIR}/SDL2)
    message(STATUS "SDL2_image include dir: ${SDL2_IMAGE_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "SDL2_image include dir not found")
endif()

find_path(SDL2_MIXER_INCLUDE_DIR SDL2/SDL_mixer.h)
if (SDL2_MIXER_INCLUDE_DIR)
    set(SDL2_MIXER_INCLUDE_DIR ${SDL2_MIXER_INCLUDE_DIR}/SDL2)
    message(STATUS "SDL2_mixer include dir: ${SDL2_MIXER_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "SDL2_mixer include dir not found")
endif()

find_library(SDL2_LIBRARY SDL2)
if (NOT SDL2_LIBRARY)
    message(FATAL_ERROR "SDL2 library not found")
else()
    message(STATUS "SDL2 library: ${SDL2_LIBRARY}")
endif()

find_library(SDL2_IMAGE_LIBRARY SDL2_image)
if (NOT SDL2_IMAGE_LIBRARY)
    message(FATAL_ERROR "SDL2_image library not found")
else()
    message(STATUS "SDL2_image library: ${SDL2_IMAGE_LIBRARY}")
endif()

find_library(SDL2_MIXER_LIBRARY SDL2_mixer)
if (NOT SDL2_MIXER_LIBRARY)
    message(FATAL_ERROR "SDL2_mixer library not found")
else()
    message(STATUS "SDL2_mixer library: ${SDL2_MIXER_LIBRARY}")
endif()

include_directories(minesweeper ${SDL2_INCLUDE_DIR})
include_directories(minesweeper ${SDL2_IMAGE_INCLUDE_DIR})
include_directories(minesweeper ${SDL2_MIXER_INCLUDE_DIR})

add_executable(minesweeper
    src/main.cpp
    src/core/Random.cpp
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

target_link_libraries(minesweeper ${SDL2_LIBRARY})
target_link_libraries(minesweeper ${SDL2_IMAGE_LIBRARY})
target_link_libraries(minesweeper ${SDL2_MIXER_LIBRARY})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/minesweeper.ico DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/tiles.bmp DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/clicking.mp3 DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/winning.mp3 DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/losing.mp3 DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
