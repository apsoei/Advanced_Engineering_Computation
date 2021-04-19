add_library(qem qem.h qem.cpp)
target_link_libraries(qem geblkernel ysclass)


add_executable(shlextviewer MACOSX_BUNDLE main.cpp glutil.h glutil.cpp)
target_link_libraries(shlextviewer fssimplewindow ysclass ysbitmapfont qem geblkernel)
