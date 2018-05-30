cmake_minimum_required(VERSION 3.10)
project(tetris_sdl)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

link_libraries("libSDL2.dylib" "libSDL2_ttf.dylib")

set(HINCLUDES include/control.h include/menu.h include/fonts.h include/game.h include/playground.h include/gameLogic.h include/gameDraw.h include/pause.h include/tetrisFont.h include/shape.h include/matrix.h)

add_executable(tetris_sdl main.cpp ${HINCLUDES})