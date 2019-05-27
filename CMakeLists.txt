cmake_minimum_required(VERSION 3.10)
project(Checkers)

set(CMAKE_CXX_STANDARD 11)

add_executable(Checkers main.cpp BoardManager.cpp BoardManager.hpp Piece.cpp Piece.hpp GameAgent.cpp GameAgent.hpp MovementManager.cpp MovementManager.hpp AI.cpp AI.h)