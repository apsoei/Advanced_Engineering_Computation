set(TARGET_NAME bintreelib)
add_library(${TARGET_NAME}
	bintree.cpp
    bintree.h
)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})