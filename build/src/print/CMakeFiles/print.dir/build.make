# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /home/pi/scav2020

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/scav2020/build

# Include any dependencies generated for this target.
include src/print/CMakeFiles/print.dir/depend.make

# Include the progress variables for this target.
include src/print/CMakeFiles/print.dir/progress.make

# Include the compile flags for this target's objects.
include src/print/CMakeFiles/print.dir/flags.make

src/print/CMakeFiles/print.dir/print.cpp.o: src/print/CMakeFiles/print.dir/flags.make
src/print/CMakeFiles/print.dir/print.cpp.o: ../src/print/print.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/scav2020/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/print/CMakeFiles/print.dir/print.cpp.o"
	cd /home/pi/scav2020/build/src/print && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/print.dir/print.cpp.o -c /home/pi/scav2020/src/print/print.cpp

src/print/CMakeFiles/print.dir/print.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/print.dir/print.cpp.i"
	cd /home/pi/scav2020/build/src/print && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/scav2020/src/print/print.cpp > CMakeFiles/print.dir/print.cpp.i

src/print/CMakeFiles/print.dir/print.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/print.dir/print.cpp.s"
	cd /home/pi/scav2020/build/src/print && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/scav2020/src/print/print.cpp -o CMakeFiles/print.dir/print.cpp.s

src/print/CMakeFiles/print.dir/print.cpp.o.requires:

.PHONY : src/print/CMakeFiles/print.dir/print.cpp.o.requires

src/print/CMakeFiles/print.dir/print.cpp.o.provides: src/print/CMakeFiles/print.dir/print.cpp.o.requires
	$(MAKE) -f src/print/CMakeFiles/print.dir/build.make src/print/CMakeFiles/print.dir/print.cpp.o.provides.build
.PHONY : src/print/CMakeFiles/print.dir/print.cpp.o.provides

src/print/CMakeFiles/print.dir/print.cpp.o.provides.build: src/print/CMakeFiles/print.dir/print.cpp.o


# Object files for target print
print_OBJECTS = \
"CMakeFiles/print.dir/print.cpp.o"

# External object files for target print
print_EXTERNAL_OBJECTS =

src/print/libprint.a: src/print/CMakeFiles/print.dir/print.cpp.o
src/print/libprint.a: src/print/CMakeFiles/print.dir/build.make
src/print/libprint.a: src/print/CMakeFiles/print.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/scav2020/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libprint.a"
	cd /home/pi/scav2020/build/src/print && $(CMAKE_COMMAND) -P CMakeFiles/print.dir/cmake_clean_target.cmake
	cd /home/pi/scav2020/build/src/print && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/print.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/print/CMakeFiles/print.dir/build: src/print/libprint.a

.PHONY : src/print/CMakeFiles/print.dir/build

src/print/CMakeFiles/print.dir/requires: src/print/CMakeFiles/print.dir/print.cpp.o.requires

.PHONY : src/print/CMakeFiles/print.dir/requires

src/print/CMakeFiles/print.dir/clean:
	cd /home/pi/scav2020/build/src/print && $(CMAKE_COMMAND) -P CMakeFiles/print.dir/cmake_clean.cmake
.PHONY : src/print/CMakeFiles/print.dir/clean

src/print/CMakeFiles/print.dir/depend:
	cd /home/pi/scav2020/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/scav2020 /home/pi/scav2020/src/print /home/pi/scav2020/build /home/pi/scav2020/build/src/print /home/pi/scav2020/build/src/print/CMakeFiles/print.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/print/CMakeFiles/print.dir/depend

