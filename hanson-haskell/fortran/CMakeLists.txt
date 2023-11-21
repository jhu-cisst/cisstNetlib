#
# Author(s):  Anton Deguet
# Created on: 2012-12-09
#
# (C) Copyright 2012-2022 Johns Hopkins University (JHU), All Rights Reserved.
#

project (cisstNetlib_hanson_haskell_Fortran VERSION ${cisstNetlib_VERSION})

set (cisstNetlib_hanson_haskell_SOURCES
     drotm.f
     drotmg.f
     lpdp.f
     lsei.f
     lsi.f
     slatec.f
     wnlit.f
     wnlsm.f
     wnnls.f
     xerabt.f
     xerclr.f
     xerctl.f
     xerdmp.f
     xermax.f
     xerprt.f
     xerror.f
     xerrwv.f
     xersav.f
     xgetf.f
     xgetua.f
     xgetun.f
     xsetf.f
     xsetua.f
     xsetun.f
)

add_library (cisstNetlib_hanson_haskell ${cisstNetlib_hanson_haskell_SOURCES})

install (TARGETS cisstNetlib_hanson_haskell
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib)
