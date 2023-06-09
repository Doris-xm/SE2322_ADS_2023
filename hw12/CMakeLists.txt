cmake_minimum_required(VERSION 3.21)
project(hw12)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw12 main.cpp Kruskal.h Parallel_kruskal.h parallel.h)
