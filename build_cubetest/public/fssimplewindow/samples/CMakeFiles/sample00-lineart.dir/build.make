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
CMAKE_SOURCE_DIR = /Users/jaeseoko/24783/cubetest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jaeseoko/24783/build_cubetest

# Include any dependencies generated for this target.
include public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/depend.make

# Include the progress variables for this target.
include public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/progress.make

# Include the compile flags for this target's objects.
include public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/flags.make

public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/sample00-lineart/sample00-lineart.cpp.o: public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/flags.make
public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/sample00-lineart/sample00-lineart.cpp.o: /Users/jaeseoko/24783/public/src/fssimplewindow/samples/sample00-lineart/sample00-lineart.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jaeseoko/24783/build_cubetest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/sample00-lineart/sample00-lineart.cpp.o"
	cd /Users/jaeseoko/24783/build_cubetest/public/fssimplewindow/samples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sample00-lineart.dir/sample00-lineart/sample00-lineart.cpp.o -c /Users/jaeseoko/24783/public/src/fssimplewindow/samples/sample00-lineart/sample00-lineart.cpp

public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/sample00-lineart/sample00-lineart.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample00-lineart.dir/sample00-lineart/sample00-lineart.cpp.i"
	cd /Users/jaeseoko/24783/build_cubetest/public/fssimplewindow/samples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jaeseoko/24783/public/src/fssimplewindow/samples/sample00-lineart/sample00-lineart.cpp > CMakeFiles/sample00-lineart.dir/sample00-lineart/sample00-lineart.cpp.i

public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/sample00-lineart/sample00-lineart.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample00-lineart.dir/sample00-lineart/sample00-lineart.cpp.s"
	cd /Users/jaeseoko/24783/build_cubetest/public/fssimplewindow/samples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jaeseoko/24783/public/src/fssimplewindow/samples/sample00-lineart/sample00-lineart.cpp -o CMakeFiles/sample00-lineart.dir/sample00-lineart/sample00-lineart.cpp.s

# Object files for target sample00-lineart
sample00__lineart_OBJECTS = \
"CMakeFiles/sample00-lineart.dir/sample00-lineart/sample00-lineart.cpp.o"

# External object files for target sample00-lineart
sample00__lineart_EXTERNAL_OBJECTS =

public/fssimplewindow/samples/sample00-lineart.app/Contents/MacOS/sample00-lineart: public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/sample00-lineart/sample00-lineart.cpp.o
public/fssimplewindow/samples/sample00-lineart.app/Contents/MacOS/sample00-lineart: public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/build.make
public/fssimplewindow/samples/sample00-lineart.app/Contents/MacOS/sample00-lineart: public/fssimplewindow/src/libfssimplewindow.a
public/fssimplewindow/samples/sample00-lineart.app/Contents/MacOS/sample00-lineart: public/ysbitmapfont/src/libysbitmapfont.a
public/fssimplewindow/samples/sample00-lineart.app/Contents/MacOS/sample00-lineart: public/ysgl/src/libysgl.a
public/fssimplewindow/samples/sample00-lineart.app/Contents/MacOS/sample00-lineart: public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jaeseoko/24783/build_cubetest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sample00-lineart.app/Contents/MacOS/sample00-lineart"
	cd /Users/jaeseoko/24783/build_cubetest/public/fssimplewindow/samples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sample00-lineart.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/build: public/fssimplewindow/samples/sample00-lineart.app/Contents/MacOS/sample00-lineart

.PHONY : public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/build

public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/clean:
	cd /Users/jaeseoko/24783/build_cubetest/public/fssimplewindow/samples && $(CMAKE_COMMAND) -P CMakeFiles/sample00-lineart.dir/cmake_clean.cmake
.PHONY : public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/clean

public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/depend:
	cd /Users/jaeseoko/24783/build_cubetest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jaeseoko/24783/cubetest /Users/jaeseoko/24783/public/src/fssimplewindow/samples /Users/jaeseoko/24783/build_cubetest /Users/jaeseoko/24783/build_cubetest/public/fssimplewindow/samples /Users/jaeseoko/24783/build_cubetest/public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : public/fssimplewindow/samples/CMakeFiles/sample00-lineart.dir/depend

