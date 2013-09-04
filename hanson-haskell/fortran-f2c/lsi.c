#line 1 "../fortran/lsi.f"
/* ../fortran/lsi.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/lsi.f"
/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;
static integer c__2 = 2;

/*<       SUBROUTINE LSI(W, MDW, MA, MG, N, PRGOPT, X, RNORM, MODE, WS, IP)  >*/
/* Subroutine */ int lsi_(doublereal *w, integer *mdw, integer *ma, integer *
	mg, integer *n, doublereal *prgopt, doublereal *x, doublereal *rnorm, 
	integer *mode, doublereal *ws, integer *ip)
{
    /* Initialized data */

    static doublereal zero = 0.;
    static doublereal drelpr = 0.;
    static doublereal one = 1.;
    static doublereal half = .5;

    /* Format strings */
    static char fmt_40[] = "";
    static char fmt_60[] = "";

    /* System generated locals */
    integer w_dim1, w_offset, i__1, i__2, i__3, i__4;
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    integer i__, j, k, l, m, n1, n2, n3;
    extern /* Subroutine */ int h12_(integer *, integer *, integer *, integer 
	    *, doublereal *, integer *, doublereal *, doublereal *, integer *,
	     integer *, integer *);
    integer ii;
    doublereal rb;
    integer il, im1, ip1, np1;
    doublereal fac, gam, tau;
    logical cov;
    integer key;
    doublereal tol;
    integer map1, krm1, krp1;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    extern /* Subroutine */ int hfti_(doublereal *, integer *, integer *, 
	    integer *, doublereal *, integer *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *, integer *);
    integer link;
    extern /* Subroutine */ int lpdp_(doublereal *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    integer last, next, igo990, igo994;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    integer krank;
    extern doublereal dasum_(integer *, doublereal *, integer *);
    doublereal anorm;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *), dswap_(integer *, doublereal *, integer 
	    *, doublereal *, integer *), daxpy_(integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *);
    doublereal xnorm;
    integer minman, mdlpdp;

    /* Assigned format variables */
    static char *igo994_fmt, *igo990_fmt;


/*     THE EDITING REQUIRED TO CONVERT THIS SUBROUTINE FROM SINGLE TO */
/*     DOUBLE PRECISION INVOLVES THE FOLLOWING CHARACTER STRING CHANGES. */
/*     USE AN EDITING COMMAND (CHANGE) /STRING-1/(TO)STRING-2/. */
/*     (START EDITING AT LINE WITH C++ IN COLS. 1-3.) */
/*     /REAL (12 BLANKS)/DOUBLE PRECISION/,/DASUM/DASUM/,/DDOT/DDOT/, */
/*     / DSQRT/ DSQRT/,/DMAX1/DMAX1/,/DSWAP/DSWAP/, */
/*     /DCOPY/DCOPY/,/DSCAL/DSCAL/,/DAXPY/DAXPY/,/D0/D0/,/DRELPR/DRELPR/ */

/*     THIS IS A COMPANION SUBPROGRAM TO LSEI( ). */
/*     THE DOCUMENTATION FOR LSEI( ) HAS MORE COMPLETE */
/*     USAGE INSTRUCTIONS. */
/*     WRITTEN BY R. J. HANSON, SLA. */

/*     SOLVE.. */
/*              AX = B,  A  MA BY N  (LEAST SQUARES EQUATIONS) */
/*     SUBJECT TO.. */

/*              GX.GE.H, G  MG BY N  (INEQUALITY CONSTRAINTS) */

/*     INPUT.. */

/*      W(*,*) CONTAINS  (A B) IN ROWS 1,...,MA+MG, COLS 1,...,N+1. */
/*                       (G H) */

/*     MDW,MA,MG,N */
/*              CONTAIN (RESP) VAR. DIMENSION OF W(*,*), */
/*              AND MATRIX DIMENSIONS. */

/*     PRGOPT(*), */
/*              PROGRAM OPTION VECTOR. */

/*     OUTPUT.. */

/*      X(*),RNORM */

/*              SOLUTION VECTOR(UNLESS MODE=2), LENGTH OF AX-B. */

/*      MODE */
/*              =0   INEQUALITY CONSTRAINTS ARE COMPATIBLE. */
/*              =2   INEQUALITY CONSTRAINTS CONTRADICTORY. */

/*      WS(*), */
/*              WORKING STORAGE OF DIMENSION K+N+(MG+2)*(N+7), */
/*              WHERE K=MAX(MA+MG,N). */
/*      IP(MG+2*N+1) */
/*              INTEGER WORKING STORAGE */
/*      REVISED OCT. 1, 1981. */

/*     SUBROUTINES CALLED */

/*     LPDP          THIS SUBPROGRAM MINIMIZES A SUM OF SQUARES */
/*                   OF UNKNOWNS SUBJECT TO LINEAR INEQUALITY */
/*                   CONSTRAINTS.  PART OF THIS PACKAGE. */

/* ++ */
/*     DDOT,DSCAL    SUBROUTINES FROM THE BLAS PACKAGE. */
/*     DAXPY,DASUM,  SEE TRANS. MATH. SOFT., VOL. 5, NO. 3, P. 308. */
/*     DCOPY,DSWAP */

/*     HFTI          SOLVES AN UNCONSTRAINED LINEAR LEAST SQUARES */
/*                   PROBLEM.  PART OF THIS PACKAGE. */

/*     H12           SUBROUTINE TO CONSTRUCT AND APPLY A HOUSEHOLDER */
/*                   TRANSFORMATION. */

/*     SUBROUTINE LSI(W,MDW,MA,MG,N,PRGOPT,X,RNORM,MODE,WS,IP) */

/*<       DOUBLE PRECISION W(MDW,1), PRGOPT(1), RNORM, WS(1), X(1) >*/
/*<       INTEGER IP(1) >*/
/*<        >*/
/*<       DOUBLE PRECISION DASUM, DDOT, DSQRT, DMAX1 >*/
/*<       LOGICAL COV >*/

/*<       DATA ZERO /0.D0/, DRELPR /0.D0/, ONE /1.D0/, HALF /.5E0/ >*/
#line 77 "../fortran/lsi.f"
    /* Parameter adjustments */
#line 77 "../fortran/lsi.f"
    w_dim1 = *mdw;
#line 77 "../fortran/lsi.f"
    w_offset = 1 + w_dim1;
#line 77 "../fortran/lsi.f"
    w -= w_offset;
#line 77 "../fortran/lsi.f"
    --prgopt;
#line 77 "../fortran/lsi.f"
    --x;
#line 77 "../fortran/lsi.f"
    --ws;
#line 77 "../fortran/lsi.f"
    --ip;
#line 77 "../fortran/lsi.f"

#line 77 "../fortran/lsi.f"
    /* Function Body */

/*     COMPUTE MACHINE PRECISION=DRELPR ONLY WHEN NECESSARY. */
/*<       IF (.NOT.(DRELPR.EQ.ZERO)) GO TO 30 >*/
#line 80 "../fortran/lsi.f"
    if (! (drelpr == zero)) {
#line 80 "../fortran/lsi.f"
	goto L30;
#line 80 "../fortran/lsi.f"
    }
/*<       DRELPR = ONE >*/
#line 81 "../fortran/lsi.f"
    drelpr = one;
/*<    10 IF (ONE+DRELPR.EQ.ONE) GO TO 20 >*/
#line 82 "../fortran/lsi.f"
L10:
#line 82 "../fortran/lsi.f"
    if (one + drelpr == one) {
#line 82 "../fortran/lsi.f"
	goto L20;
#line 82 "../fortran/lsi.f"
    }
/*<       DRELPR = DRELPR*HALF >*/
#line 83 "../fortran/lsi.f"
    drelpr *= half;
/*<       GO TO 10 >*/
#line 84 "../fortran/lsi.f"
    goto L10;
/*<    20 DRELPR = DRELPR + DRELPR >*/
#line 85 "../fortran/lsi.f"
L20:
#line 85 "../fortran/lsi.f"
    drelpr += drelpr;
/*<    30 MODE = 0 >*/
#line 86 "../fortran/lsi.f"
L30:
#line 86 "../fortran/lsi.f"
    *mode = 0;
/*<       RNORM = ZERO >*/
#line 87 "../fortran/lsi.f"
    *rnorm = zero;
/*<       M = MA + MG >*/
#line 88 "../fortran/lsi.f"
    m = *ma + *mg;
/*<       NP1 = N + 1 >*/
#line 89 "../fortran/lsi.f"
    np1 = *n + 1;
/*<       KRANK = 0 >*/
#line 90 "../fortran/lsi.f"
    krank = 0;
/*<       IF (N.LE.0 .OR. M.LE.0) GO TO 70 >*/
#line 91 "../fortran/lsi.f"
    if (*n <= 0 || m <= 0) {
#line 91 "../fortran/lsi.f"
	goto L70;
#line 91 "../fortran/lsi.f"
    }
/*<       ASSIGN 40 TO IGO994 >*/
#line 92 "../fortran/lsi.f"
    igo994 = 0;
#line 92 "../fortran/lsi.f"
    igo994_fmt = fmt_40;
/*<       GO TO 500 >*/
#line 93 "../fortran/lsi.f"
    goto L500;

/*     PROCESS-OPTION-VECTOR */

/*     COMPUTE MATRIX NORM OF LEAST SQUARES EQUAS. */
/*<    40 ANORM = ZERO >*/
#line 98 "../fortran/lsi.f"
L40:
#line 98 "../fortran/lsi.f"
    anorm = zero;
/*<       DO 50 J=1,N >*/
#line 99 "../fortran/lsi.f"
    i__1 = *n;
#line 99 "../fortran/lsi.f"
    for (j = 1; j <= i__1; ++j) {
/*<         ANORM = DMAX1(ANORM,DASUM(MA,W(1,J),1)) >*/
/* Computing MAX */
#line 100 "../fortran/lsi.f"
	d__1 = anorm, d__2 = dasum_(ma, &w[j * w_dim1 + 1], &c__1);
#line 100 "../fortran/lsi.f"
	anorm = max(d__1,d__2);
/*<    50 CONTINUE >*/
#line 101 "../fortran/lsi.f"
/* L50: */
#line 101 "../fortran/lsi.f"
    }

/*     SET TOL FOR HFTI( ) RANK TEST. */
/*<       TAU = TOL*ANORM >*/
#line 104 "../fortran/lsi.f"
    tau = tol * anorm;

/*     COMPUTE HOUSEHOLDER ORTHOGONAL DECOMP OF MATRIX. */
/*<       IF (N.GT.0) WS(1) = ZERO >*/
#line 107 "../fortran/lsi.f"
    if (*n > 0) {
#line 107 "../fortran/lsi.f"
	ws[1] = zero;
#line 107 "../fortran/lsi.f"
    }
/*<       CALL DCOPY(N, WS, 0, WS, 1) >*/
#line 108 "../fortran/lsi.f"
    dcopy_(n, &ws[1], &c__0, &ws[1], &c__1);
/*<       CALL DCOPY(MA, W(1,NP1), 1, WS, 1) >*/
#line 109 "../fortran/lsi.f"
    dcopy_(ma, &w[np1 * w_dim1 + 1], &c__1, &ws[1], &c__1);
/*<       K = MAX0(M,N) >*/
#line 110 "../fortran/lsi.f"
    k = max(m,*n);
/*<       MINMAN = MIN0(MA,N) >*/
#line 111 "../fortran/lsi.f"
    minman = min(*ma,*n);
/*<       N1 = K + 1 >*/
#line 112 "../fortran/lsi.f"
    n1 = k + 1;
/*<       N2 = N1 + N >*/
#line 113 "../fortran/lsi.f"
    n2 = n1 + *n;
/*<        >*/
#line 114 "../fortran/lsi.f"
    hfti_(&w[w_offset], mdw, ma, n, &ws[1], &c__1, &c__1, &tau, &krank, rnorm,
	     &ws[n2], &ws[n1], &ip[1]);
/*<       FAC = ONE >*/
#line 116 "../fortran/lsi.f"
    fac = one;
/*<       GAM=MA-KRANK >*/
#line 117 "../fortran/lsi.f"
    gam = (doublereal) (*ma - krank);
/*<       IF (KRANK.LT.MA) FAC = RNORM**2/GAM >*/
#line 118 "../fortran/lsi.f"
    if (krank < *ma) {
/* Computing 2nd power */
#line 118 "../fortran/lsi.f"
	d__1 = *rnorm;
#line 118 "../fortran/lsi.f"
	fac = d__1 * d__1 / gam;
#line 118 "../fortran/lsi.f"
    }
/*<       ASSIGN 60 TO IGO990 >*/
#line 119 "../fortran/lsi.f"
    igo990 = 0;
#line 119 "../fortran/lsi.f"
    igo990_fmt = fmt_60;
/*<       GO TO 80 >*/
#line 120 "../fortran/lsi.f"
    goto L80;

/*     REDUCE-TO-LPDP-AND-SOLVE */
/*<    60 CONTINUE >*/
#line 123 "../fortran/lsi.f"
L60:
/*<    70 IP(1) = KRANK >*/
#line 124 "../fortran/lsi.f"
L70:
#line 124 "../fortran/lsi.f"
    ip[1] = krank;
/*<       IP(2) = N + MAX0(M,N) + (MG+2)*(N+7) >*/
#line 125 "../fortran/lsi.f"
    ip[2] = *n + max(m,*n) + (*mg + 2) * (*n + 7);
/*<       RETURN >*/
#line 126 "../fortran/lsi.f"
    return 0;
/*<    80 CONTINUE >*/
#line 127 "../fortran/lsi.f"
L80:

/*     TO REDUCE-TO-LPDP-AND-SOLVE */
/*<       MAP1 = MA + 1 >*/
#line 130 "../fortran/lsi.f"
    map1 = *ma + 1;

/*     COMPUTE INEQ. RT-HAND SIDE FOR LPDP. */
/*<       IF (.NOT.(MA.LT.M)) GO TO 260 >*/
#line 133 "../fortran/lsi.f"
    if (! (*ma < m)) {
#line 133 "../fortran/lsi.f"
	goto L260;
#line 133 "../fortran/lsi.f"
    }
/*<       IF (.NOT.(MINMAN.GT.0)) GO TO 160 >*/
#line 134 "../fortran/lsi.f"
    if (! (minman > 0)) {
#line 134 "../fortran/lsi.f"
	goto L160;
#line 134 "../fortran/lsi.f"
    }
/*<       DO 90 I=MAP1,M >*/
#line 135 "../fortran/lsi.f"
    i__1 = m;
#line 135 "../fortran/lsi.f"
    for (i__ = map1; i__ <= i__1; ++i__) {
/*<         W(I,NP1) = W(I,NP1) - DDOT(N,W(I,1),MDW,WS,1) >*/
#line 136 "../fortran/lsi.f"
	w[i__ + np1 * w_dim1] -= ddot_(n, &w[i__ + w_dim1], mdw, &ws[1], &
		c__1);
/*<    90 CONTINUE >*/
#line 137 "../fortran/lsi.f"
/* L90: */
#line 137 "../fortran/lsi.f"
    }
/*<       DO 100 I=1,MINMAN >*/
#line 138 "../fortran/lsi.f"
    i__1 = minman;
#line 138 "../fortran/lsi.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         J = IP(I) >*/
#line 139 "../fortran/lsi.f"
	j = ip[i__];

/*     APPLY PERMUTATIONS TO COLS OF INEQ. CONSTRAINT MATRIX. */
/*<         CALL DSWAP(MG, W(MAP1,I), 1, W(MAP1,J), 1) >*/
#line 142 "../fortran/lsi.f"
	dswap_(mg, &w[map1 + i__ * w_dim1], &c__1, &w[map1 + j * w_dim1], &
		c__1);
/*<   100 CONTINUE >*/
#line 143 "../fortran/lsi.f"
/* L100: */
#line 143 "../fortran/lsi.f"
    }

