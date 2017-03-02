cmake_minimum_required(VERSION 3.2.2) # CMake version check

# we don't allow sss to be build in the source directory
set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(SimpleSatSolver)

set (CMAKE_CXX_FLAGS "-O3 -std=c++14")

add_executable (sss sss.cpp)

install (FILES ${CMAKE_BINARY_DIR}/sss DESTINATION bin/)