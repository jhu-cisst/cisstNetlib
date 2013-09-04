#line 1 "nnls.f"
/* nnls.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

#line 1 "nnls.f"
/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;
static integer c__2 = 2;

/*     SUBROUTINE NNLS  (A,MDA,M,N,B,X,RNORM,W,ZZ,INDEX,MODE) */

/*  Algorithm NNLS: NONNEGATIVE LEAST SQUARES */

/*  The original version of this code was developed by */
/*  Charles L. Lawson and Richard J. Hanson at Jet Propulsion Laboratory */
/*  1973 JUN 15, and published in the book */
/*  "SOLVING LEAST SQUARES PROBLEMS", Prentice-HalL, 1974. */
/*  Revised FEB 1995 to accompany reprinting of the book by SIAM. */

/*     GIVEN AN M BY N MATRIX, A, AND AN M-VECTOR, B,  COMPUTE AN */
/*     N-VECTOR, X, THAT SOLVES THE LEAST SQUARES PROBLEM */

/*                      A * X = B  SUBJECT TO X .GE. 0 */
/*     ------------------------------------------------------------------ */
/*                     Subroutine Arguments */

/*     A(),MDA,M,N     MDA IS THE FIRST DIMENSIONING PARAMETER FOR THE */
/*                     ARRAY, A().   ON ENTRY A() CONTAINS THE M BY N */
/*                     MATRIX, A.           ON EXIT A() CONTAINS */
/*                     THE PRODUCT MATRIX, Q*A , WHERE Q IS AN */
/*                     M BY M ORTHOGONAL MATRIX GENERATED IMPLICITLY BY */
/*                     THIS SUBROUTINE. */
/*     B()     ON ENTRY B() CONTAINS THE M-VECTOR, B.   ON EXIT B() CON- */
/*             TAINS Q*B. */
/*     X()     ON ENTRY X() NEED NOT BE INITIALIZED.  ON EXIT X() WILL */
/*             CONTAIN THE SOLUTION VECTOR. */
/*     RNORM   ON EXIT RNORM CONTAINS THE EUCLIDEAN NORM OF THE */
/*             RESIDUAL VECTOR. */
/*     W()     AN N-ARRAY OF WORKING SPACE.  ON EXIT W() WILL CONTAIN */
/*             THE DUAL SOLUTION VECTOR.   W WILL SATISFY W(I) = 0. */
/*             FOR ALL I IN SET P  AND W(I) .LE. 0. FOR ALL I IN SET Z */
/*     ZZ()     AN M-ARRAY OF WORKING SPACE. */
/*     INDEX()     AN INTEGER WORKING ARRAY OF LENGTH AT LEAST N. */
/*                 ON EXIT THE CONTENTS OF THIS ARRAY DEFINE THE SETS */
/*                 P AND Z AS FOLLOWS.. */

/*                 INDEX(1)   THRU INDEX(NSETP) = SET P. */
/*                 INDEX(IZ1) THRU INDEX(IZ2)   = SET Z. */
/*                 IZ1 = NSETP + 1 = NPP1 */
/*                 IZ2 = N */
/*     MODE    THIS IS A SUCCESS-FAILURE FLAG WITH THE FOLLOWING */
/*             MEANINGS. */
/*             1     THE SOLUTION HAS BEEN COMPUTED SUCCESSFULLY. */
/*             2     THE DIMENSIONS OF THE PROBLEM ARE BAD. */
/*                   EITHER M .LE. 0 OR N .LE. 0. */
/*             3    ITERATION COUNT EXCEEDED.  MORE THAN 3*N ITERATIONS. */