/*     APPLY HOUSEHOLDER TRANSFORMATIONS TO CONSTRAINT MATRIX. */
/*<       IF (.NOT.(0.LT.KRANK .AND. KRANK.LT.N)) GO TO 120 >*/
#line 146 "../fortran/lsi.f"
    if (! (0 < krank && krank < *n)) {
#line 146 "../fortran/lsi.f"
	goto L120;
#line 146 "../fortran/lsi.f"
    }
/*<       DO 110 II=1,KRANK >*/
#line 147 "../fortran/lsi.f"
    i__1 = krank;
#line 147 "../fortran/lsi.f"
    for (ii = 1; ii <= i__1; ++ii) {
/*<         I = KRANK + 1 - II >*/
#line 148 "../fortran/lsi.f"
	i__ = krank + 1 - ii;
/*<         L = N1 + I >*/
#line 149 "../fortran/lsi.f"
	l = n1 + i__;
/*<        >*/
#line 150 "../fortran/lsi.f"
	i__2 = krank + 1;
#line 150 "../fortran/lsi.f"
	h12_(&c__2, &i__, &i__2, n, &w[i__ + w_dim1], mdw, &ws[l - 1], &w[
		map1 + w_dim1], mdw, &c__1, mg);
/*<   110 CONTINUE >*/
#line 152 "../fortran/lsi.f"
/* L110: */
#line 152 "../fortran/lsi.f"
    }

