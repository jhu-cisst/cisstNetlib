#
# Author(s):  Anton Deguet
# Created on: 2012-12-09
#
# (C) Copyright 2012-2022 Johns Hopkins University (JHU), All Rights Reserved.
#

project (cisstNetlib_lawson_hanson VERSION ${cisstNetlib_VERSION})

if (CISSTNETLIB_C_BASED)
  add_subdirectory (fortran-f2c)
else (CISSTNETLIB_C_BASED)
  add_subdirectory (fortran)
endif (CISSTNETLIB_C_BASED)