/*     ------------------------------------------------------------------ */
/*<       SUBROUTINE NNLS (A,MDA,M,N,B,X,RNORM,W,ZZ,INDEX,MODE)  >*/
/* Subroutine */ int nnls_(doublereal *a, integer *mda, integer *m, integer *
	n, doublereal *b, doublereal *x, doublereal *rnorm, doublereal *w, 
	doublereal *zz, integer *index, integer *mode)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    doublereal d__1, d__2;
    cilist ci__1;

    /* Builtin functions */
    double sqrt(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    integer i__, j, l;
    doublereal t;
    extern /* Subroutine */ int g1_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    doublereal cc;
    extern /* Subroutine */ int h12_(integer *, integer *, integer *, integer 
	    *, doublereal *, integer *, doublereal *, doublereal *, integer *,
	     integer *, integer *);
    integer ii, jj, ip;
    doublereal sm;
    integer iz, jz;
    doublereal up, ss;
    integer iz1, iz2, npp1;
    extern doublereal diff_(doublereal *, doublereal *);
    integer iter;
    doublereal temp, wmax, alpha, asave;
    integer itmax, izmax, nsetp;
    doublereal dummy, unorm, ztest;
    integer rtnkey;

/*     ------------------------------------------------------------------ */
/*<       integer I, II, IP, ITER, ITMAX, IZ, IZ1, IZ2, IZMAX, J, JJ, JZ, L >*/
/*<       integer M, MDA, MODE,N, NPP1, NSETP, RTNKEY >*/
/*     integer INDEX(N) */
/*     double precision A(MDA,N), B(M), W(N), X(N), ZZ(M) */
/*<       integer INDEX(*)   >*/
/*<       double precision A(MDA,*), B(*), W(*), X(*), ZZ(*)    >*/
/*<       double precision ALPHA, ASAVE, CC, DIFF, DUMMY, FACTOR, RNORM >*/
/*<       double precision SM, SS, T, TEMP, TWO, UNORM, UP, WMAX >*/
/*<       double precision ZERO, ZTEST >*/
/*<       parameter(FACTOR = 0.01d0) >*/
/*<       parameter(TWO = 2.0d0, ZERO = 0.0d0) >*/
/*     ------------------------------------------------------------------ */
/*<       MODE=1 >*/
#line 64 "nnls.f"
    /* Parameter adjustments */
#line 64 "nnls.f"
    a_dim1 = *mda;
#line 64 "nnls.f"
    a_offset = 1 + a_dim1;
#line 64 "nnls.f"
    a -= a_offset;
#line 64 "nnls.f"
    --b;
#line 64 "nnls.f"
    --x;
#line 64 "nnls.f"
    --w;
#line 64 "nnls.f"
    --zz;
#line 64 "nnls.f"
    --index;
#line 64 "nnls.f"

#line 64 "nnls.f"
    /* Function Body */
#line 64 "nnls.f"
    *mode = 1;
/*<       IF (M .le. 0 .or. N .le. 0) then >*/
#line 65 "nnls.f"
    if (*m <= 0 || *n <= 0) {
/*<          MODE=2 >*/
#line 66 "nnls.f"
	*mode = 2;
/*<          RETURN >*/
#line 67 "nnls.f"
	return 0;
/*<       endif >*/
#line 68 "nnls.f"
    }
/*<       ITER=0 >*/
#line 69 "nnls.f"
    iter = 0;
/*<       ITMAX=3*N  >*/
#line 70 "nnls.f"
    itmax = *n * 3;

/*                    INITIALIZE THE ARRAYS INDEX() AND X(). */

/*<           DO 20 I=1,N    >*/
#line 74 "nnls.f"
    i__1 = *n;
#line 74 "nnls.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<           X(I)=ZERO      >*/
#line 75 "nnls.f"
	x[i__] = 0.;
/*<    20     INDEX(I)=I     >*/
#line 76 "nnls.f"
/* L20: */
#line 76 "nnls.f"
	index[i__] = i__;
#line 76 "nnls.f"
    }

/*<       IZ2=N  >*/
#line 78 "nnls.f"
    iz2 = *n;
/*<       IZ1=1  >*/
#line 79 "nnls.f"
    iz1 = 1;
/*<       NSETP=0    >*/
#line 80 "nnls.f"
    nsetp = 0;
/*<       NPP1=1 >*/
#line 81 "nnls.f"
    npp1 = 1;
/*                             ******  MAIN LOOP BEGINS HERE  ****** */
/*<    30 CONTINUE   >*/
#line 83 "nnls.f"
L30:
/*                  QUIT IF ALL COEFFICIENTS ARE ALREADY IN THE SOLUTION. */
/*                        OR IF M COLS OF A HAVE BEEN TRIANGULARIZED. */

/*<       IF (IZ1 .GT.IZ2.OR.NSETP.GE.M) GO TO 350    >*/
#line 87 "nnls.f"
    if (iz1 > iz2 || nsetp >= *m) {
#line 87 "nnls.f"
	goto L350;
#line 87 "nnls.f"
    }

