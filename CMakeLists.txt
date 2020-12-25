cmake_minimum_required(VERSION 3.17)
project(json)

set(CMAKE_CXX_STANDARD 11)

add_executable(json test.cpp json.cpp json.h)