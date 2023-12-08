#
# Author(s):  Anton Deguet
# Created on: 2012-12-09
#
# (C) Copyright 2012-2023 Johns Hopkins University (JHU), All Rights Reserved.
#

project (cisstNetlib_lawson_hanson LANGUAGES ${cisstNetlib_LANGUAGES} VERSION ${cisstNetlib_VERSION})

if (cisstNetlib_C_BASED)
  add_subdirectory (fortran-f2c)
else (cisstNetlib_C_BASED)
  add_subdirectory (fortran)
endif (cisstNetlib_C_BASED)