/*         COMPUTE COMPONENTS OF THE DUAL (NEGATIVE GRADIENT) VECTOR W(). */

/*<       DO 50 IZ=IZ1,IZ2   >*/
#line 91 "nnls.f"
    i__1 = iz2;
#line 91 "nnls.f"
    for (iz = iz1; iz <= i__1; ++iz) {
/*<          J=INDEX(IZ)    >*/
#line 92 "nnls.f"
	j = index[iz];
/*<          SM=ZERO    >*/
#line 93 "nnls.f"
	sm = 0.;
/*<          DO 40 L=NPP1,M >*/
#line 94 "nnls.f"
	i__2 = *m;
#line 94 "nnls.f"
	for (l = npp1; l <= i__2; ++l) {
/*<    40        SM=SM+A(L,J)*B(L)      >*/
#line 95 "nnls.f"
/* L40: */
#line 95 "nnls.f"
	    sm += a[l + j * a_dim1] * b[l];
#line 95 "nnls.f"
	}
/*<          W(J)=SM    >*/
#line 96 "nnls.f"
	w[j] = sm;
/*<    50 continue >*/
#line 97 "nnls.f"
/* L50: */
#line 97 "nnls.f"
    }
/*                                   FIND LARGEST POSITIVE W(J). */
/*<    60 continue >*/
#line 99 "nnls.f"
L60:
/*<       WMAX=ZERO  >*/
#line 100 "nnls.f"
    wmax = 0.;
/*<       DO 70 IZ=IZ1,IZ2   >*/
#line 101 "nnls.f"
    i__1 = iz2;
#line 101 "nnls.f"
    for (iz = iz1; iz <= i__1; ++iz) {
/*<          J=INDEX(IZ)    >*/
#line 102 "nnls.f"
	j = index[iz];
/*<          IF (W(J) .gt. WMAX) then >*/
#line 103 "nnls.f"
	if (w[j] > wmax) {
/*<             WMAX=W(J)      >*/
#line 104 "nnls.f"
	    wmax = w[j];
/*<             IZMAX=IZ   >*/
#line 105 "nnls.f"
	    izmax = iz;
/*<          endif >*/
#line 106 "nnls.f"
	}
/*<    70 CONTINUE   >*/
#line 107 "nnls.f"
/* L70: */
#line 107 "nnls.f"
    }

/*             IF WMAX .LE. 0. GO TO TERMINATION. */
/*             THIS INDICATES SATISFACTION OF THE KUHN-TUCKER CONDITIONS. */

/*<       IF (WMAX .le. ZERO) go to 350 >*/
#line 112 "nnls.f"
    if (wmax <= 0.) {
#line 112 "nnls.f"
	goto L350;
#line 112 "nnls.f"
    }
/*<       IZ=IZMAX   >*/
#line 113 "nnls.f"
    iz = izmax;
/*<       J=INDEX(IZ)    >*/
#line 114 "nnls.f"
    j = index[iz];

/*     THE SIGN OF W(J) IS OK FOR J TO BE MOVED TO SET P. */
/*     BEGIN THE TRANSFORMATION AND CHECK NEW DIAGONAL ELEMENT TO AVOID */
/*     NEAR LINEAR DEPENDENCE. */

/*<       ASAVE=A(NPP1,J)    >*/
#line 120 "nnls.f"
    asave = a[npp1 + j * a_dim1];
/*<       CALL H12 (1,NPP1,NPP1+1,M,A(1,J),1,UP,DUMMY,1,1,0)     >*/
#line 121 "nnls.f"
    i__1 = npp1 + 1;
#line 121 "nnls.f"
    h12_(&c__1, &npp1, &i__1, m, &a[j * a_dim1 + 1], &c__1, &up, &dummy, &
	    c__1, &c__1, &c__0);
/*<       UNORM=ZERO >*/
#line 122 "nnls.f"
    unorm = 0.;
