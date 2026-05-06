cmake_minimum_required(VERSION 4.0)
project(8_soubory C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -fsanitize=address")

add_executable(8_soubory main.c)
