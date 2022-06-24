#
# Author(s):  Anton Deguet
# Created on: 2012-12-09
#
# (C) Copyright 2012-2022 Johns Hopkins University (JHU), All Rights Reserved.
#

project (cisstNetlib-wrappers LANGUAGES C VERSION ${cisstNetlib_VERSION})

set (cisstNetlib_SOURCES
     cisstNetlib-lapack.c
     cisstNetlib-hanson-haskell.c
     cisstNetlib-lawson-hanson.c)

if (CISSTNETLIB_C_BASED)
  add_definitions (-DCISSTNETLIB_C_BASED)
endif (CISSTNETLIB_C_BASED)

if (NOT WIN32)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif (NOT WIN32)

add_library (cisstNetlib ${cisstNetlib_SOURCES})

install (TARGETS cisstNetlib
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib)
