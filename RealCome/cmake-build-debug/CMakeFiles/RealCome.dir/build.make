# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\LionCHIK\CLion 2020.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\LionCHIK\CLion 2020.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Git_C\My_Programm\RealCome

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Git_C\My_Programm\RealCome\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/RealCome.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RealCome.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RealCome.dir/flags.make

CMakeFiles/RealCome.dir/main.cpp.obj: CMakeFiles/RealCome.dir/flags.make
CMakeFiles/RealCome.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Git_C\My_Programm\RealCome\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RealCome.dir/main.cpp.obj"
	D:\MinGW\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\RealCome.dir\main.cpp.obj -c D:\Git_C\My_Programm\RealCome\main.cpp

CMakeFiles/RealCome.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RealCome.dir/main.cpp.i"
	D:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Git_C\My_Programm\RealCome\main.cpp > CMakeFiles\RealCome.dir\main.cpp.i

CMakeFiles/RealCome.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RealCome.dir/main.cpp.s"
	D:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Git_C\My_Programm\RealCome\main.cpp -o CMakeFiles\RealCome.dir\main.cpp.s

CMakeFiles/RealCome.dir/CMakeFiles/Realization.cpp.obj: CMakeFiles/RealCome.dir/flags.make
CMakeFiles/RealCome.dir/CMakeFiles/Realization.cpp.obj: CMakeFiles/Realization.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Git_C\My_Programm\RealCome\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/RealCome.dir/CMakeFiles/Realization.cpp.obj"
	D:\MinGW\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\RealCome.dir\CMakeFiles\Realization.cpp.obj -c D:\Git_C\My_Programm\RealCome\cmake-build-debug\CMakeFiles\Realization.cpp

CMakeFiles/RealCome.dir/CMakeFiles/Realization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RealCome.dir/CMakeFiles/Realization.cpp.i"
	D:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Git_C\My_Programm\RealCome\cmake-build-debug\CMakeFiles\Realization.cpp > CMakeFiles\RealCome.dir\CMakeFiles\Realization.cpp.i

CMakeFiles/RealCome.dir/CMakeFiles/Realization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RealCome.dir/CMakeFiles/Realization.cpp.s"
	D:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Git_C\My_Programm\RealCome\cmake-build-debug\CMakeFiles\Realization.cpp -o CMakeFiles\RealCome.dir\CMakeFiles\Realization.cpp.s

# Object files for target RealCome
RealCome_OBJECTS = \
"CMakeFiles/RealCome.dir/main.cpp.obj" \
"CMakeFiles/RealCome.dir/CMakeFiles/Realization.cpp.obj"

# External object files for target RealCome
RealCome_EXTERNAL_OBJECTS =

RealCome.exe: CMakeFiles/RealCome.dir/main.cpp.obj
RealCome.exe: CMakeFiles/RealCome.dir/CMakeFiles/Realization.cpp.obj
RealCome.exe: CMakeFiles/RealCome.dir/build.make
RealCome.exe: CMakeFiles/RealCome.dir/linklibs.rsp
RealCome.exe: CMakeFiles/RealCome.dir/objects1.rsp
RealCome.exe: CMakeFiles/RealCome.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Git_C\My_Programm\RealCome\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable RealCome.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\RealCome.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RealCome.dir/build: RealCome.exe

.PHONY : CMakeFiles/RealCome.dir/build

CMakeFiles/RealCome.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\RealCome.dir\cmake_clean.cmake
.PHONY : CMakeFiles/RealCome.dir/clean

CMakeFiles/RealCome.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Git_C\My_Programm\RealCome D:\Git_C\My_Programm\RealCome D:\Git_C\My_Programm\RealCome\cmake-build-debug D:\Git_C\My_Programm\RealCome\cmake-build-debug D:\Git_C\My_Programm\RealCome\cmake-build-debug\CMakeFiles\RealCome.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RealCome.dir/depend
