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

#include <cisstNetlib/cisstNetlib-lapack.h>

#ifdef CISSTNETLIB_C_BASED
#include <f2c.h>
#include <clapack.h>
#else
// forward declaration for C99
int dgels_(char * trans,
           CISSTNETLIB_INTEGER * m,
           CISSTNETLIB_INTEGER * n,
           CISSTNETLIB_INTEGER * nrhs,
           CISSTNETLIB_DOUBLE * a,
           CISSTNETLIB_INTEGER * lda,
           CISSTNETLIB_DOUBLE * b,
           CISSTNETLIB_INTEGER * ldb,
           CISSTNETLIB_DOUBLE * work,
           CISSTNETLIB_INTEGER * lwork,
           CISSTNETLIB_INTEGER * info);
int dgesvd_(char * jobu,
            char * jobvt,
            CISSTNETLIB_INTEGER * m,
            CISSTNETLIB_INTEGER * n,
            CISSTNETLIB_DOUBLE * a,
            CISSTNETLIB_INTEGER * lda,
            CISSTNETLIB_DOUBLE * s,
            CISSTNETLIB_DOUBLE * u,
            CISSTNETLIB_INTEGER * ldu,
            CISSTNETLIB_DOUBLE * vt,
            CISSTNETLIB_INTEGER * ldvt,
            CISSTNETLIB_DOUBLE * work,
            CISSTNETLIB_INTEGER * lwork,
            CISSTNETLIB_INTEGER * info);
int dgetrf_(CISSTNETLIB_INTEGER * m,
            CISSTNETLIB_INTEGER * n ,
            CISSTNETLIB_DOUBLE * a,
            CISSTNETLIB_INTEGER * lda,
            CISSTNETLIB_INTEGER * ipiv,
            CISSTNETLIB_INTEGER * info);
int dgetri_(CISSTNETLIB_INTEGER * n,
            CISSTNETLIB_DOUBLE * a,
            CISSTNETLIB_INTEGER * lda,
            CISSTNETLIB_INTEGER * ipiv,
            CISSTNETLIB_DOUBLE * work,
            CISSTNETLIB_INTEGER * lwork,
            CISSTNETLIB_INTEGER * info);
void dgemm_(char * TRANSA,
            char * TRANSB,
            CISSTNETLIB_INTEGER * M,
            CISSTNETLIB_INTEGER * N,
            CISSTNETLIB_INTEGER * K,
            CISSTNETLIB_DOUBLE * ALPHA,
            CISSTNETLIB_DOUBLE * A,
            CISSTNETLIB_INTEGER * LDA,
            CISSTNETLIB_DOUBLE * B,
            CISSTNETLIB_INTEGER * LDB,
            CISSTNETLIB_DOUBLE * BETA,
            CISSTNETLIB_DOUBLE * C,
            CISSTNETLIB_INTEGER * LDC);
void dscal_(CISSTNETLIB_INTEGER * N,
            CISSTNETLIB_DOUBLE * DA,
            CISSTNETLIB_DOUBLE * DX,
            CISSTNETLIB_INTEGER * INCX);
void dgelss_(CISSTNETLIB_INTEGER * M,
             CISSTNETLIB_INTEGER * N,
             CISSTNETLIB_INTEGER * NRHS,
             CISSTNETLIB_DOUBLE * A,
             CISSTNETLIB_INTEGER * LDA,
             CISSTNETLIB_DOUBLE * B,
             CISSTNETLIB_INTEGER * LDB,
             CISSTNETLIB_DOUBLE * S,
             CISSTNETLIB_DOUBLE * RCOND,
             CISSTNETLIB_INTEGER * RANK,
             CISSTNETLIB_DOUBLE * WORK,
             CISSTNETLIB_INTEGER * LWORK,
             CISSTNETLIB_INTEGER * INFO);
void dgeev_(char * JOBVL,
            char * JOBVR,
            CISSTNETLIB_INTEGER * N,
            CISSTNETLIB_DOUBLE * A,
            CISSTNETLIB_INTEGER * LDA,
            CISSTNETLIB_DOUBLE * WR,
            CISSTNETLIB_DOUBLE * WI,
            CISSTNETLIB_DOUBLE * VL,
            CISSTNETLIB_INTEGER * LDVL,
            CISSTNETLIB_DOUBLE * VR,
            CISSTNETLIB_INTEGER * LDVR,
            CISSTNETLIB_DOUBLE * WORK,
            CISSTNETLIB_INTEGER * LWORK,
            CISSTNETLIB_INTEGER * INFO);
#endif // CISSTNETLIB_C_BASED



int cisstNetlib_dgels_(char * trans,
                       CISSTNETLIB_INTEGER * m,
                       CISSTNETLIB_INTEGER * n,
                       CISSTNETLIB_INTEGER * nrhs,
                       CISSTNETLIB_DOUBLE * a,
                       CISSTNETLIB_INTEGER * lda,
                       CISSTNETLIB_DOUBLE * b,
                       CISSTNETLIB_INTEGER * ldb,
                       CISSTNETLIB_DOUBLE * work,
                       CISSTNETLIB_INTEGER * lwork,
                       CISSTNETLIB_INTEGER * info) {
    return dgels_(trans, m, n, nrhs, a, lda, b, ldb, work, lwork, info);
}

