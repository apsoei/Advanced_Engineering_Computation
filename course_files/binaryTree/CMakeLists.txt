cmake_minimum_required(VERSION 3.8)
project(binTree)

add_subdirectory(../../public/src ${CMAKE_BINARY_DIR}/public)

add_library(bintreelib ysbintree.cpp ysbintree.h)
target_include_directories(bintreelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(bintreevis MACOSX_BUNDLE bintreevis.cpp)
target_link_libraries(bintreevis bintreelib fssimplewindow ysbitmapfont)
