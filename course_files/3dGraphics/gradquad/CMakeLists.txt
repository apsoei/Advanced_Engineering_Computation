cmake_minimum_required(VERSION 3.8)
project(gradquad)

add_subdirectory(../../../public/src ${CMAKE_BINARY_DIR}/public)

add_executable(main MACOSX_BUNDLE main.cpp)
target_link_libraries(main fssimplewindow ysbitmapfont)
