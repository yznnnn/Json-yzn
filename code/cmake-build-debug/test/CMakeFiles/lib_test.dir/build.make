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
include test/CMakeFiles/lib_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/lib_test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/lib_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/lib_test.dir/flags.make

test/CMakeFiles/lib_test.dir/TestJsonGenerator.cpp.obj: test/CMakeFiles/lib_test.dir/flags.make
test/CMakeFiles/lib_test.dir/TestJsonGenerator.cpp.obj: test/CMakeFiles/lib_test.dir/includes_CXX.rsp
test/CMakeFiles/lib_test.dir/TestJsonGenerator.cpp.obj: ../test/TestJsonGenerator.cpp
test/CMakeFiles/lib_test.dir/TestJsonGenerator.cpp.obj: test/CMakeFiles/lib_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/lib_test.dir/TestJsonGenerator.cpp.obj"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/lib_test.dir/TestJsonGenerator.cpp.obj -MF CMakeFiles\lib_test.dir\TestJsonGenerator.cpp.obj.d -o CMakeFiles\lib_test.dir\TestJsonGenerator.cpp.obj -c C:\Users\yzn\Documents\GitHub\Json-yzn\code\test\TestJsonGenerator.cpp

test/CMakeFiles/lib_test.dir/TestJsonGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_test.dir/TestJsonGenerator.cpp.i"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\yzn\Documents\GitHub\Json-yzn\code\test\TestJsonGenerator.cpp > CMakeFiles\lib_test.dir\TestJsonGenerator.cpp.i

test/CMakeFiles/lib_test.dir/TestJsonGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_test.dir/TestJsonGenerator.cpp.s"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\yzn\Documents\GitHub\Json-yzn\code\test\TestJsonGenerator.cpp -o CMakeFiles\lib_test.dir\TestJsonGenerator.cpp.s

test/CMakeFiles/lib_test.dir/TestJsonNode.cpp.obj: test/CMakeFiles/lib_test.dir/flags.make
test/CMakeFiles/lib_test.dir/TestJsonNode.cpp.obj: test/CMakeFiles/lib_test.dir/includes_CXX.rsp
test/CMakeFiles/lib_test.dir/TestJsonNode.cpp.obj: ../test/TestJsonNode.cpp
test/CMakeFiles/lib_test.dir/TestJsonNode.cpp.obj: test/CMakeFiles/lib_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/lib_test.dir/TestJsonNode.cpp.obj"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/lib_test.dir/TestJsonNode.cpp.obj -MF CMakeFiles\lib_test.dir\TestJsonNode.cpp.obj.d -o CMakeFiles\lib_test.dir\TestJsonNode.cpp.obj -c C:\Users\yzn\Documents\GitHub\Json-yzn\code\test\TestJsonNode.cpp

test/CMakeFiles/lib_test.dir/TestJsonNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_test.dir/TestJsonNode.cpp.i"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\yzn\Documents\GitHub\Json-yzn\code\test\TestJsonNode.cpp > CMakeFiles\lib_test.dir\TestJsonNode.cpp.i

test/CMakeFiles/lib_test.dir/TestJsonNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_test.dir/TestJsonNode.cpp.s"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\yzn\Documents\GitHub\Json-yzn\code\test\TestJsonNode.cpp -o CMakeFiles\lib_test.dir\TestJsonNode.cpp.s

test/CMakeFiles/lib_test.dir/TestJsonParser.cpp.obj: test/CMakeFiles/lib_test.dir/flags.make
test/CMakeFiles/lib_test.dir/TestJsonParser.cpp.obj: test/CMakeFiles/lib_test.dir/includes_CXX.rsp
test/CMakeFiles/lib_test.dir/TestJsonParser.cpp.obj: ../test/TestJsonParser.cpp
test/CMakeFiles/lib_test.dir/TestJsonParser.cpp.obj: test/CMakeFiles/lib_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/CMakeFiles/lib_test.dir/TestJsonParser.cpp.obj"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/lib_test.dir/TestJsonParser.cpp.obj -MF CMakeFiles\lib_test.dir\TestJsonParser.cpp.obj.d -o CMakeFiles\lib_test.dir\TestJsonParser.cpp.obj -c C:\Users\yzn\Documents\GitHub\Json-yzn\code\test\TestJsonParser.cpp