int cisstNetlib_dgesvd_(char * jobu,
                        char * jobvt,
                        CISSTNETLIB_INTEGER * m,
                        CISSTNETLIB_INTEGER * n,
                        CISSTNETLIB_DOUBLE * a,
                        CISSTNETLIB_INTEGER * lda,
                        CISSTNETLIB_DOUBLE * s,
                        CISSTNETLIB_DOUBLE * u,
                        CISSTNETLIB_INTEGER * ldu,
                        CISSTNETLIB_DOUBLE * vt,
                        CISSTNETLIB_INTEGER * ldvt,
                        CISSTNETLIB_DOUBLE * work,
                        CISSTNETLIB_INTEGER * lwork,
                        CISSTNETLIB_INTEGER * info) {
    return dgesvd_(jobu, jobvt, m , n, a, lda, s, u, ldu, vt, ldvt, work, lwork, info);
}

int cisstNetlib_dgetrf_(CISSTNETLIB_INTEGER * m,
                        CISSTNETLIB_INTEGER * n ,
                        CISSTNETLIB_DOUBLE * a,
                        CISSTNETLIB_INTEGER * lda,
                        CISSTNETLIB_INTEGER * ipiv,
                        CISSTNETLIB_INTEGER * info) {
    return dgetrf_(m, n, a, lda, ipiv, info);
}

int cisstNetlib_dgetri_(CISSTNETLIB_INTEGER * n,
                        CISSTNETLIB_DOUBLE * a,
                        CISSTNETLIB_INTEGER * lda,
                        CISSTNETLIB_INTEGER * ipiv,
                        CISSTNETLIB_DOUBLE * work,
                        CISSTNETLIB_INTEGER * lwork,
                        CISSTNETLIB_INTEGER * info) {
    return dgetri_(n, a, lda, ipiv, work, lwork, info);
}

void cisstNetlib_dgemm_(char * TRANSA,
                        char * TRANSB,
                        CISSTNETLIB_INTEGER * M,
                        CISSTNETLIB_INTEGER * N,
                        CISSTNETLIB_INTEGER * K,
                        CISSTNETLIB_DOUBLE * ALPHA,
                        CISSTNETLIB_DOUBLE * A,
                        CISSTNETLIB_INTEGER * LDA,
                        CISSTNETLIB_DOUBLE * B,
                        CISSTNETLIB_INTEGER * LDB,
                        CISSTNETLIB_DOUBLE * BETA,
                        CISSTNETLIB_DOUBLE * C,
                        CISSTNETLIB_INTEGER * LDC) {
    dgemm_(TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC);
}

void cisstNetlib_dscal_(CISSTNETLIB_INTEGER * N,
                        CISSTNETLIB_DOUBLE * DA,
                        CISSTNETLIB_DOUBLE * DX,
                        CISSTNETLIB_INTEGER * INCX) {
    dscal_(N, DA, DX, INCX);

}

void cisstNetlib_dgelss_(CISSTNETLIB_INTEGER * M,
                         CISSTNETLIB_INTEGER * N,
                         CISSTNETLIB_INTEGER * NRHS,
                         CISSTNETLIB_DOUBLE * A,
                         CISSTNETLIB_INTEGER * LDA,
                         CISSTNETLIB_DOUBLE * B,
                         CISSTNETLIB_INTEGER * LDB,
                         CISSTNETLIB_DOUBLE * S,
                         CISSTNETLIB_DOUBLE * RCOND,
                         CISSTNETLIB_INTEGER * RANK,
                         CISSTNETLIB_DOUBLE * WORK,
                         CISSTNETLIB_INTEGER * LWORK,
                         CISSTNETLIB_INTEGER * INFO) {
    dgelss_(M, N, NRHS, A, LDA, B, LDB, S, RCOND, RANK, WORK, LWORK, INFO);
}

void cisstNetlib_dgeev_(char * JOBVL,
                        char * JOBVR,
                        CISSTNETLIB_INTEGER * N,
                        CISSTNETLIB_DOUBLE * A,
                        CISSTNETLIB_INTEGER * LDA,
                        CISSTNETLIB_DOUBLE * WR,
                        CISSTNETLIB_DOUBLE * WI,
                        CISSTNETLIB_DOUBLE * VL,
                        CISSTNETLIB_INTEGER * LDVL,
                        CISSTNETLIB_DOUBLE * VR,
                        CISSTNETLIB_INTEGER * LDVR,
                        CISSTNETLIB_DOUBLE * WORK,
                        CISSTNETLIB_INTEGER * LWORK,
                        CISSTNETLIB_INTEGER * INFO) {
    dgeev_(JOBVL, JOBVR, N, A, LDA, WR, WI, VL, LDVL, VR, LDVR, WORK, LWORK, INFO);
}
