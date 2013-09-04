#
# $Id$
#
# Author(s):  Anton Deguet
# Created on: 2012-12-09
#
# (C) Copyright 2012-2013 Johns Hopkins University (JHU), All Rights
# Reserved.
#

if (CISSTNETLIB_C_BASED)
  add_subdirectory (fortran-f2c)
else (CISSTNETLIB_C_BASED)
  add_subdirectory (fortran)
endif (CISSTNETLIB_C_BASED)
