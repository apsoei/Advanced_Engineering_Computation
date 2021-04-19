cmake_minimum_required(VERSION 3.8)
project(24783)

enable_testing()

add_executable(test1 test1.cpp yshash.h)
add_executable(test2 test2.cpp yshash.h)
add_executable(test3 test3.cpp yshash.h)
add_executable(test4 test4.cpp yshash.h)

add_test(NAME test1 COMMAND test1)
add_test(NAME test2 COMMAND test2)
add_test(NAME test3 COMMAND test3)
add_test(NAME test4 COMMAND test4)
