#line 1 "ldp.f"
/* ldp.f -- translated by f2c (version 20100827).
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

#line 1 "ldp.f"
/* Table of constant values */

static doublereal c_b12 = 1.;

/*<       SUBROUTINE LDP (G,MDG,M,N,H,X,XNORM,W,INDEX,MODE)      >*/
/* Subroutine */ int ldp_(doublereal *g, integer *mdg, integer *m, integer *n,
	 doublereal *h__, doublereal *x, doublereal *xnorm, doublereal *w, 
	integer *index, integer *mode)
{
    /* System generated locals */
    integer g_dim1, g_offset, i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    integer i__, j, jf, iw, iy, iz, np1;
    doublereal fac;
    extern doublereal diff_(doublereal *, doublereal *);
    extern /* Subroutine */ int nnls_(doublereal *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *);
    doublereal rnorm;
    integer iwdual;


/*  Algorithm LDP: LEAST DISTANCE PROGRAMMING */

/*  The original version of this code was developed by */
/*  Charles L. Lawson and Richard J. Hanson at Jet Propulsion Laboratory */
/*  1974 MAR 1, and published in the book */
/*  "SOLVING LEAST SQUARES PROBLEMS", Prentice-HalL, 1974. */
/*  Revised FEB 1995 to accompany reprinting of the book by SIAM. */
/*     ------------------------------------------------------------------ */
/*<       integer I, IW, IWDUAL, IY, IZ, J, JF, M, MDG, MODE, N, NP1 >*/
/*     integer INDEX(M) */
/*     double precision G(MDG,N), H(M), X(N), W(*) */
/*<       integer INDEX(*)   >*/
/*<       double precision G(MDG,*), H(*), X(*), W(*) >*/
/*<       double precision DIFF, FAC, ONE, RNORM, XNORM, ZERO >*/
/*<       parameter(ONE = 1.0d0, ZERO = 0.0d0) >*/
/*     ------------------------------------------------------------------ */
/*<       IF (N.LE.0) GO TO 120  >*/
#line 19 "ldp.f"
    /* Parameter adjustments */
#line 19 "ldp.f"
    g_dim1 = *mdg;
#line 19 "ldp.f"
    g_offset = 1 + g_dim1;
#line 19 "ldp.f"
    g -= g_offset;
#line 19 "ldp.f"
    --h__;
#line 19 "ldp.f"
    --x;
#line 19 "ldp.f"
    --w;
#line 19 "ldp.f"
    --index;
#line 19 "ldp.f"

#line 19 "ldp.f"
    /* Function Body */
#line 19 "ldp.f"
    if (*n <= 0) {
#line 19 "ldp.f"
	goto L120;
#line 19 "ldp.f"
    }
/*<           DO 10 J=1,N    >*/
#line 20 "ldp.f"
    i__1 = *n;
#line 20 "ldp.f"
    for (j = 1; j <= i__1; ++j) {
/*<    10     X(J)=ZERO      >*/
#line 21 "ldp.f"
/* L10: */
#line 21 "ldp.f"
	x[j] = 0.;
#line 21 "ldp.f"
    }
/*<       XNORM=ZERO >*/
#line 22 "ldp.f"
    *xnorm = 0.;
/*<       IF (M.LE.0) GO TO 110  >*/
#line 23 "ldp.f"
    if (*m <= 0) {
#line 23 "ldp.f"
	goto L110;
#line 23 "ldp.f"
    }

/*     THE DECLARED DIMENSION OF W() MUST BE AT LEAST (N+1)*(M+2)+2*M. */

/*      FIRST (N+1)*M LOCS OF W()   =  MATRIX E FOR PROBLEM NNLS. */
/*       NEXT     N+1 LOCS OF W()   =  VECTOR F FOR PROBLEM NNLS. */
/*       NEXT     N+1 LOCS OF W()   =  VECTOR Z FOR PROBLEM NNLS. */
/*       NEXT       M LOCS OF W()   =  VECTOR Y FOR PROBLEM NNLS. */
/*       NEXT       M LOCS OF W()   =  VECTOR WDUAL FOR PROBLEM NNLS. */
/*     COPY G**T INTO FIRST N ROWS AND M COLUMNS OF E. */
/*     COPY H**T INTO ROW N+1 OF E. */

/*<       IW=0   >*/
#line 35 "ldp.f"
    iw = 0;
/*<           DO 30 J=1,M    >*/
#line 36 "ldp.f"
    i__1 = *m;
#line 36 "ldp.f"
    for (j = 1; j <= i__1; ++j) {
/*<               DO 20 I=1,N    >*/
#line 37 "ldp.f"
	i__2 = *n;
#line 37 "ldp.f"
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<               IW=IW+1    >*/
#line 38 "ldp.f"
	    ++iw;
/*<    20         W(IW)=G(J,I)   >*/
#line 39 "ldp.f"
/* L20: */
#line 39 "ldp.f"
	    w[iw] = g[j + i__ * g_dim1];
#line 39 "ldp.f"
	}
/*<           IW=IW+1    >*/
#line 40 "ldp.f"
	++iw;
/*<    30     W(IW)=H(J)     >*/
#line 41 "ldp.f"
/* L30: */
#line 41 "ldp.f"
	w[iw] = h__[j];
#line 41 "ldp.f"
    }
/*<       JF=IW+1    >*/
#line 42 "ldp.f"
    jf = iw + 1;
/*                                STORE N ZEROS FOLLOWED BY A ONE INTO F. */
/*<           DO 40 I=1,N    >*/
#line 44 "ldp.f"
    i__1 = *n;
#line 44 "ldp.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<           IW=IW+1    >*/
#line 45 "ldp.f"
	++iw;
