# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tools/eo/eo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tools/eo/eo/build

# Include any dependencies generated for this target.
include src/CMakeFiles/eo.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/eo.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/eo.dir/flags.make

src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o: src/CMakeFiles/eo.dir/flags.make
src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o: ../src/eoFunctorStore.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tools/eo/eo/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o"
	cd /tools/eo/eo/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/eo.dir/eoFunctorStore.cpp.o -c /tools/eo/eo/src/eoFunctorStore.cpp

src/CMakeFiles/eo.dir/eoFunctorStore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eo.dir/eoFunctorStore.cpp.i"
	cd /tools/eo/eo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tools/eo/eo/src/eoFunctorStore.cpp > CMakeFiles/eo.dir/eoFunctorStore.cpp.i

src/CMakeFiles/eo.dir/eoFunctorStore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eo.dir/eoFunctorStore.cpp.s"
	cd /tools/eo/eo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tools/eo/eo/src/eoFunctorStore.cpp -o CMakeFiles/eo.dir/eoFunctorStore.cpp.s

src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o.requires:
.PHONY : src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o.requires

src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o.provides: src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/eo.dir/build.make src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o.provides.build
.PHONY : src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o.provides

src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o.provides.build: src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o
.PHONY : src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o.provides.build

src/CMakeFiles/eo.dir/eoPersistent.cpp.o: src/CMakeFiles/eo.dir/flags.make
src/CMakeFiles/eo.dir/eoPersistent.cpp.o: ../src/eoPersistent.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tools/eo/eo/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/eo.dir/eoPersistent.cpp.o"
	cd /tools/eo/eo/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/eo.dir/eoPersistent.cpp.o -c /tools/eo/eo/src/eoPersistent.cpp

src/CMakeFiles/eo.dir/eoPersistent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eo.dir/eoPersistent.cpp.i"
	cd /tools/eo/eo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tools/eo/eo/src/eoPersistent.cpp > CMakeFiles/eo.dir/eoPersistent.cpp.i

src/CMakeFiles/eo.dir/eoPersistent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eo.dir/eoPersistent.cpp.s"
	cd /tools/eo/eo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tools/eo/eo/src/eoPersistent.cpp -o CMakeFiles/eo.dir/eoPersistent.cpp.s

src/CMakeFiles/eo.dir/eoPersistent.cpp.o.requires:
.PHONY : src/CMakeFiles/eo.dir/eoPersistent.cpp.o.requires

src/CMakeFiles/eo.dir/eoPersistent.cpp.o.provides: src/CMakeFiles/eo.dir/eoPersistent.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/eo.dir/build.make src/CMakeFiles/eo.dir/eoPersistent.cpp.o.provides.build
.PHONY : src/CMakeFiles/eo.dir/eoPersistent.cpp.o.provides

src/CMakeFiles/eo.dir/eoPersistent.cpp.o.provides.build: src/CMakeFiles/eo.dir/eoPersistent.cpp.o
.PHONY : src/CMakeFiles/eo.dir/eoPersistent.cpp.o.provides.build

src/CMakeFiles/eo.dir/eoPrintable.cpp.o: src/CMakeFiles/eo.dir/flags.make
src/CMakeFiles/eo.dir/eoPrintable.cpp.o: ../src/eoPrintable.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tools/eo/eo/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/eo.dir/eoPrintable.cpp.o"
	cd /tools/eo/eo/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/eo.dir/eoPrintable.cpp.o -c /tools/eo/eo/src/eoPrintable.cpp

src/CMakeFiles/eo.dir/eoPrintable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eo.dir/eoPrintable.cpp.i"
	cd /tools/eo/eo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tools/eo/eo/src/eoPrintable.cpp > CMakeFiles/eo.dir/eoPrintable.cpp.i

src/CMakeFiles/eo.dir/eoPrintable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eo.dir/eoPrintable.cpp.s"
	cd /tools/eo/eo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tools/eo/eo/src/eoPrintable.cpp -o CMakeFiles/eo.dir/eoPrintable.cpp.s

src/CMakeFiles/eo.dir/eoPrintable.cpp.o.requires:
.PHONY : src/CMakeFiles/eo.dir/eoPrintable.cpp.o.requires

src/CMakeFiles/eo.dir/eoPrintable.cpp.o.provides: src/CMakeFiles/eo.dir/eoPrintable.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/eo.dir/build.make src/CMakeFiles/eo.dir/eoPrintable.cpp.o.provides.build
.PHONY : src/CMakeFiles/eo.dir/eoPrintable.cpp.o.provides

src/CMakeFiles/eo.dir/eoPrintable.cpp.o.provides.build: src/CMakeFiles/eo.dir/eoPrintable.cpp.o
.PHONY : src/CMakeFiles/eo.dir/eoPrintable.cpp.o.provides.build

src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o: src/CMakeFiles/eo.dir/flags.make
src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o: ../src/eoCtrlCContinue.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tools/eo/eo/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o"
	cd /tools/eo/eo/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o -c /tools/eo/eo/src/eoCtrlCContinue.cpp

