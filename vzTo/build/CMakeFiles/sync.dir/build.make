# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/baskin/icub-friends/icub-pusher/vzTo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/baskin/icub-friends/icub-pusher/vzTo/build

# Include any dependencies generated for this target.
include CMakeFiles/sync.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sync.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sync.dir/flags.make

CMakeFiles/sync.dir/sync.cpp.o: CMakeFiles/sync.dir/flags.make
CMakeFiles/sync.dir/sync.cpp.o: ../sync.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/baskin/icub-friends/icub-pusher/vzTo/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sync.dir/sync.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sync.dir/sync.cpp.o -c /home/baskin/icub-friends/icub-pusher/vzTo/sync.cpp

CMakeFiles/sync.dir/sync.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sync.dir/sync.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/baskin/icub-friends/icub-pusher/vzTo/sync.cpp > CMakeFiles/sync.dir/sync.cpp.i

CMakeFiles/sync.dir/sync.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sync.dir/sync.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/baskin/icub-friends/icub-pusher/vzTo/sync.cpp -o CMakeFiles/sync.dir/sync.cpp.s

CMakeFiles/sync.dir/sync.cpp.o.requires:
.PHONY : CMakeFiles/sync.dir/sync.cpp.o.requires

CMakeFiles/sync.dir/sync.cpp.o.provides: CMakeFiles/sync.dir/sync.cpp.o.requires
	$(MAKE) -f CMakeFiles/sync.dir/build.make CMakeFiles/sync.dir/sync.cpp.o.provides.build
.PHONY : CMakeFiles/sync.dir/sync.cpp.o.provides

CMakeFiles/sync.dir/sync.cpp.o.provides.build: CMakeFiles/sync.dir/sync.cpp.o

# Object files for target sync
sync_OBJECTS = \
"CMakeFiles/sync.dir/sync.cpp.o"

# External object files for target sync
sync_EXTERNAL_OBJECTS =

sync: CMakeFiles/sync.dir/sync.cpp.o
sync: CMakeFiles/sync.dir/build.make
sync: /usr/lib/x86_64-linux-gnu/libYARP_OS.so.2.3.66
sync: /usr/lib/x86_64-linux-gnu/libYARP_sig.so.2.3.66
sync: /usr/lib/x86_64-linux-gnu/libYARP_math.so.2.3.66
sync: /usr/lib/x86_64-linux-gnu/libYARP_dev.so.2.3.66
sync: /usr/lib/x86_64-linux-gnu/libYARP_init.so.2.3.66
sync: /usr/lib/x86_64-linux-gnu/libYARP_name.so.2.3.66
sync: /usr/lib/x86_64-linux-gnu/libYARP_sig.so.2.3.66
sync: /usr/lib/x86_64-linux-gnu/libYARP_OS.so.2.3.66
sync: CMakeFiles/sync.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable sync"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sync.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sync.dir/build: sync
.PHONY : CMakeFiles/sync.dir/build

CMakeFiles/sync.dir/requires: CMakeFiles/sync.dir/sync.cpp.o.requires
.PHONY : CMakeFiles/sync.dir/requires

CMakeFiles/sync.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sync.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sync.dir/clean

CMakeFiles/sync.dir/depend:
	cd /home/baskin/icub-friends/icub-pusher/vzTo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/baskin/icub-friends/icub-pusher/vzTo /home/baskin/icub-friends/icub-pusher/vzTo /home/baskin/icub-friends/icub-pusher/vzTo/build /home/baskin/icub-friends/icub-pusher/vzTo/build /home/baskin/icub-friends/icub-pusher/vzTo/build/CMakeFiles/sync.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sync.dir/depend

