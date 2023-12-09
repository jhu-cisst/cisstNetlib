#
# Author(s):  Anton Deguet
# Created on: 2012-12-09
#
# (C) Copyright 2012-2023 Johns Hopkins University (JHU), All Rights Reserved.
#

# some older versions of CMake don't handle external packages properly
cmake_minimum_required(VERSION 3.10)

if (UNIX)
  find_program (LSB_RELEASE_EXEC lsb_release)
  execute_process(COMMAND ${LSB_RELEASE_EXEC} -is
                  OUTPUT_VARIABLE LSB_RELEASE_ID
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND ${LSB_RELEASE_EXEC} -rs
                  OUTPUT_VARIABLE LSB_RELEASE_RELEASE
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  if ("${LSB_RELEASE_ID}" STREQUAL "Ubuntu" AND "${LSB_RELEASE_RELEASE}" STREQUAL "22.04")
    set (CMAKE_Fortran_COMPILER "gfortran-9")
  endif ()
endif (UNIX)

# Auto detect if Fortran compiler has been installed
if (NOT cisstNetlib_LANGUAGE)
  enable_language (Fortran OPTIONAL)
  if (CMAKE_Fortran_COMPILER_WORKS)
    set (cisstNetlib_LANGUAGE "Fortran" CACHE STRING "C or Fortran \(exact match\)" FORCE)
  else ()
    set (cisstNetlib_LANGUAGE "C" CACHE STRING "C or Fortran \(exact match\)" FORCE)
  endif ()
endif ()


# --- determine language, C or Fortran
set (_languageIsValid OFF)
if ("${cisstNetlib_LANGUAGE}" STREQUAL "C")
  set (_languageIsValid ON)
else ("${cisstNetlib_LANGUAGE}" STREQUAL "C")
  if ("${cisstNetlib_LANGUAGE}" STREQUAL "Fortran")
    set (_languageIsValid ON)
  endif ("${cisstNetlib_LANGUAGE}" STREQUAL "Fortran")
endif ("${cisstNetlib_LANGUAGE}" STREQUAL "C")

if (NOT ${_languageIsValid})
  message (FATAL_ERROR "cisstNetlib_LANGUAGE must be either \"C\" or \"Fortran\"")
endif (NOT ${_languageIsValid})

# --- cisstNetlib configuration
if ("${cisstNetlib_LANGUAGE}" STREQUAL "Fortran")
  set (cisstNetlib_LANGUAGES "Fortran;C")
else ()
  set (cisstNetlib_LANGUAGES "C")
endif ()

project (cisstNetlib LANGUAGES ${cisstNetlib_LANGUAGES} VERSION 3.1.0)

# --- determine architecture
if (APPLE)
  set (cisstNetlib_ARCHITECTURE "universal")
else (APPLE)
  if (WIN32)
    if (CMAKE_CL_64)
      set (cisstNetlib_ARCHITECTURE "x86_64")
    else (CMAKE_CL_64)
      set (cisstNetlib_ARCHITECTURE "i686")
    endif (CMAKE_CL_64)
  else (WIN32)
    # we assume Linux
    if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
      set (cisstNetlib_ARCHITECTURE "x86_64")
    else ()
      set (cisstNetlib_ARCHITECTURE "i686")
    endif ()
    # end of Linux case
  endif (WIN32)
endif (APPLE)

# --- now, download proper lapack
if ("${cisstNetlib_LANGUAGE}" STREQUAL "C")
  set (cisstNetlib_C_BASED 1)
  set (cisstNetlib_FORTRAN_BASED 0)
else ("${cisstNetlib_LANGUAGE}" STREQUAL "C")
  set (cisstNetlib_C_BASED 0)
  set (cisstNetlib_FORTRAN_BASED 1)
endif ("${cisstNetlib_LANGUAGE}" STREQUAL "C")

set (cisstNetlib_VERSION ${cisstNetlib_VERSION_MAJOR}.${cisstNetlib_VERSION_MINOR}.${cisstNetlib_VERSION_PATCH})

if (NOT WIN32)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  set (CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fPIC")
endif (NOT WIN32)

# --- set path for generated libraries
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

# --- get and compile lapack
include (ExternalProject)

set (cisstNetlib_EXTERNAL_NAME cisstNetlib_${cisstNetlib_LANGUAGE})
set (cisstNetlib_EXTERNAL_PREFIX cisstNetlibLapack)

if (cisstNetlib_C_BASED)
  ExternalProject_Add (
    ${cisstNetlib_EXTERNAL_NAME}
    PREFIX ${cisstNetlib_EXTERNAL_PREFIX}
    GIT_REPOSITORY "https://github.com/jhu-cisst-external/clapack"
    GIT_TAG "main"
    CMAKE_CACHE_ARGS
    -DBUILD_SINGLE:BOOL=OFF
    -DBUILD_COMPLEX:BOOL=OFF
    -DBUILD_COMPLEX16:BOOL=OFF
    -DCMAKE_OSX_ARCHITECTURES:STRING=${CMAKE_OSX_ARCHITECTURES}
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
    -DCMAKE_Fortran_COMPILER:STRING=${CMAKE_Fortran_COMPILER}
    -DCMAKE_Fortran_FLAGS:STRING=${CMAKE_Fortran_FLAGS}
    -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
    -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
    -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    INSTALL_COMMAND ""
    )

else (cisstNetlib_C_BASED)
  set (cisstNetlib_LAPACK_URL "https://github.com/Reference-LAPACK/lapack/archive/refs/tags/v3.10.1.tar.gz")
  set (cisstNetlib_LAPACK_URL_MD5 722407217a080a0012ae3d6913fb8008)
  # older MD5 if needed
  # 3.5.0 set (cisstNetlib_LAPACK_URL_MD5 b1d3e3e425b2e44a06760ff173104bdf)
  # 3.4.2 set (cisstNetlib_LAPACK_URL_MD5 61bf1a8a4469d4bdb7604f5897179478)
  ExternalProject_Add (
    ${cisstNetlib_EXTERNAL_NAME}
    PREFIX ${cisstNetlib_EXTERNAL_PREFIX}
    URL ${cisstNetlib_LAPACK_URL}
    URL_MD5 ${cisstNetlib_LAPACK_URL_MD5}
    CMAKE_CACHE_ARGS
    -DBUILD_SINGLE:BOOL=OFF
    -DBUILD_COMPLEX:BOOL=OFF
    -DBUILD_COMPLEX16:BOOL=OFF
    -DCMAKE_OSX_ARCHITECTURES:STRING=${CMAKE_OSX_ARCHITECTURES}
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
    -DCMAKE_Fortran_COMPILER:STRING=${CMAKE_Fortran_COMPILER}
    -DCMAKE_Fortran_FLAGS:STRING=${CMAKE_Fortran_FLAGS}
    -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
    -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
    -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    INSTALL_COMMAND ""
    )
endif (cisstNetlib_C_BASED)


# --- figure out where the external project has compiled its libraries
set (cisstNetlib_LAPACK_ROOT "${CMAKE_CURRENT_BINARY_DIR}/${cisstNetlib_EXTERNAL_PREFIX}")
set (cisstNetlib_LAPACK_BUILD_DIR "${cisstNetlib_LAPACK_ROOT}/src/${cisstNetlib_EXTERNAL_NAME}-build")

# --- include directories for f2c code not part of clapack
if (cisstNetlib_C_BASED)
  include_directories ("${cisstNetlib_LAPACK_ROOT}/src/${cisstNetlib_EXTERNAL_NAME}/F2CLIBS/libf2c"
                       "${cisstNetlib_LAPACK_ROOT}/src/${cisstNetlib_EXTERNAL_NAME}/INCLUDE")
endif (cisstNetlib_C_BASED)

# --- compile extra numerical routines
add_subdirectory (hanson-haskell)
add_dependencies (cisstNetlib_hanson_haskell cisstNetlib_${cisstNetlib_LANGUAGE})

add_subdirectory (lawson-hanson)
add_dependencies (cisstNetlib_lawson_hanson cisstNetlib_${cisstNetlib_LANGUAGE})

# --- compile c wrappers to hide all f2c references and typedefs
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include
                     ${CMAKE_CURRENT_BINARY_DIR}/include
                     ${CMAKE_CURRENT_SOURCE_DIR})

# should really read, look into f2c.h to figure which one it is
if (cisstNetlib_C_BASED)
  set (cisstNetlib_INTEGER "long int")
  set (cisstNetlib_DOUBLE "double")
else (cisstNetlib_C_BASED)
  set (cisstNetlib_INTEGER "int")
  set (cisstNetlib_DOUBLE "double")
endif (cisstNetlib_C_BASED)

configure_file (cisstNetlib.h.in "${CMAKE_CURRENT_BINARY_DIR}/include/cisstNetlib.h")
configure_file (cisstNetlib-types.h.in "${CMAKE_CURRENT_BINARY_DIR}/include/cisstNetlib/cisstNetlib-types.h")
install (FILES "${CMAKE_CURRENT_BINARY_DIR}/include/cisstNetlib.h"
         DESTINATION "include/")
install (FILES "${CMAKE_CURRENT_BINARY_DIR}/include/cisstNetlib/cisstNetlib-types.h"
               "${CMAKE_CURRENT_SOURCE_DIR}/include/cisstNetlib/cisstNetlib-lapack.h"
               "${CMAKE_CURRENT_SOURCE_DIR}/include/cisstNetlib/cisstNetlib-hanson-haskell.h"
               "${CMAKE_CURRENT_SOURCE_DIR}/include/cisstNetlib/cisstNetlib-lawson-hanson.h"
         DESTINATION "include/cisstNetlib/")

add_subdirectory (cisstNetlib-wrappers)
add_dependencies (cisstNetlib cisstNetlib_${cisstNetlib_LANGUAGE})

# --- do we need the "Release"/"Debug" suffix to find libraries
if (WIN32)
  set (LIB_SUBDIR "/\${CMAKE_INSTALL_CONFIG_NAME}/")
else (WIN32)
  set (LIB_SUBDIR "/")
endif (WIN32)

if (cisstNetlib_C_BASED)
  # --- C - find and install all libraries with new names, also copy in current binary so we can use local build as an install tree
  set (cisstNetlib_lapack_lib "${cisstNetlib_LAPACK_BUILD_DIR}/SRC${LIB_SUBDIR}${CMAKE_STATIC_LIBRARY_PREFIX}lapack${CMAKE_STATIC_LIBRARY_SUFFIX}")
  set (newFileName "${CMAKE_STATIC_LIBRARY_PREFIX}cisstNetlib_lapack${CMAKE_STATIC_LIBRARY_SUFFIX}")
  install (FILES "${cisstNetlib_lapack_lib}"
           DESTINATION "lib"
           RENAME "${newFileName}")

  set (cisstNetlib_blas_lib "${cisstNetlib_LAPACK_BUILD_DIR}/BLAS/SRC${LIB_SUBDIR}${CMAKE_STATIC_LIBRARY_PREFIX}blas${CMAKE_STATIC_LIBRARY_SUFFIX}")
  set (newFileName "${CMAKE_STATIC_LIBRARY_PREFIX}cisstNetlib_blas${CMAKE_STATIC_LIBRARY_SUFFIX}")
  install (FILES "${cisstNetlib_blas_lib}"
           DESTINATION "lib"
           RENAME "${newFileName}")

  # - note: for we don't know what reason the f2c has a static prefic "lib" in F2CLIBS/libf2c/CMakeLists.txt
  set (cisstNetlib_f2c_lib "${cisstNetlib_LAPACK_BUILD_DIR}/F2CLIBS/libf2c${LIB_SUBDIR}libf2c${CMAKE_STATIC_LIBRARY_SUFFIX}")
  set (newFileName "${CMAKE_STATIC_LIBRARY_PREFIX}cisstNetlib_f2c${CMAKE_STATIC_LIBRARY_SUFFIX}")
  install (FILES "${cisstNetlib_f2c_lib}"
           DESTINATION "lib"
           RENAME "${newFileName}")

else (cisstNetlib_C_BASED)

  # --- Fortran - find and install all libraries with new names
  set (cisstNetlib_lapack_lib "${cisstNetlib_LAPACK_BUILD_DIR}/lib${LIB_SUBDIR}${CMAKE_STATIC_LIBRARY_PREFIX}lapack${CMAKE_STATIC_LIBRARY_SUFFIX}")
  set (newFileName "${CMAKE_STATIC_LIBRARY_PREFIX}cisstNetlib_lapack${CMAKE_STATIC_LIBRARY_SUFFIX}")
  install (FILES "${cisstNetlib_lapack_lib}"
           DESTINATION "lib"
           RENAME "${newFileName}")

  set (cisstNetlib_blas_lib "${cisstNetlib_LAPACK_BUILD_DIR}/lib${LIB_SUBDIR}${CMAKE_STATIC_LIBRARY_PREFIX}blas${CMAKE_STATIC_LIBRARY_SUFFIX}")
  set (newFileName "${CMAKE_STATIC_LIBRARY_PREFIX}cisstNetlib_blas${CMAKE_STATIC_LIBRARY_SUFFIX}")
  install (FILES "${cisstNetlib_blas_lib}"
           DESTINATION "lib"
           RENAME "${newFileName}")

  # hard coded to find gfortran runtime library
  # use name of static library to find path to shared library :-)
  execute_process (COMMAND ${CMAKE_Fortran_COMPILER} -print-file-name=libgfortran.a
                   OUTPUT_VARIABLE cisstNetlib_fortran_runtime_static
                   OUTPUT_STRIP_TRAILING_WHITESPACE)
  # remove the filename to get the directory only
  get_filename_component (cisstNetlib_fortran_runtime_directory ${cisstNetlib_fortran_runtime_static} PATH)
  # now find the dynamic library ...
  find_library (cisstNetlib_fortran_runtime_link gfortran HINTS ${cisstNetlib_fortran_runtime_directory})
  # the result might be a link, find the real path
  get_filename_component (cisstNetlib_fortran_runtime ${cisstNetlib_fortran_runtime_link} REALPATH)
  message ("Using fortran runtime library: ${cisstNetlib_fortran_runtime}")
  install (FILES "${cisstNetlib_fortran_runtime}"
           DESTINATION "lib"
           RENAME "${CMAKE_SHARED_LIBRARY_PREFIX}cisstNetlib_gfortran${CMAKE_SHARED_LIBRARY_SUFFIX}")
  execute_process (COMMAND ${CMAKE_Fortran_COMPILER} -print-file-name=libgcc.a
                   OUTPUT_VARIABLE cisstNetlib_gcc_runtime
                   OUTPUT_STRIP_TRAILING_WHITESPACE)
  message ("Using gcc runtime library: ${cisstNetlib_gcc_runtime}")
  install (FILES "${cisstNetlib_gcc_runtime}"
           DESTINATION "lib"
           RENAME "${CMAKE_STATIC_LIBRARY_PREFIX}cisstNetlib_gcc${CMAKE_STATIC_LIBRARY_SUFFIX}")
  execute_process (COMMAND ${CMAKE_Fortran_COMPILER} -print-file-name=libquadmath.a
                   OUTPUT_VARIABLE cisstNetlib_quadmath
                   OUTPUT_STRIP_TRAILING_WHITESPACE)
  message ("Using quadmath library: ${cisstNetlib_quadmath}")
  install (FILES "${cisstNetlib_quadmath}"
           DESTINATION "lib"
           RENAME "${CMAKE_STATIC_LIBRARY_PREFIX}cisstNetlib_quadmath${CMAKE_STATIC_LIBRARY_SUFFIX}")

endif (cisstNetlib_C_BASED)

# -- configure CMake config file for cisstnetlib
if (cisstNetlib_C_BASED)
  set (cisstNetlib_LIBRARIES_SHORT_NAMES
       cisstNetlib
       cisstNetlib_hanson_haskell
       cisstNetlib_lawson_hanson
       cisstNetlib_lapack
       cisstNetlib_blas
       cisstNetlib_f2c)
else (cisstNetlib_C_BASED)
  set (cisstNetlib_LIBRARIES_SHORT_NAMES
       cisstNetlib
       cisstNetlib_hanson_haskell
       cisstNetlib_lawson_hanson
       cisstNetlib_lapack
       cisstNetlib_blas
       cisstNetlib_gfortran
       cisstNetlib_quadmath
       cisstNetlib_gcc)
endif (cisstNetlib_C_BASED)

configure_file (CisstNetlibConfig.cmake.in
                "${CMAKE_CURRENT_BINARY_DIR}/CisstNetlibConfig.cmake"
                @ONLY)
install (FILES "${CMAKE_CURRENT_BINARY_DIR}/CisstNetlibConfig.cmake"
         DESTINATION "share/cisstNetlib")

# --- prepare installer, tgz on unix systems
set (CPACK_GENERATOR "TGZ;ZIP;DEB")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "JHU CISST binary distribution of netlib.org routines (${cisstNetlib_LANGUAGE} version)")
set (CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}-${cisstNetlib_ARCHITECTURE}")
set (CPACK_PACKAGE_NAME "cisstNetlib-${cisstNetlib_LANGUAGE}")
set (CPACK_PACKAGE_VENDOR "JHU")
set (CPACK_PACKAGE_VERSION "3.1.0")
set (CPACK_PACKAGE_VERSION_MAJOR "3")
set (CPACK_PACKAGE_VERSION_MINOR "1")
set (CPACK_PACKAGE_VERSION_PATCH "0")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "anton.deguet@jhu.edu")
set (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
include (CPack)
