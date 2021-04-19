cmake_minimum_required(VERSION 3.8)
project(YS)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../public/src ${CMAKE_BINARY_DIR}/public)
add_subdirectory(bitmap)
add_subdirectory(pngviewer)
