cmake_minimum_required(VERSION 3.10)

project(lab2)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Werror -g -O3")

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(SRC ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/main.hpp  
  )

add_executable(lab2 ${SRC})
