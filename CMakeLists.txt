cmake_minimum_required(VERSION 3.26)
project(game C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(game
        game_logic.c
        game_logic.h
        main.c)
