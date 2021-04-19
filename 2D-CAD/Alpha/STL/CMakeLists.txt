add_executable(univSTL MACOSX_BUNDLE main.cpp)
target_link_libraries(univSTL fssimplewindow ysclass ysbitmapfont binstllib)

add_library(binstllib binstl.cpp binstl.h)
target_include_directories(STL PUBLIC .)
