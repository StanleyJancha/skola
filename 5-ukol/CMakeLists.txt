cmake_minimum_required(VERSION 4.0)
project(5_ukol C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")

add_executable(5_ukol main.c)
