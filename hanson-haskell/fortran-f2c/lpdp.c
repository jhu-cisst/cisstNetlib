#line 1 "../fortran/lpdp.f"
/* ../fortran/lpdp.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/lpdp.f"
/* Table of constant values */

static integer c__0 = 0;
static integer c__1 = 1;

/*<       SUBROUTINE LPDP(A, MDA, M, N1, N2, PRGOPT, X, WNORM, MODE, WS, IS) >*/
/* Subroutine */ int lpdp_(doublereal *a, integer *mda, integer *m, integer *
	n1, integer *n2, doublereal *prgopt, doublereal *x, doublereal *wnorm,
	 integer *mode, doublereal *ws, integer *is)
{
    /* Initialized data */

    static doublereal zero = 0.;
    static doublereal one = 1.;
    static doublereal fac = .1;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Local variables */
    integer i__, j, l, n;
    doublereal sc;
    integer iw, ix, np1;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *), dnrm2_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    integer modew;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    doublereal rnorm;
    extern /* Subroutine */ int wnnls_(doublereal *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, doublereal *);
    doublereal ynorm;


/*     THE EDITING REQUIRED TO CONVERT THIS SUBROUTINE FROM SINGLE TO */
/*     DOUBLE PRECISION INVOLVES THE FOLLOWING CHARACTER STRING CHANGES. */
/*     USE AN EDITING COMMAND (CHANGE) /STRING-1/(TO)STRING-2/. */
/*     (START EDITING AT LINE WITH C++ IN COLS. 1-3.) */
/*     /REAL (12 BLANKS)/DOUBLE PRECISION/,/DNRM2/DNRM2/,/DDOT/DDOT/, */
/*     /DCOPY/DCOPY/,/DSCAL/DSCAL/,/DABS(/DABS(/, DABS/, DABS/,/D0/D0/ */

/*     DIMENSION A(MDA,N+1),PRGOPT(*),X(N),WS((M+2)*(N+7)),IS(M+N+1), */
/*     WHERE N=N1+N2.  THIS IS A SLIGHT OVERESTIMATE FOR WS(*). */

/*     WRITTEN BY R. J. HANSON AND K. H. HASKELL, SANDIA LABS */
/*     REVISED OCT. 1, 1981. */

/*     DETERMINE AN N1-VECTOR W, AND */
/*               AN N2-VECTOR Z */
/*     WHICH MINIMIZES THE EUCLIDEAN LENGTH OF W */
/*     SUBJECT TO G*W+H*Z .GE. Y. */
/*     THIS IS THE LEAST PROJECTED DISTANCE PROBLEM, LPDP. */
/*     THE MATRICES G AND H ARE OF RESPECTIVE */
/*     DIMENSIONS M BY N1 AND M BY N2. */

/*     CALLED BY SUBPROGRAM LSI( ). */

/*     THE MATRIX */
/*                (G H Y) */

/*     OCCUPIES ROWS 1,...,M AND COLS 1,...,N1+N2+1 OF A(*,*). */

/*     THE SOLUTION (W) IS RETURNED IN X(*). */
/*                  (Z) */

/*     THE VALUE OF MODE INDICATES THE STATUS OF */
/*     THE COMPUTATION AFTER RETURNING TO THE USER. */

/*          MODE=1  THE SOLUTION WAS SUCCESSFULLY OBTAINED. */

/*          MODE=2  THE INEQUALITIES ARE INCONSISTENT. */

/*     SUBROUTINES CALLED */

/*     WNNLS         SOLVES A NONNEGATIVELY CONSTRAINED LINEAR LEAST */
/*                   SQUARES PROBLEM WITH LINEAR EQUALITY CONSTRAINTS. */
/*                   PART OF THIS PACKAGE. */

/* ++ */
/*     DDOT,         SUBROUTINES FROM THE BLAS PACKAGE. */
/*     DSCAL,DNRM2,  SEE TRANS. MATH. SOFT., VOL. 5, NO. 3, P. 308. */
/*     DCOPY */

