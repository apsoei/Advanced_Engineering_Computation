set(TARGET_NAME Visualize)
add_library(${TARGET_NAME}
	glutil.cpp
    glutil.h
    lattice.h
    mesh.cpp
    mesh.h
    cube.cpp
    cube.h
)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Visualize ysclass ysbitmapfont)