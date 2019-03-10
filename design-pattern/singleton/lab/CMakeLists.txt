
#Required Version of Cmake
cmake_minimum_required(VERSION 3.10)

#Project Name
project(Error CXX)

#Setting Compiler flags
set( CMAKE_CXX_FLAGS "-std=c++1z -g -O3 -Wall -Weffc++ -pedantic  -pedantic-errors -Wextra -Waggregate-return -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wfloat-equal -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self -Winline -Winvalid-pch -Wlong-long -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wpadded -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wswitch-default -Wswitch-enum -Wunreachable-code -Wunused -Wunused-parameter -Wvariadic-macros -Wwrite-strings" )

#Exporing Compilation Commands
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

#Setting up the source files
set( SRC ${PROJECT_SOURCE_DIR}/main.cpp
   )


add_executable(main ${SRC})
    