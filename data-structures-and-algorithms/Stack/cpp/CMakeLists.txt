cmake_minimum_required(VERSION 3.9.2)
project(Stack)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Werror -g" )
set (SRC
    ${PROJECT_SOURCE_DIR}/stack.cpp
  )

add_executable(stack ${SRC})
