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
include bintreelib/CMakeFiles/bintreelib.dir/depend.make

# Include the progress variables for this target.
include bintreelib/CMakeFiles/bintreelib.dir/progress.make

# Include the compile flags for this target's objects.
include bintreelib/CMakeFiles/bintreelib.dir/flags.make

bintreelib/CMakeFiles/bintreelib.dir/bintree.cpp.o: bintreelib/CMakeFiles/bintreelib.dir/flags.make
bintreelib/CMakeFiles/bintreelib.dir/bintree.cpp.o: /Users/jaeseoko/24783/jaeseoko/ps5/bintreelib/bintree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jaeseoko/24783/build_ps5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bintreelib/CMakeFiles/bintreelib.dir/bintree.cpp.o"
	cd /Users/jaeseoko/24783/build_ps5/bintreelib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bintreelib.dir/bintree.cpp.o -c /Users/jaeseoko/24783/jaeseoko/ps5/bintreelib/bintree.cpp

bintreelib/CMakeFiles/bintreelib.dir/bintree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bintreelib.dir/bintree.cpp.i"
	cd /Users/jaeseoko/24783/build_ps5/bintreelib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jaeseoko/24783/jaeseoko/ps5/bintreelib/bintree.cpp > CMakeFiles/bintreelib.dir/bintree.cpp.i

bintreelib/CMakeFiles/bintreelib.dir/bintree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bintreelib.dir/bintree.cpp.s"
	cd /Users/jaeseoko/24783/build_ps5/bintreelib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jaeseoko/24783/jaeseoko/ps5/bintreelib/bintree.cpp -o CMakeFiles/bintreelib.dir/bintree.cpp.s

# Object files for target bintreelib
bintreelib_OBJECTS = \
"CMakeFiles/bintreelib.dir/bintree.cpp.o"

# External object files for target bintreelib
bintreelib_EXTERNAL_OBJECTS =

bintreelib/libbintreelib.a: bintreelib/CMakeFiles/bintreelib.dir/bintree.cpp.o
bintreelib/libbintreelib.a: bintreelib/CMakeFiles/bintreelib.dir/build.make
bintreelib/libbintreelib.a: bintreelib/CMakeFiles/bintreelib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jaeseoko/24783/build_ps5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libbintreelib.a"
	cd /Users/jaeseoko/24783/build_ps5/bintreelib && $(CMAKE_COMMAND) -P CMakeFiles/bintreelib.dir/cmake_clean_target.cmake
	cd /Users/jaeseoko/24783/build_ps5/bintreelib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bintreelib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bintreelib/CMakeFiles/bintreelib.dir/build: bintreelib/libbintreelib.a

.PHONY : bintreelib/CMakeFiles/bintreelib.dir/build

bintreelib/CMakeFiles/bintreelib.dir/clean:
	cd /Users/jaeseoko/24783/build_ps5/bintreelib && $(CMAKE_COMMAND) -P CMakeFiles/bintreelib.dir/cmake_clean.cmake
.PHONY : bintreelib/CMakeFiles/bintreelib.dir/clean

bintreelib/CMakeFiles/bintreelib.dir/depend:
	cd /Users/jaeseoko/24783/build_ps5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jaeseoko/24783/jaeseoko/ps5 /Users/jaeseoko/24783/jaeseoko/ps5/bintreelib /Users/jaeseoko/24783/build_ps5 /Users/jaeseoko/24783/build_ps5/bintreelib /Users/jaeseoko/24783/build_ps5/bintreelib/CMakeFiles/bintreelib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bintreelib/CMakeFiles/bintreelib.dir/depend
