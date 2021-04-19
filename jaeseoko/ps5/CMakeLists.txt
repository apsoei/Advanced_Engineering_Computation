cmake_minimum_required(VERSION 3.8)
project(jaeseoko)

enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ps5_1)
add_subdirectory(ps5_2)
add_subdirectory(ps5_3)
add_subdirectory(bintreelib)

add_subdirectory(../../public/src ${CMAKE_BINARY_DIR}/public)