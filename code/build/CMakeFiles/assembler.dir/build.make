# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/abdullah/SB/Hypothetical-Machine-Assembler/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/abdullah/SB/Hypothetical-Machine-Assembler/code/build

# Include any dependencies generated for this target.
include CMakeFiles/assembler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/assembler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/assembler.dir/flags.make

CMakeFiles/assembler.dir/lib/assembler.cpp.o: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/lib/assembler.cpp.o: ../lib/assembler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abdullah/SB/Hypothetical-Machine-Assembler/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/assembler.dir/lib/assembler.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/assembler.dir/lib/assembler.cpp.o -c /home/abdullah/SB/Hypothetical-Machine-Assembler/code/lib/assembler.cpp

CMakeFiles/assembler.dir/lib/assembler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/lib/assembler.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abdullah/SB/Hypothetical-Machine-Assembler/code/lib/assembler.cpp > CMakeFiles/assembler.dir/lib/assembler.cpp.i

CMakeFiles/assembler.dir/lib/assembler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/lib/assembler.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abdullah/SB/Hypothetical-Machine-Assembler/code/lib/assembler.cpp -o CMakeFiles/assembler.dir/lib/assembler.cpp.s

CMakeFiles/assembler.dir/lib/assembler.cpp.o.requires:

.PHONY : CMakeFiles/assembler.dir/lib/assembler.cpp.o.requires

CMakeFiles/assembler.dir/lib/assembler.cpp.o.provides: CMakeFiles/assembler.dir/lib/assembler.cpp.o.requires
	$(MAKE) -f CMakeFiles/assembler.dir/build.make CMakeFiles/assembler.dir/lib/assembler.cpp.o.provides.build
.PHONY : CMakeFiles/assembler.dir/lib/assembler.cpp.o.provides

CMakeFiles/assembler.dir/lib/assembler.cpp.o.provides.build: CMakeFiles/assembler.dir/lib/assembler.cpp.o


# Object files for target assembler
assembler_OBJECTS = \
"CMakeFiles/assembler.dir/lib/assembler.cpp.o"

# External object files for target assembler
assembler_EXTERNAL_OBJECTS =

libbin/libassembler.a: CMakeFiles/assembler.dir/lib/assembler.cpp.o
libbin/libassembler.a: CMakeFiles/assembler.dir/build.make
libbin/libassembler.a: CMakeFiles/assembler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/abdullah/SB/Hypothetical-Machine-Assembler/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libbin/libassembler.a"
	$(CMAKE_COMMAND) -P CMakeFiles/assembler.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/assembler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/assembler.dir/build: libbin/libassembler.a

.PHONY : CMakeFiles/assembler.dir/build

CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/lib/assembler.cpp.o.requires

.PHONY : CMakeFiles/assembler.dir/requires

CMakeFiles/assembler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/assembler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/assembler.dir/clean

CMakeFiles/assembler.dir/depend:
	cd /home/abdullah/SB/Hypothetical-Machine-Assembler/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abdullah/SB/Hypothetical-Machine-Assembler/code /home/abdullah/SB/Hypothetical-Machine-Assembler/code /home/abdullah/SB/Hypothetical-Machine-Assembler/code/build /home/abdullah/SB/Hypothetical-Machine-Assembler/code/build /home/abdullah/SB/Hypothetical-Machine-Assembler/code/build/CMakeFiles/assembler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/assembler.dir/depend