src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eo.dir/eoCtrlCContinue.cpp.i"
	cd /tools/eo/eo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tools/eo/eo/src/eoCtrlCContinue.cpp > CMakeFiles/eo.dir/eoCtrlCContinue.cpp.i

src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eo.dir/eoCtrlCContinue.cpp.s"
	cd /tools/eo/eo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tools/eo/eo/src/eoCtrlCContinue.cpp -o CMakeFiles/eo.dir/eoCtrlCContinue.cpp.s

src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o.requires:
.PHONY : src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o.requires

src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o.provides: src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/eo.dir/build.make src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o.provides.build
.PHONY : src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o.provides

src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o.provides.build: src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o
.PHONY : src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o.provides.build

src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o: src/CMakeFiles/eo.dir/flags.make
src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o: ../src/eoScalarFitnessAssembled.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tools/eo/eo/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o"
	cd /tools/eo/eo/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o -c /tools/eo/eo/src/eoScalarFitnessAssembled.cpp

src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.i"
	cd /tools/eo/eo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tools/eo/eo/src/eoScalarFitnessAssembled.cpp > CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.i

src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.s"
	cd /tools/eo/eo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tools/eo/eo/src/eoScalarFitnessAssembled.cpp -o CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.s

src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o.requires:
.PHONY : src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o.requires

src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o.provides: src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/eo.dir/build.make src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o.provides.build
.PHONY : src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o.provides

src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o.provides.build: src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o
.PHONY : src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o.provides.build

src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o: src/CMakeFiles/eo.dir/flags.make
src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o: ../src/eoSIGContinue.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tools/eo/eo/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o"
	cd /tools/eo/eo/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/eo.dir/eoSIGContinue.cpp.o -c /tools/eo/eo/src/eoSIGContinue.cpp

src/CMakeFiles/eo.dir/eoSIGContinue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eo.dir/eoSIGContinue.cpp.i"
	cd /tools/eo/eo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tools/eo/eo/src/eoSIGContinue.cpp > CMakeFiles/eo.dir/eoSIGContinue.cpp.i

src/CMakeFiles/eo.dir/eoSIGContinue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eo.dir/eoSIGContinue.cpp.s"
	cd /tools/eo/eo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tools/eo/eo/src/eoSIGContinue.cpp -o CMakeFiles/eo.dir/eoSIGContinue.cpp.s

src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o.requires:
.PHONY : src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o.requires

src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o.provides: src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/eo.dir/build.make src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o.provides.build
.PHONY : src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o.provides

src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o.provides.build: src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o
.PHONY : src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o.provides.build

# Object files for target eo
eo_OBJECTS = \
"CMakeFiles/eo.dir/eoFunctorStore.cpp.o" \
"CMakeFiles/eo.dir/eoPersistent.cpp.o" \
"CMakeFiles/eo.dir/eoPrintable.cpp.o" \
"CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o" \
"CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o" \
"CMakeFiles/eo.dir/eoSIGContinue.cpp.o"

# External object files for target eo
eo_EXTERNAL_OBJECTS =

lib/libeo.a: src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o
lib/libeo.a: src/CMakeFiles/eo.dir/eoPersistent.cpp.o
lib/libeo.a: src/CMakeFiles/eo.dir/eoPrintable.cpp.o
lib/libeo.a: src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o
lib/libeo.a: src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o
lib/libeo.a: src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o
lib/libeo.a: src/CMakeFiles/eo.dir/build.make
lib/libeo.a: src/CMakeFiles/eo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../lib/libeo.a"
	cd /tools/eo/eo/build/src && $(CMAKE_COMMAND) -P CMakeFiles/eo.dir/cmake_clean_target.cmake
	cd /tools/eo/eo/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/eo.dir/build: lib/libeo.a
.PHONY : src/CMakeFiles/eo.dir/build

src/CMakeFiles/eo.dir/requires: src/CMakeFiles/eo.dir/eoFunctorStore.cpp.o.requires
src/CMakeFiles/eo.dir/requires: src/CMakeFiles/eo.dir/eoPersistent.cpp.o.requires
src/CMakeFiles/eo.dir/requires: src/CMakeFiles/eo.dir/eoPrintable.cpp.o.requires
src/CMakeFiles/eo.dir/requires: src/CMakeFiles/eo.dir/eoCtrlCContinue.cpp.o.requires
src/CMakeFiles/eo.dir/requires: src/CMakeFiles/eo.dir/eoScalarFitnessAssembled.cpp.o.requires
src/CMakeFiles/eo.dir/requires: src/CMakeFiles/eo.dir/eoSIGContinue.cpp.o.requires
.PHONY : src/CMakeFiles/eo.dir/requires

src/CMakeFiles/eo.dir/clean:
	cd /tools/eo/eo/build/src && $(CMAKE_COMMAND) -P CMakeFiles/eo.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/eo.dir/clean

src/CMakeFiles/eo.dir/depend:
	cd /tools/eo/eo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tools/eo/eo /tools/eo/eo/src /tools/eo/eo/build /tools/eo/eo/build/src /tools/eo/eo/build/src/CMakeFiles/eo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/eo.dir/depend

