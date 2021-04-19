cmake_minimum_required(VERSION 3.8)
project(Mesh)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(../../public/src ${CMAKE_BINARY_DIR}/public)

add_subdirectory(meshlib)
add_subdirectory(meshviewer)
# add_subdirectory(shellext)
