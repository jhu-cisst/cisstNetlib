/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  Author(s):  Anton Deguet
  Created on: 2012-09-25

  (C) Copyright 2012-2020 Johns Hopkins University (JHU), All Rights Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/


#include <cisstNetlib/cisstNetlib-hanson-haskell.h>

#ifdef CISSTNETLIB_C_BASED
#include <f2c.h>
#include <hanson-haskell/fortran-f2c/lsei.P>
#include <hanson-haskell/fortran-f2c/lsi.P>
#else
// forward declarations for C99
int lsei_(CISSTNETLIB_DOUBLE * w,
          CISSTNETLIB_INTEGER * mdw,
          CISSTNETLIB_INTEGER * me,
          CISSTNETLIB_INTEGER * ma,
          CISSTNETLIB_INTEGER * mg,
          CISSTNETLIB_INTEGER * n,
          CISSTNETLIB_DOUBLE * prgopt,
          CISSTNETLIB_DOUBLE * x,
          CISSTNETLIB_DOUBLE * rnorme,
          CISSTNETLIB_DOUBLE * rnorml,
          CISSTNETLIB_INTEGER * mode,
          CISSTNETLIB_DOUBLE * ws,
          CISSTNETLIB_INTEGER * ip);
void lsi_(CISSTNETLIB_DOUBLE * w,
          CISSTNETLIB_INTEGER * mdw,
          CISSTNETLIB_INTEGER * ma,
          CISSTNETLIB_INTEGER * mg,
          CISSTNETLIB_INTEGER * n,
          CISSTNETLIB_DOUBLE * prgopt,
          CISSTNETLIB_DOUBLE * x,
          CISSTNETLIB_DOUBLE * rnorm,
          CISSTNETLIB_INTEGER * mode,
          CISSTNETLIB_DOUBLE * ws,
          CISSTNETLIB_INTEGER * ip);
#endif // CISSTNETLIB_C_BASED

int cisstNetlib_lsei_(CISSTNETLIB_DOUBLE * w,
                      CISSTNETLIB_INTEGER * mdw,
                      CISSTNETLIB_INTEGER * me,
                      CISSTNETLIB_INTEGER * ma,
                      CISSTNETLIB_INTEGER * mg,
                      CISSTNETLIB_INTEGER * n,
                      CISSTNETLIB_DOUBLE * prgopt,
                      CISSTNETLIB_DOUBLE * x,
                      CISSTNETLIB_DOUBLE * rnorme,
                      CISSTNETLIB_DOUBLE * rnorml,
                      CISSTNETLIB_INTEGER * mode,
                      CISSTNETLIB_DOUBLE * ws,
                      CISSTNETLIB_INTEGER * ip) {
    return lsei_(w, mdw, me, ma, mg, n, prgopt, x, rnorme, rnorml, mode, ws, ip);
}

void cisstNetlib_lsi_(CISSTNETLIB_DOUBLE * w,
                      CISSTNETLIB_INTEGER * mdw,
                      CISSTNETLIB_INTEGER * ma,
                      CISSTNETLIB_INTEGER * mg,
                      CISSTNETLIB_INTEGER * n,
                      CISSTNETLIB_DOUBLE * prgopt,
                      CISSTNETLIB_DOUBLE * x,
                      CISSTNETLIB_DOUBLE * rnorm,
                      CISSTNETLIB_INTEGER * mode,
                      CISSTNETLIB_DOUBLE * ws,
                      CISSTNETLIB_INTEGER * ip) {
    lsi_(w, mdw, ma, mg, n, prgopt, x, rnorm, mode, ws, ip);
}
