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
include public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/depend.make

# Include the progress variables for this target.
include public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/progress.make

# Include the compile flags for this target's objects.
include public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/flags.make

public/ysgebl/src/main/ysgebl64.app/Contents/Resources/APPL.icns: /Users/jaeseoko/24783/public/src/ysgebl/src/main/macosx/APPL.icns
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Copying OS X content public/ysgebl/src/main/ysgebl64.app/Contents/Resources/APPL.icns"
	$(CMAKE_COMMAND) -E copy /Users/jaeseoko/24783/public/src/ysgebl/src/main/macosx/APPL.icns public/ysgebl/src/main/ysgebl64.app/Contents/Resources/APPL.icns

public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/ysgebl_gui_extension.cpp.o: public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/flags.make
public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/ysgebl_gui_extension.cpp.o: /Users/jaeseoko/24783/public/src/ysgebl/src/main/ysgebl_gui_extension.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jaeseoko/24783/build_cubetest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/ysgebl_gui_extension.cpp.o"
	cd /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ysgebl64.dir/ysgebl_gui_extension.cpp.o -c /Users/jaeseoko/24783/public/src/ysgebl/src/main/ysgebl_gui_extension.cpp

public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/ysgebl_gui_extension.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ysgebl64.dir/ysgebl_gui_extension.cpp.i"
	cd /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jaeseoko/24783/public/src/ysgebl/src/main/ysgebl_gui_extension.cpp > CMakeFiles/ysgebl64.dir/ysgebl_gui_extension.cpp.i

public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/ysgebl_gui_extension.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ysgebl64.dir/ysgebl_gui_extension.cpp.s"
	cd /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jaeseoko/24783/public/src/ysgebl/src/main/ysgebl_gui_extension.cpp -o CMakeFiles/ysgebl64.dir/ysgebl_gui_extension.cpp.s

# Object files for target ysgebl64
ysgebl64_OBJECTS = \
"CMakeFiles/ysgebl64.dir/ysgebl_gui_extension.cpp.o"

# External object files for target ysgebl64
ysgebl64_EXTERNAL_OBJECTS =

public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/ysgebl_gui_extension.cpp.o
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/build.make
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/fslazywindow/src/libfslazywindow.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysgebl/src/kernel/libgeblkernel.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysgebl/src/kernelutil/libgeblutil.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysgebl/src/gui/libgeblgui.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/fslazywindow/src/libfslazywindow.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysgebl/src/gui_foundation/libgeblgui_foundation.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysgebl/src/shellrender/libgeblgl.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysgebl/src/kernelutil/libgeblutil.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysgebl/src/kernel/libgeblkernel.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysglcpp/src/libysglcpp.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysclass11/src/libysclass11.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysglcpp/src/gl2/libysglcpp_gl2.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/fsguilib/filedialog/libfsguifiledialog.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/fsgui3d/src/libfsgui3d.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/fsguilib/src/libfsguilib.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysfontrenderer/src/libysfontrenderer.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/fsgui3d/src/gl2/libfsgui3d_gl2.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/fsguilib/src/gl2/libfsguilib_gl2.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/fssimplewindow/src/libfssimplewindow.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/yssystemfont/src/libyssystemfont.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysbitmap/src/libysbitmap.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysbitmapfont/src/libysbitmapfont.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysgl/src/libysgl.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysport/src/libysport.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysclass/src/libysclass.a
public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64: public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jaeseoko/24783/build_cubetest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ysgebl64.app/Contents/MacOS/ysgebl64"
	cd /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ysgebl64.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main && echo For: ysgebl64
	cd /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main && echo Copy
	cd /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main && echo From: /Users/jaeseoko/24783/public/src/ysgebl/src/main/../../runtime
	cd /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main && echo To: /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/../Resources
	cd /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main && /usr/local/Cellar/cmake/3.17.3/bin/cmake -E make_directory "/Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/../Resources"
	cd /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main && /usr/local/Cellar/cmake/3.17.3/bin/cmake -E copy_directory "/Users/jaeseoko/24783/public/src/ysgebl/src/main/../../runtime" "/Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/../Resources"

# Rule to build all files generated by this target.
public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/build: public/ysgebl/src/main/ysgebl64.app/Contents/MacOS/ysgebl64
public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/build: public/ysgebl/src/main/ysgebl64.app/Contents/Resources/APPL.icns

.PHONY : public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/build

public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/clean:
	cd /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main && $(CMAKE_COMMAND) -P CMakeFiles/ysgebl64.dir/cmake_clean.cmake
.PHONY : public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/clean

public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/depend:
	cd /Users/jaeseoko/24783/build_cubetest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jaeseoko/24783/cubetest /Users/jaeseoko/24783/public/src/ysgebl/src/main /Users/jaeseoko/24783/build_cubetest /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main /Users/jaeseoko/24783/build_cubetest/public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : public/ysgebl/src/main/CMakeFiles/ysgebl64.dir/depend

