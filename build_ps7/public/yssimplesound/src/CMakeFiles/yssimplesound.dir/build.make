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
CMAKE_SOURCE_DIR = /Users/jaeseoko/24783/jaeseoko/ps7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jaeseoko/24783/build_ps7

# Include any dependencies generated for this target.
include public/yssimplesound/src/CMakeFiles/yssimplesound.dir/depend.make

# Include the progress variables for this target.
include public/yssimplesound/src/CMakeFiles/yssimplesound.dir/progress.make

# Include the compile flags for this target's objects.
include public/yssimplesound/src/CMakeFiles/yssimplesound.dir/flags.make

public/yssimplesound/src/CMakeFiles/yssimplesound.dir/yssimplesound.cpp.o: public/yssimplesound/src/CMakeFiles/yssimplesound.dir/flags.make
public/yssimplesound/src/CMakeFiles/yssimplesound.dir/yssimplesound.cpp.o: /Users/jaeseoko/24783/public/src/yssimplesound/src/yssimplesound.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jaeseoko/24783/build_ps7/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object public/yssimplesound/src/CMakeFiles/yssimplesound.dir/yssimplesound.cpp.o"
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/yssimplesound.dir/yssimplesound.cpp.o -c /Users/jaeseoko/24783/public/src/yssimplesound/src/yssimplesound.cpp

public/yssimplesound/src/CMakeFiles/yssimplesound.dir/yssimplesound.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yssimplesound.dir/yssimplesound.cpp.i"
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jaeseoko/24783/public/src/yssimplesound/src/yssimplesound.cpp > CMakeFiles/yssimplesound.dir/yssimplesound.cpp.i

public/yssimplesound/src/CMakeFiles/yssimplesound.dir/yssimplesound.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yssimplesound.dir/yssimplesound.cpp.s"
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jaeseoko/24783/public/src/yssimplesound/src/yssimplesound.cpp -o CMakeFiles/yssimplesound.dir/yssimplesound.cpp.s

# Object files for target yssimplesound
yssimplesound_OBJECTS = \
"CMakeFiles/yssimplesound.dir/yssimplesound.cpp.o"

# External object files for target yssimplesound
yssimplesound_EXTERNAL_OBJECTS =

public/yssimplesound/src/libyssimplesound.a: public/yssimplesound/src/CMakeFiles/yssimplesound.dir/yssimplesound.cpp.o
public/yssimplesound/src/libyssimplesound.a: public/yssimplesound/src/CMakeFiles/yssimplesound.dir/build.make
public/yssimplesound/src/libyssimplesound.a: public/yssimplesound/src/CMakeFiles/yssimplesound.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jaeseoko/24783/build_ps7/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libyssimplesound.a"
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/src && $(CMAKE_COMMAND) -P CMakeFiles/yssimplesound.dir/cmake_clean_target.cmake
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yssimplesound.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
public/yssimplesound/src/CMakeFiles/yssimplesound.dir/build: public/yssimplesound/src/libyssimplesound.a

.PHONY : public/yssimplesound/src/CMakeFiles/yssimplesound.dir/build

public/yssimplesound/src/CMakeFiles/yssimplesound.dir/clean:
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/src && $(CMAKE_COMMAND) -P CMakeFiles/yssimplesound.dir/cmake_clean.cmake
.PHONY : public/yssimplesound/src/CMakeFiles/yssimplesound.dir/clean

public/yssimplesound/src/CMakeFiles/yssimplesound.dir/depend:
	cd /Users/jaeseoko/24783/build_ps7 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jaeseoko/24783/jaeseoko/ps7 /Users/jaeseoko/24783/public/src/yssimplesound/src /Users/jaeseoko/24783/build_ps7 /Users/jaeseoko/24783/build_ps7/public/yssimplesound/src /Users/jaeseoko/24783/build_ps7/public/yssimplesound/src/CMakeFiles/yssimplesound.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : public/yssimplesound/src/CMakeFiles/yssimplesound.dir/depend

