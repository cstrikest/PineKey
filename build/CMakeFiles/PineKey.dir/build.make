# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Pine\Prog\PineKey

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Pine\Prog\PineKey\build

# Include any dependencies generated for this target.
include CMakeFiles/PineKey.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PineKey.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PineKey.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PineKey.dir/flags.make

CMakeFiles/PineKey.dir/main.cpp.obj: CMakeFiles/PineKey.dir/flags.make
CMakeFiles/PineKey.dir/main.cpp.obj: CMakeFiles/PineKey.dir/includes_CXX.rsp
CMakeFiles/PineKey.dir/main.cpp.obj: C:/Pine/Prog/PineKey/main.cpp
CMakeFiles/PineKey.dir/main.cpp.obj: CMakeFiles/PineKey.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Pine\Prog\PineKey\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PineKey.dir/main.cpp.obj"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PineKey.dir/main.cpp.obj -MF CMakeFiles\PineKey.dir\main.cpp.obj.d -o CMakeFiles\PineKey.dir\main.cpp.obj -c C:\Pine\Prog\PineKey\main.cpp

CMakeFiles/PineKey.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PineKey.dir/main.cpp.i"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Pine\Prog\PineKey\main.cpp > CMakeFiles\PineKey.dir\main.cpp.i

CMakeFiles/PineKey.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PineKey.dir/main.cpp.s"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Pine\Prog\PineKey\main.cpp -o CMakeFiles\PineKey.dir\main.cpp.s

CMakeFiles/PineKey.dir/KeyHook.cpp.obj: CMakeFiles/PineKey.dir/flags.make
CMakeFiles/PineKey.dir/KeyHook.cpp.obj: CMakeFiles/PineKey.dir/includes_CXX.rsp
CMakeFiles/PineKey.dir/KeyHook.cpp.obj: C:/Pine/Prog/PineKey/KeyHook.cpp
CMakeFiles/PineKey.dir/KeyHook.cpp.obj: CMakeFiles/PineKey.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Pine\Prog\PineKey\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PineKey.dir/KeyHook.cpp.obj"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PineKey.dir/KeyHook.cpp.obj -MF CMakeFiles\PineKey.dir\KeyHook.cpp.obj.d -o CMakeFiles\PineKey.dir\KeyHook.cpp.obj -c C:\Pine\Prog\PineKey\KeyHook.cpp

CMakeFiles/PineKey.dir/KeyHook.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PineKey.dir/KeyHook.cpp.i"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Pine\Prog\PineKey\KeyHook.cpp > CMakeFiles\PineKey.dir\KeyHook.cpp.i

CMakeFiles/PineKey.dir/KeyHook.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PineKey.dir/KeyHook.cpp.s"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Pine\Prog\PineKey\KeyHook.cpp -o CMakeFiles\PineKey.dir\KeyHook.cpp.s

CMakeFiles/PineKey.dir/imgui-master/imgui.cpp.obj: CMakeFiles/PineKey.dir/flags.make
CMakeFiles/PineKey.dir/imgui-master/imgui.cpp.obj: CMakeFiles/PineKey.dir/includes_CXX.rsp
CMakeFiles/PineKey.dir/imgui-master/imgui.cpp.obj: C:/Pine/Prog/PineKey/imgui-master/imgui.cpp
CMakeFiles/PineKey.dir/imgui-master/imgui.cpp.obj: CMakeFiles/PineKey.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Pine\Prog\PineKey\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PineKey.dir/imgui-master/imgui.cpp.obj"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PineKey.dir/imgui-master/imgui.cpp.obj -MF CMakeFiles\PineKey.dir\imgui-master\imgui.cpp.obj.d -o CMakeFiles\PineKey.dir\imgui-master\imgui.cpp.obj -c C:\Pine\Prog\PineKey\imgui-master\imgui.cpp

CMakeFiles/PineKey.dir/imgui-master/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PineKey.dir/imgui-master/imgui.cpp.i"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Pine\Prog\PineKey\imgui-master\imgui.cpp > CMakeFiles\PineKey.dir\imgui-master\imgui.cpp.i

