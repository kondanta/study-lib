
#Required Version of Cmake
cmake_minimum_required(VERSION 3.11)

#Project Name
project(visitor CXX)

#Set C++ Version
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED 
    CMAKE_EXPORT_COMPILE_COMMANDS)

#Setting Compiler flags
set( CMAKE_CXX_FLAGS "-g -O3 -Wall -Weffc++ -pedantic  -pedantic-errors -Wextra -Waggregate-return -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wfloat-equal -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self -Winline -Winvalid-pch -Wlong-long -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wpadded -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wswitch-default -Wswitch-enum -Wunreachable-code -Wunused -Wunused-parameter -Wvariadic-macros -Wwrite-strings" )


#Setting up the source files
set( SRC ${PROJECT_SOURCE_DIR}/main.cpp
   )


add_executable(visitor ${SRC})
    