/*<       DOUBLE PRECISION A(MDA,1), PRGOPT(1), WS(1), WNORM, X(1) >*/
/*<       INTEGER IS(1) >*/
/*<       DOUBLE PRECISION FAC, ONE, RNORM, SC, YNORM, ZERO >*/
/*<       DOUBLE PRECISION DDOT, DNRM2, DABS >*/
/*<       DATA ZERO, ONE /0.D0,1.D0/, FAC /0.1E0/ >*/
#line 56 "../fortran/lpdp.f"
    /* Parameter adjustments */
#line 56 "../fortran/lpdp.f"
    a_dim1 = *mda;
#line 56 "../fortran/lpdp.f"
    a_offset = 1 + a_dim1;
#line 56 "../fortran/lpdp.f"
    a -= a_offset;
#line 56 "../fortran/lpdp.f"
    --prgopt;
#line 56 "../fortran/lpdp.f"
    --x;
#line 56 "../fortran/lpdp.f"
    --ws;
#line 56 "../fortran/lpdp.f"
    --is;
#line 56 "../fortran/lpdp.f"

#line 56 "../fortran/lpdp.f"
    /* Function Body */
/*<       N = N1 + N2 >*/
#line 57 "../fortran/lpdp.f"
    n = *n1 + *n2;
/*<       MODE = 1 >*/
#line 58 "../fortran/lpdp.f"
    *mode = 1;
/*<       IF (.NOT.(M.LE.0)) GO TO 20 >*/
#line 59 "../fortran/lpdp.f"
    if (! (*m <= 0)) {
#line 59 "../fortran/lpdp.f"
	goto L20;
#line 59 "../fortran/lpdp.f"
    }
/*<       IF (.NOT.(N.GT.0)) GO TO 10 >*/
#line 60 "../fortran/lpdp.f"
    if (! (n > 0)) {
#line 60 "../fortran/lpdp.f"
	goto L10;
#line 60 "../fortran/lpdp.f"
    }
/*<       X(1) = ZERO >*/
#line 61 "../fortran/lpdp.f"
    x[1] = zero;
/*<       CALL DCOPY(N, X, 0, X, 1) >*/
#line 62 "../fortran/lpdp.f"
    dcopy_(&n, &x[1], &c__0, &x[1], &c__1);
/*<    10 WNORM = ZERO >*/
#line 63 "../fortran/lpdp.f"
L10:
#line 63 "../fortran/lpdp.f"
    *wnorm = zero;
/*<       RETURN >*/
#line 64 "../fortran/lpdp.f"
    return 0;
/*<    20 NP1 = N + 1 >*/
#line 65 "../fortran/lpdp.f"
L20:
#line 65 "../fortran/lpdp.f"
    np1 = n + 1;

/*     SCALE NONZERO ROWS OF INEQUALITY MATRIX TO HAVE LENGTH ONE. */
/*<       DO 40 I=1,M >*/
#line 68 "../fortran/lpdp.f"
    i__1 = *m;
#line 68 "../fortran/lpdp.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         SC = DNRM2(N,A(I,1),MDA) >*/
#line 69 "../fortran/lpdp.f"
	sc = dnrm2_(&n, &a[i__ + a_dim1], mda);
/*<         IF (.NOT.(SC.NE.ZERO)) GO TO 30 >*/
#line 70 "../fortran/lpdp.f"
	if (! (sc != zero)) {
#line 70 "../fortran/lpdp.f"
	    goto L30;
#line 70 "../fortran/lpdp.f"
	}
/*<         SC = ONE/SC >*/
#line 71 "../fortran/lpdp.f"
	sc = one / sc;
/*<         CALL DSCAL(NP1, SC, A(I,1), MDA) >*/
#line 72 "../fortran/lpdp.f"
	dscal_(&np1, &sc, &a[i__ + a_dim1], mda);
/*<    30   CONTINUE >*/
#line 73 "../fortran/lpdp.f"
L30:
/*<    40 CONTINUE >*/
#line 74 "../fortran/lpdp.f"
/* L40: */
#line 74 "../fortran/lpdp.f"
	;
