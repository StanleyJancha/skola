cmake_minimum_required(VERSION 4.0)
project(7_struktury C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -fsanitize=address -LSAN_OPTIONS=verbosity=1:log_threads=1")

add_executable(7_struktury main.c)
