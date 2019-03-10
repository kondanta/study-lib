cmake_minimum_required(VERSION 3.9.6)
project(lab1)

set(CMAKE_CXX_STANDARD 17)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g")

set(SRC main.cpp)
add_executable(lab1 ${SRC})
