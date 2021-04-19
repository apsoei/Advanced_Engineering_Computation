set(TARGET_NAME simplebitmap)
add_library(${TARGET_NAME}
	simplebitmap.cpp
	simplebitmap.h
	simplebitmaptemplate.h
	yspng.cpp
	yspng.h
	yspngenc.cpp
	yspngenc.h
)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})