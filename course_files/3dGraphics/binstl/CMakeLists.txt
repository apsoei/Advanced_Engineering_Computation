add_executable(binstl MACOSX_BUNDLE main.cpp)
target_link_libraries(binstl fssimplewindow ysclass ysbitmapfont binstllib)

add_library(binstllib binstl.cpp binstl.h)
target_include_directories(binstllib PUBLIC .)
