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
CMAKE_SOURCE_DIR = /Users/jaeseoko/24783/jaeseoko/ps6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jaeseoko/24783/build_ps6

# Include any dependencies generated for this target.
include public/ysgl/src/CMakeFiles/ysgl_makec.dir/depend.make

# Include the progress variables for this target.
include public/ysgl/src/CMakeFiles/ysgl_makec.dir/progress.make

# Include the compile flags for this target's objects.
include public/ysgl/src/CMakeFiles/ysgl_makec.dir/flags.make

public/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o: public/ysgl/src/CMakeFiles/ysgl_makec.dir/flags.make
public/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o: /Users/jaeseoko/24783/public/src/ysgl/src/glsl_src/makec.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jaeseoko/24783/build_ps6/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object public/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o"
	cd /Users/jaeseoko/24783/build_ps6/public/ysgl/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o -c /Users/jaeseoko/24783/public/src/ysgl/src/glsl_src/makec.cpp

public/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.i"
	cd /Users/jaeseoko/24783/build_ps6/public/ysgl/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jaeseoko/24783/public/src/ysgl/src/glsl_src/makec.cpp > CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.i

public/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.s"
	cd /Users/jaeseoko/24783/build_ps6/public/ysgl/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jaeseoko/24783/public/src/ysgl/src/glsl_src/makec.cpp -o CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.s

# Object files for target ysgl_makec
ysgl_makec_OBJECTS = \
"CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o"

# External object files for target ysgl_makec
ysgl_makec_EXTERNAL_OBJECTS =

exe/ysgl_makec: public/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o
exe/ysgl_makec: public/ysgl/src/CMakeFiles/ysgl_makec.dir/build.make
exe/ysgl_makec: public/ysclass/src/libysclass.a
exe/ysgl_makec: public/ysgl/src/CMakeFiles/ysgl_makec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jaeseoko/24783/build_ps6/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../exe/ysgl_makec"
	cd /Users/jaeseoko/24783/build_ps6/public/ysgl/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ysgl_makec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
public/ysgl/src/CMakeFiles/ysgl_makec.dir/build: exe/ysgl_makec

.PHONY : public/ysgl/src/CMakeFiles/ysgl_makec.dir/build

public/ysgl/src/CMakeFiles/ysgl_makec.dir/clean:
	cd /Users/jaeseoko/24783/build_ps6/public/ysgl/src && $(CMAKE_COMMAND) -P CMakeFiles/ysgl_makec.dir/cmake_clean.cmake
.PHONY : public/ysgl/src/CMakeFiles/ysgl_makec.dir/clean

public/ysgl/src/CMakeFiles/ysgl_makec.dir/depend:
	cd /Users/jaeseoko/24783/build_ps6 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jaeseoko/24783/jaeseoko/ps6 /Users/jaeseoko/24783/public/src/ysgl/src /Users/jaeseoko/24783/build_ps6 /Users/jaeseoko/24783/build_ps6/public/ysgl/src /Users/jaeseoko/24783/build_ps6/public/ysgl/src/CMakeFiles/ysgl_makec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : public/ysgl/src/CMakeFiles/ysgl_makec.dir/depend