CMakeFiles/PineKey.dir/imgui-master/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PineKey.dir/imgui-master/imgui.cpp.s"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Pine\Prog\PineKey\imgui-master\imgui.cpp -o CMakeFiles\PineKey.dir\imgui-master\imgui.cpp.s

CMakeFiles/PineKey.dir/imgui-master/imgui_draw.cpp.obj: CMakeFiles/PineKey.dir/flags.make
CMakeFiles/PineKey.dir/imgui-master/imgui_draw.cpp.obj: CMakeFiles/PineKey.dir/includes_CXX.rsp
CMakeFiles/PineKey.dir/imgui-master/imgui_draw.cpp.obj: C:/Pine/Prog/PineKey/imgui-master/imgui_draw.cpp
CMakeFiles/PineKey.dir/imgui-master/imgui_draw.cpp.obj: CMakeFiles/PineKey.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Pine\Prog\PineKey\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PineKey.dir/imgui-master/imgui_draw.cpp.obj"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PineKey.dir/imgui-master/imgui_draw.cpp.obj -MF CMakeFiles\PineKey.dir\imgui-master\imgui_draw.cpp.obj.d -o CMakeFiles\PineKey.dir\imgui-master\imgui_draw.cpp.obj -c C:\Pine\Prog\PineKey\imgui-master\imgui_draw.cpp

CMakeFiles/PineKey.dir/imgui-master/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PineKey.dir/imgui-master/imgui_draw.cpp.i"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Pine\Prog\PineKey\imgui-master\imgui_draw.cpp > CMakeFiles\PineKey.dir\imgui-master\imgui_draw.cpp.i

CMakeFiles/PineKey.dir/imgui-master/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PineKey.dir/imgui-master/imgui_draw.cpp.s"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Pine\Prog\PineKey\imgui-master\imgui_draw.cpp -o CMakeFiles\PineKey.dir\imgui-master\imgui_draw.cpp.s

CMakeFiles/PineKey.dir/imgui-master/imgui_widgets.cpp.obj: CMakeFiles/PineKey.dir/flags.make
CMakeFiles/PineKey.dir/imgui-master/imgui_widgets.cpp.obj: CMakeFiles/PineKey.dir/includes_CXX.rsp
CMakeFiles/PineKey.dir/imgui-master/imgui_widgets.cpp.obj: C:/Pine/Prog/PineKey/imgui-master/imgui_widgets.cpp
CMakeFiles/PineKey.dir/imgui-master/imgui_widgets.cpp.obj: CMakeFiles/PineKey.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Pine\Prog\PineKey\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/PineKey.dir/imgui-master/imgui_widgets.cpp.obj"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PineKey.dir/imgui-master/imgui_widgets.cpp.obj -MF CMakeFiles\PineKey.dir\imgui-master\imgui_widgets.cpp.obj.d -o CMakeFiles\PineKey.dir\imgui-master\imgui_widgets.cpp.obj -c C:\Pine\Prog\PineKey\imgui-master\imgui_widgets.cpp

CMakeFiles/PineKey.dir/imgui-master/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PineKey.dir/imgui-master/imgui_widgets.cpp.i"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Pine\Prog\PineKey\imgui-master\imgui_widgets.cpp > CMakeFiles\PineKey.dir\imgui-master\imgui_widgets.cpp.i

CMakeFiles/PineKey.dir/imgui-master/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PineKey.dir/imgui-master/imgui_widgets.cpp.s"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Pine\Prog\PineKey\imgui-master\imgui_widgets.cpp -o CMakeFiles\PineKey.dir\imgui-master\imgui_widgets.cpp.s

CMakeFiles/PineKey.dir/imgui-master/imgui_tables.cpp.obj: CMakeFiles/PineKey.dir/flags.make
CMakeFiles/PineKey.dir/imgui-master/imgui_tables.cpp.obj: CMakeFiles/PineKey.dir/includes_CXX.rsp
CMakeFiles/PineKey.dir/imgui-master/imgui_tables.cpp.obj: C:/Pine/Prog/PineKey/imgui-master/imgui_tables.cpp
CMakeFiles/PineKey.dir/imgui-master/imgui_tables.cpp.obj: CMakeFiles/PineKey.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Pine\Prog\PineKey\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/PineKey.dir/imgui-master/imgui_tables.cpp.obj"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PineKey.dir/imgui-master/imgui_tables.cpp.obj -MF CMakeFiles\PineKey.dir\imgui-master\imgui_tables.cpp.obj.d -o CMakeFiles\PineKey.dir\imgui-master\imgui_tables.cpp.obj -c C:\Pine\Prog\PineKey\imgui-master\imgui_tables.cpp

