cmake_minimum_required(VERSION 3.8)
project(ps6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ps6 MACOSX_BUNDLE ps6.cpp)

add_subdirectory(../../public/src ${CMAKE_BINARY_DIR}/public)
target_link_libraries(ps6 fssimplewindow ysclass)