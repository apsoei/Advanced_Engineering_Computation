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
include public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/depend.make

# Include the progress variables for this target.
include public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/progress.make

# Include the compile flags for this target's objects.
include public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/flags.make

public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/main.cpp.o: public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/flags.make
public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/main.cpp.o: /Users/jaeseoko/24783/public/src/yssimplesound/sample_fssimplewindow/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jaeseoko/24783/build_ps7/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/main.cpp.o"
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/yssimplesound_sample_fssimplewindow.dir/main.cpp.o -c /Users/jaeseoko/24783/public/src/yssimplesound/sample_fssimplewindow/main.cpp

public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yssimplesound_sample_fssimplewindow.dir/main.cpp.i"
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jaeseoko/24783/public/src/yssimplesound/sample_fssimplewindow/main.cpp > CMakeFiles/yssimplesound_sample_fssimplewindow.dir/main.cpp.i

public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yssimplesound_sample_fssimplewindow.dir/main.cpp.s"
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jaeseoko/24783/public/src/yssimplesound/sample_fssimplewindow/main.cpp -o CMakeFiles/yssimplesound_sample_fssimplewindow.dir/main.cpp.s

# Object files for target yssimplesound_sample_fssimplewindow
yssimplesound_sample_fssimplewindow_OBJECTS = \
"CMakeFiles/yssimplesound_sample_fssimplewindow.dir/main.cpp.o"

# External object files for target yssimplesound_sample_fssimplewindow
yssimplesound_sample_fssimplewindow_EXTERNAL_OBJECTS =

public/yssimplesound/sample_fssimplewindow/yssimplesound_sample_fssimplewindow.app/Contents/MacOS/yssimplesound_sample_fssimplewindow: public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/main.cpp.o
public/yssimplesound/sample_fssimplewindow/yssimplesound_sample_fssimplewindow.app/Contents/MacOS/yssimplesound_sample_fssimplewindow: public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/build.make
public/yssimplesound/sample_fssimplewindow/yssimplesound_sample_fssimplewindow.app/Contents/MacOS/yssimplesound_sample_fssimplewindow: public/fssimplewindow/src/libfssimplewindow.a
public/yssimplesound/sample_fssimplewindow/yssimplesound_sample_fssimplewindow.app/Contents/MacOS/yssimplesound_sample_fssimplewindow: public/yssimplesound/src/libyssimplesound.a
public/yssimplesound/sample_fssimplewindow/yssimplesound_sample_fssimplewindow.app/Contents/MacOS/yssimplesound_sample_fssimplewindow: public/yssimplesound/src/macosx/libyssimplesound_macosx.a
public/yssimplesound/sample_fssimplewindow/yssimplesound_sample_fssimplewindow.app/Contents/MacOS/yssimplesound_sample_fssimplewindow: public/yssimplesound/src/libyssimplesound.a
public/yssimplesound/sample_fssimplewindow/yssimplesound_sample_fssimplewindow.app/Contents/MacOS/yssimplesound_sample_fssimplewindow: public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jaeseoko/24783/build_ps7/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable yssimplesound_sample_fssimplewindow.app/Contents/MacOS/yssimplesound_sample_fssimplewindow"
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yssimplesound_sample_fssimplewindow.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow && echo For: yssimplesound_sample_fssimplewindow
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow && echo Copy
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow && echo From: /Users/jaeseoko/24783/public/src/yssimplesound/sample_fssimplewindow/datafiles
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow && echo To: /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow/yssimplesound_sample_fssimplewindow.app/Contents/MacOS/../Resources
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow && /usr/local/Cellar/cmake/3.17.3/bin/cmake -E make_directory "/Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow/yssimplesound_sample_fssimplewindow.app/Contents/MacOS/../Resources"
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow && /usr/local/Cellar/cmake/3.17.3/bin/cmake -E copy_directory "/Users/jaeseoko/24783/public/src/yssimplesound/sample_fssimplewindow/datafiles" "/Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow/yssimplesound_sample_fssimplewindow.app/Contents/MacOS/../Resources"

# Rule to build all files generated by this target.
public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/build: public/yssimplesound/sample_fssimplewindow/yssimplesound_sample_fssimplewindow.app/Contents/MacOS/yssimplesound_sample_fssimplewindow

.PHONY : public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/build

public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/clean:
	cd /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow && $(CMAKE_COMMAND) -P CMakeFiles/yssimplesound_sample_fssimplewindow.dir/cmake_clean.cmake
.PHONY : public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/clean

public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/depend:
	cd /Users/jaeseoko/24783/build_ps7 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jaeseoko/24783/jaeseoko/ps7 /Users/jaeseoko/24783/public/src/yssimplesound/sample_fssimplewindow /Users/jaeseoko/24783/build_ps7 /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow /Users/jaeseoko/24783/build_ps7/public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : public/yssimplesound/sample_fssimplewindow/CMakeFiles/yssimplesound_sample_fssimplewindow.dir/depend