CMakeFiles/PineKey.dir/imgui-master/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PineKey.dir/imgui-master/imgui_tables.cpp.i"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Pine\Prog\PineKey\imgui-master\imgui_tables.cpp > CMakeFiles\PineKey.dir\imgui-master\imgui_tables.cpp.i

CMakeFiles/PineKey.dir/imgui-master/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PineKey.dir/imgui-master/imgui_tables.cpp.s"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Pine\Prog\PineKey\imgui-master\imgui_tables.cpp -o CMakeFiles\PineKey.dir\imgui-master\imgui_tables.cpp.s

CMakeFiles/PineKey.dir/imgui-master/imgui_demo.cpp.obj: CMakeFiles/PineKey.dir/flags.make
CMakeFiles/PineKey.dir/imgui-master/imgui_demo.cpp.obj: CMakeFiles/PineKey.dir/includes_CXX.rsp
CMakeFiles/PineKey.dir/imgui-master/imgui_demo.cpp.obj: C:/Pine/Prog/PineKey/imgui-master/imgui_demo.cpp
CMakeFiles/PineKey.dir/imgui-master/imgui_demo.cpp.obj: CMakeFiles/PineKey.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Pine\Prog\PineKey\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/PineKey.dir/imgui-master/imgui_demo.cpp.obj"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PineKey.dir/imgui-master/imgui_demo.cpp.obj -MF CMakeFiles\PineKey.dir\imgui-master\imgui_demo.cpp.obj.d -o CMakeFiles\PineKey.dir\imgui-master\imgui_demo.cpp.obj -c C:\Pine\Prog\PineKey\imgui-master\imgui_demo.cpp

CMakeFiles/PineKey.dir/imgui-master/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PineKey.dir/imgui-master/imgui_demo.cpp.i"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Pine\Prog\PineKey\imgui-master\imgui_demo.cpp > CMakeFiles\PineKey.dir\imgui-master\imgui_demo.cpp.i

CMakeFiles/PineKey.dir/imgui-master/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PineKey.dir/imgui-master/imgui_demo.cpp.s"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Pine\Prog\PineKey\imgui-master\imgui_demo.cpp -o CMakeFiles\PineKey.dir\imgui-master\imgui_demo.cpp.s

CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_opengl3.cpp.obj: CMakeFiles/PineKey.dir/flags.make
CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_opengl3.cpp.obj: CMakeFiles/PineKey.dir/includes_CXX.rsp
CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_opengl3.cpp.obj: C:/Pine/Prog/PineKey/imgui-master/backends/imgui_impl_opengl3.cpp
CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_opengl3.cpp.obj: CMakeFiles/PineKey.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Pine\Prog\PineKey\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_opengl3.cpp.obj"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_opengl3.cpp.obj -MF CMakeFiles\PineKey.dir\imgui-master\backends\imgui_impl_opengl3.cpp.obj.d -o CMakeFiles\PineKey.dir\imgui-master\backends\imgui_impl_opengl3.cpp.obj -c C:\Pine\Prog\PineKey\imgui-master\backends\imgui_impl_opengl3.cpp

CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_opengl3.cpp.i"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Pine\Prog\PineKey\imgui-master\backends\imgui_impl_opengl3.cpp > CMakeFiles\PineKey.dir\imgui-master\backends\imgui_impl_opengl3.cpp.i

CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_opengl3.cpp.s"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Pine\Prog\PineKey\imgui-master\backends\imgui_impl_opengl3.cpp -o CMakeFiles\PineKey.dir\imgui-master\backends\imgui_impl_opengl3.cpp.s

CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_glfw.cpp.obj: CMakeFiles/PineKey.dir/flags.make
CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_glfw.cpp.obj: CMakeFiles/PineKey.dir/includes_CXX.rsp
CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_glfw.cpp.obj: C:/Pine/Prog/PineKey/imgui-master/backends/imgui_impl_glfw.cpp
CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_glfw.cpp.obj: CMakeFiles/PineKey.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Pine\Prog\PineKey\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_glfw.cpp.obj"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_glfw.cpp.obj -MF CMakeFiles\PineKey.dir\imgui-master\backends\imgui_impl_glfw.cpp.obj.d -o CMakeFiles\PineKey.dir\imgui-master\backends\imgui_impl_glfw.cpp.obj -c C:\Pine\Prog\PineKey\imgui-master\backends\imgui_impl_glfw.cpp

CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_glfw.cpp.i"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Pine\Prog\PineKey\imgui-master\backends\imgui_impl_glfw.cpp > CMakeFiles\PineKey.dir\imgui-master\backends\imgui_impl_glfw.cpp.i

CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_glfw.cpp.s"
	C:\Pine\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Pine\Prog\PineKey\imgui-master\backends\imgui_impl_glfw.cpp -o CMakeFiles\PineKey.dir\imgui-master\backends\imgui_impl_glfw.cpp.s

# Object files for target PineKey
PineKey_OBJECTS = \
"CMakeFiles/PineKey.dir/main.cpp.obj" \
"CMakeFiles/PineKey.dir/KeyHook.cpp.obj" \
"CMakeFiles/PineKey.dir/imgui-master/imgui.cpp.obj" \
"CMakeFiles/PineKey.dir/imgui-master/imgui_draw.cpp.obj" \
"CMakeFiles/PineKey.dir/imgui-master/imgui_widgets.cpp.obj" \
"CMakeFiles/PineKey.dir/imgui-master/imgui_tables.cpp.obj" \
"CMakeFiles/PineKey.dir/imgui-master/imgui_demo.cpp.obj" \
"CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_opengl3.cpp.obj" \
"CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_glfw.cpp.obj"

# External object files for target PineKey
PineKey_EXTERNAL_OBJECTS =

PineKey.exe: CMakeFiles/PineKey.dir/main.cpp.obj
PineKey.exe: CMakeFiles/PineKey.dir/KeyHook.cpp.obj
PineKey.exe: CMakeFiles/PineKey.dir/imgui-master/imgui.cpp.obj
PineKey.exe: CMakeFiles/PineKey.dir/imgui-master/imgui_draw.cpp.obj
PineKey.exe: CMakeFiles/PineKey.dir/imgui-master/imgui_widgets.cpp.obj
PineKey.exe: CMakeFiles/PineKey.dir/imgui-master/imgui_tables.cpp.obj
PineKey.exe: CMakeFiles/PineKey.dir/imgui-master/imgui_demo.cpp.obj
PineKey.exe: CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_opengl3.cpp.obj
PineKey.exe: CMakeFiles/PineKey.dir/imgui-master/backends/imgui_impl_glfw.cpp.obj
PineKey.exe: CMakeFiles/PineKey.dir/build.make
PineKey.exe: C:/Pine/Prog/PineKey/bin/SDL2.dll
PineKey.exe: C:/Pine/Prog/PineKey/lib/glfw3.dll
PineKey.exe: CMakeFiles/PineKey.dir/linkLibs.rsp
PineKey.exe: CMakeFiles/PineKey.dir/objects1.rsp
PineKey.exe: CMakeFiles/PineKey.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Pine\Prog\PineKey\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable PineKey.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\PineKey.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PineKey.dir/build: PineKey.exe
.PHONY : CMakeFiles/PineKey.dir/build

CMakeFiles/PineKey.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\PineKey.dir\cmake_clean.cmake
.PHONY : CMakeFiles/PineKey.dir/clean

CMakeFiles/PineKey.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Pine\Prog\PineKey C:\Pine\Prog\PineKey C:\Pine\Prog\PineKey\build C:\Pine\Prog\PineKey\build C:\Pine\Prog\PineKey\build\CMakeFiles\PineKey.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/PineKey.dir/depend

