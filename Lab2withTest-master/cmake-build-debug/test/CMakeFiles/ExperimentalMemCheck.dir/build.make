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
CMAKE_COMMAND = /home/mikhail/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/mikhail/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mikhail/CLionProjects/testProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mikhail/CLionProjects/testProject/cmake-build-debug

# Utility rule file for ExperimentalMemCheck.

# Include the progress variables for this target.
include test/CMakeFiles/ExperimentalMemCheck.dir/progress.make

test/CMakeFiles/ExperimentalMemCheck:
	cd /home/mikhail/CLionProjects/testProject/cmake-build-debug/test && /home/mikhail/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/ctest -D ExperimentalMemCheck

ExperimentalMemCheck: test/CMakeFiles/ExperimentalMemCheck
ExperimentalMemCheck: test/CMakeFiles/ExperimentalMemCheck.dir/build.make

.PHONY : ExperimentalMemCheck

# Rule to build all files generated by this target.
test/CMakeFiles/ExperimentalMemCheck.dir/build: ExperimentalMemCheck

.PHONY : test/CMakeFiles/ExperimentalMemCheck.dir/build

test/CMakeFiles/ExperimentalMemCheck.dir/clean:
	cd /home/mikhail/CLionProjects/testProject/cmake-build-debug/test && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalMemCheck.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/ExperimentalMemCheck.dir/clean

test/CMakeFiles/ExperimentalMemCheck.dir/depend:
	cd /home/mikhail/CLionProjects/testProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mikhail/CLionProjects/testProject /home/mikhail/CLionProjects/testProject/test /home/mikhail/CLionProjects/testProject/cmake-build-debug /home/mikhail/CLionProjects/testProject/cmake-build-debug/test /home/mikhail/CLionProjects/testProject/cmake-build-debug/test/CMakeFiles/ExperimentalMemCheck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/ExperimentalMemCheck.dir/depend

