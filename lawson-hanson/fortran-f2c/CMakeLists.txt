#
# $Id$
#
# Author(s):  Anton Deguet
# Created on: 2012-12-09
#
# (C) Copyright 2012-2013 Johns Hopkins University (JHU), All Rights
# Reserved.
#

set (cisstNetlib_lawson_hanson_SOURCES
     diff.c
     g1.c
     h12.c
     hfti.c
     ldp.c
     nnls.c
     qrbd.c
     svdrs.c
)

add_library (cisstNetlib_lawson_hanson ${cisstNetlib_lawson_hanson_SOURCES})

install (TARGETS cisstNetlib_lawson_hanson
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib)
