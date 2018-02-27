cmake_minimum_required(VERSION 3.10)

project(lab2)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Werror -g -O3")

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(SRC ${PROJECT_SOURCE_DIR}/taylan-dogan-lab-2.cpp
        ${PROJECT_SOURCE_DIR}/taylan-dogan-lab-2.hpp  
  )

add_executable(lab2 ${SRC})
