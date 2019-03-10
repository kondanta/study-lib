cmake_minimum_required(VERSION 3.10)

# Project Name
project(comp CXX)

#Flags
set( CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -g -O3 -pedantic" )

#Compiler and stuff
set( CMAKE_CXX_STANDART 17 )
set( CMAKE_CXX_STANDART_REQUIRED ON )
set( CMAKE_C_COMPILER "/usr/bin/clang" )
set( CMAKE_CXX_COMPILER "/usr/bin/clang++" )
set( SRC ${PROJECT_SOURCE_DIR}/main.cpp)

# Compilation Db
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_executable(main ${SRC})
