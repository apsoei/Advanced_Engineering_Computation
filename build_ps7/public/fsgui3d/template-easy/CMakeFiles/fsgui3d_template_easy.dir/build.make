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
include public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/depend.make

# Include the progress variables for this target.
include public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/progress.make

# Include the compile flags for this target's objects.
include public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/flags.make

public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/fsgui3dmain.cpp.o: public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/flags.make
public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/fsgui3dmain.cpp.o: /Users/jaeseoko/24783/public/src/fsgui3d/template-easy/fsgui3dmain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jaeseoko/24783/build_ps7/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/fsgui3dmain.cpp.o"
	cd /Users/jaeseoko/24783/build_ps7/public/fsgui3d/template-easy && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fsgui3d_template_easy.dir/fsgui3dmain.cpp.o -c /Users/jaeseoko/24783/public/src/fsgui3d/template-easy/fsgui3dmain.cpp

public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/fsgui3dmain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fsgui3d_template_easy.dir/fsgui3dmain.cpp.i"
	cd /Users/jaeseoko/24783/build_ps7/public/fsgui3d/template-easy && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jaeseoko/24783/public/src/fsgui3d/template-easy/fsgui3dmain.cpp > CMakeFiles/fsgui3d_template_easy.dir/fsgui3dmain.cpp.i

public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/fsgui3dmain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fsgui3d_template_easy.dir/fsgui3dmain.cpp.s"
	cd /Users/jaeseoko/24783/build_ps7/public/fsgui3d/template-easy && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jaeseoko/24783/public/src/fsgui3d/template-easy/fsgui3dmain.cpp -o CMakeFiles/fsgui3d_template_easy.dir/fsgui3dmain.cpp.s

# Object files for target fsgui3d_template_easy
fsgui3d_template_easy_OBJECTS = \
"CMakeFiles/fsgui3d_template_easy.dir/fsgui3dmain.cpp.o"

# External object files for target fsgui3d_template_easy
fsgui3d_template_easy_EXTERNAL_OBJECTS =

public/fsgui3d/template-easy/fsgui3d_template_easy: public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/fsgui3dmain.cpp.o
public/fsgui3d/template-easy/fsgui3d_template_easy: public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/build.make
public/fsgui3d/template-easy/fsgui3d_template_easy: public/ysgl/src/libysgl.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/fsgui3d/src/libfsgui3d.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/fsguilib/src/gl1/libfsguilib_gl1.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/fsgui3d/src/gl1/libfsgui3d_gl1.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/fsguilib/src/libfsguilib.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/ysfontrenderer/src/libysfontrenderer.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/fsguilib/src/gl1/libfsguilib_gl1.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/yssystemfont/src/libyssystemfont.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/ysclass/src/libysclass.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/ysbitmap/src/libysbitmap.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/fssimplewindow/src/libfssimplewindow.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/ysbitmapfont/src/libysbitmapfont.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/ysgl/src/libysgl.a
public/fsgui3d/template-easy/fsgui3d_template_easy: public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jaeseoko/24783/build_ps7/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fsgui3d_template_easy"
	cd /Users/jaeseoko/24783/build_ps7/public/fsgui3d/template-easy && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fsgui3d_template_easy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/build: public/fsgui3d/template-easy/fsgui3d_template_easy

.PHONY : public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/build

public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/clean:
	cd /Users/jaeseoko/24783/build_ps7/public/fsgui3d/template-easy && $(CMAKE_COMMAND) -P CMakeFiles/fsgui3d_template_easy.dir/cmake_clean.cmake
.PHONY : public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/clean

public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/depend:
	cd /Users/jaeseoko/24783/build_ps7 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jaeseoko/24783/jaeseoko/ps7 /Users/jaeseoko/24783/public/src/fsgui3d/template-easy /Users/jaeseoko/24783/build_ps7 /Users/jaeseoko/24783/build_ps7/public/fsgui3d/template-easy /Users/jaeseoko/24783/build_ps7/public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : public/fsgui3d/template-easy/CMakeFiles/fsgui3d_template_easy.dir/depend