/*     COMPUTE PERMUTED INEQ. CONSTR. MATRIX TIMES R-INVERSE. */
/*<   120 DO 150 I=MAP1,M >*/
#line 155 "../fortran/lsi.f"
L120:
#line 155 "../fortran/lsi.f"
    i__1 = m;
#line 155 "../fortran/lsi.f"
    for (i__ = map1; i__ <= i__1; ++i__) {
/*<         IF (.NOT.(0.LT.KRANK)) GO TO 140 >*/
#line 156 "../fortran/lsi.f"
	if (! (0 < krank)) {
#line 156 "../fortran/lsi.f"
	    goto L140;
#line 156 "../fortran/lsi.f"
	}
/*<         DO 130 J=1,KRANK >*/
#line 157 "../fortran/lsi.f"
	i__2 = krank;
#line 157 "../fortran/lsi.f"
	for (j = 1; j <= i__2; ++j) {
/*<           W(I,J) = (W(I,J)-DDOT(J-1,W(1,J),1,W(I,1),MDW))/W(J,J) >*/
#line 158 "../fortran/lsi.f"
	    i__3 = j - 1;
#line 158 "../fortran/lsi.f"
	    w[i__ + j * w_dim1] = (w[i__ + j * w_dim1] - ddot_(&i__3, &w[j * 
		    w_dim1 + 1], &c__1, &w[i__ + w_dim1], mdw)) / w[j + j * 
		    w_dim1];
/*<   130   CONTINUE >*/
#line 159 "../fortran/lsi.f"
/* L130: */
#line 159 "../fortran/lsi.f"
	}
/*<   140   CONTINUE >*/
#line 160 "../fortran/lsi.f"
L140:
/*<   150 CONTINUE >*/
#line 161 "../fortran/lsi.f"
/* L150: */
#line 161 "../fortran/lsi.f"
	;
#line 161 "../fortran/lsi.f"
    }

