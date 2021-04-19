add_executable(ps5_3 MACOSX_BUNDLE main.cpp)
target_link_libraries(ps5_3 bintreelib)

add_test(NAME ps5test COMMAND ps5_3)
