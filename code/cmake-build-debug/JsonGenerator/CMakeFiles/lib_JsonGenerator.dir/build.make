# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.1.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\yzn\Documents\GitHub\Json-yzn\code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug

# Include any dependencies generated for this target.
include JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/compiler_depend.make

# Include the progress variables for this target.
include JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/progress.make

# Include the compile flags for this target's objects.
include JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/flags.make

JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/JsonGenerator.cpp.obj: JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/flags.make
JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/JsonGenerator.cpp.obj: JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/includes_CXX.rsp
JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/JsonGenerator.cpp.obj: ../JsonGenerator/JsonGenerator.cpp
JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/JsonGenerator.cpp.obj: JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/JsonGenerator.cpp.obj"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\JsonGenerator && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/JsonGenerator.cpp.obj -MF CMakeFiles\lib_JsonGenerator.dir\JsonGenerator.cpp.obj.d -o CMakeFiles\lib_JsonGenerator.dir\JsonGenerator.cpp.obj -c C:\Users\yzn\Documents\GitHub\Json-yzn\code\JsonGenerator\JsonGenerator.cpp

JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/JsonGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_JsonGenerator.dir/JsonGenerator.cpp.i"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\JsonGenerator && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\yzn\Documents\GitHub\Json-yzn\code\JsonGenerator\JsonGenerator.cpp > CMakeFiles\lib_JsonGenerator.dir\JsonGenerator.cpp.i

JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/JsonGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_JsonGenerator.dir/JsonGenerator.cpp.s"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\JsonGenerator && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\yzn\Documents\GitHub\Json-yzn\code\JsonGenerator\JsonGenerator.cpp -o CMakeFiles\lib_JsonGenerator.dir\JsonGenerator.cpp.s

# Object files for target lib_JsonGenerator
lib_JsonGenerator_OBJECTS = \
"CMakeFiles/lib_JsonGenerator.dir/JsonGenerator.cpp.obj"

# External object files for target lib_JsonGenerator
lib_JsonGenerator_EXTERNAL_OBJECTS =

JsonGenerator/liblib_JsonGenerator.a: JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/JsonGenerator.cpp.obj
JsonGenerator/liblib_JsonGenerator.a: JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/build.make
JsonGenerator/liblib_JsonGenerator.a: JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblib_JsonGenerator.a"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\JsonGenerator && $(CMAKE_COMMAND) -P CMakeFiles\lib_JsonGenerator.dir\cmake_clean_target.cmake
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\JsonGenerator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lib_JsonGenerator.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/build: JsonGenerator/liblib_JsonGenerator.a
.PHONY : JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/build

JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/clean:
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\JsonGenerator && $(CMAKE_COMMAND) -P CMakeFiles\lib_JsonGenerator.dir\cmake_clean.cmake
.PHONY : JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/clean

JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\yzn\Documents\GitHub\Json-yzn\code C:\Users\yzn\Documents\GitHub\Json-yzn\code\JsonGenerator C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\JsonGenerator C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\JsonGenerator\CMakeFiles\lib_JsonGenerator.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : JsonGenerator/CMakeFiles/lib_JsonGenerator.dir/depend
