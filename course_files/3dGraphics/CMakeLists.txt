cmake_minimum_required(VERSION 3.8)
project(3DGraphics)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../../public/src ${CMAKE_BINARY_DIR}/public)

add_subdirectory(clickdraw)
add_subdirectory(cube)
add_subdirectory(binstl)