/*<    40     W(IW)=ZERO     >*/
#line 46 "ldp.f"
/* L40: */
#line 46 "ldp.f"
	w[iw] = 0.;
#line 46 "ldp.f"
    }
/*<       W(IW+1)=ONE    >*/
#line 47 "ldp.f"
    w[iw + 1] = 1.;

/*<       NP1=N+1    >*/
#line 49 "ldp.f"
    np1 = *n + 1;
/*<       IZ=IW+2    >*/
#line 50 "ldp.f"
    iz = iw + 2;
/*<       IY=IZ+NP1  >*/
#line 51 "ldp.f"
    iy = iz + np1;
/*<       IWDUAL=IY+M    >*/
#line 52 "ldp.f"
    iwdual = iy + *m;

/*<        >*/
#line 54 "ldp.f"
    nnls_(&w[1], &np1, &np1, m, &w[jf], &w[iy], &rnorm, &w[iwdual], &w[iz], &
	    index[1], mode);
/*                      USE THE FOLLOWING RETURN IF UNSUCCESSFUL IN NNLS. */
/*<       IF (MODE.NE.1) RETURN  >*/
#line 57 "ldp.f"
    if (*mode != 1) {
#line 57 "ldp.f"
	return 0;
#line 57 "ldp.f"
    }
/*<       IF (RNORM) 130,130,50  >*/
#line 58 "ldp.f"
    if (rnorm <= 0.) {
#line 58 "ldp.f"
	goto L130;
#line 58 "ldp.f"
    } else {
#line 58 "ldp.f"
	goto L50;
#line 58 "ldp.f"
    }
/*<    50 FAC=ONE    >*/
#line 59 "ldp.f"
L50:
#line 59 "ldp.f"
    fac = 1.;
/*<       IW=IY-1    >*/
#line 60 "ldp.f"
    iw = iy - 1;
/*<           DO 60 I=1,M    >*/
#line 61 "ldp.f"
    i__1 = *m;
#line 61 "ldp.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<           IW=IW+1    >*/
#line 62 "ldp.f"
	++iw;
/*                               HERE WE ARE USING THE SOLUTION VECTOR Y. */
/*<    60     FAC=FAC-H(I)*W(IW) >*/
#line 64 "ldp.f"
/* L60: */
#line 64 "ldp.f"
	fac -= h__[i__] * w[iw];
#line 64 "ldp.f"
    }

/*<       IF (DIFF(ONE+FAC,ONE)) 130,130,70  >*/
#line 66 "ldp.f"
    d__1 = fac + 1.;
#line 66 "ldp.f"
    if (diff_(&d__1, &c_b12) <= 0.) {
#line 66 "ldp.f"
	goto L130;
#line 66 "ldp.f"
    } else {
#line 66 "ldp.f"
	goto L70;
#line 66 "ldp.f"
    }
/*<    70 FAC=ONE/FAC    >*/
#line 67 "ldp.f"
L70:
#line 67 "ldp.f"
    fac = 1. / fac;
/*<           DO 90 J=1,N    >*/
#line 68 "ldp.f"
    i__1 = *n;
#line 68 "ldp.f"
    for (j = 1; j <= i__1; ++j) {
/*<           IW=IY-1    >*/
#line 69 "ldp.f"
	iw = iy - 1;
/*<               DO 80 I=1,M    >*/
#line 70 "ldp.f"
	i__2 = *m;
#line 70 "ldp.f"
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<               IW=IW+1    >*/
#line 71 "ldp.f"
	    ++iw;
/*                               HERE WE ARE USING THE SOLUTION VECTOR Y. */
/*<    80         X(J)=X(J)+G(I,J)*W(IW) >*/
#line 73 "ldp.f"
/* L80: */
#line 73 "ldp.f"
	    x[j] += g[i__ + j * g_dim1] * w[iw];
#line 73 "ldp.f"
	}
/*<    90     X(J)=X(J)*FAC  >*/
#line 74 "ldp.f"
/* L90: */
#line 74 "ldp.f"
	x[j] *= fac;
#line 74 "ldp.f"
    }
/*<           DO 100 J=1,N   >*/
#line 75 "ldp.f"
    i__1 = *n;
#line 75 "ldp.f"
    for (j = 1; j <= i__1; ++j) {
/*<   100     XNORM=XNORM+X(J)**2    >*/
#line 76 "ldp.f"
/* L100: */
/* Computing 2nd power */
#line 76 "ldp.f"
	d__1 = x[j];
#line 76 "ldp.f"
	*xnorm += d__1 * d__1;
#line 76 "ldp.f"
    }
/*<       XNORM=sqrt(XNORM)  >*/
#line 77 "ldp.f"
    *xnorm = sqrt(*xnorm);
/*                             SUCCESSFUL RETURN. */
/*<   110 MODE=1 >*/
#line 79 "ldp.f"
L110:
#line 79 "ldp.f"
    *mode = 1;
/*<       RETURN >*/
#line 80 "ldp.f"
    return 0;
/*                             ERROR RETURN.       N .LE. 0. */
/*<   120 MODE=2 >*/
#line 82 "ldp.f"
L120:
#line 82 "ldp.f"
    *mode = 2;
/*<       RETURN >*/
#line 83 "ldp.f"
    return 0;
/*                             RETURNING WITH CONSTRAINTS NOT COMPATIBLE. */
/*<   130 MODE=4 >*/
#line 85 "ldp.f"
L130:
#line 85 "ldp.f"
    *mode = 4;
/*<       RETURN >*/
#line 86 "ldp.f"
    return 0;
/*<       END    >*/
} /* ldp_ */

