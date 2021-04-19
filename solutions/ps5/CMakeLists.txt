cmake_minimum_required(VERSION 3.8)
project(ps5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory("../../public/src" ${CMAKE_BINARY_DIR}/public)
add_subdirectory("ps5_1")
add_subdirectory("ps5_2")
add_subdirectory("ps5_3")
add_subdirectory("bintreelib")
