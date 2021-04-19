cmake_minimum_required(VERSION 3.8)
project(ps6)

add_subdirectory(../../public/src ${CMAKE_BINARY_DIR}/public)

add_executable(ps6 MACOSX_BUNDLE ps6.cpp)
target_link_libraries(ps6 ysclass fssimplewindow)

