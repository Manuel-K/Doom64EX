##------------------------------------------------------------------------------
##
## Doom64EX CMake configuration
##
## LICENSE:
##
## Copyright(C) 2016 Zohar Malamant
##
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License
## as published by the Free Software Foundation; either version 2
## of the License, or (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
## 02111-1307, USA.
##

cmake_minimum_required(VERSION 2.8.11)

project(doom64ex C CXX)

##------------------------------------------------------------------------------
## Build Options
##

option(GENERATE_KEXWAD "Generate kex.wad" ON)
option(BUILD_TESTS "Compile unit tests" ON)
option(FORCE_INCLUDE_OPENGL "Include OpenGL without using find_package" OFF)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" "${CMAKE_SOURCE_DIR}/extern")
set(CMAKE_FIND_ROOT_PATH "${CMAKE_PREFIX_PATH}" "${CMAKE_FIND_ROOT_PATH}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(DATA_DIR "${CMAKE_SOURCE_DIR}/data")

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  set(USE_CONAN ON)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup()
else()
  set(USE_CONAN OFF)
endif()

##------------------------------------------------------------------------------
## Compiler Options
##

if(MINGW)
  set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++ -Wl,--subsystem,windows")
endif(MINGW)

##------------------------------------------------------------------------------
## CMake functions
##

function(add_include_directories)
  unset(NEW_INCLUDES)
  foreach (ARG ${ARGN})
    list(APPEND NEW_INCLUDES ${ARG})
  endforeach ()
  set(INCLUDES ${INCLUDES} ${NEW_INCLUDES} PARENT_SCOPE)
endfunction()

function(add_sources PREFIX)
  unset(NEW_SOURCES)
  foreach (ARG ${ARGN})
    list(APPEND NEW_SOURCES "${SOURCE_ROOT_DIR}/${PREFIX}/${ARG}")
  endforeach ()
  set(SOURCES ${SOURCES} ${NEW_SOURCES} PARENT_SCOPE)
  set(INCLUDES ${INCLUDES} "${SOURCE_ROOT_DIR}/${PREFIX}" PARENT_SCOPE)
endfunction()

function(add_link_libraries)
  unset(NEW_LIBRARIES)
  foreach (ARG ${ARGN})
    list(APPEND NEW_LIBRARIES ${ARG})
  endforeach ()
  set(LIBRARIES ${LIBRARIES} ${NEW_LIBRARIES} PARENT_SCOPE)
endfunction()

##------------------------------------------------------------------------------
## Project-wide Dependencies
##

if(BUILD_TESTS)
  find_package(GTest)
endif(BUILD_TESTS)

##------------------------------------------------------------------------------
## Include subprojects
##

add_subdirectory("${CMAKE_SOURCE_DIR}/src/wadtool")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/engine")
