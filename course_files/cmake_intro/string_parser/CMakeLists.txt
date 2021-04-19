add_library(fgets fgets.cpp fgets.h)

add_library(parserClass parserClass.cpp parserClass.h)

add_executable(main main.cpp)
target_link_libraries(main fgets parserClass)
