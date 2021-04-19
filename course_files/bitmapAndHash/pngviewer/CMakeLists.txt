set(TARGET_NAME pngviewer)
add_executable(${TARGET_NAME} MACOSX_BUNDLE pngviewer)
target_link_libraries(${TARGET_NAME} simplebitmap fssimplewindow)
