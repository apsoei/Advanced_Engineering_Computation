
cmake_minimum_required(VERSION 3.8)
project(finalProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Process MACOSX_BUNDLE main.cpp)
#target_link_libraries(Process Visualize STL)