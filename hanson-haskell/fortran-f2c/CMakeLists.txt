#
# $Id$
#
# Author(s):  Anton Deguet
# Created on: 2012-12-09
#
# (C) Copyright 2012-2013 Johns Hopkins University (JHU), All Rights
# Reserved.
#

set (cisstNetlib_hanson_haskell_SOURCES
     drotm.c
     drotmg.c
     lpdp.c
     lsei.c
     lsi.c
     slatec.c
     wnlit.c
     wnlsm.c
     wnnls.c
     xerabt.c
     xerclr.c
     xerctl.c
     xerdmp.c
     xermax.c
     xerprt.c
     xerror.c
     xerrwv.c
     xersav.c
     xgetf.c
     xgetua.c
     xgetun.c
     xsetf.c
     xsetua.c
     xsetun.c
)

add_library (cisstNetlib_hanson_haskell ${cisstNetlib_hanson_haskell_SOURCES})

install (TARGETS cisstNetlib_hanson_haskell
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib)
