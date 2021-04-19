add_library(shootinggame
  shoot-3-class.cpp
  shoot-3-class.h)
target_include_directories(shootinggame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(shootinggame simplewindow ysglfontdata)
