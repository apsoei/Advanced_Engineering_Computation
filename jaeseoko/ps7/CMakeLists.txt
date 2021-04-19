cmake_minimum_required(VERSION 3.8)
project(ps7)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../../public/src ${CMAKE_BINARY_DIR}/public)


add_library(glutil glutil.cpp glutil.h)
target_link_libraries(glutil ysclass)


add_library(meshlattice meshlattice.cpp meshlattice.h lattice.h)
target_link_libraries(meshlattice geblkernel)

add_library(ps7lib ps7lib.cpp ps7lib.h)
target_link_libraries(ps7lib geblkernel glutil meshlattice fssimplewindow)

add_executable(ps7 MACOSX_BUNDLE main.cpp)
target_link_libraries(ps7 ps7lib)

# set(TARGET_NAME glutil)
# add_library(${TARGET_NAME}
#     glutil.cpp
#     glutil.h
# )