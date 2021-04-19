add_executable(ps4_2 MACOSX_BUNDLE main.cpp)
# target_link_libraries(ps4_2 fssimplewindow yssimplesound_platform mmlplayer ym2612
#                       simplebitmap hashutil)
target_link_libraries(ps4_2 fssimplewindow simplebitmap hashutil mmlplayer yssimplesound yssimplesound_platform)