/*     SOLVE THE REDUCED PROBLEM WITH LPDP ALGORITHM, */
/*     THE LEAST PROJECTED DISTANCE PROBLEM. */
/*<   160  >*/
#line 165 "../fortran/lsi.f"
L160:
#line 165 "../fortran/lsi.f"
    i__1 = *n - krank;
#line 165 "../fortran/lsi.f"
    lpdp_(&w[map1 + w_dim1], mdw, mg, &krank, &i__1, &prgopt[1], &x[1], &
	    xnorm, &mdlpdp, &ws[n2], &ip[*n + 1]);
/*<       IF (.NOT.(MDLPDP.EQ.1)) GO TO 240 >*/
#line 167 "../fortran/lsi.f"
    if (! (mdlpdp == 1)) {
#line 167 "../fortran/lsi.f"
	goto L240;
#line 167 "../fortran/lsi.f"
    }
/*<       IF (.NOT.(KRANK.GT.0)) GO TO 180 >*/
#line 168 "../fortran/lsi.f"
    if (! (krank > 0)) {
#line 168 "../fortran/lsi.f"
	goto L180;
#line 168 "../fortran/lsi.f"
    }

/*     COMPUTE SOLN IN ORIGINAL COORDINATES. */
/*<       DO 170 II=1,KRANK >*/
#line 171 "../fortran/lsi.f"
    i__1 = krank;
#line 171 "../fortran/lsi.f"
    for (ii = 1; ii <= i__1; ++ii) {
/*<         I = KRANK + 1 - II >*/
#line 172 "../fortran/lsi.f"
	i__ = krank + 1 - ii;
/*<         X(I) = (X(I)-DDOT(II-1,W(I,I+1),MDW,X(I+1),1))/W(I,I) >*/
#line 173 "../fortran/lsi.f"
	i__2 = ii - 1;
#line 173 "../fortran/lsi.f"
	x[i__] = (x[i__] - ddot_(&i__2, &w[i__ + (i__ + 1) * w_dim1], mdw, &x[
		i__ + 1], &c__1)) / w[i__ + i__ * w_dim1];
/*<   170 CONTINUE >*/
#line 174 "../fortran/lsi.f"
/* L170: */
#line 174 "../fortran/lsi.f"
    }

/*     APPLY HOUSEHOLDER TRANS. TO SOLN VECTOR. */
/*<   180 IF (.NOT.(0.LT.KRANK .AND. KRANK.LT.N)) GO TO 200 >*/
#line 177 "../fortran/lsi.f"
L180:
#line 177 "../fortran/lsi.f"
    if (! (0 < krank && krank < *n)) {
#line 177 "../fortran/lsi.f"
	goto L200;
#line 177 "../fortran/lsi.f"
    }
/*<       DO 190 I=1,KRANK >*/
#line 178 "../fortran/lsi.f"
    i__1 = krank;
#line 178 "../fortran/lsi.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         L = N1 + I >*/
#line 179 "../fortran/lsi.f"
	l = n1 + i__;
/*<         CALL H12(2, I, KRANK+1, N, W(I,1), MDW, WS(L-1), X, 1, 1, 1) >*/
#line 180 "../fortran/lsi.f"
	i__2 = krank + 1;
#line 180 "../fortran/lsi.f"
	h12_(&c__2, &i__, &i__2, n, &w[i__ + w_dim1], mdw, &ws[l - 1], &x[1], 
		&c__1, &c__1, &c__1);
/*<   190 CONTINUE >*/
#line 181 "../fortran/lsi.f"
/* L190: */
#line 181 "../fortran/lsi.f"
    }
/*<   200 IF (.NOT.(MINMAN.GT.0)) GO TO 230 >*/
#line 182 "../fortran/lsi.f"
L200:
#line 182 "../fortran/lsi.f"
    if (! (minman > 0)) {
#line 182 "../fortran/lsi.f"
	goto L230;
#line 182 "../fortran/lsi.f"
    }

/*     REPERMUTE VARIABLES TO THEIR INPUT ORDER. */
/*<       DO 210 II=1,MINMAN >*/
#line 185 "../fortran/lsi.f"
    i__1 = minman;
#line 185 "../fortran/lsi.f"
    for (ii = 1; ii <= i__1; ++ii) {
/*<         I = MINMAN + 1 - II >*/
#line 186 "../fortran/lsi.f"
	i__ = minman + 1 - ii;
/*<         J = IP(I) >*/
#line 187 "../fortran/lsi.f"
	j = ip[i__];
/*<         CALL DSWAP(1, X(I), 1, X(J), 1) >*/
#line 188 "../fortran/lsi.f"
	dswap_(&c__1, &x[i__], &c__1, &x[j], &c__1);
/*<   210 CONTINUE >*/
#line 189 "../fortran/lsi.f"
/* L210: */
#line 189 "../fortran/lsi.f"
    }

