#
# Author(s):  Anton Deguet
# Created on: 2012-12-09
#
# (C) Copyright 2012-2023 Johns Hopkins University (JHU), All Rights Reserved.
#

project (cisstNetlib_lawson_hanson_Fortran LANGUAGES ${cisstNetlib_LANGUAGES} VERSION ${cisstNetlib_VERSION})

set (cisstNetlib_lawson_hanson_SOURCES
     diff.f
     g1.f
     h12.f
     hfti.f
     ldp.f
     nnls.f
     qrbd.f
     svdrs.f
)

add_library (cisstNetlib_lawson_hanson ${cisstNetlib_lawson_hanson_SOURCES})

install (TARGETS cisstNetlib_lawson_hanson
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib)
