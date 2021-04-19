add_executable(meshviewer MACOSX_BUNDLE main.cpp glutil.h glutil.cpp)
target_link_libraries(meshviewer fssimplewindow ysclass ysbitmapfont meshlib)