/*     VARIABLES ARE NOW IN ORIG. COORDINATES. */
/*     ADD SOLN OF UNSCONSTRAINED PROB. */
/*<       DO 220 I=1,N >*/
#line 193 "../fortran/lsi.f"
    i__1 = *n;
#line 193 "../fortran/lsi.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         X(I) = X(I) + WS(I) >*/
#line 194 "../fortran/lsi.f"
	x[i__] += ws[i__];
/*<   220 CONTINUE >*/
#line 195 "../fortran/lsi.f"
/* L220: */
#line 195 "../fortran/lsi.f"
    }

/*     COMPUTE THE RESIDUAL VECTOR NORM. */
/*<       RNORM = DSQRT(RNORM**2+XNORM**2) >*/
/* Computing 2nd power */
#line 198 "../fortran/lsi.f"
    d__1 = *rnorm;
/* Computing 2nd power */
#line 198 "../fortran/lsi.f"
    d__2 = xnorm;
#line 198 "../fortran/lsi.f"
    *rnorm = sqrt(d__1 * d__1 + d__2 * d__2);
/*<   230 GO TO 250 >*/
#line 199 "../fortran/lsi.f"
L230:
#line 199 "../fortran/lsi.f"
    goto L250;
/*<   240 MODE = 2 >*/
#line 200 "../fortran/lsi.f"
L240:
#line 200 "../fortran/lsi.f"
    *mode = 2;
/*<   250 GO TO 270 >*/
#line 201 "../fortran/lsi.f"
L250:
#line 201 "../fortran/lsi.f"
    goto L270;
/*<   260 CALL DCOPY(N, WS, 1, X, 1) >*/
#line 202 "../fortran/lsi.f"
L260:
#line 202 "../fortran/lsi.f"
    dcopy_(n, &ws[1], &c__1, &x[1], &c__1);
/*<   270 IF (.NOT.(COV .AND. KRANK.GT.0)) GO TO 490 >*/
#line 203 "../fortran/lsi.f"
L270:
#line 203 "../fortran/lsi.f"
    if (! (cov && krank > 0)) {
#line 203 "../fortran/lsi.f"
	goto L490;
#line 203 "../fortran/lsi.f"
    }

/*     COMPUTE COVARIANCE MATRIX BASED ON THE ORTHOGONAL DECOMP. */
/*     FROM HFTI( ). */

/*<       KRM1 = KRANK - 1 >*/
#line 208 "../fortran/lsi.f"
    krm1 = krank - 1;
/*<       KRP1 = KRANK + 1 >*/
#line 209 "../fortran/lsi.f"
    krp1 = krank + 1;

/*     COPY DIAG. TERMS TO WORKING ARRAY. */
/*<       CALL DCOPY(KRANK, W, MDW+1, WS(N2), 1) >*/
#line 212 "../fortran/lsi.f"
    i__1 = *mdw + 1;
#line 212 "../fortran/lsi.f"
    dcopy_(&krank, &w[w_offset], &i__1, &ws[n2], &c__1);

/*     RECIPROCATE DIAG. TERMS. */
/*<       DO 280 J=1,KRANK >*/
#line 215 "../fortran/lsi.f"
    i__1 = krank;
#line 215 "../fortran/lsi.f"
    for (j = 1; j <= i__1; ++j) {
/*<         W(J,J) = ONE/W(J,J) >*/
#line 216 "../fortran/lsi.f"
	w[j + j * w_dim1] = one / w[j + j * w_dim1];
/*<   280 CONTINUE >*/
#line 217 "../fortran/lsi.f"
/* L280: */
#line 217 "../fortran/lsi.f"
    }
/*<       IF (.NOT.(KRANK.GT.1)) GO TO 310 >*/
#line 218 "../fortran/lsi.f"
    if (! (krank > 1)) {
#line 218 "../fortran/lsi.f"
	goto L310;
#line 218 "../fortran/lsi.f"
    }

/*     INVERT THE UPPER TRIANGULAR QR FACTOR ON ITSELF. */
/*<       DO 300 I=1,KRM1 >*/
#line 221 "../fortran/lsi.f"
    i__1 = krm1;
#line 221 "../fortran/lsi.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         IP1 = I + 1 >*/
#line 222 "../fortran/lsi.f"
	ip1 = i__ + 1;
/*<         DO 290 J=IP1,KRANK >*/
#line 223 "../fortran/lsi.f"
	i__2 = krank;
#line 223 "../fortran/lsi.f"
	for (j = ip1; j <= i__2; ++j) {
/*<           W(I,J) = -DDOT(J-I,W(I,I),MDW,W(I,J),1)*W(J,J) >*/
#line 224 "../fortran/lsi.f"
	    i__3 = j - i__;
#line 224 "../fortran/lsi.f"
	    w[i__ + j * w_dim1] = -ddot_(&i__3, &w[i__ + i__ * w_dim1], mdw, &
		    w[i__ + j * w_dim1], &c__1) * w[j + j * w_dim1];
/*<   290   CONTINUE >*/
#line 225 "../fortran/lsi.f"
/* L290: */
#line 225 "../fortran/lsi.f"
	}
/*<   300 CONTINUE >*/
#line 226 "../fortran/lsi.f"
/* L300: */
#line 226 "../fortran/lsi.f"
    }

/*     COMPUTE THE INVERTED FACTOR TIMES ITS TRANSPOSE. */
/*<   310 DO 330 I=1,KRANK >*/
#line 229 "../fortran/lsi.f"
L310:
#line 229 "../fortran/lsi.f"
    i__1 = krank;
#line 229 "../fortran/lsi.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         DO 320 J=I,KRANK >*/
#line 230 "../fortran/lsi.f"
	i__2 = krank;