#line 74 "../fortran/lpdp.f"
    }

/*     SCALE RT.-SIDE VECTOR TO HAVE LENGTH ONE (OR ZERO). */
/*<       YNORM = DNRM2(M,A(1,NP1),1) >*/
#line 77 "../fortran/lpdp.f"
    ynorm = dnrm2_(m, &a[np1 * a_dim1 + 1], &c__1);
/*<       IF (.NOT.(YNORM.NE.ZERO)) GO TO 50 >*/
#line 78 "../fortran/lpdp.f"
    if (! (ynorm != zero)) {
#line 78 "../fortran/lpdp.f"
	goto L50;
#line 78 "../fortran/lpdp.f"
    }
/*<       SC = ONE/YNORM >*/
#line 79 "../fortran/lpdp.f"
    sc = one / ynorm;
/*<       CALL DSCAL(M, SC, A(1,NP1), 1) >*/
#line 80 "../fortran/lpdp.f"
    dscal_(m, &sc, &a[np1 * a_dim1 + 1], &c__1);

/*     SCALE COLS OF MATRIX H. */
/*<    50 J = N1 + 1 >*/
#line 83 "../fortran/lpdp.f"
L50:
#line 83 "../fortran/lpdp.f"
    j = *n1 + 1;
/*<    60 IF (.NOT.(J.LE.N)) GO TO 70 >*/
#line 84 "../fortran/lpdp.f"
L60:
#line 84 "../fortran/lpdp.f"
    if (! (j <= n)) {
#line 84 "../fortran/lpdp.f"
	goto L70;
#line 84 "../fortran/lpdp.f"
    }
/*<       SC = DNRM2(M,A(1,J),1) >*/
#line 85 "../fortran/lpdp.f"
    sc = dnrm2_(m, &a[j * a_dim1 + 1], &c__1);
/*<       IF (SC.NE.ZERO) SC = ONE/SC >*/
#line 86 "../fortran/lpdp.f"
    if (sc != zero) {
#line 86 "../fortran/lpdp.f"
	sc = one / sc;
#line 86 "../fortran/lpdp.f"
    }
/*<       CALL DSCAL(M, SC, A(1,J), 1) >*/
#line 87 "../fortran/lpdp.f"
    dscal_(m, &sc, &a[j * a_dim1 + 1], &c__1);
/*<       X(J) = SC >*/
#line 88 "../fortran/lpdp.f"
    x[j] = sc;
/*<       J = J + 1 >*/
#line 89 "../fortran/lpdp.f"
    ++j;
/*<       GO TO 60 >*/
#line 90 "../fortran/lpdp.f"
    goto L60;
/*<    70 IF (.NOT.(N1.GT.0)) GO TO 130 >*/
#line 91 "../fortran/lpdp.f"
L70:
#line 91 "../fortran/lpdp.f"
    if (! (*n1 > 0)) {
#line 91 "../fortran/lpdp.f"
	goto L130;
#line 91 "../fortran/lpdp.f"
    }

/*     COPY TRANSPOSE OF (H G Y) TO WORK ARRAY WS(*). */
/*<       IW = 0 >*/
#line 94 "../fortran/lpdp.f"
    iw = 0;
/*<       DO 80 I=1,M >*/
#line 95 "../fortran/lpdp.f"
    i__1 = *m;
