cmake_minimum_required(VERSION 3.8)
project(XYZ)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../../../public/src ${CMAKE_BINARY_DIR}/public)

add_executable(main MACOSX_BUNDLE floodfill.cpp)
target_link_libraries(main fssimplewindow)