#line 230 "../fortran/lsi.f"
	for (j = i__; j <= i__2; ++j) {
/*<           W(I,J) = DDOT(KRANK+1-J,W(I,J),MDW,W(J,J),MDW) >*/
#line 231 "../fortran/lsi.f"
	    i__3 = krank + 1 - j;
#line 231 "../fortran/lsi.f"
	    w[i__ + j * w_dim1] = ddot_(&i__3, &w[i__ + j * w_dim1], mdw, &w[
		    j + j * w_dim1], mdw);
/*<   320   CONTINUE >*/
#line 232 "../fortran/lsi.f"
/* L320: */
#line 232 "../fortran/lsi.f"
	}
/*<   330 CONTINUE >*/
#line 233 "../fortran/lsi.f"
/* L330: */
#line 233 "../fortran/lsi.f"
    }
/*<       IF (.NOT.(KRANK.LT.N)) GO TO 450 >*/
#line 234 "../fortran/lsi.f"
    if (! (krank < *n)) {
#line 234 "../fortran/lsi.f"
	goto L450;
#line 234 "../fortran/lsi.f"
    }

/*     ZERO OUT LOWER TRAPEZOIDAL PART. */
/*     COPY UPPER TRI. TO LOWER TRI. PART. */
/*<       DO 340 J=1,KRANK >*/
#line 238 "../fortran/lsi.f"
    i__1 = krank;
#line 238 "../fortran/lsi.f"
    for (j = 1; j <= i__1; ++j) {
/*<         CALL DCOPY(J, W(1,J), 1, W(J,1), MDW) >*/
#line 239 "../fortran/lsi.f"
	dcopy_(&j, &w[j * w_dim1 + 1], &c__1, &w[j + w_dim1], mdw);
/*<   340 CONTINUE >*/
#line 240 "../fortran/lsi.f"
/* L340: */
#line 240 "../fortran/lsi.f"
    }
/*<       DO 350 I=KRP1,N >*/
#line 241 "../fortran/lsi.f"
    i__1 = *n;
#line 241 "../fortran/lsi.f"
    for (i__ = krp1; i__ <= i__1; ++i__) {
/*<         W(I,1) = ZERO >*/
#line 242 "../fortran/lsi.f"
	w[i__ + w_dim1] = zero;
/*<         CALL DCOPY(I, W(I,1), 0, W(I,1), MDW) >*/
#line 243 "../fortran/lsi.f"
	dcopy_(&i__, &w[i__ + w_dim1], &c__0, &w[i__ + w_dim1], mdw);
/*<   350 CONTINUE >*/
#line 244 "../fortran/lsi.f"
/* L350: */
#line 244 "../fortran/lsi.f"
    }

/*     APPLY RIGHT SIDE TRANSFORMATIONS TO LOWER TRI. */
/*<       N3 = N2 + KRP1 >*/
#line 247 "../fortran/lsi.f"
    n3 = n2 + krp1;
/*<       DO 430 I=1,KRANK >*/
#line 248 "../fortran/lsi.f"
    i__1 = krank;
#line 248 "../fortran/lsi.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         L = N1 + I >*/
#line 249 "../fortran/lsi.f"
	l = n1 + i__;
/*<         K = N2 + I >*/
#line 250 "../fortran/lsi.f"
	k = n2 + i__;
/*<         RB = WS(L-1)*WS(K-1) >*/
#line 251 "../fortran/lsi.f"
	rb = ws[l - 1] * ws[k - 1];
/*<         IF (.NOT.(RB.LT.ZERO)) GO TO 420 >*/
#line 252 "../fortran/lsi.f"
	if (! (rb < zero)) {
#line 252 "../fortran/lsi.f"
	    goto L420;
#line 252 "../fortran/lsi.f"
	}

/*     IF RB.GE.ZERO, TRANSFORMATION CAN BE REGARDED AS ZERO. */
/*<         RB = ONE/RB >*/
#line 255 "../fortran/lsi.f"
	rb = one / rb;

/*     STORE UNSCALED RANK-ONE HOUSEHOLDER UPDATE IN WORK ARRAY. */
/*<         WS(N3) = ZERO >*/
#line 258 "../fortran/lsi.f"
	ws[n3] = zero;
/*<         CALL DCOPY(N, WS(N3), 0, WS(N3), 1) >*/
#line 259 "../fortran/lsi.f"
	dcopy_(n, &ws[n3], &c__0, &ws[n3], &c__1);
/*<         L = N1 + I >*/
#line 260 "../fortran/lsi.f"
	l = n1 + i__;
/*<         K = N3 + I >*/
#line 261 "../fortran/lsi.f"
	k = n3 + i__;
/*<         WS(K-1) = WS(L-1) >*/
#line 262 "../fortran/lsi.f"
	ws[k - 1] = ws[l - 1];
/*<         DO 360 J=KRP1,N >*/
#line 263 "../fortran/lsi.f"
	i__2 = *n;
#line 263 "../fortran/lsi.f"
	for (j = krp1; j <= i__2; ++j) {
/*<           K = N3 + J >*/
#line 264 "../fortran/lsi.f"
	    k = n3 + j;
/*<           WS(K-1) = W(I,J) >*/
#line 265 "../fortran/lsi.f"
	    ws[k - 1] = w[i__ + j * w_dim1];
/*<   360   CONTINUE >*/
#line 266 "../fortran/lsi.f"
/* L360: */
#line 266 "../fortran/lsi.f"
	}
/*<         DO 370 J=1,N >*/
#line 267 "../fortran/lsi.f"
	i__2 = *n;
