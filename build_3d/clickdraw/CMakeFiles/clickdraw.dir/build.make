# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.17.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.17.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jaeseoko/24783/course_files/3dGraphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jaeseoko/24783/build_3d

# Include any dependencies generated for this target.
include clickdraw/CMakeFiles/clickdraw.dir/depend.make

# Include the progress variables for this target.
include clickdraw/CMakeFiles/clickdraw.dir/progress.make

# Include the compile flags for this target's objects.
include clickdraw/CMakeFiles/clickdraw.dir/flags.make

clickdraw/CMakeFiles/clickdraw.dir/main.cpp.o: clickdraw/CMakeFiles/clickdraw.dir/flags.make
clickdraw/CMakeFiles/clickdraw.dir/main.cpp.o: /Users/jaeseoko/24783/course_files/3dGraphics/clickdraw/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jaeseoko/24783/build_3d/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object clickdraw/CMakeFiles/clickdraw.dir/main.cpp.o"
	cd /Users/jaeseoko/24783/build_3d/clickdraw && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clickdraw.dir/main.cpp.o -c /Users/jaeseoko/24783/course_files/3dGraphics/clickdraw/main.cpp

clickdraw/CMakeFiles/clickdraw.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clickdraw.dir/main.cpp.i"
	cd /Users/jaeseoko/24783/build_3d/clickdraw && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jaeseoko/24783/course_files/3dGraphics/clickdraw/main.cpp > CMakeFiles/clickdraw.dir/main.cpp.i

clickdraw/CMakeFiles/clickdraw.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clickdraw.dir/main.cpp.s"
	cd /Users/jaeseoko/24783/build_3d/clickdraw && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jaeseoko/24783/course_files/3dGraphics/clickdraw/main.cpp -o CMakeFiles/clickdraw.dir/main.cpp.s

# Object files for target clickdraw
clickdraw_OBJECTS = \
"CMakeFiles/clickdraw.dir/main.cpp.o"

# External object files for target clickdraw
clickdraw_EXTERNAL_OBJECTS =

clickdraw/clickdraw.app/Contents/MacOS/clickdraw: clickdraw/CMakeFiles/clickdraw.dir/main.cpp.o
clickdraw/clickdraw.app/Contents/MacOS/clickdraw: clickdraw/CMakeFiles/clickdraw.dir/build.make
clickdraw/clickdraw.app/Contents/MacOS/clickdraw: public/fssimplewindow/src/libfssimplewindow.a
clickdraw/clickdraw.app/Contents/MacOS/clickdraw: public/ysbitmapfont/src/libysbitmapfont.a
clickdraw/clickdraw.app/Contents/MacOS/clickdraw: public/ysgl/src/libysgl.a
clickdraw/clickdraw.app/Contents/MacOS/clickdraw: clickdraw/CMakeFiles/clickdraw.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jaeseoko/24783/build_3d/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable clickdraw.app/Contents/MacOS/clickdraw"
	cd /Users/jaeseoko/24783/build_3d/clickdraw && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clickdraw.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
clickdraw/CMakeFiles/clickdraw.dir/build: clickdraw/clickdraw.app/Contents/MacOS/clickdraw

.PHONY : clickdraw/CMakeFiles/clickdraw.dir/build

clickdraw/CMakeFiles/clickdraw.dir/clean:
	cd /Users/jaeseoko/24783/build_3d/clickdraw && $(CMAKE_COMMAND) -P CMakeFiles/clickdraw.dir/cmake_clean.cmake
.PHONY : clickdraw/CMakeFiles/clickdraw.dir/clean

clickdraw/CMakeFiles/clickdraw.dir/depend:
	cd /Users/jaeseoko/24783/build_3d && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jaeseoko/24783/course_files/3dGraphics /Users/jaeseoko/24783/course_files/3dGraphics/clickdraw /Users/jaeseoko/24783/build_3d /Users/jaeseoko/24783/build_3d/clickdraw /Users/jaeseoko/24783/build_3d/clickdraw/CMakeFiles/clickdraw.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : clickdraw/CMakeFiles/clickdraw.dir/depend