test/CMakeFiles/lib_test.dir/TestJsonParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_test.dir/TestJsonParser.cpp.i"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\yzn\Documents\GitHub\Json-yzn\code\test\TestJsonParser.cpp > CMakeFiles\lib_test.dir\TestJsonParser.cpp.i

test/CMakeFiles/lib_test.dir/TestJsonParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_test.dir/TestJsonParser.cpp.s"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\yzn\Documents\GitHub\Json-yzn\code\test\TestJsonParser.cpp -o CMakeFiles\lib_test.dir\TestJsonParser.cpp.s

test/CMakeFiles/lib_test.dir/test.cpp.obj: test/CMakeFiles/lib_test.dir/flags.make
test/CMakeFiles/lib_test.dir/test.cpp.obj: test/CMakeFiles/lib_test.dir/includes_CXX.rsp
test/CMakeFiles/lib_test.dir/test.cpp.obj: ../test/test.cpp
test/CMakeFiles/lib_test.dir/test.cpp.obj: test/CMakeFiles/lib_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object test/CMakeFiles/lib_test.dir/test.cpp.obj"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/lib_test.dir/test.cpp.obj -MF CMakeFiles\lib_test.dir\test.cpp.obj.d -o CMakeFiles\lib_test.dir\test.cpp.obj -c C:\Users\yzn\Documents\GitHub\Json-yzn\code\test\test.cpp

test/CMakeFiles/lib_test.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_test.dir/test.cpp.i"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\yzn\Documents\GitHub\Json-yzn\code\test\test.cpp > CMakeFiles\lib_test.dir\test.cpp.i

test/CMakeFiles/lib_test.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_test.dir/test.cpp.s"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\yzn\Documents\GitHub\Json-yzn\code\test\test.cpp -o CMakeFiles\lib_test.dir\test.cpp.s

# Object files for target lib_test
lib_test_OBJECTS = \
"CMakeFiles/lib_test.dir/TestJsonGenerator.cpp.obj" \
"CMakeFiles/lib_test.dir/TestJsonNode.cpp.obj" \
"CMakeFiles/lib_test.dir/TestJsonParser.cpp.obj" \
"CMakeFiles/lib_test.dir/test.cpp.obj"

# External object files for target lib_test
lib_test_EXTERNAL_OBJECTS =

test/liblib_test.a: test/CMakeFiles/lib_test.dir/TestJsonGenerator.cpp.obj
test/liblib_test.a: test/CMakeFiles/lib_test.dir/TestJsonNode.cpp.obj
test/liblib_test.a: test/CMakeFiles/lib_test.dir/TestJsonParser.cpp.obj
test/liblib_test.a: test/CMakeFiles/lib_test.dir/test.cpp.obj
test/liblib_test.a: test/CMakeFiles/lib_test.dir/build.make
test/liblib_test.a: test/CMakeFiles/lib_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library liblib_test.a"
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && $(CMAKE_COMMAND) -P CMakeFiles\lib_test.dir\cmake_clean_target.cmake
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lib_test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/lib_test.dir/build: test/liblib_test.a
.PHONY : test/CMakeFiles/lib_test.dir/build

test/CMakeFiles/lib_test.dir/clean:
	cd /d C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test && $(CMAKE_COMMAND) -P CMakeFiles\lib_test.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/lib_test.dir/clean

test/CMakeFiles/lib_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\yzn\Documents\GitHub\Json-yzn\code C:\Users\yzn\Documents\GitHub\Json-yzn\code\test C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test C:\Users\yzn\Documents\GitHub\Json-yzn\code\cmake-build-debug\test\CMakeFiles\lib_test.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/lib_test.dir/depend

