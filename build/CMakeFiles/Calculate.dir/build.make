# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/build"

# Include any dependencies generated for this target.
include CMakeFiles/Calculate.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Calculate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Calculate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Calculate.dir/flags.make

CMakeFiles/Calculate.dir/src/main.cpp.o: CMakeFiles/Calculate.dir/flags.make
CMakeFiles/Calculate.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/Calculate.dir/src/main.cpp.o: CMakeFiles/Calculate.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Calculate.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Calculate.dir/src/main.cpp.o -MF CMakeFiles/Calculate.dir/src/main.cpp.o.d -o CMakeFiles/Calculate.dir/src/main.cpp.o -c "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/src/main.cpp"

CMakeFiles/Calculate.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Calculate.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/src/main.cpp" > CMakeFiles/Calculate.dir/src/main.cpp.i

CMakeFiles/Calculate.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Calculate.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/src/main.cpp" -o CMakeFiles/Calculate.dir/src/main.cpp.s

CMakeFiles/Calculate.dir/api/calculate.cpp.o: CMakeFiles/Calculate.dir/flags.make
CMakeFiles/Calculate.dir/api/calculate.cpp.o: ../api/calculate.cpp
CMakeFiles/Calculate.dir/api/calculate.cpp.o: CMakeFiles/Calculate.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Calculate.dir/api/calculate.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Calculate.dir/api/calculate.cpp.o -MF CMakeFiles/Calculate.dir/api/calculate.cpp.o.d -o CMakeFiles/Calculate.dir/api/calculate.cpp.o -c "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/api/calculate.cpp"

CMakeFiles/Calculate.dir/api/calculate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Calculate.dir/api/calculate.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/api/calculate.cpp" > CMakeFiles/Calculate.dir/api/calculate.cpp.i

CMakeFiles/Calculate.dir/api/calculate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Calculate.dir/api/calculate.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/api/calculate.cpp" -o CMakeFiles/Calculate.dir/api/calculate.cpp.s

# Object files for target Calculate
Calculate_OBJECTS = \
"CMakeFiles/Calculate.dir/src/main.cpp.o" \
"CMakeFiles/Calculate.dir/api/calculate.cpp.o"

# External object files for target Calculate
Calculate_EXTERNAL_OBJECTS =

Calculate: CMakeFiles/Calculate.dir/src/main.cpp.o
Calculate: CMakeFiles/Calculate.dir/api/calculate.cpp.o
Calculate: CMakeFiles/Calculate.dir/build.make
Calculate: /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
Calculate: CMakeFiles/Calculate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Calculate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Calculate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Calculate.dir/build: Calculate
.PHONY : CMakeFiles/Calculate.dir/build

CMakeFiles/Calculate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Calculate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Calculate.dir/clean

CMakeFiles/Calculate.dir/depend:
	cd "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w" "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w" "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/build" "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/build" "/media/lukas/500GB_hdd/programování/C++/programy a aplikace/Calculate_w/build/CMakeFiles/Calculate.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Calculate.dir/depend

