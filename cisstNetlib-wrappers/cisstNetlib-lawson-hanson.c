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

#include <cisstNetlib/cisstNetlib-lawson-hanson.h>

#ifdef CISSTNETLIB_C_BASED
#include <f2c.h>
#include <lawson-hanson/fortran-f2c/svdrs.P>
#else
// forward declarations for C99
int svdrs_(CISSTNETLIB_DOUBLE * a,
           CISSTNETLIB_INTEGER * mda,
           CISSTNETLIB_INTEGER * m1,
           CISSTNETLIB_INTEGER * n1,
           CISSTNETLIB_DOUBLE * b,
           CISSTNETLIB_INTEGER * mdb,
           CISSTNETLIB_INTEGER * nb,
           CISSTNETLIB_DOUBLE * s,
           CISSTNETLIB_DOUBLE * work);
int nnls_(CISSTNETLIB_DOUBLE * a,
          CISSTNETLIB_INTEGER * mda,
          CISSTNETLIB_INTEGER * m,
          CISSTNETLIB_INTEGER * n,
          CISSTNETLIB_DOUBLE * b,
          CISSTNETLIB_DOUBLE * x,
          CISSTNETLIB_DOUBLE * rnorm,
          CISSTNETLIB_DOUBLE * w,
          CISSTNETLIB_DOUBLE * zz,
          CISSTNETLIB_INTEGER * index,
          CISSTNETLIB_INTEGER * mode);
CISSTNETLIB_DOUBLE diff_(CISSTNETLIB_DOUBLE * x,
                         CISSTNETLIB_DOUBLE * y);
#endif // CISSTNETLIB_C_BASED

int cisstNetlib_svdrs_(CISSTNETLIB_DOUBLE * a,
                       CISSTNETLIB_INTEGER * mda,
                       CISSTNETLIB_INTEGER * m1,
                       CISSTNETLIB_INTEGER * n1,
                       CISSTNETLIB_DOUBLE * b,
                       CISSTNETLIB_INTEGER * mdb,
                       CISSTNETLIB_INTEGER * nb,
                       CISSTNETLIB_DOUBLE * s,
                       CISSTNETLIB_DOUBLE * work) {
    return svdrs_(a, mda, m1, n1, b, mdb, nb, s, work);
}


int cisstNetlib_nnls_(CISSTNETLIB_DOUBLE * a,
                      CISSTNETLIB_INTEGER * mda,
                      CISSTNETLIB_INTEGER * m,
                      CISSTNETLIB_INTEGER * n,
                      CISSTNETLIB_DOUBLE * b,
                      CISSTNETLIB_DOUBLE * x,
                      CISSTNETLIB_DOUBLE * rnorm,
                      CISSTNETLIB_DOUBLE * w,
                      CISSTNETLIB_DOUBLE * zz,
                      CISSTNETLIB_INTEGER * index,
                      CISSTNETLIB_INTEGER * mode)
{
    return nnls_(a, mda, m, n, b, x, rnorm, w, zz, index, mode);
}

CISSTNETLIB_DOUBLE cisstNetlib_diff_(CISSTNETLIB_DOUBLE * x,
                                     CISSTNETLIB_DOUBLE * y)
{
    return diff_(x, y);
}