#line 267 "../fortran/lsi.f"
	for (j = 1; j <= i__2; ++j) {
/*<           L = N3 + I >*/
#line 268 "../fortran/lsi.f"
	    l = n3 + i__;
/*<           K = N3 + J >*/
#line 269 "../fortran/lsi.f"
	    k = n3 + j;
/*<        >*/
#line 270 "../fortran/lsi.f"
	    i__3 = j - i__;
#line 270 "../fortran/lsi.f"
	    i__4 = *n - j + 1;
#line 270 "../fortran/lsi.f"
	    ws[j] = ddot_(&i__3, &w[j + i__ * w_dim1], mdw, &ws[l - 1], &c__1)
		     + ddot_(&i__4, &w[j + j * w_dim1], &c__1, &ws[k - 1], &
		    c__1);
/*<           WS(J) = WS(J)*RB >*/
#line 272 "../fortran/lsi.f"
	    ws[j] *= rb;
/*<   370   CONTINUE >*/
#line 273 "../fortran/lsi.f"
/* L370: */
#line 273 "../fortran/lsi.f"
	}
/*<         L = N3 + I >*/
#line 274 "../fortran/lsi.f"
	l = n3 + i__;
/*<         GAM = DDOT(N-I+1,WS(L-1),1,WS(I),1)*RB >*/
#line 275 "../fortran/lsi.f"
	i__2 = *n - i__ + 1;
#line 275 "../fortran/lsi.f"
	gam = ddot_(&i__2, &ws[l - 1], &c__1, &ws[i__], &c__1) * rb;
/*<         GAM = GAM*HALF >*/
#line 276 "../fortran/lsi.f"
	gam *= half;
/*<         CALL DAXPY(N-I+1, GAM, WS(L-1), 1, WS(I), 1) >*/
#line 277 "../fortran/lsi.f"
	i__2 = *n - i__ + 1;
#line 277 "../fortran/lsi.f"
	daxpy_(&i__2, &gam, &ws[l - 1], &c__1, &ws[i__], &c__1);
/*<         DO 410 J=I,N >*/
#line 278 "../fortran/lsi.f"
	i__2 = *n;
#line 278 "../fortran/lsi.f"
	for (j = i__; j <= i__2; ++j) {
/*<           IF (.NOT.(I.GT.1)) GO TO 390 >*/
#line 279 "../fortran/lsi.f"
	    if (! (i__ > 1)) {
#line 279 "../fortran/lsi.f"
		goto L390;
#line 279 "../fortran/lsi.f"
	    }
/*<           IM1 = I - 1 >*/
#line 280 "../fortran/lsi.f"
	    im1 = i__ - 1;
/*<           K = N3 + J >*/
#line 281 "../fortran/lsi.f"
	    k = n3 + j;
/*<           DO 380 L=1,IM1 >*/
#line 282 "../fortran/lsi.f"
	    i__3 = im1;
#line 282 "../fortran/lsi.f"
	    for (l = 1; l <= i__3; ++l) {
/*<             W(J,L) = W(J,L) + WS(K-1)*WS(L) >*/
#line 283 "../fortran/lsi.f"
		w[j + l * w_dim1] += ws[k - 1] * ws[l];
/*<   380     CONTINUE >*/
#line 284 "../fortran/lsi.f"
/* L380: */
#line 284 "../fortran/lsi.f"
	    }
/*<   390     K = N3 + J >*/
#line 285 "../fortran/lsi.f"
L390:
#line 285 "../fortran/lsi.f"
	    k = n3 + j;
/*<           DO 400 L=I,J >*/
#line 286 "../fortran/lsi.f"
	    i__3 = j;
#line 286 "../fortran/lsi.f"
	    for (l = i__; l <= i__3; ++l) {
/*<             IL = N3 + L >*/
#line 287 "../fortran/lsi.f"
		il = n3 + l;
/*<             W(J,L) = W(J,L) + WS(J)*WS(IL-1) + WS(L)*WS(K-1) >*/
#line 288 "../fortran/lsi.f"
		w[j + l * w_dim1] = w[j + l * w_dim1] + ws[j] * ws[il - 1] + 
			ws[l] * ws[k - 1];
/*<   400     CONTINUE >*/
#line 289 "../fortran/lsi.f"
/* L400: */
#line 289 "../fortran/lsi.f"
	    }
/*<   410   CONTINUE >*/
#line 290 "../fortran/lsi.f"
/* L410: */
#line 290 "../fortran/lsi.f"
	}
/*<   420   CONTINUE >*/
#line 291 "../fortran/lsi.f"
L420:
/*<   430 CONTINUE >*/
#line 292 "../fortran/lsi.f"
/* L430: */
#line 292 "../fortran/lsi.f"
	;
#line 292 "../fortran/lsi.f"
    }

/*     COPY LOWER TRI. TO UPPER TRI. TO SYMMETRIZE THE COVARIANCE MATRIX. */
/*<       DO 440 I=1,N >*/
#line 295 "../fortran/lsi.f"
    i__1 = *n;
#line 295 "../fortran/lsi.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         CALL DCOPY(I, W(I,1), MDW, W(1,I), 1) >*/
#line 296 "../fortran/lsi.f"
	dcopy_(&i__, &w[i__ + w_dim1], mdw, &w[i__ * w_dim1 + 1], &c__1);
/*<   440 CONTINUE >*/
#line 297 "../fortran/lsi.f"
/* L440: */
#line 297 "../fortran/lsi.f"
    }

/*     REPERMUTE ROWS AND COLS. */
/*<   450 DO 470 II=1,MINMAN >*/
#line 300 "../fortran/lsi.f"
L450:
#line 300 "../fortran/lsi.f"
    i__1 = minman;