#line 95 "../fortran/lpdp.f"
    for (i__ = 1; i__ <= i__1; ++i__) {

/*     MOVE COL OF TRANSPOSE OF H INTO WORK ARRAY. */
/*<         CALL DCOPY(N2, A(I,N1+1), MDA, WS(IW+1), 1) >*/
#line 98 "../fortran/lpdp.f"
	dcopy_(n2, &a[i__ + (*n1 + 1) * a_dim1], mda, &ws[iw + 1], &c__1);
/*<         IW = IW + N2 >*/
#line 99 "../fortran/lpdp.f"
	iw += *n2;

/*     MOVE COL OF TRANSPOSE OF G INTO WORK ARRAY. */
/*<         CALL DCOPY(N1, A(I,1), MDA, WS(IW+1), 1) >*/
#line 102 "../fortran/lpdp.f"
	dcopy_(n1, &a[i__ + a_dim1], mda, &ws[iw + 1], &c__1);
/*<         IW = IW + N1 >*/
#line 103 "../fortran/lpdp.f"
	iw += *n1;

/*     MOVE COMPONENT OF VECTOR Y INTO WORK ARRAY. */
/*<         WS(IW+1) = A(I,NP1) >*/
#line 106 "../fortran/lpdp.f"
	ws[iw + 1] = a[i__ + np1 * a_dim1];
/*<         IW = IW + 1 >*/
#line 107 "../fortran/lpdp.f"
	++iw;
/*<    80 CONTINUE >*/
#line 108 "../fortran/lpdp.f"
/* L80: */
#line 108 "../fortran/lpdp.f"
    }
/*<       WS(IW+1) = ZERO >*/
#line 109 "../fortran/lpdp.f"
    ws[iw + 1] = zero;
/*<       CALL DCOPY(N, WS(IW+1), 0, WS(IW+1), 1) >*/
#line 110 "../fortran/lpdp.f"
    dcopy_(&n, &ws[iw + 1], &c__0, &ws[iw + 1], &c__1);
/*<       IW = IW + N >*/
#line 111 "../fortran/lpdp.f"
    iw += n;
/*<       WS(IW+1) = ONE >*/
#line 112 "../fortran/lpdp.f"
    ws[iw + 1] = one;
/*<       IW = IW + 1 >*/
#line 113 "../fortran/lpdp.f"
    ++iw;

/*     SOLVE EU=F SUBJECT TO (TRANSPOSE OF H)U=0, U.GE.0.  THE */
/*     MATRIX E = TRANSPOSE OF (G Y), AND THE (N+1)-VECTOR */
/*     F = TRANSPOSE OF (0,...,0,1). */
/*<       IX = IW + 1 >*/
#line 118 "../fortran/lpdp.f"
    ix = iw + 1;
/*<       IW = IW + M >*/
#line 119 "../fortran/lpdp.f"
    iw += *m;

/*     DO NOT CHECK LENGTHS OF WORK ARRAYS IN THIS USAGE OF WNNLS( ). */
/*<       IS(1) = 0 >*/
#line 122 "../fortran/lpdp.f"
    is[1] = 0;
/*<       IS(2) = 0 >*/
#line 123 "../fortran/lpdp.f"
    is[2] = 0;
/*<        >*/
#line 124 "../fortran/lpdp.f"
    i__1 = np1 - *n2;
#line 124 "../fortran/lpdp.f"
    wnnls_(&ws[1], &np1, n2, &i__1, m, &c__0, &prgopt[1], &ws[ix], &rnorm, &
	    modew, &is[1], &ws[iw + 1]);

/*     COMPUTE THE COMPONENTS OF THE SOLN DENOTED ABOVE BY W. */
/*<       SC = ONE - DDOT(M,A(1,NP1),1,WS(IX),1) >*/
#line 128 "../fortran/lpdp.f"
    sc = one - ddot_(m, &a[np1 * a_dim1 + 1], &c__1, &ws[ix], &c__1);
/*<       IF (.NOT.(ONE+FAC*DABS(SC).NE.ONE .AND. RNORM.GT.ZERO)) GO TO 110 >*/
#line 129 "../fortran/lpdp.f"
    if (! (one + fac * abs(sc) != one && rnorm > zero)) {
#line 129 "../fortran/lpdp.f"
	goto L110;
#line 129 "../fortran/lpdp.f"
    }
/*<       SC = ONE/SC >*/
#line 130 "../fortran/lpdp.f"
    sc = one / sc;
/*<       DO 90 J=1,N1 >*/
#line 131 "../fortran/lpdp.f"
    i__1 = *n1;
