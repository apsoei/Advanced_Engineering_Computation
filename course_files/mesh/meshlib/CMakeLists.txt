add_library(meshlib mesh.cpp mesh.h)
target_include_directories(meshlib PUBLIC .)
target_link_libraries(meshlib ysclass)

add_executable(meshtest1 test1.cpp)
target_link_libraries(meshtest1 meshlib)

add_test(NAME meshtest1 COMMAND meshtest1)


add_executable(meshtest2 test2.cpp)
target_link_libraries(meshtest2 meshlib)

add_test(NAME meshtest2 COMMAND meshtest2)


add_executable(meshtest3 test3.cpp)
target_link_libraries(meshtest3 meshlib)
