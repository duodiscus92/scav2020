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
include src/modcam/CMakeFiles/modcam.dir/depend.make

# Include the progress variables for this target.
include src/modcam/CMakeFiles/modcam.dir/progress.make

# Include the compile flags for this target's objects.
include src/modcam/CMakeFiles/modcam.dir/flags.make

src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o: src/modcam/CMakeFiles/modcam.dir/flags.make
src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o: src/modcam/modcam.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/scav2020/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o"
	cd /home/pi/scav2020/src/modcam && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modcam.dir/modcam.cpp.o -c /home/pi/scav2020/src/modcam/modcam.cpp

src/modcam/CMakeFiles/modcam.dir/modcam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modcam.dir/modcam.cpp.i"
	cd /home/pi/scav2020/src/modcam && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/scav2020/src/modcam/modcam.cpp > CMakeFiles/modcam.dir/modcam.cpp.i

src/modcam/CMakeFiles/modcam.dir/modcam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modcam.dir/modcam.cpp.s"
	cd /home/pi/scav2020/src/modcam && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/scav2020/src/modcam/modcam.cpp -o CMakeFiles/modcam.dir/modcam.cpp.s

src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o.requires:

.PHONY : src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o.requires

src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o.provides: src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o.requires
	$(MAKE) -f src/modcam/CMakeFiles/modcam.dir/build.make src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o.provides.build
.PHONY : src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o.provides

src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o.provides.build: src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o


# Object files for target modcam
modcam_OBJECTS = \
"CMakeFiles/modcam.dir/modcam.cpp.o"

# External object files for target modcam
modcam_EXTERNAL_OBJECTS =

src/modcam/modcam: src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o
src/modcam/modcam: src/modcam/CMakeFiles/modcam.dir/build.make
src/modcam/modcam: src/modmngr/libmodmngr.a
src/modcam/modcam: src/modcam/CMakeFiles/modcam.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/scav2020/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable modcam"
	cd /home/pi/scav2020/src/modcam && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/modcam.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/modcam/CMakeFiles/modcam.dir/build: src/modcam/modcam

.PHONY : src/modcam/CMakeFiles/modcam.dir/build

src/modcam/CMakeFiles/modcam.dir/requires: src/modcam/CMakeFiles/modcam.dir/modcam.cpp.o.requires

.PHONY : src/modcam/CMakeFiles/modcam.dir/requires

src/modcam/CMakeFiles/modcam.dir/clean:
	cd /home/pi/scav2020/src/modcam && $(CMAKE_COMMAND) -P CMakeFiles/modcam.dir/cmake_clean.cmake
.PHONY : src/modcam/CMakeFiles/modcam.dir/clean

src/modcam/CMakeFiles/modcam.dir/depend:
	cd /home/pi/scav2020 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/scav2020 /home/pi/scav2020/src/modcam /home/pi/scav2020 /home/pi/scav2020/src/modcam /home/pi/scav2020/src/modcam/CMakeFiles/modcam.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/modcam/CMakeFiles/modcam.dir/depend