#line 131 "../fortran/lpdp.f"
    for (j = 1; j <= i__1; ++j) {
/*<         X(J) = SC*DDOT(M,A(1,J),1,WS(IX),1) >*/
#line 132 "../fortran/lpdp.f"
	x[j] = sc * ddot_(m, &a[j * a_dim1 + 1], &c__1, &ws[ix], &c__1);
/*<    90 CONTINUE >*/
#line 133 "../fortran/lpdp.f"
/* L90: */
#line 133 "../fortran/lpdp.f"
    }

/*     COMPUTE THE VECTOR Q=Y-GW.  OVERWRITE Y WITH THIS VECTOR. */
/*<       DO 100 I=1,M >*/
#line 136 "../fortran/lpdp.f"
    i__1 = *m;
#line 136 "../fortran/lpdp.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         A(I,NP1) = A(I,NP1) - DDOT(N1,A(I,1),MDA,X,1) >*/
#line 137 "../fortran/lpdp.f"
	a[i__ + np1 * a_dim1] -= ddot_(n1, &a[i__ + a_dim1], mda, &x[1], &
		c__1);
/*<   100 CONTINUE >*/
#line 138 "../fortran/lpdp.f"
/* L100: */
#line 138 "../fortran/lpdp.f"
    }
/*<       GO TO 120 >*/
#line 139 "../fortran/lpdp.f"
    goto L120;
/*<   110 MODE = 2 >*/
#line 140 "../fortran/lpdp.f"
L110:
#line 140 "../fortran/lpdp.f"
    *mode = 2;
/*<       RETURN >*/
#line 141 "../fortran/lpdp.f"
    return 0;
/*<   120 CONTINUE >*/
#line 142 "../fortran/lpdp.f"
L120:
/*<   130 IF (.NOT.(N2.GT.0)) GO TO 180 >*/
#line 143 "../fortran/lpdp.f"
L130:
#line 143 "../fortran/lpdp.f"
    if (! (*n2 > 0)) {
#line 143 "../fortran/lpdp.f"
	goto L180;
#line 143 "../fortran/lpdp.f"
    }

/*     COPY TRANSPOSE OF (H Q) TO WORK ARRAY WS(*). */
/*<       IW = 0 >*/
#line 146 "../fortran/lpdp.f"
    iw = 0;
/*<       DO 140 I=1,M >*/
#line 147 "../fortran/lpdp.f"
    i__1 = *m;
#line 147 "../fortran/lpdp.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         CALL DCOPY(N2, A(I,N1+1), MDA, WS(IW+1), 1) >*/
#line 148 "../fortran/lpdp.f"
	dcopy_(n2, &a[i__ + (*n1 + 1) * a_dim1], mda, &ws[iw + 1], &c__1);
/*<         IW = IW + N2 >*/
#line 149 "../fortran/lpdp.f"
	iw += *n2;
/*<         WS(IW+1) = A(I,NP1) >*/
#line 150 "../fortran/lpdp.f"
	ws[iw + 1] = a[i__ + np1 * a_dim1];
/*<         IW = IW + 1 >*/
#line 151 "../fortran/lpdp.f"
	++iw;
/*<   140 CONTINUE >*/
#line 152 "../fortran/lpdp.f"
/* L140: */
#line 152 "../fortran/lpdp.f"
    }
/*<       WS(IW+1) = ZERO >*/
#line 153 "../fortran/lpdp.f"
    ws[iw + 1] = zero;
/*<       CALL DCOPY(N2, WS(IW+1), 0, WS(IW+1), 1) >*/
#line 154 "../fortran/lpdp.f"
    dcopy_(n2, &ws[iw + 1], &c__0, &ws[iw + 1], &c__1);
/*<       IW = IW + N2 >*/
#line 155 "../fortran/lpdp.f"
    iw += *n2;
/*<       WS(IW+1) = ONE >*/
#line 156 "../fortran/lpdp.f"
    ws[iw + 1] = one;
/*<       IW = IW + 1 >*/
#line 157 "../fortran/lpdp.f"
    ++iw;
/*<       IX = IW + 1 >*/
#line 158 "../fortran/lpdp.f"
    ix = iw + 1;
