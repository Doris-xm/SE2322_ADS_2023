cmake_minimum_required(VERSION 3.21)
project(bloom)

set(CMAKE_CXX_STANDARD 14)

add_executable(bloom main.cpp BloomFilter.h Bloomfilter.cpp)
