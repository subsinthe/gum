# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_SOURCE_DIR = /media/dev/C++/cppgear

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/dev/C++/cppgear/build

# Include any dependencies generated for this target.
include cppgear/CMakeFiles/cppgear-static.dir/depend.make

# Include the progress variables for this target.
include cppgear/CMakeFiles/cppgear-static.dir/progress.make

# Include the compile flags for this target's objects.
include cppgear/CMakeFiles/cppgear-static.dir/flags.make

cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o: cppgear/CMakeFiles/cppgear-static.dir/flags.make
cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o: ../cppgear/options/options.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/dev/C++/cppgear/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o"
	cd /media/dev/C++/cppgear/build/cppgear && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cppgear-static.dir/options/options.cpp.o -c /media/dev/C++/cppgear/cppgear/options/options.cpp

cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cppgear-static.dir/options/options.cpp.i"
	cd /media/dev/C++/cppgear/build/cppgear && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/dev/C++/cppgear/cppgear/options/options.cpp > CMakeFiles/cppgear-static.dir/options/options.cpp.i

cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cppgear-static.dir/options/options.cpp.s"
	cd /media/dev/C++/cppgear/build/cppgear && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/dev/C++/cppgear/cppgear/options/options.cpp -o CMakeFiles/cppgear-static.dir/options/options.cpp.s

cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o.requires:

.PHONY : cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o.requires

cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o.provides: cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o.requires
	$(MAKE) -f cppgear/CMakeFiles/cppgear-static.dir/build.make cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o.provides.build
.PHONY : cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o.provides

cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o.provides.build: cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o


# Object files for target cppgear-static
cppgear__static_OBJECTS = \
"CMakeFiles/cppgear-static.dir/options/options.cpp.o"

# External object files for target cppgear-static
cppgear__static_EXTERNAL_OBJECTS =

cppgear/libcppgear.a: cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o
cppgear/libcppgear.a: cppgear/CMakeFiles/cppgear-static.dir/build.make
cppgear/libcppgear.a: cppgear/CMakeFiles/cppgear-static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/dev/C++/cppgear/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcppgear.a"
	cd /media/dev/C++/cppgear/build/cppgear && $(CMAKE_COMMAND) -P CMakeFiles/cppgear-static.dir/cmake_clean_target.cmake
	cd /media/dev/C++/cppgear/build/cppgear && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cppgear-static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cppgear/CMakeFiles/cppgear-static.dir/build: cppgear/libcppgear.a

.PHONY : cppgear/CMakeFiles/cppgear-static.dir/build

cppgear/CMakeFiles/cppgear-static.dir/requires: cppgear/CMakeFiles/cppgear-static.dir/options/options.cpp.o.requires

.PHONY : cppgear/CMakeFiles/cppgear-static.dir/requires

cppgear/CMakeFiles/cppgear-static.dir/clean:
	cd /media/dev/C++/cppgear/build/cppgear && $(CMAKE_COMMAND) -P CMakeFiles/cppgear-static.dir/cmake_clean.cmake
.PHONY : cppgear/CMakeFiles/cppgear-static.dir/clean

cppgear/CMakeFiles/cppgear-static.dir/depend:
	cd /media/dev/C++/cppgear/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/dev/C++/cppgear /media/dev/C++/cppgear/cppgear /media/dev/C++/cppgear/build /media/dev/C++/cppgear/build/cppgear /media/dev/C++/cppgear/build/cppgear/CMakeFiles/cppgear-static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cppgear/CMakeFiles/cppgear-static.dir/depend

