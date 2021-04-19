set(TARGET_NAME hashutil)
add_library(${TARGET_NAME}
	yshash.cpp
    yshash.h
)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})