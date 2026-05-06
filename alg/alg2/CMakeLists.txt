cmake_minimum_required(VERSION 4.1)
project(alg2)

set(CMAKE_CXX_STANDARD 20)

add_executable(alg2 main.cpp
        Graph.cpp
        Graph.h
        BSTree.cpp
        BSTree.h
        johnsonTrotter.cpp
        johnsonTrotter.h
)
