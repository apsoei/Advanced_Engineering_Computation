set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore")
    message(FATAL_ERROR "This framework not supported for UWP")
elseif(MSVC)
    set(LIB_SRCS
        graphics/windows/fssimplewindow.cpp
        graphics/windows/fssimplewindow.h
    )
    set(HEADER_PATH graphics/windows)
elseif(APPLE)
    set(LIB_SRCS
        graphics/macosx/fssimplewindow.h
        graphics/macosx/fssimplewindowcpp.cpp
        graphics/macosx/fssimplewindowobjc.m
    )
    set(HEADER_PATH graphics/macosx)
elseif(UNIX)
    set(LIB_SRCS
        graphics/linux/fssimplewindow.cpp
        graphics/linux/fssimplewindow.h
    )
    set(HEADER_PATH graphics/linux)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()



add_library(simplewindow ${LIB_SRCS})
target_include_directories(simplewindow PUBLIC ${HEADER_PATH})

if(APPLE)
	find_library(COCOA_LIB Cocoa)
	find_library(OPENGL_LIB OpenGL)
	target_link_libraries(simplewindow ${COCOA_LIB} ${OPENGL_LIB})
elseif(UNIX)
	target_link_libraries(simplewindow GL GLU X11)
endif()




add_executable(bouncing_ball MACOSX_BUNDLE main.cpp)
target_link_libraries(bouncing_ball simplewindow)