/*<       IW = IW + M >*/
#line 159 "../fortran/lpdp.f"
    iw += *m;

/*     SOLVE RV=S SUBJECT TO V.GE.0.  THE MATRIX R =(TRANSPOSE */
/*     OF (H Q)), WHERE Q=Y-GW.  THE (N2+1)-VECTOR S =(TRANSPOSE */
/*     OF (0,...,0,1)). */

/*     DO NOT CHECK LENGTHS OF WORK ARRAYS IN THIS USAGE OF WNNLS( ). */
/*<       IS(1) = 0 >*/
#line 166 "../fortran/lpdp.f"
    is[1] = 0;
/*<       IS(2) = 0 >*/
#line 167 "../fortran/lpdp.f"
    is[2] = 0;
/*<        >*/
#line 168 "../fortran/lpdp.f"
    i__1 = *n2 + 1;
#line 168 "../fortran/lpdp.f"
    i__2 = *n2 + 1;
#line 168 "../fortran/lpdp.f"
    wnnls_(&ws[1], &i__1, &c__0, &i__2, m, &c__0, &prgopt[1], &ws[ix], &rnorm,
	     &modew, &is[1], &ws[iw + 1]);

/*     COMPUTE THE COMPONENTS OF THE SOLN DENOTED ABOVE BY Z. */
/*<       SC = ONE - DDOT(M,A(1,NP1),1,WS(IX),1) >*/
#line 172 "../fortran/lpdp.f"
    sc = one - ddot_(m, &a[np1 * a_dim1 + 1], &c__1, &ws[ix], &c__1);
/*<       IF (.NOT.(ONE+FAC*DABS(SC).NE.ONE .AND. RNORM.GT.ZERO)) GO TO 160 >*/
#line 173 "../fortran/lpdp.f"
    if (! (one + fac * abs(sc) != one && rnorm > zero)) {
#line 173 "../fortran/lpdp.f"
	goto L160;
#line 173 "../fortran/lpdp.f"
    }
/*<       SC = ONE/SC >*/
#line 174 "../fortran/lpdp.f"
    sc = one / sc;
/*<       DO 150 J=1,N2 >*/
#line 175 "../fortran/lpdp.f"
    i__1 = *n2;
#line 175 "../fortran/lpdp.f"
    for (j = 1; j <= i__1; ++j) {
/*<         L = N1 + J >*/
#line 176 "../fortran/lpdp.f"
	l = *n1 + j;
/*<         X(L) = SC*DDOT(M,A(1,L),1,WS(IX),1)*X(L) >*/
#line 177 "../fortran/lpdp.f"
	x[l] = sc * ddot_(m, &a[l * a_dim1 + 1], &c__1, &ws[ix], &c__1) * x[l]
		;
/*<   150 CONTINUE >*/
#line 178 "../fortran/lpdp.f"
/* L150: */
#line 178 "../fortran/lpdp.f"
    }
/*<       GO TO 170 >*/
#line 179 "../fortran/lpdp.f"
    goto L170;
/*<   160 MODE = 2 >*/
#line 180 "../fortran/lpdp.f"
L160:
#line 180 "../fortran/lpdp.f"
    *mode = 2;
/*<       RETURN >*/
#line 181 "../fortran/lpdp.f"
    return 0;
/*<   170 CONTINUE >*/
#line 182 "../fortran/lpdp.f"
L170:

/*     ACCOUNT FOR SCALING OF RT.-SIDE VECTOR IN SOLUTION. */
/*<   180 CALL DSCAL(N, YNORM, X, 1) >*/
#line 185 "../fortran/lpdp.f"
L180:
#line 185 "../fortran/lpdp.f"
    dscal_(&n, &ynorm, &x[1], &c__1);
/*<       WNORM = DNRM2(N1,X,1) >*/
#line 186 "../fortran/lpdp.f"
    *wnorm = dnrm2_(n1, &x[1], &c__1);
/*<       RETURN >*/
#line 187 "../fortran/lpdp.f"
    return 0;
/*<       END >*/
} /* lpdp_ */

