cmake_minimum_required(VERSION 3.21)
project(hw2)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw2 main.cpp SkipList.h SkipList.cpp SkipListTest.cpp SkipListTest.h kvstore_api.h)