/*<       IF (NSETP .ne. 0) then >*/
#line 123 "nnls.f"
    if (nsetp != 0) {
/*<           DO 90 L=1,NSETP    >*/
#line 124 "nnls.f"
	i__1 = nsetp;
#line 124 "nnls.f"
	for (l = 1; l <= i__1; ++l) {
/*<    90       UNORM=UNORM+A(L,J)**2      >*/
#line 125 "nnls.f"
/* L90: */
/* Computing 2nd power */
#line 125 "nnls.f"
	    d__1 = a[l + j * a_dim1];
#line 125 "nnls.f"
	    unorm += d__1 * d__1;
#line 125 "nnls.f"
	}
/*<       endif >*/
#line 126 "nnls.f"
    }
/*<       UNORM=sqrt(UNORM)  >*/
#line 127 "nnls.f"
    unorm = sqrt(unorm);
/*<       IF (DIFF(UNORM+ABS(A(NPP1,J))*FACTOR,UNORM) .gt. ZERO) then >*/
#line 128 "nnls.f"
    d__2 = unorm + (d__1 = a[npp1 + j * a_dim1], abs(d__1)) * .01;
#line 128 "nnls.f"
    if (diff_(&d__2, &unorm) > 0.) {

/*        COL J IS SUFFICIENTLY INDEPENDENT.  COPY B INTO ZZ, UPDATE ZZ */
/*        AND SOLVE FOR ZTEST ( = PROPOSED NEW VALUE FOR X(J) ). */

/*<          DO 120 L=1,M   >*/
#line 133 "nnls.f"
	i__1 = *m;
#line 133 "nnls.f"
	for (l = 1; l <= i__1; ++l) {
/*<   120        ZZ(L)=B(L)     >*/
#line 134 "nnls.f"
/* L120: */
#line 134 "nnls.f"
	    zz[l] = b[l];
#line 134 "nnls.f"
	}
/*<          CALL H12 (2,NPP1,NPP1+1,M,A(1,J),1,UP,ZZ,1,1,1)    >*/
#line 135 "nnls.f"
	i__1 = npp1 + 1;
#line 135 "nnls.f"
	h12_(&c__2, &npp1, &i__1, m, &a[j * a_dim1 + 1], &c__1, &up, &zz[1], &
		c__1, &c__1, &c__1);
/*<          ZTEST=ZZ(NPP1)/A(NPP1,J)   >*/
#line 136 "nnls.f"
	ztest = zz[npp1] / a[npp1 + j * a_dim1];

/*                                     SEE IF ZTEST IS POSITIVE */

/*<          IF (ZTEST .gt. ZERO) go to 140 >*/
#line 140 "nnls.f"
	if (ztest > 0.) {
#line 140 "nnls.f"
	    goto L140;
#line 140 "nnls.f"
	}
/*<       endif >*/
#line 141 "nnls.f"
    }

/*     REJECT J AS A CANDIDATE TO BE MOVED FROM SET Z TO SET P. */
/*     RESTORE A(NPP1,J), SET W(J)=0., AND LOOP BACK TO TEST DUAL */
/*     COEFFS AGAIN. */

/*<       A(NPP1,J)=ASAVE    >*/
#line 147 "nnls.f"
    a[npp1 + j * a_dim1] = asave;
/*<       W(J)=ZERO  >*/
#line 148 "nnls.f"
    w[j] = 0.;
/*<       GO TO 60   >*/
#line 149 "nnls.f"
    goto L60;

/*     THE INDEX  J=INDEX(IZ)  HAS BEEN SELECTED TO BE MOVED FROM */
/*     SET Z TO SET P.    UPDATE B,  UPDATE INDICES,  APPLY HOUSEHOLDER */
/*     TRANSFORMATIONS TO COLS IN NEW SET Z,  ZERO SUBDIAGONAL ELTS IN */
/*     COL J,  SET W(J)=0. */

/*<   140 continue >*/
#line 156 "nnls.f"
L140:
/*<       DO 150 L=1,M   >*/
#line 157 "nnls.f"
    i__1 = *m;
#line 157 "nnls.f"
    for (l = 1; l <= i__1; ++l) {
/*<   150    B(L)=ZZ(L)     >*/
#line 158 "nnls.f"
/* L150: */
#line 158 "nnls.f"
	b[l] = zz[l];
#line 158 "nnls.f"
    }

/*<       INDEX(IZ)=INDEX(IZ1)   >*/
#line 160 "nnls.f"
    index[iz] = index[iz1];
/*<       INDEX(IZ1)=J   >*/
#line 161 "nnls.f"
    index[iz1] = j;
