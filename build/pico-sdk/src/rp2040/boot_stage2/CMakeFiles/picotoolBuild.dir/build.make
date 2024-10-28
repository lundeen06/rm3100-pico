# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build

# Utility rule file for picotoolBuild.

# Include any custom commands dependencies for this target.
include pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild.dir/compiler_depend.make

# Include the progress variables for this target.
include pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild.dir/progress.make

pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild: pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild-complete

pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild-complete: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-install
pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild-complete: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-mkdir
pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild-complete: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-download
pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild-complete: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-update
pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild-complete: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-patch
pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild-complete: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-configure
pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild-complete: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-build
pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild-complete: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-install
pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild-complete: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-test
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'picotoolBuild'"
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E make_directory /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2/CMakeFiles
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E touch /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild-complete
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E touch /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-done

pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-build: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing build step for 'picotoolBuild'"
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/_deps/picotool-build && $(MAKE)

pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-configure: pico-sdk/src/rp2040/boot_stage2/picotool/tmp/picotoolBuild-cfgcmd.txt
pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-configure: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Performing configure step for 'picotoolBuild'"
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/_deps/picotool-build && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake --no-warn-unused-cli -DCMAKE_MAKE_PROGRAM:FILEPATH=/usr/bin/make -DPICO_SDK_PATH:FILEPATH=/Users/lundeencahilly/pico-sdk -DPICOTOOL_NO_LIBUSB=1 -DPICOTOOL_FLAT_INSTALL=1 -DCMAKE_INSTALL_PREFIX=/Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/_deps -DCMAKE_RULE_MESSAGES=OFF -DCMAKE_INSTALL_MESSAGE=NEVER "-GUnix Makefiles" -S /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/_deps/picotool-src -B /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/_deps/picotool-build
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/_deps/picotool-build && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E touch /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-configure

pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-download: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-source_dirinfo.txt
pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-download: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "No download step for 'picotoolBuild'"
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E echo_append
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E touch /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-download

pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-install: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-build
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Performing install step for 'picotoolBuild'"
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/_deps/picotool-build && $(MAKE) install

pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'picotoolBuild'"
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -Dcfgdir= -P /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2/picotool/tmp/picotoolBuild-mkdirs.cmake
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E touch /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-mkdir

pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-patch: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-patch-info.txt
pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-patch: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-update
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'picotoolBuild'"
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E echo_append
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E touch /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-patch

pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-test: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-install
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Performing test step for 'picotoolBuild'"
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/_deps/picotool-build && /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/_deps/picotool/picotool version 2.0.0
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/_deps/picotool-build && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E touch /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-test

pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-update: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-update-info.txt
pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-update: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-download
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "No update step for 'picotoolBuild'"
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E echo_append
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 && /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E touch /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-update

picotoolBuild: pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild
picotoolBuild: pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild-complete
picotoolBuild: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-build
picotoolBuild: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-configure
picotoolBuild: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-download
picotoolBuild: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-install
picotoolBuild: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-mkdir
picotoolBuild: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-patch
picotoolBuild: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-test
picotoolBuild: pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/picotoolBuild-update
picotoolBuild: pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild.dir/build.make
.PHONY : picotoolBuild

# Rule to build all files generated by this target.
pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild.dir/build: picotoolBuild
.PHONY : pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild.dir/build

pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild.dir/clean:
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 && $(CMAKE_COMMAND) -P CMakeFiles/picotoolBuild.dir/cmake_clean.cmake
.PHONY : pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild.dir/clean

pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild.dir/depend:
	cd /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico /Users/lundeencahilly/pico-sdk/src/rp2040/boot_stage2 /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2 /Users/lundeencahilly/Desktop/github/0-SSI/rm3100-pico/build/pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : pico-sdk/src/rp2040/boot_stage2/CMakeFiles/picotoolBuild.dir/depend

