cmake_minimum_required(VERSION 3.15)
project(CUB3D C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(getnextline)

add_executable(CUB3D
        getnextline/get_next_line.c
        getnextline/get_next_line.h
        getnextline/get_next_line_utils.c
        cub3.c
        cub3.h)
