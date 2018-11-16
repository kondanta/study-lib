cmake_minimum_required(VERSION 3.12)
project (singlylist CXX)

# Set C++ Version
SET(CMAKE_CXX_STANDART 17)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}
  )

# Link runTests with what we want to test and the GTest and pthread library
add_executable(singlylist test.cpp)
target_link_libraries(singlylist
  ${GTEST_LIBRARIES}
  pthread
  )