/*<       IZ1=IZ1+1  >*/
#line 162 "nnls.f"
    ++iz1;
/*<       NSETP=NPP1 >*/
#line 163 "nnls.f"
    nsetp = npp1;
/*<       NPP1=NPP1+1    >*/
#line 164 "nnls.f"
    ++npp1;

/*<       IF (IZ1 .le. IZ2) then >*/
#line 166 "nnls.f"
    if (iz1 <= iz2) {
/*<          DO 160 JZ=IZ1,IZ2  >*/
#line 167 "nnls.f"
	i__1 = iz2;
#line 167 "nnls.f"
	for (jz = iz1; jz <= i__1; ++jz) {
/*<             JJ=INDEX(JZ)   >*/
#line 168 "nnls.f"
	    jj = index[jz];
/*<             CALL H12 (2,NSETP,NPP1,M,A(1,J),1,UP,A(1,JJ),1,MDA,1) >*/
#line 169 "nnls.f"
	    h12_(&c__2, &nsetp, &npp1, m, &a[j * a_dim1 + 1], &c__1, &up, &a[
		    jj * a_dim1 + 1], &c__1, mda, &c__1);
/*<   160    continue >*/
#line 170 "nnls.f"
/* L160: */
#line 170 "nnls.f"
	}
/*<       endif >*/
#line 171 "nnls.f"
    }

/*<       IF (NSETP .ne. M) then >*/
#line 173 "nnls.f"
    if (nsetp != *m) {
/*<          DO 180 L=NPP1,M    >*/
#line 174 "nnls.f"
	i__1 = *m;
#line 174 "nnls.f"
	for (l = npp1; l <= i__1; ++l) {
/*<   180       A(L,J)=ZERO    >*/
#line 175 "nnls.f"
/* L180: */
#line 175 "nnls.f"
	    a[l + j * a_dim1] = 0.;
#line 175 "nnls.f"
	}
/*<       endif >*/
#line 176 "nnls.f"
    }

/*<       W(J)=ZERO  >*/
#line 178 "nnls.f"
    w[j] = 0.;
/*                                SOLVE THE TRIANGULAR SYSTEM. */
/*                                STORE THE SOLUTION TEMPORARILY IN ZZ(). */
/*<       RTNKEY = 1 >*/
#line 181 "nnls.f"
    rtnkey = 1;
/*<       GO TO 400  >*/
#line 182 "nnls.f"
    goto L400;
/*<   200 CONTINUE   >*/
#line 183 "nnls.f"
L200:

/*                       ******  SECONDARY LOOP BEGINS HERE ****** */

/*                          ITERATION COUNTER. */

/*<   210 continue   >*/
#line 189 "nnls.f"
L210:
/*<       ITER=ITER+1    >*/
#line 190 "nnls.f"
    ++iter;
/*<       IF (ITER .gt. ITMAX) then >*/
#line 191 "nnls.f"
    if (iter > itmax) {
/*<          MODE=3 >*/
#line 192 "nnls.f"
	*mode = 3;
/*<          write (*,'(/a)') ' NNLS quitting on iteration count.' >*/
#line 193 "nnls.f"
	ci__1.cierr = 0;
#line 193 "nnls.f"
	ci__1.ciunit = 6;
#line 193 "nnls.f"
	ci__1.cifmt = "(/a)";
#line 193 "nnls.f"
	s_wsfe(&ci__1);
#line 193 "nnls.f"
	do_fio(&c__1, " NNLS quitting on iteration count.", (ftnlen)34);
#line 193 "nnls.f"
	e_wsfe();
/*<          GO TO 350  >*/
#line 194 "nnls.f"
	goto L350;
/*<       endif >*/
#line 195 "nnls.f"
    }

/*                    SEE IF ALL NEW CONSTRAINED COEFFS ARE FEASIBLE. */
/*                                  IF NOT COMPUTE ALPHA. */

/*<       ALPHA=TWO  >*/
#line 200 "nnls.f"
    alpha = 2.;
/*<       DO 240 IP=1,NSETP  >*/
#line 201 "nnls.f"
    i__1 = nsetp;
