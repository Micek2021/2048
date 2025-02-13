cmake_minimum_required(VERSION 3.29)
project(2048_v2)

set(CMAKE_CXX_STANDARD 20)

add_executable(2048_v2 main.cpp
        GameSquare.cpp
        GameSquare.h
        Constants.h
        GameBoard.cpp
        GameBoard.h)
