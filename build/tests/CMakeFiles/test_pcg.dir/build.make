# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nuss/91/bt717591/PNLA_Stefan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nuss/91/bt717591/PNLA_Stefan/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_pcg.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_pcg.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_pcg.dir/flags.make

tests/CMakeFiles/test_pcg.dir/test_pcg.cpp.o: tests/CMakeFiles/test_pcg.dir/flags.make
tests/CMakeFiles/test_pcg.dir/test_pcg.cpp.o: ../tests/test_pcg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nuss/91/bt717591/PNLA_Stefan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_pcg.dir/test_pcg.cpp.o"
	cd /home/nuss/91/bt717591/PNLA_Stefan/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_pcg.dir/test_pcg.cpp.o -c /home/nuss/91/bt717591/PNLA_Stefan/tests/test_pcg.cpp

tests/CMakeFiles/test_pcg.dir/test_pcg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_pcg.dir/test_pcg.cpp.i"
	cd /home/nuss/91/bt717591/PNLA_Stefan/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nuss/91/bt717591/PNLA_Stefan/tests/test_pcg.cpp > CMakeFiles/test_pcg.dir/test_pcg.cpp.i

tests/CMakeFiles/test_pcg.dir/test_pcg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_pcg.dir/test_pcg.cpp.s"
	cd /home/nuss/91/bt717591/PNLA_Stefan/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nuss/91/bt717591/PNLA_Stefan/tests/test_pcg.cpp -o CMakeFiles/test_pcg.dir/test_pcg.cpp.s

# Object files for target test_pcg
test_pcg_OBJECTS = \
"CMakeFiles/test_pcg.dir/test_pcg.cpp.o"

# External object files for target test_pcg
test_pcg_EXTERNAL_OBJECTS =

tests/test_pcg: tests/CMakeFiles/test_pcg.dir/test_pcg.cpp.o
tests/test_pcg: tests/CMakeFiles/test_pcg.dir/build.make
tests/test_pcg: libpnla.a
tests/test_pcg: tests/CMakeFiles/test_pcg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nuss/91/bt717591/PNLA_Stefan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_pcg"
	cd /home/nuss/91/bt717591/PNLA_Stefan/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_pcg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_pcg.dir/build: tests/test_pcg

.PHONY : tests/CMakeFiles/test_pcg.dir/build

tests/CMakeFiles/test_pcg.dir/clean:
	cd /home/nuss/91/bt717591/PNLA_Stefan/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_pcg.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_pcg.dir/clean

tests/CMakeFiles/test_pcg.dir/depend:
	cd /home/nuss/91/bt717591/PNLA_Stefan/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nuss/91/bt717591/PNLA_Stefan /home/nuss/91/bt717591/PNLA_Stefan/tests /home/nuss/91/bt717591/PNLA_Stefan/build /home/nuss/91/bt717591/PNLA_Stefan/build/tests /home/nuss/91/bt717591/PNLA_Stefan/build/tests/CMakeFiles/test_pcg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_pcg.dir/depend