#line 201 "nnls.f"
    for (ip = 1; ip <= i__1; ++ip) {
/*<          L=INDEX(IP)    >*/
#line 202 "nnls.f"
	l = index[ip];
/*<          IF (ZZ(IP) .le. ZERO) then >*/
#line 203 "nnls.f"
	if (zz[ip] <= 0.) {
/*<             T=-X(L)/(ZZ(IP)-X(L))      >*/
#line 204 "nnls.f"
	    t = -x[l] / (zz[ip] - x[l]);
/*<             IF (ALPHA .gt. T) then >*/
#line 205 "nnls.f"
	    if (alpha > t) {
/*<                ALPHA=T    >*/
#line 206 "nnls.f"
		alpha = t;
/*<                JJ=IP  >*/
#line 207 "nnls.f"
		jj = ip;
/*<             endif >*/
#line 208 "nnls.f"
	    }
/*<          endif >*/
#line 209 "nnls.f"
	}
/*<   240 CONTINUE   >*/
#line 210 "nnls.f"
/* L240: */
#line 210 "nnls.f"
    }

/*          IF ALL NEW CONSTRAINED COEFFS ARE FEASIBLE THEN ALPHA WILL */
/*          STILL = 2.    IF SO EXIT FROM SECONDARY LOOP TO MAIN LOOP. */

/*<       IF (ALPHA.EQ.TWO) GO TO 330    >*/
#line 215 "nnls.f"
    if (alpha == 2.) {
#line 215 "nnls.f"
	goto L330;
#line 215 "nnls.f"
    }

/*          OTHERWISE USE ALPHA WHICH WILL BE BETWEEN 0. AND 1. TO */
/*          INTERPOLATE BETWEEN THE OLD X AND THE NEW ZZ. */

/*<       DO 250 IP=1,NSETP  >*/
#line 220 "nnls.f"
    i__1 = nsetp;
#line 220 "nnls.f"
    for (ip = 1; ip <= i__1; ++ip) {
/*<          L=INDEX(IP)    >*/
#line 221 "nnls.f"
	l = index[ip];
/*<          X(L)=X(L)+ALPHA*(ZZ(IP)-X(L))  >*/
#line 222 "nnls.f"
	x[l] += alpha * (zz[ip] - x[l]);
/*<   250 continue >*/
#line 223 "nnls.f"
/* L250: */
#line 223 "nnls.f"
    }

/*        MODIFY A AND B AND THE INDEX ARRAYS TO MOVE COEFFICIENT I */
/*        FROM SET P TO SET Z. */

/*<       I=INDEX(JJ)    >*/
#line 228 "nnls.f"
    i__ = index[jj];
/*<   260 continue >*/
#line 229 "nnls.f"
L260:
/*<       X(I)=ZERO  >*/
#line 230 "nnls.f"
    x[i__] = 0.;

/*<       IF (JJ .ne. NSETP) then >*/
#line 232 "nnls.f"
    if (jj != nsetp) {
/*<          JJ=JJ+1    >*/
#line 233 "nnls.f"
	++jj;
/*<          DO 280 J=JJ,NSETP  >*/
#line 234 "nnls.f"
	i__1 = nsetp;
#line 234 "nnls.f"
	for (j = jj; j <= i__1; ++j) {
/*<             II=INDEX(J)    >*/
#line 235 "nnls.f"
	    ii = index[j];
/*<             INDEX(J-1)=II  >*/
#line 236 "nnls.f"
	    index[j - 1] = ii;
/*<             CALL G1 (A(J-1,II),A(J,II),CC,SS,A(J-1,II))    >*/
#line 237 "nnls.f"
	    g1_(&a[j - 1 + ii * a_dim1], &a[j + ii * a_dim1], &cc, &ss, &a[j 
		    - 1 + ii * a_dim1]);
/*<             A(J,II)=ZERO   >*/
#line 238 "nnls.f"
	    a[j + ii * a_dim1] = 0.;
/*<             DO 270 L=1,N   >*/
#line 239 "nnls.f"
	    i__2 = *n;
#line 239 "nnls.f"
	    for (l = 1; l <= i__2; ++l) {
/*<                IF (L.NE.II) then >*/
#line 240 "nnls.f"
		if (l != ii) {

/*                 Apply procedure G2 (CC,SS,A(J-1,L),A(J,L)) */

/*<                   TEMP = A(J-1,L) >*/
#line 244 "nnls.f"
		    temp = a[j - 1 + l * a_dim1];
/*<                   A(J-1,L) = CC*TEMP + SS*A(J,L) >*/
#line 245 "nnls.f"
		    a[j - 1 + l * a_dim1] = cc * temp + ss * a[j + l * a_dim1]
			    ;
/*<                   A(J,L)   =-SS*TEMP + CC*A(J,L) >*/
#line 246 "nnls.f"
		    a[j + l * a_dim1] = -ss * temp + cc * a[j + l * a_dim1];
/*<                endif >*/
#line 247 "nnls.f"
		}
/*<   270       CONTINUE   >*/
#line 248 "nnls.f"
/* L270: */
#line 248 "nnls.f"
	    }

/*                 Apply procedure G2 (CC,SS,B(J-1),B(J)) */

/*<             TEMP = B(J-1) >*/
#line 252 "nnls.f"
	    temp = b[j - 1];
/*<             B(J-1) = CC*TEMP + SS*B(J)     >*/
#line 253 "nnls.f"
	    b[j - 1] = cc * temp + ss * b[j];
/*<             B(J)   =-SS*TEMP + CC*B(J)     >*/
#line 254 "nnls.f"
	    b[j] = -ss * temp + cc * b[j];
/*<   280    continue >*/
#line 255 "nnls.f"
/* L280: */
#line 255 "nnls.f"
	}
/*<       endif >*/
#line 256 "nnls.f"
    }

