# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/janos/quantizationEngine/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/janos/quantizationEngine/build

# Include any dependencies generated for this target.
include CMakeFiles/../engine.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/../engine.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/../engine.out.dir/flags.make

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o: CMakeFiles/../engine.out.dir/flags.make
CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o: /home/janos/quantizationEngine/main/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/janos/quantizationEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o -c /home/janos/quantizationEngine/main/main.cpp

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/janos/quantizationEngine/main/main.cpp > CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.i

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/janos/quantizationEngine/main/main.cpp -o CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.s

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o.requires:

.PHONY : CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o.requires

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o.provides: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/../engine.out.dir/build.make CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o.provides.build
.PHONY : CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o.provides

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o.provides.build: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o


CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o: CMakeFiles/../engine.out.dir/flags.make
CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o: /home/janos/quantizationEngine/network/network.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/janos/quantizationEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o -c /home/janos/quantizationEngine/network/network.cpp

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/janos/quantizationEngine/network/network.cpp > CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.i

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/janos/quantizationEngine/network/network.cpp -o CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.s

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o.requires:

.PHONY : CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o.requires

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o.provides: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o.requires
	$(MAKE) -f CMakeFiles/../engine.out.dir/build.make CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o.provides.build
.PHONY : CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o.provides

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o.provides.build: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o


CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o: CMakeFiles/../engine.out.dir/flags.make
CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o: /home/janos/quantizationEngine/io/io.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/janos/quantizationEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o -c /home/janos/quantizationEngine/io/io.cpp

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/janos/quantizationEngine/io/io.cpp > CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.i

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/janos/quantizationEngine/io/io.cpp -o CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.s

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o.requires:

.PHONY : CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o.requires

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o.provides: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o.requires
	$(MAKE) -f CMakeFiles/../engine.out.dir/build.make CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o.provides.build
.PHONY : CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o.provides

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o.provides.build: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o


CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o: CMakeFiles/../engine.out.dir/flags.make
CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o: /home/janos/quantizationEngine/io/iopool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/janos/quantizationEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o -c /home/janos/quantizationEngine/io/iopool.cpp

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/janos/quantizationEngine/io/iopool.cpp > CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.i

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/janos/quantizationEngine/io/iopool.cpp -o CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.s

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o.requires:

.PHONY : CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o.requires

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o.provides: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o.requires
	$(MAKE) -f CMakeFiles/../engine.out.dir/build.make CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o.provides.build
.PHONY : CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o.provides

CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o.provides.build: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o


# Object files for target ../engine.out
__/engine_out_OBJECTS = \
"CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o" \
"CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o" \
"CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o" \
"CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o"

# External object files for target ../engine.out
__/engine_out_EXTERNAL_OBJECTS =

../engine.out: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o
../engine.out: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o
../engine.out: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o
../engine.out: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o
../engine.out: CMakeFiles/../engine.out.dir/build.make
../engine.out: CMakeFiles/../engine.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/janos/quantizationEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../engine.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/../engine.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/../engine.out.dir/build: ../engine.out

.PHONY : CMakeFiles/../engine.out.dir/build

CMakeFiles/../engine.out.dir/requires: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/main/main.cpp.o.requires
CMakeFiles/../engine.out.dir/requires: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/network/network.cpp.o.requires
CMakeFiles/../engine.out.dir/requires: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/io.cpp.o.requires
CMakeFiles/../engine.out.dir/requires: CMakeFiles/../engine.out.dir/home/janos/quantizationEngine/io/iopool.cpp.o.requires

.PHONY : CMakeFiles/../engine.out.dir/requires

CMakeFiles/../engine.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/../engine.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/../engine.out.dir/clean

CMakeFiles/../engine.out.dir/depend:
	cd /home/janos/quantizationEngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/janos/quantizationEngine/build /home/janos/quantizationEngine/build /home/janos/quantizationEngine/build /home/janos/quantizationEngine/build /home/janos/quantizationEngine/build/engine.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/../engine.out.dir/depend

