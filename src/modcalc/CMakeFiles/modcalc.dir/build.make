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
include src/modcalc/CMakeFiles/modcalc.dir/depend.make

# Include the progress variables for this target.
include src/modcalc/CMakeFiles/modcalc.dir/progress.make

# Include the compile flags for this target's objects.
include src/modcalc/CMakeFiles/modcalc.dir/flags.make

src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o: src/modcalc/CMakeFiles/modcalc.dir/flags.make
src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o: src/modcalc/modcalc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/scav2020/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o"
	cd /home/pi/scav2020/src/modcalc && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modcalc.dir/modcalc.cpp.o -c /home/pi/scav2020/src/modcalc/modcalc.cpp

src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modcalc.dir/modcalc.cpp.i"
	cd /home/pi/scav2020/src/modcalc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/scav2020/src/modcalc/modcalc.cpp > CMakeFiles/modcalc.dir/modcalc.cpp.i

src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modcalc.dir/modcalc.cpp.s"
	cd /home/pi/scav2020/src/modcalc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/scav2020/src/modcalc/modcalc.cpp -o CMakeFiles/modcalc.dir/modcalc.cpp.s

src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o.requires:

.PHONY : src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o.requires

src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o.provides: src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o.requires
	$(MAKE) -f src/modcalc/CMakeFiles/modcalc.dir/build.make src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o.provides.build
.PHONY : src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o.provides

src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o.provides.build: src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o


# Object files for target modcalc
modcalc_OBJECTS = \
"CMakeFiles/modcalc.dir/modcalc.cpp.o"

# External object files for target modcalc
modcalc_EXTERNAL_OBJECTS =

src/modcalc/modcalc: src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o
src/modcalc/modcalc: src/modcalc/CMakeFiles/modcalc.dir/build.make
src/modcalc/modcalc: src/modmngr/libmodmngr.a
src/modcalc/modcalc: src/modcalc/CMakeFiles/modcalc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/scav2020/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable modcalc"
	cd /home/pi/scav2020/src/modcalc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/modcalc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/modcalc/CMakeFiles/modcalc.dir/build: src/modcalc/modcalc

.PHONY : src/modcalc/CMakeFiles/modcalc.dir/build

src/modcalc/CMakeFiles/modcalc.dir/requires: src/modcalc/CMakeFiles/modcalc.dir/modcalc.cpp.o.requires

.PHONY : src/modcalc/CMakeFiles/modcalc.dir/requires

src/modcalc/CMakeFiles/modcalc.dir/clean:
	cd /home/pi/scav2020/src/modcalc && $(CMAKE_COMMAND) -P CMakeFiles/modcalc.dir/cmake_clean.cmake
.PHONY : src/modcalc/CMakeFiles/modcalc.dir/clean

src/modcalc/CMakeFiles/modcalc.dir/depend:
	cd /home/pi/scav2020 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/scav2020 /home/pi/scav2020/src/modcalc /home/pi/scav2020 /home/pi/scav2020/src/modcalc /home/pi/scav2020/src/modcalc/CMakeFiles/modcalc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/modcalc/CMakeFiles/modcalc.dir/depend