/*<       NPP1=NSETP >*/
#line 258 "nnls.f"
    npp1 = nsetp;
/*<       NSETP=NSETP-1      >*/
#line 259 "nnls.f"
    --nsetp;
/*<       IZ1=IZ1-1  >*/
#line 260 "nnls.f"
    --iz1;
/*<       INDEX(IZ1)=I   >*/
#line 261 "nnls.f"
    index[iz1] = i__;

/*        SEE IF THE REMAINING COEFFS IN SET P ARE FEASIBLE.  THEY SHOULD */
/*        BE BECAUSE OF THE WAY ALPHA WAS DETERMINED. */
/*        IF ANY ARE INFEASIBLE IT IS DUE TO ROUND-OFF ERROR.  ANY */
/*        THAT ARE NONPOSITIVE WILL BE SET TO ZERO */
/*        AND MOVED FROM SET P TO SET Z. */

/*<       DO 300 JJ=1,NSETP  >*/
#line 269 "nnls.f"
    i__1 = nsetp;
#line 269 "nnls.f"
    for (jj = 1; jj <= i__1; ++jj) {
/*<          I=INDEX(JJ)    >*/
#line 270 "nnls.f"
	i__ = index[jj];
/*<          IF (X(I) .le. ZERO) go to 260 >*/
#line 271 "nnls.f"
	if (x[i__] <= 0.) {
#line 271 "nnls.f"
	    goto L260;
#line 271 "nnls.f"
	}
/*<   300 CONTINUE   >*/
#line 272 "nnls.f"
/* L300: */
#line 272 "nnls.f"
    }

/*         COPY B( ) INTO ZZ( ).  THEN SOLVE AGAIN AND LOOP BACK. */

/*<       DO 310 I=1,M   >*/
#line 276 "nnls.f"
    i__1 = *m;
#line 276 "nnls.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<   310     ZZ(I)=B(I)     >*/
#line 277 "nnls.f"
/* L310: */
#line 277 "nnls.f"
	zz[i__] = b[i__];
#line 277 "nnls.f"
    }
/*<       RTNKEY = 2 >*/
#line 278 "nnls.f"
    rtnkey = 2;
/*<       GO TO 400  >*/
#line 279 "nnls.f"
    goto L400;
/*<   320 CONTINUE   >*/
#line 280 "nnls.f"
L320:
/*<       GO TO 210  >*/
#line 281 "nnls.f"
    goto L210;
/*                      ******  END OF SECONDARY LOOP  ****** */

/*<   330 continue >*/
#line 284 "nnls.f"
L330:
/*<       DO 340 IP=1,NSETP  >*/
#line 285 "nnls.f"
    i__1 = nsetp;
#line 285 "nnls.f"
    for (ip = 1; ip <= i__1; ++ip) {
/*<           I=INDEX(IP)    >*/
#line 286 "nnls.f"
	i__ = index[ip];
/*<   340     X(I)=ZZ(IP)    >*/
#line 287 "nnls.f"
/* L340: */
#line 287 "nnls.f"
	x[i__] = zz[ip];
#line 287 "nnls.f"
    }
