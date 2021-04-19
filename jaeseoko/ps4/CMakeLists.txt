cmake_minimum_required(VERSION 3.8)
project(jaeseoko)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ps4_1)
add_subdirectory(ps4_2)
add_subdirectory(hashutil)
add_subdirectory(simplebitmap)

add_subdirectory(../../public/src ${CMAKE_BINARY_DIR}/public)
add_subdirectory(../../MMLPlayer/ym2612 ${CMAKE_BINARY_DIR}/ym2612)
add_subdirectory(../../MMLPlayer/mmlplayer ${CMAKE_BINARY_DIR}/mmlplayer)