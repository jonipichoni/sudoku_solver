cmake_minimum_required (VERSION 2.6)
project (Sudoku)


# The version number.
set (S_VERSION_MAJOR 1)
set (S_VERSION_MINOR 0)

set( CMAKE_VERBOSE_MAKEFILE on )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

file(GLOB_RECURSE sources 
	src/*.cpp 
	src/*.h)

include_directories("${PROJECT_BINARY_DIR}")

# binary compiling all sources
add_executable(Sudoku_all ${sources})

# Creating dynamic library
add_library(sudoku SHARED ${PROJECT_SOURCE_DIR}/src/sudoku_lib.cpp)

# Binary without the lib sources
add_executable(Sudoku_dll 
	${PROJECT_SOURCE_DIR}/src/main.cpp 
	${PROJECT_SOURCE_DIR}/src/config.h
	${PROJECT_SOURCE_DIR}/src/sudoku_lib.h )


target_compile_options(Sudoku_all PUBLIC -std=c++0x -Wall -O0)

target_compile_options(sudoku PUBLIC -std=c++0x -Wall -O0 -DBUILD_LIB)

target_compile_options(Sudoku_dll PUBLIC -std=c++0x -Wall -O0)

target_link_libraries(Sudoku_dll sudoku)



# if you are building in-source, this is the same as CMAKE_SOURCE_DIR, otherwise 
# this is the top level directory of your build tree 
MESSAGE( STATUS "CMAKE_BINARY_DIR:         " ${CMAKE_BINARY_DIR} )

# if you are building in-source, this is the same as CMAKE_CURRENT_SOURCE_DIR, otherwise this 
# is the directory where the compiled or generated files from the current CMakeLists.txt will go to 
MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR} )

# this is the directory, from which cmake was started, i.e. the top level source directory 
MESSAGE( STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR} )

# this is the directory where the currently processed CMakeLists.txt is located in 
MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )

# contains the full path to the top level directory of your build tree 
MESSAGE( STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )

# contains the full path to the root of your project source directory,
# i.e. to the nearest directory where CMakeLists.txt contains the PROJECT() command 
MESSAGE( STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR} )

# set this variable to specify a common place where CMake should put all executable files
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE( STATUS "EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH} )

# set this variable to specify a common place where CMake should put all libraries 
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE( STATUS "LIBRARY_OUTPUT_PATH:     " ${LIBRARY_OUTPUT_PATH} )

# tell CMake to search first in directories listed in CMAKE_MODULE_PATH
# when you use FIND_PACKAGE() or INCLUDE()
MESSAGE( STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH} )

# this is the complete path of the cmake which runs currently (e.g. /usr/local/bin/cmake) 
MESSAGE( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )

# this is the CMake installation directory 
MESSAGE( STATUS "CMAKE_ROOT: " ${CMAKE_ROOT} )