/*        ALL NEW COEFFS ARE POSITIVE.  LOOP BACK TO BEGINNING. */
/*<       GO TO 30   >*/
#line 289 "nnls.f"
    goto L30;

/*                        ******  END OF MAIN LOOP  ****** */

/*                        COME TO HERE FOR TERMINATION. */
/*                     COMPUTE THE NORM OF THE FINAL RESIDUAL VECTOR. */

/*<   350 continue   >*/
#line 296 "nnls.f"
L350:
/*<       SM=ZERO    >*/
#line 297 "nnls.f"
    sm = 0.;
/*<       IF (NPP1 .le. M) then >*/
#line 298 "nnls.f"
    if (npp1 <= *m) {
/*<          DO 360 I=NPP1,M    >*/
#line 299 "nnls.f"
	i__1 = *m;
#line 299 "nnls.f"
	for (i__ = npp1; i__ <= i__1; ++i__) {
/*<   360       SM=SM+B(I)**2  >*/
#line 300 "nnls.f"
/* L360: */
/* Computing 2nd power */
#line 300 "nnls.f"
	    d__1 = b[i__];
#line 300 "nnls.f"
	    sm += d__1 * d__1;
#line 300 "nnls.f"
	}
/*<       else >*/
#line 301 "nnls.f"
    } else {
/*<          DO 380 J=1,N   >*/
#line 302 "nnls.f"
	i__1 = *n;
#line 302 "nnls.f"
	for (j = 1; j <= i__1; ++j) {
/*<   380       W(J)=ZERO      >*/
#line 303 "nnls.f"
/* L380: */
#line 303 "nnls.f"
	    w[j] = 0.;
#line 303 "nnls.f"
	}
/*<       endif >*/
#line 304 "nnls.f"
    }
/*<       RNORM=sqrt(SM)     >*/
#line 305 "nnls.f"
    *rnorm = sqrt(sm);
/*<       RETURN >*/
#line 306 "nnls.f"
    return 0;

/*     THE FOLLOWING BLOCK OF CODE IS USED AS AN INTERNAL SUBROUTINE */
/*     TO SOLVE THE TRIANGULAR SYSTEM, PUTTING THE SOLUTION IN ZZ(). */

/*<   400 continue >*/
#line 311 "nnls.f"
L400:
/*<       DO 430 L=1,NSETP   >*/
#line 312 "nnls.f"
    i__1 = nsetp;
#line 312 "nnls.f"
    for (l = 1; l <= i__1; ++l) {
/*<          IP=NSETP+1-L   >*/
#line 313 "nnls.f"
	ip = nsetp + 1 - l;
/*<          IF (L .ne. 1) then >*/
#line 314 "nnls.f"
	if (l != 1) {
/*<             DO 410 II=1,IP >*/
#line 315 "nnls.f"
	    i__2 = ip;
#line 315 "nnls.f"
	    for (ii = 1; ii <= i__2; ++ii) {
/*<                ZZ(II)=ZZ(II)-A(II,JJ)*ZZ(IP+1)    >*/
#line 316 "nnls.f"
		zz[ii] -= a[ii + jj * a_dim1] * zz[ip + 1];
/*<   410       continue >*/
#line 317 "nnls.f"
/* L410: */
#line 317 "nnls.f"
	    }
/*<          endif >*/
#line 318 "nnls.f"
	}
/*<          JJ=INDEX(IP)   >*/
#line 319 "nnls.f"
	jj = index[ip];
/*<          ZZ(IP)=ZZ(IP)/A(IP,JJ)     >*/
#line 320 "nnls.f"
	zz[ip] /= a[ip + jj * a_dim1];
/*<   430 continue >*/
#line 321 "nnls.f"
/* L430: */
#line 321 "nnls.f"
    }
/*<       go to (200, 320), RTNKEY >*/
#line 322 "nnls.f"
    switch (rtnkey) {
#line 322 "nnls.f"
	case 1:  goto L200;
#line 322 "nnls.f"
	case 2:  goto L320;
#line 322 "nnls.f"
    }
/*<       END    >*/
#line 323 "nnls.f"
    return 0;
} /* nnls_ */

