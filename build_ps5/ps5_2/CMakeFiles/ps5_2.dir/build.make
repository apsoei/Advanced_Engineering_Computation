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
CMAKE_SOURCE_DIR = /Users/jaeseoko/24783/jaeseoko/ps5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jaeseoko/24783/build_ps5

# Include any dependencies generated for this target.
include ps5_2/CMakeFiles/ps5_2.dir/depend.make

# Include the progress variables for this target.
include ps5_2/CMakeFiles/ps5_2.dir/progress.make

# Include the compile flags for this target's objects.
include ps5_2/CMakeFiles/ps5_2.dir/flags.make

ps5_2/CMakeFiles/ps5_2.dir/main.cpp.o: ps5_2/CMakeFiles/ps5_2.dir/flags.make
ps5_2/CMakeFiles/ps5_2.dir/main.cpp.o: /Users/jaeseoko/24783/jaeseoko/ps5/ps5_2/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jaeseoko/24783/build_ps5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ps5_2/CMakeFiles/ps5_2.dir/main.cpp.o"
	cd /Users/jaeseoko/24783/build_ps5/ps5_2 && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ps5_2.dir/main.cpp.o -c /Users/jaeseoko/24783/jaeseoko/ps5/ps5_2/main.cpp

ps5_2/CMakeFiles/ps5_2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ps5_2.dir/main.cpp.i"
	cd /Users/jaeseoko/24783/build_ps5/ps5_2 && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jaeseoko/24783/jaeseoko/ps5/ps5_2/main.cpp > CMakeFiles/ps5_2.dir/main.cpp.i

ps5_2/CMakeFiles/ps5_2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ps5_2.dir/main.cpp.s"
	cd /Users/jaeseoko/24783/build_ps5/ps5_2 && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jaeseoko/24783/jaeseoko/ps5/ps5_2/main.cpp -o CMakeFiles/ps5_2.dir/main.cpp.s

# Object files for target ps5_2
ps5_2_OBJECTS = \
"CMakeFiles/ps5_2.dir/main.cpp.o"

# External object files for target ps5_2
ps5_2_EXTERNAL_OBJECTS =

ps5_2/ps5_2.app/Contents/MacOS/ps5_2: ps5_2/CMakeFiles/ps5_2.dir/main.cpp.o
ps5_2/ps5_2.app/Contents/MacOS/ps5_2: ps5_2/CMakeFiles/ps5_2.dir/build.make
ps5_2/ps5_2.app/Contents/MacOS/ps5_2: public/fssimplewindow/src/libfssimplewindow.a
ps5_2/ps5_2.app/Contents/MacOS/ps5_2: public/ysbitmapfont/src/libysbitmapfont.a
ps5_2/ps5_2.app/Contents/MacOS/ps5_2: bintreelib/libbintreelib.a
ps5_2/ps5_2.app/Contents/MacOS/ps5_2: public/ysgl/src/libysgl.a
ps5_2/ps5_2.app/Contents/MacOS/ps5_2: ps5_2/CMakeFiles/ps5_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jaeseoko/24783/build_ps5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ps5_2.app/Contents/MacOS/ps5_2"
	cd /Users/jaeseoko/24783/build_ps5/ps5_2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ps5_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ps5_2/CMakeFiles/ps5_2.dir/build: ps5_2/ps5_2.app/Contents/MacOS/ps5_2

.PHONY : ps5_2/CMakeFiles/ps5_2.dir/build

ps5_2/CMakeFiles/ps5_2.dir/clean:
	cd /Users/jaeseoko/24783/build_ps5/ps5_2 && $(CMAKE_COMMAND) -P CMakeFiles/ps5_2.dir/cmake_clean.cmake
.PHONY : ps5_2/CMakeFiles/ps5_2.dir/clean

ps5_2/CMakeFiles/ps5_2.dir/depend:
	cd /Users/jaeseoko/24783/build_ps5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jaeseoko/24783/jaeseoko/ps5 /Users/jaeseoko/24783/jaeseoko/ps5/ps5_2 /Users/jaeseoko/24783/build_ps5 /Users/jaeseoko/24783/build_ps5/ps5_2 /Users/jaeseoko/24783/build_ps5/ps5_2/CMakeFiles/ps5_2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ps5_2/CMakeFiles/ps5_2.dir/depend

