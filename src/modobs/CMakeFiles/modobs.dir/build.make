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
CMAKE_BINARY_DIR = /home/pi/scav2020

# Include any dependencies generated for this target.
include src/modobs/CMakeFiles/modobs.dir/depend.make

# Include the progress variables for this target.
include src/modobs/CMakeFiles/modobs.dir/progress.make

# Include the compile flags for this target's objects.
include src/modobs/CMakeFiles/modobs.dir/flags.make

src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o: src/modobs/CMakeFiles/modobs.dir/flags.make
src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o: src/modobs/modobs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/scav2020/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o"
	cd /home/pi/scav2020/src/modobs && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modobs.dir/modobs.cpp.o -c /home/pi/scav2020/src/modobs/modobs.cpp

src/modobs/CMakeFiles/modobs.dir/modobs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modobs.dir/modobs.cpp.i"
	cd /home/pi/scav2020/src/modobs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/scav2020/src/modobs/modobs.cpp > CMakeFiles/modobs.dir/modobs.cpp.i

src/modobs/CMakeFiles/modobs.dir/modobs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modobs.dir/modobs.cpp.s"
	cd /home/pi/scav2020/src/modobs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/scav2020/src/modobs/modobs.cpp -o CMakeFiles/modobs.dir/modobs.cpp.s

src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o.requires:

.PHONY : src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o.requires

src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o.provides: src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o.requires
	$(MAKE) -f src/modobs/CMakeFiles/modobs.dir/build.make src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o.provides.build
.PHONY : src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o.provides

src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o.provides.build: src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o


# Object files for target modobs
modobs_OBJECTS = \
"CMakeFiles/modobs.dir/modobs.cpp.o"

# External object files for target modobs
modobs_EXTERNAL_OBJECTS =

src/modobs/modobs: src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o
src/modobs/modobs: src/modobs/CMakeFiles/modobs.dir/build.make
src/modobs/modobs: src/modmngr/libmodmngr.a
src/modobs/modobs: src/modobs/CMakeFiles/modobs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/scav2020/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable modobs"
	cd /home/pi/scav2020/src/modobs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/modobs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/modobs/CMakeFiles/modobs.dir/build: src/modobs/modobs

.PHONY : src/modobs/CMakeFiles/modobs.dir/build

src/modobs/CMakeFiles/modobs.dir/requires: src/modobs/CMakeFiles/modobs.dir/modobs.cpp.o.requires

.PHONY : src/modobs/CMakeFiles/modobs.dir/requires

src/modobs/CMakeFiles/modobs.dir/clean:
	cd /home/pi/scav2020/src/modobs && $(CMAKE_COMMAND) -P CMakeFiles/modobs.dir/cmake_clean.cmake
.PHONY : src/modobs/CMakeFiles/modobs.dir/clean

src/modobs/CMakeFiles/modobs.dir/depend:
	cd /home/pi/scav2020 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/scav2020 /home/pi/scav2020/src/modobs /home/pi/scav2020 /home/pi/scav2020/src/modobs /home/pi/scav2020/src/modobs/CMakeFiles/modobs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/modobs/CMakeFiles/modobs.dir/depend