#line 300 "../fortran/lsi.f"
    for (ii = 1; ii <= i__1; ++ii) {
/*<         I = MINMAN + 1 - II >*/
#line 301 "../fortran/lsi.f"
	i__ = minman + 1 - ii;
/*<         K = IP(I) >*/
#line 302 "../fortran/lsi.f"
	k = ip[i__];
/*<         IF (.NOT.(I.NE.K)) GO TO 460 >*/
#line 303 "../fortran/lsi.f"
	if (! (i__ != k)) {
#line 303 "../fortran/lsi.f"
	    goto L460;
#line 303 "../fortran/lsi.f"
	}
/*<         CALL DSWAP(1, W(I,I), 1, W(K,K), 1) >*/
#line 304 "../fortran/lsi.f"
	dswap_(&c__1, &w[i__ + i__ * w_dim1], &c__1, &w[k + k * w_dim1], &
		c__1);
/*<         CALL DSWAP(I-1, W(1,I), 1, W(1,K), 1) >*/
#line 305 "../fortran/lsi.f"
	i__2 = i__ - 1;
#line 305 "../fortran/lsi.f"
	dswap_(&i__2, &w[i__ * w_dim1 + 1], &c__1, &w[k * w_dim1 + 1], &c__1);
/*<         CALL DSWAP(K-I-1, W(I,I+1), MDW, W(I+1,K), 1) >*/
#line 306 "../fortran/lsi.f"
	i__2 = k - i__ - 1;
#line 306 "../fortran/lsi.f"
	dswap_(&i__2, &w[i__ + (i__ + 1) * w_dim1], mdw, &w[i__ + 1 + k * 
		w_dim1], &c__1);
/*<         CALL DSWAP(N-K, W(I,K+1), MDW, W(K,K+1), MDW) >*/
#line 307 "../fortran/lsi.f"
	i__2 = *n - k;
#line 307 "../fortran/lsi.f"
	dswap_(&i__2, &w[i__ + (k + 1) * w_dim1], mdw, &w[k + (k + 1) * 
		w_dim1], mdw);
/*<   460   CONTINUE >*/
#line 308 "../fortran/lsi.f"
L460:
/*<   470 CONTINUE >*/
#line 309 "../fortran/lsi.f"
/* L470: */
#line 309 "../fortran/lsi.f"
	;
#line 309 "../fortran/lsi.f"
    }

/*     PUT IN NORMALIZED RESIDUAL SUM OF SQUARES SCALE FACTOR */
/*     AND SYMMETRIZE THE RESULTING COVARIANCE MARIX. */
/*<       DO 480 J=1,N >*/
#line 313 "../fortran/lsi.f"
    i__1 = *n;
#line 313 "../fortran/lsi.f"
    for (j = 1; j <= i__1; ++j) {
/*<         CALL DSCAL(J, FAC, W(1,J), 1) >*/
#line 314 "../fortran/lsi.f"
	dscal_(&j, &fac, &w[j * w_dim1 + 1], &c__1);
/*<         CALL DCOPY(J, W(1,J), 1, W(J,1), MDW) >*/
#line 315 "../fortran/lsi.f"
	dcopy_(&j, &w[j * w_dim1 + 1], &c__1, &w[j + w_dim1], mdw);
/*<   480 CONTINUE >*/
#line 316 "../fortran/lsi.f"
/* L480: */
#line 316 "../fortran/lsi.f"
    }
/*<   490 GO TO 540 >*/
#line 317 "../fortran/lsi.f"
L490:
#line 317 "../fortran/lsi.f"
    goto L540;
/*<   500 CONTINUE >*/
#line 318 "../fortran/lsi.f"
L500:

/*     TO PROCESS-OPTION-VECTOR */

/*     THE NOMINAL TOLERANCE USED IN THE CODE, */
/*<       TOL = DSQRT(DRELPR) >*/
#line 323 "../fortran/lsi.f"
    tol = sqrt(drelpr);
/*<       COV = .FALSE. >*/
#line 324 "../fortran/lsi.f"
    cov = FALSE_;
/*<       LAST = 1 >*/
#line 325 "../fortran/lsi.f"
    last = 1;
/*<       LINK = PRGOPT(1) >*/
#line 326 "../fortran/lsi.f"
    link = (integer) prgopt[1];
/*<   510 IF (.NOT.(LINK.GT.1)) GO TO 520 >*/
#line 327 "../fortran/lsi.f"
L510:
#line 327 "../fortran/lsi.f"
    if (! (link > 1)) {
#line 327 "../fortran/lsi.f"
	goto L520;
#line 327 "../fortran/lsi.f"
    }
/*<       KEY = PRGOPT(LAST+1) >*/
#line 328 "../fortran/lsi.f"
    key = (integer) prgopt[last + 1];
/*<       IF (KEY.EQ.1) COV = PRGOPT(LAST+2).NE.ZERO >*/
#line 329 "../fortran/lsi.f"
    if (key == 1) {
#line 329 "../fortran/lsi.f"
	cov = prgopt[last + 2] != zero;
#line 329 "../fortran/lsi.f"
    }
/*<       IF (KEY.EQ.5) TOL = DMAX1(DRELPR,PRGOPT(LAST+2)) >*/
#line 330 "../fortran/lsi.f"
    if (key == 5) {
/* Computing MAX */
#line 330 "../fortran/lsi.f"
	d__1 = drelpr, d__2 = prgopt[last + 2];
#line 330 "../fortran/lsi.f"
	tol = max(d__1,d__2);
#line 330 "../fortran/lsi.f"
    }
/*<       NEXT = PRGOPT(LINK) >*/
#line 331 "../fortran/lsi.f"
    next = (integer) prgopt[link];
/*<       LAST = LINK >*/
#line 332 "../fortran/lsi.f"
    last = link;
/*<       LINK = NEXT >*/
#line 333 "../fortran/lsi.f"
    link = next;
/*<       GO TO 510 >*/
#line 334 "../fortran/lsi.f"
    goto L510;
/*<   520 GO TO 530 >*/
#line 335 "../fortran/lsi.f"
L520:
#line 335 "../fortran/lsi.f"
    goto L530;
/*<   530 GO TO IGO994, (40) >*/
#line 336 "../fortran/lsi.f"
L530:
#line 336 "../fortran/lsi.f"
    switch (igo994) {
#line 336 "../fortran/lsi.f"
	case 0: goto L40;
#line 336 "../fortran/lsi.f"
    }
/*<   540 GO TO IGO990, (60) >*/
#line 337 "../fortran/lsi.f"
L540:
#line 337 "../fortran/lsi.f"
    switch (igo990) {
#line 337 "../fortran/lsi.f"
	case 0: goto L60;
#line 337 "../fortran/lsi.f"
    }
/*<       END >*/
} /* lsi_ */

