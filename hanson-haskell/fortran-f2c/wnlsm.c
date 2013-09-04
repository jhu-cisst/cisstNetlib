#line 1 "../fortran/wnlsm.f"
/* ../fortran/wnlsm.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/wnlsm.f"
/* Table of constant values */

static integer c__0 = 0;
static integer c__1 = 1;
static integer c__39 = 39;
static integer c__53 = 53;
static integer c__2 = 2;

/*<        >*/
/* Subroutine */ int wnlsm_(doublereal *w, integer *mdw, integer *mme, 
	integer *ma, integer *n, integer *l, doublereal *prgopt, doublereal *
	x, doublereal *rnorm, integer *mode, integer *ipivot, integer *itype, 
	doublereal *wd, doublereal *h__, doublereal *scale, doublereal *z__, 
	doublereal *temp, doublereal *d__)
{
    /* Initialized data */

    static doublereal zero = 0.;
    static doublereal one = 1.;
    static doublereal two = 2.;
    static doublereal drelpr = 0.;

    /* Format strings */
    static char fmt_10[] = "";
    static char fmt_20[] = "";
    static char fmt_30[] = "";
    static char fmt_40[] = "";
    static char fmt_60[] = "";
    static char fmt_90[] = "";
    static char fmt_220[] = "";
    static char fmt_310[] = "";
    static char fmt_460[] = "";
    static char fmt_480[] = "";
    static char fmt_500[] = "";
    static char fmt_520[] = "";
    static char fmt_880[] = "";
    static char fmt_900[] = "";
    static char fmt_1010[] = "";

    /* System generated locals */
    integer w_dim1, w_offset, i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    integer i__, j, m;
    doublereal t;
    integer l1;
    doublereal z2;
    extern /* Subroutine */ int h12_(integer *, integer *, integer *, integer 
	    *, doublereal *, integer *, doublereal *, doublereal *, integer *,
	     integer *, integer *);
    integer me, jj, jp;
    doublereal sm, zz;
    integer jm1, nm1, lp1, np1;
    doublereal fac;
    integer key;
    doublereal tau;
    integer niv;
    logical pos;
    integer mep1, krp1, niv1, nsp1;
    logical done;
    doublereal amax, dope[4];
    integer jcon, link, imax;
    doublereal alsq;
    integer last, iter, nerr, isol, iopt;
    doublereal wmax;
    integer next, nopt, igo980, igo991;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    integer igo983, igo958, igo995, igo986, igo977, igo998, igo938, igo897;
    doublereal alpha;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    integer idope[8], krank;
    extern doublereal dasum_(integer *, doublereal *, integer *);
    integer nlink;
    doublereal bnorm;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    integer itemp;
    extern /* Subroutine */ int dswap_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    integer itmax;
    extern /* Subroutine */ int drotm_(integer *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *);
    integer iwmax;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    integer nsoln;
    extern /* Subroutine */ int wnlit_(doublereal *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, logical *);
    doublereal alamda;
    logical feasbl;
    extern integer idamax_(integer *, doublereal *, integer *);
    doublereal eanorm, sparam[5];
    logical hitcon;
    extern /* Subroutine */ int drotmg_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    integer ntimes;
    doublereal blowup;
    extern /* Subroutine */ int xerror_(char *, integer *, integer *, integer 
	    *, ftnlen);

    /* Assigned format variables */
    static char *igo998_fmt, *igo995_fmt, *igo991_fmt, *igo986_fmt, *
	    igo983_fmt, *igo980_fmt, *igo977_fmt, *igo958_fmt, *igo938_fmt, *
	    igo897_fmt;



/*     THE EDITING REQUIRED TO CONVERT THIS SUBROUTINE FROM SINGLE TO */
/*     DOUBLE PRECISION INVOLVES THE FOLLOWING CHARACTER STRING CHANGES. */
/*     USE AN EDITING COMMAND (CHANGE) /STRING-1/(TO)STRING-2/. */
/*     (START CHANGES AT LINE WITH C++ IN COLS. 1-3.) */
/*     /REAL (12 BLANKS)/DOUBLE PRECISION/,/DASUM/DASUM/,/DROTMG/DROTMG/, */
/*     /DNRM2/DNRM2/,/ DSQRT/ DSQRT/,/DROTM/DROTM/,/DMAX1/DMAX1/, */
/*     /DCOPY/DCOPY/,/DSCAL/DSCAL/,/DAXPY/DAXPY/,/D0/D0/,/DSWAP/DSWAP/, */
/*     /IDAMAX/IDAMAX/,/DRELPR/DRELPR/,/.D-/.D-/                   REMK */

/*     THIS IS A COMPANION SUBPROGRAM TO WNNLS( ). */
/*     THE DOCUMENTATION FOR WNNLS( ) HAS MORE COMPLETE */
/*     USAGE INSTRUCTIONS. */

/*     WRITTEN BY KAREN H. HASKELL, SANDIA LABORATORIES, */
/*     WITH THE HELP OF R.J. HANSON, SANDIA LABORATORIES, */
/*     DECEMBER 1976 - JANUARY 1978. */
/*     REVISED MAR. 4, 1982. */

/*     IN ADDITION TO THE PARAMETERS DISCUSSED IN THE PROLOGUE TO */
/*     SUBROUTINE WNNLS, THE FOLLOWING WORK ARRAYS ARE USED IN */
/*     SUBROUTINE WNLSM  (THEY ARE PASSED THROUGH THE CALLING */
/*     SEQUENCE FROM WNNLS FOR PURPOSES OF VARIABLE DIMENSIONING). */
/*     THEIR CONTENTS WILL IN GENERAL BE OF NO INTEREST TO THE USER. */

/*         IPIVOT(*) */
/*            AN ARRAY OF LENGTH N.  UPON COMPLETION IT CONTAINS THE */
/*         PIVOTING INFORMATION FOR THE COLS OF W(*,*). */

/*         ITYPE(*) */
/*            AN ARRAY OF LENGTH M WHICH IS USED TO KEEP TRACK */
/*         OF THE CLASSIFICATION OF THE EQUATIONS.  ITYPE(I)=0 */
/*         DENOTES EQUATION I AS AN EQUALITY CONSTRAINT. */
/*         ITYPE(I)=1 DENOTES EQUATION I AS A LEAST SQUARES */
/*         EQUATION. */

/*         WD(*) */
/*            AN ARRAY OF LENGTH N.  UPON COMPLETION IT CONTAINS THE */
/*         DUAL SOLUTION VECTOR. */

/*         H(*) */
/*            AN ARRAY OF LENGTH N.  UPON COMPLETION IT CONTAINS THE */
/*         PIVOT SCALARS OF THE HOUSEHOLDER TRANSFORMATIONS PERFORMED */
/*         IN THE CASE KRANK.LT.L. */

/*         SCALE(*) */
/*            AN ARRAY OF LENGTH M WHICH IS USED BY THE SUBROUTINE */
/*         TO STORE THE DIAGONAL MATRIX OF WEIGHTS. */
/*         THESE ARE USED TO APPLY THE MODIFIED GIVENS */
/*         TRANSFORMATIONS. */

/*         Z(*),TEMP(*) */
/*            WORKING ARRAYS OF LENGTH N. */

/*         D(*) */
/*            AN ARRAY OF LENGTH N THAT CONTAINS THE */
/*         COLUMN SCALING FOR THE MATRIX (E). */
/*                                       (A) */

/*     SUBROUTINE WNLSM (W,MDW,MME,MA,N,L,PRGOPT,X,RNORM,MODE, */
/*    1                  IPIVOT,ITYPE,WD,H,SCALE,Z,TEMP,D) */
/* ++ */
/*<       DOUBLE PRECISION W(MDW,1), X(1), WD(1), H(1), SCALE(1), DOPE(4) >*/
/*<       DOUBLE PRECISION Z(1), TEMP(1), PRGOPT(1), D(1), SPARAM(5) >*/
/*<       DOUBLE PRECISION ALAMDA, ALPHA, ALSQ, AMAX, BNORM, EANORM >*/
/*<       DOUBLE PRECISION DRELPR, FAC, ONE, BLOWUP >*/
/*<       DOUBLE PRECISION RNORM, SM, T, TAU, TWO, WMAX, ZERO, ZZ, Z2 >*/
/*<       DOUBLE PRECISION DMAX1, DSQRT, DNRM2, DASUM >*/
/*<       INTEGER IPIVOT(1), ITYPE(1), IDAMAX, IDOPE(8) >*/
/*<       LOGICAL HITCON, FEASBL, DONE, POS >*/
/*<       DATA ZERO /0.D0/, ONE /1.D0/, TWO /2.D0/, DRELPR /0.D0/ >*/
#line 74 "../fortran/wnlsm.f"
    /* Parameter adjustments */
#line 74 "../fortran/wnlsm.f"
    w_dim1 = *mdw;
#line 74 "../fortran/wnlsm.f"
    w_offset = 1 + w_dim1;
#line 74 "../fortran/wnlsm.f"
    w -= w_offset;
#line 74 "../fortran/wnlsm.f"
    --prgopt;
#line 74 "../fortran/wnlsm.f"
    --x;
#line 74 "../fortran/wnlsm.f"
    --ipivot;
#line 74 "../fortran/wnlsm.f"
    --itype;
#line 74 "../fortran/wnlsm.f"
    --wd;
#line 74 "../fortran/wnlsm.f"
    --h__;
#line 74 "../fortran/wnlsm.f"
    --scale;
#line 74 "../fortran/wnlsm.f"
    --z__;
#line 74 "../fortran/wnlsm.f"
    --temp;
#line 74 "../fortran/wnlsm.f"
    --d__;
#line 74 "../fortran/wnlsm.f"

#line 74 "../fortran/wnlsm.f"
    /* Function Body */

/*     INITIALIZE-VARIABLES */
/*<       ASSIGN 10 TO IGO998 >*/
#line 77 "../fortran/wnlsm.f"
    igo998 = 0;
#line 77 "../fortran/wnlsm.f"
    igo998_fmt = fmt_10;
/*<       GO TO 180 >*/
#line 78 "../fortran/wnlsm.f"
    goto L180;

/*     PERFORM INITIAL TRIANGULARIZATION IN THE SUBMATRIX */
/*     CORRESPONDING TO THE UNCONSTRAINED VARIABLES USING */
/*     THE PROCEDURE INITIALLY-TRIANGULARIZE. */
/*<    10 ASSIGN 20 TO IGO995 >*/
#line 83 "../fortran/wnlsm.f"
L10:
#line 83 "../fortran/wnlsm.f"
    igo995 = 0;
#line 83 "../fortran/wnlsm.f"
    igo995_fmt = fmt_20;
/*<       GO TO 280 >*/
#line 84 "../fortran/wnlsm.f"
    goto L280;

/*     PERFORM WNNLS ALGORITHM USING THE FOLLOWING STEPS. */

/*     UNTIL(DONE) */

/*        COMPUTE-SEARCH-DIRECTION-AND-FEASIBLE-POINT */

/*        WHEN (HITCON) ADD-CONSTRAINTS */

/*        ELSE PERFORM-MULTIPLIER-TEST-AND-DROP-A-CONSTRAINT */

/*        FIN */

/*     COMPUTE-FINAL-SOLUTION */

/*<    20 IF (DONE) GO TO 80 >*/
#line 100 "../fortran/wnlsm.f"
L20:
#line 100 "../fortran/wnlsm.f"
    if (done) {
#line 100 "../fortran/wnlsm.f"
	goto L80;
#line 100 "../fortran/wnlsm.f"
    }

/*<       ASSIGN 30 TO IGO991 >*/
#line 102 "../fortran/wnlsm.f"
    igo991 = 0;
#line 102 "../fortran/wnlsm.f"
    igo991_fmt = fmt_30;
/*<       GO TO 300 >*/
#line 103 "../fortran/wnlsm.f"
    goto L300;

/*     COMPUTE-SEARCH-DIRECTION-AND-FEASIBLE-POINT */

/*<    30 IF (.NOT.(HITCON)) GO TO 50 >*/
#line 107 "../fortran/wnlsm.f"
L30:
#line 107 "../fortran/wnlsm.f"
    if (! hitcon) {
#line 107 "../fortran/wnlsm.f"
	goto L50;
#line 107 "../fortran/wnlsm.f"
    }
/*<       ASSIGN 40 TO IGO986 >*/
#line 108 "../fortran/wnlsm.f"
    igo986 = 0;
#line 108 "../fortran/wnlsm.f"
    igo986_fmt = fmt_40;
/*<       GO TO 370 >*/
#line 109 "../fortran/wnlsm.f"
    goto L370;
/*<    40 GO TO 70 >*/
#line 110 "../fortran/wnlsm.f"
L40:
#line 110 "../fortran/wnlsm.f"
    goto L70;

/*     WHEN (HITCON) ADD-CONSTRAINTS */

/*<    50 ASSIGN 60 TO IGO983 >*/
#line 114 "../fortran/wnlsm.f"
L50:
#line 114 "../fortran/wnlsm.f"
    igo983 = 0;
#line 114 "../fortran/wnlsm.f"
    igo983_fmt = fmt_60;
/*<       GO TO 640 >*/
#line 115 "../fortran/wnlsm.f"
    goto L640;
/*<    60 CONTINUE >*/
#line 116 "../fortran/wnlsm.f"
L60:

/*     ELSE PERFORM-MULTIPLIER-TEST-AND-DROP-A-CONSTRAINT */

/*<    70 GO TO 20 >*/
#line 120 "../fortran/wnlsm.f"
L70:
#line 120 "../fortran/wnlsm.f"
    goto L20;

/*<    80 ASSIGN 90 TO IGO980 >*/
#line 122 "../fortran/wnlsm.f"
L80:
#line 122 "../fortran/wnlsm.f"
    igo980 = 0;
#line 122 "../fortran/wnlsm.f"
    igo980_fmt = fmt_90;
/*<       GO TO 1000 >*/
#line 123 "../fortran/wnlsm.f"
    goto L1000;

/*     COMPUTE-FINAL-SOLUTION */

/*<    90 RETURN >*/
#line 127 "../fortran/wnlsm.f"
L90:
#line 127 "../fortran/wnlsm.f"
    return 0;
/*<   100 CONTINUE >*/
#line 128 "../fortran/wnlsm.f"
L100:

/*     TO PROCESS-OPTION-VECTOR */
/*<       FAC = 1.D-4 >*/
#line 131 "../fortran/wnlsm.f"
    fac = 1e-4;

/*     THE NOMINAL TOLERANCE USED IN THE CODE, */
/*<       TAU = DSQRT(DRELPR) >*/
#line 134 "../fortran/wnlsm.f"
    tau = sqrt(drelpr);

/*     THE NOMINAL BLOW-UP FACTOR USED IN THE CODE. */
/*<       BLOWUP = TAU >*/
#line 137 "../fortran/wnlsm.f"
    blowup = tau;

/*     THE NOMINAL COLUMN SCALING USED IN THE CODE IS */
/*     THE IDENTITY SCALING. */
/*<       D(1) = ONE >*/
#line 141 "../fortran/wnlsm.f"
    d__[1] = one;
/*<       CALL DCOPY(N, D, 0, D, 1) >*/
#line 142 "../fortran/wnlsm.f"
    dcopy_(n, &d__[1], &c__0, &d__[1], &c__1);

/*     DEFINE BOUND FOR NUMBER OF OPTIONS TO CHANGE. */
/*<       NOPT = 1000 >*/
#line 145 "../fortran/wnlsm.f"
    nopt = 1000;

/*     DEFINE BOUND FOR POSITIVE VALUE OF LINK. */
/*<       NLINK = 100000 >*/
#line 148 "../fortran/wnlsm.f"
    nlink = 100000;
/*<       NTIMES = 0 >*/
#line 149 "../fortran/wnlsm.f"
    ntimes = 0;
/*<       LAST = 1 >*/
#line 150 "../fortran/wnlsm.f"
    last = 1;
/*<       LINK = PRGOPT(1) >*/
#line 151 "../fortran/wnlsm.f"
    link = (integer) prgopt[1];
/*<       IF (.NOT.(LINK.LE.0 .OR. LINK.GT.NLINK)) GO TO 110 >*/
#line 152 "../fortran/wnlsm.f"
    if (! (link <= 0 || link > nlink)) {
#line 152 "../fortran/wnlsm.f"
	goto L110;
#line 152 "../fortran/wnlsm.f"
    }
/*<       NERR = 3 >*/
#line 153 "../fortran/wnlsm.f"
    nerr = 3;
/*<       IOPT = 1 >*/
#line 154 "../fortran/wnlsm.f"
    iopt = 1;
/*<        >*/
#line 155 "../fortran/wnlsm.f"
    xerror_("WNNLS( ) THE OPTION VECTOR IS UNDEFINED", &c__39, &nerr, &iopt, (
	    ftnlen)39);
/*<       MODE = 2 >*/
#line 157 "../fortran/wnlsm.f"
    *mode = 2;
/*<       RETURN >*/
#line 158 "../fortran/wnlsm.f"
    return 0;
/*<   110 IF (.NOT.(LINK.GT.1)) GO TO 160 >*/
#line 159 "../fortran/wnlsm.f"
L110:
#line 159 "../fortran/wnlsm.f"
    if (! (link > 1)) {
#line 159 "../fortran/wnlsm.f"
	goto L160;
#line 159 "../fortran/wnlsm.f"
    }
/*<       NTIMES = NTIMES + 1 >*/
#line 160 "../fortran/wnlsm.f"
    ++ntimes;
/*<       IF (.NOT.(NTIMES.GT.NOPT)) GO TO 120 >*/
#line 161 "../fortran/wnlsm.f"
    if (! (ntimes > nopt)) {
#line 161 "../fortran/wnlsm.f"
	goto L120;
#line 161 "../fortran/wnlsm.f"
    }
/*<       NERR = 3 >*/
#line 162 "../fortran/wnlsm.f"
    nerr = 3;
/*<       IOPT = 1 >*/
#line 163 "../fortran/wnlsm.f"
    iopt = 1;
/*<        >*/
#line 164 "../fortran/wnlsm.f"
    xerror_("WNNLS( ). THE LINKS IN THE OPTION VECTOR ARE CYCLING.", &c__53, &
	    nerr, &iopt, (ftnlen)53);
/*<       MODE = 2 >*/
#line 167 "../fortran/wnlsm.f"
    *mode = 2;
/*<       RETURN >*/
#line 168 "../fortran/wnlsm.f"
    return 0;
/*<   120 KEY = PRGOPT(LAST+1) >*/
#line 169 "../fortran/wnlsm.f"
L120:
#line 169 "../fortran/wnlsm.f"
    key = (integer) prgopt[last + 1];
/*<       IF (.NOT.(KEY.EQ.6 .AND. PRGOPT(LAST+2).NE.ZERO)) GO TO 140 >*/
#line 170 "../fortran/wnlsm.f"
    if (! (key == 6 && prgopt[last + 2] != zero)) {
#line 170 "../fortran/wnlsm.f"
	goto L140;
#line 170 "../fortran/wnlsm.f"
    }
/*<       DO 130 J=1,N >*/
#line 171 "../fortran/wnlsm.f"
    i__1 = *n;
#line 171 "../fortran/wnlsm.f"
    for (j = 1; j <= i__1; ++j) {
/*<         T = DNRM2(M,W(1,J),1) >*/
#line 172 "../fortran/wnlsm.f"
	t = dnrm2_(&m, &w[j * w_dim1 + 1], &c__1);
/*<         IF (T.NE.ZERO) T = ONE/T >*/
#line 173 "../fortran/wnlsm.f"
	if (t != zero) {
#line 173 "../fortran/wnlsm.f"
	    t = one / t;
#line 173 "../fortran/wnlsm.f"
	}
/*<         D(J) = T >*/
#line 174 "../fortran/wnlsm.f"
	d__[j] = t;
/*<   130 CONTINUE >*/
#line 175 "../fortran/wnlsm.f"
/* L130: */
#line 175 "../fortran/wnlsm.f"
    }
/*<   140 IF (KEY.EQ.7) CALL DCOPY(N, PRGOPT(LAST+2), 1, D, 1) >*/
#line 176 "../fortran/wnlsm.f"
L140:
#line 176 "../fortran/wnlsm.f"
    if (key == 7) {
#line 176 "../fortran/wnlsm.f"
	dcopy_(n, &prgopt[last + 2], &c__1, &d__[1], &c__1);
#line 176 "../fortran/wnlsm.f"
    }
/*<       IF (KEY.EQ.8) TAU = DMAX1(DRELPR,PRGOPT(LAST+2)) >*/
#line 177 "../fortran/wnlsm.f"
    if (key == 8) {
/* Computing MAX */
#line 177 "../fortran/wnlsm.f"
	d__1 = drelpr, d__2 = prgopt[last + 2];
#line 177 "../fortran/wnlsm.f"
	tau = max(d__1,d__2);
#line 177 "../fortran/wnlsm.f"
    }
/*<       IF (KEY.EQ.9) BLOWUP = DMAX1(DRELPR,PRGOPT(LAST+2)) >*/
#line 178 "../fortran/wnlsm.f"
    if (key == 9) {
/* Computing MAX */
#line 178 "../fortran/wnlsm.f"
	d__1 = drelpr, d__2 = prgopt[last + 2];
#line 178 "../fortran/wnlsm.f"
	blowup = max(d__1,d__2);
#line 178 "../fortran/wnlsm.f"
    }
/*<       NEXT = PRGOPT(LINK) >*/
#line 179 "../fortran/wnlsm.f"
    next = (integer) prgopt[link];
/*<       IF (.NOT.(NEXT.LE.0 .OR. NEXT.GT.NLINK)) GO TO 150 >*/
#line 180 "../fortran/wnlsm.f"
    if (! (next <= 0 || next > nlink)) {
#line 180 "../fortran/wnlsm.f"
	goto L150;
#line 180 "../fortran/wnlsm.f"
    }
/*<       NERR = 3 >*/
#line 181 "../fortran/wnlsm.f"
    nerr = 3;
/*<       IOPT = 1 >*/
#line 182 "../fortran/wnlsm.f"
    iopt = 1;
/*<        >*/
#line 183 "../fortran/wnlsm.f"
    xerror_("WNNLS( ) THE OPTION VECTOR IS UNDEFINED", &c__39, &nerr, &iopt, (
	    ftnlen)39);
/*<       MODE = 2 >*/
#line 185 "../fortran/wnlsm.f"
    *mode = 2;
/*<       RETURN >*/
#line 186 "../fortran/wnlsm.f"
    return 0;
/*<   150 LAST = LINK >*/
#line 187 "../fortran/wnlsm.f"
L150:
#line 187 "../fortran/wnlsm.f"
    last = link;
/*<       LINK = NEXT >*/
#line 188 "../fortran/wnlsm.f"
    link = next;
/*<       GO TO 110 >*/
#line 189 "../fortran/wnlsm.f"
    goto L110;
/*<   160 DO 170 J=1,N >*/
#line 190 "../fortran/wnlsm.f"
L160:
#line 190 "../fortran/wnlsm.f"
    i__1 = *n;
#line 190 "../fortran/wnlsm.f"
    for (j = 1; j <= i__1; ++j) {
/*<         CALL DSCAL(M, D(J), W(1,J), 1) >*/
#line 191 "../fortran/wnlsm.f"
	dscal_(&m, &d__[j], &w[j * w_dim1 + 1], &c__1);
/*<   170 CONTINUE >*/
#line 192 "../fortran/wnlsm.f"
/* L170: */
#line 192 "../fortran/wnlsm.f"
    }
/*<       GO TO 1260 >*/
#line 193 "../fortran/wnlsm.f"
    goto L1260;
/*<   180 CONTINUE >*/
#line 194 "../fortran/wnlsm.f"
L180:

/*     TO INITIALIZE-VARIABLES */

/*     DRELPR IS THE PRECISION FOR THE PARTICULAR MACHINE */
/*     BEING USED.  THIS LOGIC AVOIDS RECOMPUTING IT EVERY ENTRY. */
/*<       IF (.NOT.(DRELPR.EQ.ZERO)) GO TO 210 >*/
#line 200 "../fortran/wnlsm.f"
    if (! (drelpr == zero)) {
#line 200 "../fortran/wnlsm.f"
	goto L210;
#line 200 "../fortran/wnlsm.f"
    }
/*<       DRELPR = ONE >*/
#line 201 "../fortran/wnlsm.f"
    drelpr = one;
/*<   190 IF (ONE+DRELPR.EQ.ONE) GO TO 200 >*/
#line 202 "../fortran/wnlsm.f"
L190:
#line 202 "../fortran/wnlsm.f"
    if (one + drelpr == one) {
#line 202 "../fortran/wnlsm.f"
	goto L200;
#line 202 "../fortran/wnlsm.f"
    }
/*<       DRELPR = DRELPR/TWO >*/
#line 203 "../fortran/wnlsm.f"
    drelpr /= two;
/*<       GO TO 190 >*/
#line 204 "../fortran/wnlsm.f"
    goto L190;
/*<   200 DRELPR = DRELPR*TWO >*/
#line 205 "../fortran/wnlsm.f"
L200:
#line 205 "../fortran/wnlsm.f"
    drelpr *= two;
/*<   210 M = MA + MME >*/
#line 206 "../fortran/wnlsm.f"
L210:
#line 206 "../fortran/wnlsm.f"
    m = *ma + *mme;
/*<       ME = MME >*/
#line 207 "../fortran/wnlsm.f"
    me = *mme;
/*<       MEP1 = ME + 1 >*/
#line 208 "../fortran/wnlsm.f"
    mep1 = me + 1;
/*<       ASSIGN 220 TO IGO977 >*/
#line 209 "../fortran/wnlsm.f"
    igo977 = 0;
#line 209 "../fortran/wnlsm.f"
    igo977_fmt = fmt_220;
/*<       GO TO 100 >*/
#line 210 "../fortran/wnlsm.f"
    goto L100;

/*     PROCESS-OPTION-VECTOR */
/*<   220 DONE = .FALSE. >*/
#line 213 "../fortran/wnlsm.f"
L220:
#line 213 "../fortran/wnlsm.f"
    done = FALSE_;
/*<       ITER = 0 >*/
#line 214 "../fortran/wnlsm.f"
    iter = 0;
/*<       ITMAX = 3*(N-L) >*/
#line 215 "../fortran/wnlsm.f"
    itmax = (*n - *l) * 3;
/*<       MODE = 0 >*/
#line 216 "../fortran/wnlsm.f"
    *mode = 0;
/*<       LP1 = L + 1 >*/
#line 217 "../fortran/wnlsm.f"
    lp1 = *l + 1;
/*<       NSOLN = L >*/
#line 218 "../fortran/wnlsm.f"
    nsoln = *l;
/*<       NSP1 = NSOLN + 1 >*/
#line 219 "../fortran/wnlsm.f"
    nsp1 = nsoln + 1;
/*<       NP1 = N + 1 >*/
#line 220 "../fortran/wnlsm.f"
    np1 = *n + 1;
/*<       NM1 = N - 1 >*/
#line 221 "../fortran/wnlsm.f"
    nm1 = *n - 1;
/*<       L1 = MIN0(M,L) >*/
#line 222 "../fortran/wnlsm.f"
    l1 = min(m,*l);

/*     COMPUTE SCALE FACTOR TO APPLY TO EQUAL. CONSTRAINT EQUAS. */
/*<       DO 230 J=1,N >*/
#line 225 "../fortran/wnlsm.f"
    i__1 = *n;
#line 225 "../fortran/wnlsm.f"
    for (j = 1; j <= i__1; ++j) {
/*<         WD(J) = DASUM(M,W(1,J),1) >*/
#line 226 "../fortran/wnlsm.f"
	wd[j] = dasum_(&m, &w[j * w_dim1 + 1], &c__1);
/*<   230 CONTINUE >*/
#line 227 "../fortran/wnlsm.f"
/* L230: */
#line 227 "../fortran/wnlsm.f"
    }
/*<       IMAX = IDAMAX(N,WD,1) >*/
#line 228 "../fortran/wnlsm.f"
    imax = idamax_(n, &wd[1], &c__1);
/*<       EANORM = WD(IMAX) >*/
#line 229 "../fortran/wnlsm.f"
    eanorm = wd[imax];
/*<       BNORM = DASUM(M,W(1,NP1),1) >*/
#line 230 "../fortran/wnlsm.f"
    bnorm = dasum_(&m, &w[np1 * w_dim1 + 1], &c__1);
/*<       ALAMDA = EANORM/(DRELPR*FAC) >*/
#line 231 "../fortran/wnlsm.f"
    alamda = eanorm / (drelpr * fac);

/*     DEFINE SCALING DIAG MATRIX FOR MOD GIVENS USAGE AND */
/*     CLASSIFY EQUATION TYPES. */
/*<       ALSQ = ALAMDA**2 >*/
/* Computing 2nd power */
#line 235 "../fortran/wnlsm.f"
    d__1 = alamda;
#line 235 "../fortran/wnlsm.f"
    alsq = d__1 * d__1;
/*<       DO 260 I=1,M >*/
#line 236 "../fortran/wnlsm.f"
    i__1 = m;
#line 236 "../fortran/wnlsm.f"
    for (i__ = 1; i__ <= i__1; ++i__) {

/*     WHEN EQU I IS HEAVILY WEIGHTED ITYPE(I)=0, ELSE ITYPE(I)=1. */
/*<         IF (.NOT.(I.LE.ME)) GO TO 240 >*/
#line 239 "../fortran/wnlsm.f"
	if (! (i__ <= me)) {
#line 239 "../fortran/wnlsm.f"
	    goto L240;
#line 239 "../fortran/wnlsm.f"
	}
/*<         T = ALSQ >*/
#line 240 "../fortran/wnlsm.f"
	t = alsq;
/*<         ITEMP = 0 >*/
#line 241 "../fortran/wnlsm.f"
	itemp = 0;
/*<         GO TO 250 >*/
#line 242 "../fortran/wnlsm.f"
	goto L250;
/*<   240   T = ONE >*/
#line 243 "../fortran/wnlsm.f"
L240:
#line 243 "../fortran/wnlsm.f"
	t = one;
/*<         ITEMP = 1 >*/
#line 244 "../fortran/wnlsm.f"
	itemp = 1;
/*<   250   SCALE(I) = T >*/
#line 245 "../fortran/wnlsm.f"
L250:
#line 245 "../fortran/wnlsm.f"
	scale[i__] = t;
/*<         ITYPE(I) = ITEMP >*/
#line 246 "../fortran/wnlsm.f"
	itype[i__] = itemp;
/*<   260 CONTINUE >*/
#line 247 "../fortran/wnlsm.f"
/* L260: */
#line 247 "../fortran/wnlsm.f"
    }

/*     SET THE SOLN VECTOR X(*) TO ZERO AND THE COL INTERCHANGE */
/*     MATRIX TO THE IDENTITY. */
/*<       X(1) = ZERO >*/
#line 251 "../fortran/wnlsm.f"
    x[1] = zero;
/*<       CALL DCOPY(N, X, 0, X, 1) >*/
#line 252 "../fortran/wnlsm.f"
    dcopy_(n, &x[1], &c__0, &x[1], &c__1);
/*<       DO 270 I=1,N >*/
#line 253 "../fortran/wnlsm.f"
    i__1 = *n;
#line 253 "../fortran/wnlsm.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         IPIVOT(I) = I >*/
#line 254 "../fortran/wnlsm.f"
	ipivot[i__] = i__;
/*<   270 CONTINUE >*/
#line 255 "../fortran/wnlsm.f"
/* L270: */
#line 255 "../fortran/wnlsm.f"
    }
/*<       GO TO 1230 >*/
#line 256 "../fortran/wnlsm.f"
    goto L1230;
/*<   280 CONTINUE >*/
#line 257 "../fortran/wnlsm.f"
L280:

/*     TO INITIALLY-TRIANGULARIZE */

/*     SET FIRST L COMPS. OF DUAL VECTOR TO ZERO BECAUSE */
/*     THESE CORRESPOND TO THE UNCONSTRAINED VARIABLES. */
/*<       IF (.NOT.(L.GT.0)) GO TO 290 >*/
#line 263 "../fortran/wnlsm.f"
    if (! (*l > 0)) {
#line 263 "../fortran/wnlsm.f"
	goto L290;
#line 263 "../fortran/wnlsm.f"
    }
/*<       WD(1) = ZERO >*/
#line 264 "../fortran/wnlsm.f"
    wd[1] = zero;
/*<       CALL DCOPY(L, WD, 0, WD, 1) >*/
#line 265 "../fortran/wnlsm.f"
    dcopy_(l, &wd[1], &c__0, &wd[1], &c__1);

/*     THE ARRAYS IDOPE(*) AND DOPE(*) ARE USED TO PASS */
/*     INFORMATION TO WNLIT().  THIS WAS DONE TO AVOID */
/*     A LONG CALLING SEQUENCE OR THE USE OF COMMON. */
/*<   290 IDOPE(1) = ME >*/
#line 270 "../fortran/wnlsm.f"
L290:
#line 270 "../fortran/wnlsm.f"
    idope[0] = me;
/*<       IDOPE(2) = MEP1 >*/
#line 271 "../fortran/wnlsm.f"
    idope[1] = mep1;
/*<       IDOPE(3) = 0 >*/
#line 272 "../fortran/wnlsm.f"
    idope[2] = 0;
/*<       IDOPE(4) = 1 >*/
#line 273 "../fortran/wnlsm.f"
    idope[3] = 1;
/*<       IDOPE(5) = NSOLN >*/
#line 274 "../fortran/wnlsm.f"
    idope[4] = nsoln;
/*<       IDOPE(6) = 0 >*/
#line 275 "../fortran/wnlsm.f"
    idope[5] = 0;
/*<       IDOPE(7) = 1 >*/
#line 276 "../fortran/wnlsm.f"
    idope[6] = 1;
/*<       IDOPE(8) = L1 >*/
#line 277 "../fortran/wnlsm.f"
    idope[7] = l1;

/*<       DOPE(1) = ALSQ >*/
#line 279 "../fortran/wnlsm.f"
    dope[0] = alsq;
/*<       DOPE(2) = EANORM >*/
#line 280 "../fortran/wnlsm.f"
    dope[1] = eanorm;
/*<       DOPE(3) = FAC >*/
#line 281 "../fortran/wnlsm.f"
    dope[2] = fac;
/*<       DOPE(4) = TAU >*/
#line 282 "../fortran/wnlsm.f"
    dope[3] = tau;
/*<        >*/
#line 283 "../fortran/wnlsm.f"
    wnlit_(&w[w_offset], mdw, &m, n, l, &ipivot[1], &itype[1], &h__[1], &
	    scale[1], rnorm, idope, dope, &done);
/*<       ME = IDOPE(1) >*/
#line 285 "../fortran/wnlsm.f"
    me = idope[0];
/*<       MEP1 = IDOPE(2) >*/
#line 286 "../fortran/wnlsm.f"
    mep1 = idope[1];
/*<       KRANK = IDOPE(3) >*/
#line 287 "../fortran/wnlsm.f"
    krank = idope[2];
/*<       KRP1 = IDOPE(4) >*/
#line 288 "../fortran/wnlsm.f"
    krp1 = idope[3];
/*<       NSOLN = IDOPE(5) >*/
#line 289 "../fortran/wnlsm.f"
    nsoln = idope[4];
/*<       NIV = IDOPE(6) >*/
#line 290 "../fortran/wnlsm.f"
    niv = idope[5];
/*<       NIV1 = IDOPE(7) >*/
#line 291 "../fortran/wnlsm.f"
    niv1 = idope[6];
/*<       L1 = IDOPE(8) >*/
#line 292 "../fortran/wnlsm.f"
    l1 = idope[7];
/*<       GO TO 1240 >*/
#line 293 "../fortran/wnlsm.f"
    goto L1240;
/*<   300 CONTINUE >*/
#line 294 "../fortran/wnlsm.f"
L300:

/*     TO COMPUTE-SEARCH-DIRECTION-AND-FEASIBLE-POINT */

/*     SOLVE THE TRIANGULAR SYSTEM OF CURRENTLY NON-ACTIVE */
/*     VARIABLES AND STORE THE SOLUTION IN Z(*). */

/*     SOLVE-SYSTEM */
/*<       ASSIGN 310 TO IGO958 >*/
#line 302 "../fortran/wnlsm.f"
    igo958 = 0;
#line 302 "../fortran/wnlsm.f"
    igo958_fmt = fmt_310;
/*<       GO TO 1110 >*/
#line 303 "../fortran/wnlsm.f"
    goto L1110;

/*     INCREMENT ITERATION COUNTER AND CHECK AGAINST MAX. NUMBER */
/*     OF ITERATIONS. */
/*<   310 ITER = ITER + 1 >*/
#line 307 "../fortran/wnlsm.f"
L310:
#line 307 "../fortran/wnlsm.f"
    ++iter;
/*<       IF (.NOT.(ITER.GT.ITMAX)) GO TO 320 >*/
#line 308 "../fortran/wnlsm.f"
    if (! (iter > itmax)) {
#line 308 "../fortran/wnlsm.f"
	goto L320;
#line 308 "../fortran/wnlsm.f"
    }
/*<       MODE = 1 >*/
#line 309 "../fortran/wnlsm.f"
    *mode = 1;
/*<       DONE = .TRUE. >*/
#line 310 "../fortran/wnlsm.f"
    done = TRUE_;

/*     CHECK TO SEE IF ANY CONSTRAINTS HAVE BECOME ACTIVE. */
/*     IF SO, CALCULATE AN INTERPOLATION FACTOR SO THAT ALL */
/*     ACTIVE CONSTRAINTS ARE REMOVED FROM THE BASIS. */
/*<   320 ALPHA = TWO >*/
#line 315 "../fortran/wnlsm.f"
L320:
#line 315 "../fortran/wnlsm.f"
    alpha = two;
/*<       HITCON = .FALSE. >*/
#line 316 "../fortran/wnlsm.f"
    hitcon = FALSE_;
/*<       IF (.NOT.(L.LT.NSOLN)) GO TO 360 >*/
#line 317 "../fortran/wnlsm.f"
    if (! (*l < nsoln)) {
#line 317 "../fortran/wnlsm.f"
	goto L360;
#line 317 "../fortran/wnlsm.f"
    }
/*<       DO 350 J=LP1,NSOLN >*/
#line 318 "../fortran/wnlsm.f"
    i__1 = nsoln;
#line 318 "../fortran/wnlsm.f"
    for (j = lp1; j <= i__1; ++j) {
/*<         ZZ = Z(J) >*/
#line 319 "../fortran/wnlsm.f"
	zz = z__[j];
/*<         IF (.NOT.(ZZ.LE.ZERO)) GO TO 340 >*/
#line 320 "../fortran/wnlsm.f"
	if (! (zz <= zero)) {
#line 320 "../fortran/wnlsm.f"
	    goto L340;
#line 320 "../fortran/wnlsm.f"
	}
/*<         T = X(J)/(X(J)-ZZ) >*/
#line 321 "../fortran/wnlsm.f"
	t = x[j] / (x[j] - zz);
/*<         IF (.NOT.(T.LT.ALPHA)) GO TO 330 >*/
#line 322 "../fortran/wnlsm.f"
	if (! (t < alpha)) {
#line 322 "../fortran/wnlsm.f"
	    goto L330;
#line 322 "../fortran/wnlsm.f"
	}
/*<         ALPHA = T >*/
#line 323 "../fortran/wnlsm.f"
	alpha = t;
/*<         JCON = J >*/
#line 324 "../fortran/wnlsm.f"
	jcon = j;
/*<   330   HITCON = .TRUE. >*/
#line 325 "../fortran/wnlsm.f"
L330:
#line 325 "../fortran/wnlsm.f"
	hitcon = TRUE_;
/*<   340   CONTINUE >*/
#line 326 "../fortran/wnlsm.f"
L340:
/*<   350 CONTINUE >*/
#line 327 "../fortran/wnlsm.f"
/* L350: */
#line 327 "../fortran/wnlsm.f"
	;
#line 327 "../fortran/wnlsm.f"
    }
/*<   360 GO TO 1220 >*/
#line 328 "../fortran/wnlsm.f"
L360:
#line 328 "../fortran/wnlsm.f"
    goto L1220;
/*<   370 CONTINUE >*/
#line 329 "../fortran/wnlsm.f"
L370:

/*     TO ADD-CONSTRAINTS */

/*     USE COMPUTED ALPHA TO INTERPOLATE BETWEEN LAST */
/*     FEASIBLE SOLUTION X(*) AND CURRENT UNCONSTRAINED */
/*     (AND INFEASIBLE) SOLUTION Z(*). */
/*<       IF (.NOT.(LP1.LE.NSOLN)) GO TO 390 >*/
#line 336 "../fortran/wnlsm.f"
    if (! (lp1 <= nsoln)) {
#line 336 "../fortran/wnlsm.f"
	goto L390;
#line 336 "../fortran/wnlsm.f"
    }
/*<       DO 380 J=LP1,NSOLN >*/
#line 337 "../fortran/wnlsm.f"
    i__1 = nsoln;
#line 337 "../fortran/wnlsm.f"
    for (j = lp1; j <= i__1; ++j) {
/*<         X(J) = X(J) + ALPHA*(Z(J)-X(J)) >*/
#line 338 "../fortran/wnlsm.f"
	x[j] += alpha * (z__[j] - x[j]);
/*<   380 CONTINUE >*/
#line 339 "../fortran/wnlsm.f"
/* L380: */
#line 339 "../fortran/wnlsm.f"
    }
/*<   390 FEASBL = .FALSE. >*/
#line 340 "../fortran/wnlsm.f"
L390:
#line 340 "../fortran/wnlsm.f"
    feasbl = FALSE_;
/*<       GO TO 410 >*/
#line 341 "../fortran/wnlsm.f"
    goto L410;
/*<   400 IF (FEASBL) GO TO 610 >*/
#line 342 "../fortran/wnlsm.f"
L400:
#line 342 "../fortran/wnlsm.f"
    if (feasbl) {
#line 342 "../fortran/wnlsm.f"
	goto L610;
#line 342 "../fortran/wnlsm.f"
    }

/*     REMOVE COL JCON AND SHIFT COLS JCON+1 THROUGH N TO THE */
/*     LEFT. SWAP COL JCON INTO THE N-TH POSITION.  THIS ACHIEVES */
/*     UPPER HESSENBERG FORM FOR THE NONACTIVE CONSTRAINTS AND */
/*     LEAVES AN UPPER HESSENBERG MATRIX TO RETRIANGULARIZE. */
/*<   410 DO 420 I=1,M >*/
#line 348 "../fortran/wnlsm.f"
L410:
#line 348 "../fortran/wnlsm.f"
    i__1 = m;
#line 348 "../fortran/wnlsm.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         T = W(I,JCON) >*/
#line 349 "../fortran/wnlsm.f"
	t = w[i__ + jcon * w_dim1];
/*<         CALL DCOPY(N-JCON, W(I,JCON+1), MDW, W(I,JCON), MDW) >*/
#line 350 "../fortran/wnlsm.f"
	i__2 = *n - jcon;
#line 350 "../fortran/wnlsm.f"
	dcopy_(&i__2, &w[i__ + (jcon + 1) * w_dim1], mdw, &w[i__ + jcon * 
		w_dim1], mdw);
/*<         W(I,N) = T >*/
#line 351 "../fortran/wnlsm.f"
	w[i__ + *n * w_dim1] = t;
/*<   420 CONTINUE >*/
#line 352 "../fortran/wnlsm.f"
/* L420: */
#line 352 "../fortran/wnlsm.f"
    }

/*     UPDATE PERMUTED INDEX VECTOR TO REFLECT THIS SHIFT AND SWAP. */
/*<       ITEMP = IPIVOT(JCON) >*/
#line 355 "../fortran/wnlsm.f"
    itemp = ipivot[jcon];
/*<       IF (.NOT.(JCON.LT.N)) GO TO 440 >*/
#line 356 "../fortran/wnlsm.f"
    if (! (jcon < *n)) {
#line 356 "../fortran/wnlsm.f"
	goto L440;
#line 356 "../fortran/wnlsm.f"
    }
/*<       DO 430 I=JCON,NM1 >*/
#line 357 "../fortran/wnlsm.f"
    i__1 = nm1;
#line 357 "../fortran/wnlsm.f"
    for (i__ = jcon; i__ <= i__1; ++i__) {
/*<         IPIVOT(I) = IPIVOT(I+1) >*/
#line 358 "../fortran/wnlsm.f"
	ipivot[i__] = ipivot[i__ + 1];
/*<   430 CONTINUE >*/
#line 359 "../fortran/wnlsm.f"
/* L430: */
#line 359 "../fortran/wnlsm.f"
    }
/*<   440 IPIVOT(N) = ITEMP >*/
#line 360 "../fortran/wnlsm.f"
L440:
#line 360 "../fortran/wnlsm.f"
    ipivot[*n] = itemp;

/*     SIMILARLY REPERMUTE X(*) VECTOR. */
/*<       CALL DCOPY(N-JCON, X(JCON+1), 1, X(JCON), 1) >*/
#line 363 "../fortran/wnlsm.f"
    i__1 = *n - jcon;
#line 363 "../fortran/wnlsm.f"
    dcopy_(&i__1, &x[jcon + 1], &c__1, &x[jcon], &c__1);
/*<       X(N) = ZERO >*/
#line 364 "../fortran/wnlsm.f"
    x[*n] = zero;
/*<       NSP1 = NSOLN >*/
#line 365 "../fortran/wnlsm.f"
    nsp1 = nsoln;
/*<       NSOLN = NSOLN - 1 >*/
#line 366 "../fortran/wnlsm.f"
    --nsoln;
/*<       NIV1 = NIV >*/
#line 367 "../fortran/wnlsm.f"
    niv1 = niv;
/*<       NIV = NIV - 1 >*/
#line 368 "../fortran/wnlsm.f"
    --niv;

/*     RETRIANGULARIZE UPPER HESSENBERG MATRIX AFTER ADDING CONSTRAINTS. */
/*<       J = JCON >*/
#line 371 "../fortran/wnlsm.f"
    j = jcon;
/*<       I = KRANK + JCON - L >*/
#line 372 "../fortran/wnlsm.f"
    i__ = krank + jcon - *l;
/*<   450 IF (.NOT.(J.LE.NSOLN)) GO TO 570 >*/
#line 373 "../fortran/wnlsm.f"
L450:
#line 373 "../fortran/wnlsm.f"
    if (! (j <= nsoln)) {
#line 373 "../fortran/wnlsm.f"
	goto L570;
#line 373 "../fortran/wnlsm.f"
    }
/*<       IF (.NOT.(ITYPE(I).EQ.0 .AND. ITYPE(I+1).EQ.0)) GO TO 470 >*/
#line 374 "../fortran/wnlsm.f"
    if (! (itype[i__] == 0 && itype[i__ + 1] == 0)) {
#line 374 "../fortran/wnlsm.f"
	goto L470;
#line 374 "../fortran/wnlsm.f"
    }
/*<       ASSIGN 460 TO IGO938 >*/
#line 375 "../fortran/wnlsm.f"
    igo938 = 0;
#line 375 "../fortran/wnlsm.f"
    igo938_fmt = fmt_460;
/*<       GO TO 620 >*/
#line 376 "../fortran/wnlsm.f"
    goto L620;

/*     (ITYPE(I).EQ.0 .AND. ITYPE(I+1).EQ.0) ZERO-IP1-TO-I-IN-COL-J */
/*<   460 GO TO 560 >*/
#line 379 "../fortran/wnlsm.f"
L460:
#line 379 "../fortran/wnlsm.f"
    goto L560;
/*<   470 IF (.NOT.(ITYPE(I).EQ.1 .AND. ITYPE(I+1).EQ.1)) GO TO 490 >*/
#line 380 "../fortran/wnlsm.f"
L470:
#line 380 "../fortran/wnlsm.f"
    if (! (itype[i__] == 1 && itype[i__ + 1] == 1)) {
#line 380 "../fortran/wnlsm.f"
	goto L490;
#line 380 "../fortran/wnlsm.f"
    }
/*<       ASSIGN 480 TO IGO938 >*/
#line 381 "../fortran/wnlsm.f"
    igo938 = 1;
#line 381 "../fortran/wnlsm.f"
    igo938_fmt = fmt_480;
/*<       GO TO 620 >*/
#line 382 "../fortran/wnlsm.f"
    goto L620;

/*     (ITYPE(I).EQ.1 .AND. ITYPE(I+1).EQ.1) ZERO-IP1-TO-I-IN-COL-J */
/*<   480 GO TO 560 >*/
#line 385 "../fortran/wnlsm.f"
L480:
#line 385 "../fortran/wnlsm.f"
    goto L560;
/*<   490 IF (.NOT.(ITYPE(I).EQ.1 .AND. ITYPE(I+1).EQ.0)) GO TO 510 >*/
#line 386 "../fortran/wnlsm.f"
L490:
#line 386 "../fortran/wnlsm.f"
    if (! (itype[i__] == 1 && itype[i__ + 1] == 0)) {
#line 386 "../fortran/wnlsm.f"
	goto L510;
#line 386 "../fortran/wnlsm.f"
    }
/*<       CALL DSWAP(NP1, W(I,1), MDW, W(I+1,1), MDW) >*/
#line 387 "../fortran/wnlsm.f"
    dswap_(&np1, &w[i__ + w_dim1], mdw, &w[i__ + 1 + w_dim1], mdw);
/*<       CALL DSWAP(1, SCALE(I), 1, SCALE(I+1), 1) >*/
#line 388 "../fortran/wnlsm.f"
    dswap_(&c__1, &scale[i__], &c__1, &scale[i__ + 1], &c__1);
/*<       ITEMP = ITYPE(I+1) >*/
#line 389 "../fortran/wnlsm.f"
    itemp = itype[i__ + 1];
/*<       ITYPE(I+1) = ITYPE(I) >*/
#line 390 "../fortran/wnlsm.f"
    itype[i__ + 1] = itype[i__];
/*<       ITYPE(I) = ITEMP >*/
#line 391 "../fortran/wnlsm.f"
    itype[i__] = itemp;

/*     SWAPPED ROW WAS FORMERLY A PIVOT ELT., SO IT WILL */
/*     BE LARGE ENOUGH TO PERFORM ELIM. */
/*<       ASSIGN 500 TO IGO938 >*/
#line 395 "../fortran/wnlsm.f"
    igo938 = 2;
#line 395 "../fortran/wnlsm.f"
    igo938_fmt = fmt_500;
/*<       GO TO 620 >*/
#line 396 "../fortran/wnlsm.f"
    goto L620;

/*     ZERO-IP1-TO-I-IN-COL-J */
/*<   500 GO TO 560 >*/
#line 399 "../fortran/wnlsm.f"
L500:
#line 399 "../fortran/wnlsm.f"
    goto L560;
/*<   510 IF (.NOT.(ITYPE(I).EQ.0 .AND. ITYPE(I+1).EQ.1)) GO TO 550 >*/
#line 400 "../fortran/wnlsm.f"
L510:
#line 400 "../fortran/wnlsm.f"
    if (! (itype[i__] == 0 && itype[i__ + 1] == 1)) {
#line 400 "../fortran/wnlsm.f"
	goto L550;
#line 400 "../fortran/wnlsm.f"
    }
/*<       T = SCALE(I)*W(I,J)**2/ALSQ >*/
/* Computing 2nd power */
#line 401 "../fortran/wnlsm.f"
    d__1 = w[i__ + j * w_dim1];
#line 401 "../fortran/wnlsm.f"
    t = scale[i__] * (d__1 * d__1) / alsq;
/*<       IF (.NOT.(T.GT.TAU**2*EANORM**2)) GO TO 530 >*/
/* Computing 2nd power */
#line 402 "../fortran/wnlsm.f"
    d__1 = tau;
/* Computing 2nd power */
#line 402 "../fortran/wnlsm.f"
    d__2 = eanorm;
#line 402 "../fortran/wnlsm.f"
    if (! (t > d__1 * d__1 * (d__2 * d__2))) {
#line 402 "../fortran/wnlsm.f"
	goto L530;
#line 402 "../fortran/wnlsm.f"
    }
/*<       ASSIGN 520 TO IGO938 >*/
#line 403 "../fortran/wnlsm.f"
    igo938 = 3;
#line 403 "../fortran/wnlsm.f"
    igo938_fmt = fmt_520;
/*<       GO TO 620 >*/
#line 404 "../fortran/wnlsm.f"
    goto L620;
/*<   520 GO TO 540 >*/
#line 405 "../fortran/wnlsm.f"
L520:
#line 405 "../fortran/wnlsm.f"
    goto L540;
/*<   530 CALL DSWAP(NP1, W(I,1), MDW, W(I+1,1), MDW) >*/
#line 406 "../fortran/wnlsm.f"
L530:
#line 406 "../fortran/wnlsm.f"
    dswap_(&np1, &w[i__ + w_dim1], mdw, &w[i__ + 1 + w_dim1], mdw);
/*<       CALL DSWAP(1, SCALE(I), 1, SCALE(I+1), 1) >*/
#line 407 "../fortran/wnlsm.f"
    dswap_(&c__1, &scale[i__], &c__1, &scale[i__ + 1], &c__1);
/*<       ITEMP = ITYPE(I+1) >*/
#line 408 "../fortran/wnlsm.f"
    itemp = itype[i__ + 1];
/*<       ITYPE(I+1) = ITYPE(I) >*/
#line 409 "../fortran/wnlsm.f"
    itype[i__ + 1] = itype[i__];
/*<       ITYPE(I) = ITEMP >*/
#line 410 "../fortran/wnlsm.f"
    itype[i__] = itemp;
/*<       W(I+1,J) = ZERO >*/
#line 411 "../fortran/wnlsm.f"
    w[i__ + 1 + j * w_dim1] = zero;
/*<   540 CONTINUE >*/
#line 412 "../fortran/wnlsm.f"
L540:
/*<   550 CONTINUE >*/
#line 413 "../fortran/wnlsm.f"
L550:
/*<   560 I = I + 1 >*/
#line 414 "../fortran/wnlsm.f"
L560:
#line 414 "../fortran/wnlsm.f"
    ++i__;
/*<       J = J + 1 >*/
#line 415 "../fortran/wnlsm.f"
    ++j;
/*<       GO TO 450 >*/
#line 416 "../fortran/wnlsm.f"
    goto L450;

/*     SEE IF THE REMAINING COEFFS IN THE SOLN SET ARE FEASIBLE.  THEY */
/*     SHOULD BE BECAUSE OF THE WAY ALPHA WAS DETERMINED.  IF ANY ARE */
/*     INFEASIBLE IT IS DUE TO ROUNDOFF ERROR.  ANY THAT ARE NON- */
/*     POSITIVE WILL BE SET TO ZERO AND REMOVED FROM THE SOLN SET. */
/*<   570 IF (.NOT.(LP1.LE.NSOLN)) GO TO 590 >*/
#line 422 "../fortran/wnlsm.f"
L570:
#line 422 "../fortran/wnlsm.f"
    if (! (lp1 <= nsoln)) {
#line 422 "../fortran/wnlsm.f"
	goto L590;
#line 422 "../fortran/wnlsm.f"
    }
/*<       DO 580 JCON=LP1,NSOLN >*/
#line 423 "../fortran/wnlsm.f"
    i__1 = nsoln;
#line 423 "../fortran/wnlsm.f"
    for (jcon = lp1; jcon <= i__1; ++jcon) {
/*<         IF (X(JCON).LE.ZERO) GO TO 600 >*/
#line 424 "../fortran/wnlsm.f"
	if (x[jcon] <= zero) {
#line 424 "../fortran/wnlsm.f"
	    goto L600;
#line 424 "../fortran/wnlsm.f"
	}
/*<   580 CONTINUE >*/
#line 425 "../fortran/wnlsm.f"
/* L580: */
#line 425 "../fortran/wnlsm.f"
    }
/*<   590 FEASBL = .TRUE. >*/
#line 426 "../fortran/wnlsm.f"
L590:
#line 426 "../fortran/wnlsm.f"
    feasbl = TRUE_;
/*<   600 CONTINUE >*/
#line 427 "../fortran/wnlsm.f"
L600:
/*<       GO TO 400 >*/
#line 428 "../fortran/wnlsm.f"
    goto L400;
/*<   610 GO TO 1200 >*/
#line 429 "../fortran/wnlsm.f"
L610:
#line 429 "../fortran/wnlsm.f"
    goto L1200;
/*<   620 CONTINUE >*/
#line 430 "../fortran/wnlsm.f"
L620:

/*     TO ZERO-IP1-TO-I-IN-COL-J */
/*<       IF (.NOT.(W(I+1,J).NE.ZERO)) GO TO 630 >*/
#line 433 "../fortran/wnlsm.f"
    if (! (w[i__ + 1 + j * w_dim1] != zero)) {
#line 433 "../fortran/wnlsm.f"
	goto L630;
#line 433 "../fortran/wnlsm.f"
    }
/*<       CALL DROTMG(SCALE(I), SCALE(I+1), W(I,J), W(I+1,J), SPARAM) >*/
#line 434 "../fortran/wnlsm.f"
    drotmg_(&scale[i__], &scale[i__ + 1], &w[i__ + j * w_dim1], &w[i__ + 1 + 
	    j * w_dim1], sparam);
/*<       W(I+1,J) = ZERO >*/
#line 435 "../fortran/wnlsm.f"
    w[i__ + 1 + j * w_dim1] = zero;
/*<       CALL DROTM(NP1-J, W(I,J+1), MDW, W(I+1,J+1), MDW, SPARAM) >*/
#line 436 "../fortran/wnlsm.f"
    i__1 = np1 - j;
#line 436 "../fortran/wnlsm.f"
    drotm_(&i__1, &w[i__ + (j + 1) * w_dim1], mdw, &w[i__ + 1 + (j + 1) * 
	    w_dim1], mdw, sparam);
/*<   630 GO TO 1290 >*/
#line 437 "../fortran/wnlsm.f"
L630:
#line 437 "../fortran/wnlsm.f"
    goto L1290;
/*<   640 CONTINUE >*/
#line 438 "../fortran/wnlsm.f"
L640:

/*     TO PERFORM-MULTIPLIER-TEST-AND-DROP-A-CONSTRAINT */
/*<       CALL DCOPY(NSOLN, Z, 1, X, 1) >*/
#line 441 "../fortran/wnlsm.f"
    dcopy_(&nsoln, &z__[1], &c__1, &x[1], &c__1);
/*<       IF (.NOT.(NSOLN.LT.N)) GO TO 650 >*/
#line 442 "../fortran/wnlsm.f"
    if (! (nsoln < *n)) {
#line 442 "../fortran/wnlsm.f"
	goto L650;
#line 442 "../fortran/wnlsm.f"
    }
/*<       X(NSP1) = ZERO >*/
#line 443 "../fortran/wnlsm.f"
    x[nsp1] = zero;
/*<       CALL DCOPY(N-NSOLN, X(NSP1), 0, X(NSP1), 1) >*/
#line 444 "../fortran/wnlsm.f"
    i__1 = *n - nsoln;
#line 444 "../fortran/wnlsm.f"
    dcopy_(&i__1, &x[nsp1], &c__0, &x[nsp1], &c__1);
/*<   650 I = NIV1 >*/
#line 445 "../fortran/wnlsm.f"
L650:
#line 445 "../fortran/wnlsm.f"
    i__ = niv1;
/*<   660 IF (.NOT.(I.LE.ME)) GO TO 690 >*/
#line 446 "../fortran/wnlsm.f"
L660:
#line 446 "../fortran/wnlsm.f"
    if (! (i__ <= me)) {
#line 446 "../fortran/wnlsm.f"
	goto L690;
#line 446 "../fortran/wnlsm.f"
    }

/*     RECLASSIFY LEAST SQUARES EQATIONS AS EQUALITIES AS */
/*     NECESSARY. */
/*<       IF (.NOT.(ITYPE(I).EQ.0)) GO TO 670 >*/
#line 450 "../fortran/wnlsm.f"
    if (! (itype[i__] == 0)) {
#line 450 "../fortran/wnlsm.f"
	goto L670;
#line 450 "../fortran/wnlsm.f"
    }
/*<       I = I + 1 >*/
#line 451 "../fortran/wnlsm.f"
    ++i__;
/*<       GO TO 680 >*/
#line 452 "../fortran/wnlsm.f"
    goto L680;
/*<   670 CALL DSWAP(NP1, W(I,1), MDW, W(ME,1), MDW) >*/
#line 453 "../fortran/wnlsm.f"
L670:
#line 453 "../fortran/wnlsm.f"
    dswap_(&np1, &w[i__ + w_dim1], mdw, &w[me + w_dim1], mdw);
/*<       CALL DSWAP(1, SCALE(I), 1, SCALE(ME), 1) >*/
#line 454 "../fortran/wnlsm.f"
    dswap_(&c__1, &scale[i__], &c__1, &scale[me], &c__1);
/*<       ITEMP = ITYPE(I) >*/
#line 455 "../fortran/wnlsm.f"
    itemp = itype[i__];
/*<       ITYPE(I) = ITYPE(ME) >*/
#line 456 "../fortran/wnlsm.f"
    itype[i__] = itype[me];
/*<       ITYPE(ME) = ITEMP >*/
#line 457 "../fortran/wnlsm.f"
    itype[me] = itemp;
/*<       MEP1 = ME >*/
#line 458 "../fortran/wnlsm.f"
    mep1 = me;
/*<       ME = ME - 1 >*/
#line 459 "../fortran/wnlsm.f"
    --me;
/*<   680 GO TO 660 >*/
#line 460 "../fortran/wnlsm.f"
L680:
#line 460 "../fortran/wnlsm.f"
    goto L660;

/*     FORM INNER PRODUCT VECTOR WD(*) OF DUAL COEFFS. */
/*<   690 IF (.NOT.(NSP1.LE.N)) GO TO 730 >*/
#line 463 "../fortran/wnlsm.f"
L690:
#line 463 "../fortran/wnlsm.f"
    if (! (nsp1 <= *n)) {
#line 463 "../fortran/wnlsm.f"
	goto L730;
#line 463 "../fortran/wnlsm.f"
    }
/*<       DO 720 J=NSP1,N >*/
#line 464 "../fortran/wnlsm.f"
    i__1 = *n;
#line 464 "../fortran/wnlsm.f"
    for (j = nsp1; j <= i__1; ++j) {
/*<         SM = ZERO >*/
#line 465 "../fortran/wnlsm.f"
	sm = zero;
/*<         IF (.NOT.(NSOLN.LT.M)) GO TO 710 >*/
#line 466 "../fortran/wnlsm.f"
	if (! (nsoln < m)) {
#line 466 "../fortran/wnlsm.f"
	    goto L710;
#line 466 "../fortran/wnlsm.f"
	}
/*<         DO 700 I=NSP1,M >*/
#line 467 "../fortran/wnlsm.f"
	i__2 = m;
#line 467 "../fortran/wnlsm.f"
	for (i__ = nsp1; i__ <= i__2; ++i__) {
/*<           SM = SM + SCALE(I)*W(I,J)*W(I,NP1) >*/
#line 468 "../fortran/wnlsm.f"
	    sm += scale[i__] * w[i__ + j * w_dim1] * w[i__ + np1 * w_dim1];
/*<   700   CONTINUE >*/
#line 469 "../fortran/wnlsm.f"
/* L700: */
#line 469 "../fortran/wnlsm.f"
	}
/*<   710   WD(J) = SM >*/
#line 470 "../fortran/wnlsm.f"
L710:
#line 470 "../fortran/wnlsm.f"
	wd[j] = sm;
/*<   720 CONTINUE >*/
#line 471 "../fortran/wnlsm.f"
/* L720: */
#line 471 "../fortran/wnlsm.f"
    }
/*<   730 GO TO 750 >*/
#line 472 "../fortran/wnlsm.f"
L730:
#line 472 "../fortran/wnlsm.f"
    goto L750;
/*<   740 IF (POS .OR. DONE) GO TO 970 >*/
#line 473 "../fortran/wnlsm.f"
L740:
#line 473 "../fortran/wnlsm.f"
    if (pos || done) {
#line 473 "../fortran/wnlsm.f"
	goto L970;
#line 473 "../fortran/wnlsm.f"
    }

/*     FIND J SUCH THAT WD(J)=WMAX IS MAXIMUM.  THIS DETERMINES */
/*     THAT THE INCOMING COL J WILL REDUCE THE RESIDUAL VECTOR */
/*     AND BE POSITIVE. */
/*<   750 WMAX = ZERO >*/
#line 478 "../fortran/wnlsm.f"
L750:
#line 478 "../fortran/wnlsm.f"
    wmax = zero;
/*<       IWMAX = NSP1 >*/
#line 479 "../fortran/wnlsm.f"
    iwmax = nsp1;
/*<       IF (.NOT.(NSP1.LE.N)) GO TO 780 >*/
#line 480 "../fortran/wnlsm.f"
    if (! (nsp1 <= *n)) {
#line 480 "../fortran/wnlsm.f"
	goto L780;
#line 480 "../fortran/wnlsm.f"
    }
/*<       DO 770 J=NSP1,N >*/
#line 481 "../fortran/wnlsm.f"
    i__1 = *n;
#line 481 "../fortran/wnlsm.f"
    for (j = nsp1; j <= i__1; ++j) {
/*<         IF (.NOT.(WD(J).GT.WMAX)) GO TO 760 >*/
#line 482 "../fortran/wnlsm.f"
	if (! (wd[j] > wmax)) {
#line 482 "../fortran/wnlsm.f"
	    goto L760;
#line 482 "../fortran/wnlsm.f"
	}
/*<         WMAX = WD(J) >*/
#line 483 "../fortran/wnlsm.f"
	wmax = wd[j];
/*<         IWMAX = J >*/
#line 484 "../fortran/wnlsm.f"
	iwmax = j;
/*<   760   CONTINUE >*/
#line 485 "../fortran/wnlsm.f"
L760:
/*<   770 CONTINUE >*/
#line 486 "../fortran/wnlsm.f"
/* L770: */
#line 486 "../fortran/wnlsm.f"
	;
#line 486 "../fortran/wnlsm.f"
    }
/*<   780 IF (.NOT.(WMAX.LE.ZERO)) GO TO 790 >*/
#line 487 "../fortran/wnlsm.f"
L780:
#line 487 "../fortran/wnlsm.f"
    if (! (wmax <= zero)) {
#line 487 "../fortran/wnlsm.f"
	goto L790;
#line 487 "../fortran/wnlsm.f"
    }
/*<       DONE = .TRUE. >*/
#line 488 "../fortran/wnlsm.f"
    done = TRUE_;
/*<       GO TO 960 >*/
#line 489 "../fortran/wnlsm.f"
    goto L960;

/*     SET DUAL COEFF TO ZERO FOR INCOMING COL. */
/*<   790 WD(IWMAX) = ZERO >*/
#line 492 "../fortran/wnlsm.f"
L790:
#line 492 "../fortran/wnlsm.f"
    wd[iwmax] = zero;

/*     WMAX .GT. ZERO, SO OKAY TO MOVE COL IWMAX TO SOLN SET. */
/*     PERFORM TRANSFORMATION TO RETRIANGULARIZE, AND TEST */
/*     FOR NEAR LINEAR DEPENDENCE. */
/*     SWAP COL IWMAX INTO NSOLN-TH POSITION TO MAINTAIN UPPER */
/*     HESSENBERG FORM OF ADJACENT COLS, AND ADD NEW COL TO */
/*     TRIANGULAR DECOMPOSITION. */
/*<       NSOLN = NSP1 >*/
#line 500 "../fortran/wnlsm.f"
    nsoln = nsp1;
/*<       NSP1 = NSOLN + 1 >*/
#line 501 "../fortran/wnlsm.f"
    nsp1 = nsoln + 1;
/*<       NIV = NIV1 >*/
#line 502 "../fortran/wnlsm.f"
    niv = niv1;
/*<       NIV1 = NIV + 1 >*/
#line 503 "../fortran/wnlsm.f"
    niv1 = niv + 1;
/*<       IF (.NOT.(NSOLN.NE.IWMAX)) GO TO 800 >*/
#line 504 "../fortran/wnlsm.f"
    if (! (nsoln != iwmax)) {
#line 504 "../fortran/wnlsm.f"
	goto L800;
#line 504 "../fortran/wnlsm.f"
    }
/*<       CALL DSWAP(M, W(1,NSOLN), 1, W(1,IWMAX), 1) >*/
#line 505 "../fortran/wnlsm.f"
    dswap_(&m, &w[nsoln * w_dim1 + 1], &c__1, &w[iwmax * w_dim1 + 1], &c__1);
/*<       WD(IWMAX) = WD(NSOLN) >*/
#line 506 "../fortran/wnlsm.f"
    wd[iwmax] = wd[nsoln];
/*<       WD(NSOLN) = ZERO >*/
#line 507 "../fortran/wnlsm.f"
    wd[nsoln] = zero;
/*<       ITEMP = IPIVOT(NSOLN) >*/
#line 508 "../fortran/wnlsm.f"
    itemp = ipivot[nsoln];
/*<       IPIVOT(NSOLN) = IPIVOT(IWMAX) >*/
#line 509 "../fortran/wnlsm.f"
    ipivot[nsoln] = ipivot[iwmax];
/*<       IPIVOT(IWMAX) = ITEMP >*/
#line 510 "../fortran/wnlsm.f"
    ipivot[iwmax] = itemp;

/*     REDUCE COL NSOLN SO THAT THE MATRIX OF NONACTIVE */
/*     CONSTRAINTS VARIABLES IS TRIANGULAR. */
/*<   800 J = M >*/
#line 514 "../fortran/wnlsm.f"
L800:
#line 514 "../fortran/wnlsm.f"
    j = m;
/*<   810 IF (.NOT.(J.GT.NIV)) GO TO 870 >*/
#line 515 "../fortran/wnlsm.f"
L810:
#line 515 "../fortran/wnlsm.f"
    if (! (j > niv)) {
#line 515 "../fortran/wnlsm.f"
	goto L870;
#line 515 "../fortran/wnlsm.f"
    }
/*<       JM1 = J - 1 >*/
#line 516 "../fortran/wnlsm.f"
    jm1 = j - 1;
/*<       JP = JM1 >*/
#line 517 "../fortran/wnlsm.f"
    jp = jm1;

/*     WHEN OPERATING NEAR THE ME LINE, TEST TO SEE IF THE PIVOT ELT. */
/*     IS NEAR ZERO.  IF SO, USE THE LARGEST ELT. ABOVE IT AS THE PIVOT. */
/*     THIS IS TO MAINTAIN THE SHARP INTERFACE BETWEEN WEIGHTED AND */
/*     NON-WEIGHTED ROWS IN ALL CASES. */
/*<       IF (.NOT.(J.EQ.MEP1)) GO TO 850 >*/
#line 523 "../fortran/wnlsm.f"
    if (! (j == mep1)) {
#line 523 "../fortran/wnlsm.f"
	goto L850;
#line 523 "../fortran/wnlsm.f"
    }
/*<       IMAX = ME >*/
#line 524 "../fortran/wnlsm.f"
    imax = me;
/*<       AMAX = SCALE(ME)*W(ME,NSOLN)**2 >*/
/* Computing 2nd power */
#line 525 "../fortran/wnlsm.f"
    d__1 = w[me + nsoln * w_dim1];
#line 525 "../fortran/wnlsm.f"
    amax = scale[me] * (d__1 * d__1);
/*<   820 IF (.NOT.(JP.GE.NIV)) GO TO 840 >*/
#line 526 "../fortran/wnlsm.f"
L820:
#line 526 "../fortran/wnlsm.f"
    if (! (jp >= niv)) {
#line 526 "../fortran/wnlsm.f"
	goto L840;
#line 526 "../fortran/wnlsm.f"
    }
/*<       T = SCALE(JP)*W(JP,NSOLN)**2 >*/
/* Computing 2nd power */
#line 527 "../fortran/wnlsm.f"
    d__1 = w[jp + nsoln * w_dim1];
#line 527 "../fortran/wnlsm.f"
    t = scale[jp] * (d__1 * d__1);
/*<       IF (.NOT.(T.GT.AMAX)) GO TO 830 >*/
#line 528 "../fortran/wnlsm.f"
    if (! (t > amax)) {
#line 528 "../fortran/wnlsm.f"
	goto L830;
#line 528 "../fortran/wnlsm.f"
    }
/*<       IMAX = JP >*/
#line 529 "../fortran/wnlsm.f"
    imax = jp;
/*<       AMAX = T >*/
#line 530 "../fortran/wnlsm.f"
    amax = t;
/*<   830 JP = JP - 1 >*/
#line 531 "../fortran/wnlsm.f"
L830:
#line 531 "../fortran/wnlsm.f"
    --jp;
/*<       GO TO 820 >*/
#line 532 "../fortran/wnlsm.f"
    goto L820;
/*<   840 JP = IMAX >*/
#line 533 "../fortran/wnlsm.f"
L840:
#line 533 "../fortran/wnlsm.f"
    jp = imax;
/*<   850 IF (.NOT.(W(J,NSOLN).NE.ZERO)) GO TO 860 >*/
#line 534 "../fortran/wnlsm.f"
L850:
#line 534 "../fortran/wnlsm.f"
    if (! (w[j + nsoln * w_dim1] != zero)) {
#line 534 "../fortran/wnlsm.f"
	goto L860;
#line 534 "../fortran/wnlsm.f"
    }
/*<       CALL DROTMG(SCALE(JP), SCALE(J), W(JP,NSOLN), W(J,NSOLN), SPARAM) >*/
#line 535 "../fortran/wnlsm.f"
    drotmg_(&scale[jp], &scale[j], &w[jp + nsoln * w_dim1], &w[j + nsoln * 
	    w_dim1], sparam);
/*<       W(J,NSOLN) = ZERO >*/
#line 536 "../fortran/wnlsm.f"
    w[j + nsoln * w_dim1] = zero;
/*<       CALL DROTM(NP1-NSOLN, W(JP,NSP1), MDW, W(J,NSP1), MDW, SPARAM) >*/
#line 537 "../fortran/wnlsm.f"
    i__1 = np1 - nsoln;
#line 537 "../fortran/wnlsm.f"
    drotm_(&i__1, &w[jp + nsp1 * w_dim1], mdw, &w[j + nsp1 * w_dim1], mdw, 
	    sparam);
/*<   860 J = JM1 >*/
#line 538 "../fortran/wnlsm.f"
L860:
#line 538 "../fortran/wnlsm.f"
    j = jm1;
/*<       GO TO 810 >*/
#line 539 "../fortran/wnlsm.f"
    goto L810;

/*     SOLVE FOR Z(NSOLN)=PROPOSED NEW VALUE FOR X(NSOLN). */
/*     TEST IF THIS IS NONPOSITIVE OR TOO LARGE. */
/*     IF THIS WAS TRUE OR IF THE PIVOT TERM WAS ZERO REJECT */
/*     THE COL AS DEPENDENT. */
/*<   870 IF (.NOT.(W(NIV,NSOLN).NE.ZERO)) GO TO 890 >*/
#line 545 "../fortran/wnlsm.f"
L870:
#line 545 "../fortran/wnlsm.f"
    if (! (w[niv + nsoln * w_dim1] != zero)) {
#line 545 "../fortran/wnlsm.f"
	goto L890;
#line 545 "../fortran/wnlsm.f"
    }
/*<       ISOL = NIV >*/
#line 546 "../fortran/wnlsm.f"
    isol = niv;
/*<       ASSIGN 880 TO IGO897 >*/
#line 547 "../fortran/wnlsm.f"
    igo897 = 0;
#line 547 "../fortran/wnlsm.f"
    igo897_fmt = fmt_880;
/*<       GO TO 980 >*/
#line 548 "../fortran/wnlsm.f"
    goto L980;

/*     TEST-PROPOSED-NEW-COMPONENT */
/*<   880 GO TO 940 >*/
#line 551 "../fortran/wnlsm.f"
L880:
#line 551 "../fortran/wnlsm.f"
    goto L940;
/*<   890 IF (.NOT.(NIV.LE.ME .AND. W(MEP1,NSOLN).NE.ZERO)) GO TO 920 >*/
#line 552 "../fortran/wnlsm.f"
L890:
#line 552 "../fortran/wnlsm.f"
    if (! (niv <= me && w[mep1 + nsoln * w_dim1] != zero)) {
#line 552 "../fortran/wnlsm.f"
	goto L920;
#line 552 "../fortran/wnlsm.f"
    }

/*     TRY TO ADD ROW MEP1 AS AN ADDITIONAL EQUALITY CONSTRAINT. */
/*     CHECK SIZE OF PROPOSED NEW SOLN COMPONENT. */
/*     REJECT IT IF IT IS TOO LARGE. */
/*<       ISOL = MEP1 >*/
#line 557 "../fortran/wnlsm.f"
    isol = mep1;
/*<       ASSIGN 900 TO IGO897 >*/
#line 558 "../fortran/wnlsm.f"
    igo897 = 1;
#line 558 "../fortran/wnlsm.f"
    igo897_fmt = fmt_900;
/*<       GO TO 980 >*/
#line 559 "../fortran/wnlsm.f"
    goto L980;

/*     TEST-PROPOSED-NEW-COMPONENT */
/*<   900 IF (.NOT.(POS)) GO TO 910 >*/
#line 562 "../fortran/wnlsm.f"
L900:
#line 562 "../fortran/wnlsm.f"
    if (! pos) {
#line 562 "../fortran/wnlsm.f"
	goto L910;
#line 562 "../fortran/wnlsm.f"
    }

/*     SWAP ROWS MEP1 AND NIV, AND SCALE FACTORS FOR THESE ROWS. */
/*<       CALL DSWAP(NP1, W(MEP1,1), MDW, W(NIV,1), MDW) >*/
#line 565 "../fortran/wnlsm.f"
    dswap_(&np1, &w[mep1 + w_dim1], mdw, &w[niv + w_dim1], mdw);
/*<       CALL DSWAP(1, SCALE(MEP1), 1, SCALE(NIV), 1) >*/
#line 566 "../fortran/wnlsm.f"
    dswap_(&c__1, &scale[mep1], &c__1, &scale[niv], &c__1);
/*<       ITEMP = ITYPE(MEP1) >*/
#line 567 "../fortran/wnlsm.f"
    itemp = itype[mep1];
/*<       ITYPE(MEP1) = ITYPE(NIV) >*/
#line 568 "../fortran/wnlsm.f"
    itype[mep1] = itype[niv];
/*<       ITYPE(NIV) = ITEMP >*/
#line 569 "../fortran/wnlsm.f"
    itype[niv] = itemp;
/*<       ME = MEP1 >*/
#line 570 "../fortran/wnlsm.f"
    me = mep1;
/*<       MEP1 = ME + 1 >*/
#line 571 "../fortran/wnlsm.f"
    mep1 = me + 1;
/*<   910 GO TO 930 >*/
#line 572 "../fortran/wnlsm.f"
L910:
#line 572 "../fortran/wnlsm.f"
    goto L930;
/*<   920 POS = .FALSE. >*/
#line 573 "../fortran/wnlsm.f"
L920:
#line 573 "../fortran/wnlsm.f"
    pos = FALSE_;
/*<   930 CONTINUE >*/
#line 574 "../fortran/wnlsm.f"
L930:
/*<   940 IF (POS) GO TO 950 >*/
#line 575 "../fortran/wnlsm.f"
L940:
#line 575 "../fortran/wnlsm.f"
    if (pos) {
#line 575 "../fortran/wnlsm.f"
	goto L950;
#line 575 "../fortran/wnlsm.f"
    }
/*<       NSP1 = NSOLN >*/
#line 576 "../fortran/wnlsm.f"
    nsp1 = nsoln;
/*<       NSOLN = NSOLN - 1 >*/
#line 577 "../fortran/wnlsm.f"
    --nsoln;
/*<       NIV1 = NIV >*/
#line 578 "../fortran/wnlsm.f"
    niv1 = niv;
/*<       NIV = NIV - 1 >*/
#line 579 "../fortran/wnlsm.f"
    --niv;
/*<   950 CONTINUE >*/
#line 580 "../fortran/wnlsm.f"
L950:
/*<   960 GO TO 740 >*/
#line 581 "../fortran/wnlsm.f"
L960:
#line 581 "../fortran/wnlsm.f"
    goto L740;
/*<   970 GO TO 1250 >*/
#line 582 "../fortran/wnlsm.f"
L970:
#line 582 "../fortran/wnlsm.f"
    goto L1250;
/*<   980 CONTINUE >*/
#line 583 "../fortran/wnlsm.f"
L980:

/*     TO TEST-PROPOSED-NEW-COMPONENT */
/*<       Z2 = W(ISOL,NP1)/W(ISOL,NSOLN) >*/
#line 586 "../fortran/wnlsm.f"
    z2 = w[isol + np1 * w_dim1] / w[isol + nsoln * w_dim1];
/*<       Z(NSOLN) = Z2 >*/
#line 587 "../fortran/wnlsm.f"
    z__[nsoln] = z2;
/*<       POS = Z2.GT.ZERO >*/
#line 588 "../fortran/wnlsm.f"
    pos = z2 > zero;
/*<       IF (.NOT.(Z2*EANORM.GE.BNORM .AND. POS)) GO TO 990 >*/
#line 589 "../fortran/wnlsm.f"
    if (! (z2 * eanorm >= bnorm && pos)) {
#line 589 "../fortran/wnlsm.f"
	goto L990;
#line 589 "../fortran/wnlsm.f"
    }
/*<       POS = .NOT.(BLOWUP*Z2*EANORM.GE.BNORM) >*/
#line 590 "../fortran/wnlsm.f"
    pos = ! (blowup * z2 * eanorm >= bnorm);
/*<   990 GO TO 1280 >*/
#line 591 "../fortran/wnlsm.f"
L990:
#line 591 "../fortran/wnlsm.f"
    goto L1280;
/*<  1000 CONTINUE >*/
#line 592 "../fortran/wnlsm.f"
L1000:
/*     TO COMPUTE-FINAL-SOLUTION */

/*     SOLVE SYSTEM, STORE RESULTS IN X(*). */

/*<       ASSIGN 1010 TO IGO958 >*/
#line 597 "../fortran/wnlsm.f"
    igo958 = 1;
#line 597 "../fortran/wnlsm.f"
    igo958_fmt = fmt_1010;
/*<       GO TO 1110 >*/
#line 598 "../fortran/wnlsm.f"
    goto L1110;
/*     SOLVE-SYSTEM */
/*<  1010 CALL DCOPY(NSOLN, Z, 1, X, 1) >*/
#line 600 "../fortran/wnlsm.f"
L1010:
#line 600 "../fortran/wnlsm.f"
    dcopy_(&nsoln, &z__[1], &c__1, &x[1], &c__1);

/*     APPLY HOUSEHOLDER TRANSFORMATIONS TO X(*) IF KRANK.LT.L */
/*<       IF (.NOT.(0.LT.KRANK .AND. KRANK.LT.L)) GO TO 1030 >*/
#line 603 "../fortran/wnlsm.f"
    if (! (0 < krank && krank < *l)) {
#line 603 "../fortran/wnlsm.f"
	goto L1030;
#line 603 "../fortran/wnlsm.f"
    }
/*<       DO 1020 I=1,KRANK >*/
#line 604 "../fortran/wnlsm.f"
    i__1 = krank;
#line 604 "../fortran/wnlsm.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         CALL H12(2, I, KRP1, L, W(I,1), MDW, H(I), X, 1, 1, 1) >*/
#line 605 "../fortran/wnlsm.f"
	h12_(&c__2, &i__, &krp1, l, &w[i__ + w_dim1], mdw, &h__[i__], &x[1], &
		c__1, &c__1, &c__1);
/*<  1020 CONTINUE >*/
#line 606 "../fortran/wnlsm.f"
/* L1020: */
#line 606 "../fortran/wnlsm.f"
    }

/*     FILL IN TRAILING ZEROES FOR CONSTRAINED VARIABLES NOT IN SOLN. */
/*<  1030 IF (.NOT.(NSOLN.LT.N)) GO TO 1040 >*/
#line 609 "../fortran/wnlsm.f"
L1030:
#line 609 "../fortran/wnlsm.f"
    if (! (nsoln < *n)) {
#line 609 "../fortran/wnlsm.f"
	goto L1040;
#line 609 "../fortran/wnlsm.f"
    }
/*<       X(NSP1) = ZERO >*/
#line 610 "../fortran/wnlsm.f"
    x[nsp1] = zero;
/*<       CALL DCOPY(N-NSOLN, X(NSP1), 0, X(NSP1), 1) >*/
#line 611 "../fortran/wnlsm.f"
    i__1 = *n - nsoln;
#line 611 "../fortran/wnlsm.f"
    dcopy_(&i__1, &x[nsp1], &c__0, &x[nsp1], &c__1);

/*     REPERMUTE SOLN VECTOR TO NATURAL ORDER. */
/*<  1040 DO 1070 I=1,N >*/
#line 614 "../fortran/wnlsm.f"
L1040:
#line 614 "../fortran/wnlsm.f"
    i__1 = *n;
#line 614 "../fortran/wnlsm.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         J = I >*/
#line 615 "../fortran/wnlsm.f"
	j = i__;
/*<  1050   IF (IPIVOT(J).EQ.I) GO TO 1060 >*/
#line 616 "../fortran/wnlsm.f"
L1050:
#line 616 "../fortran/wnlsm.f"
	if (ipivot[j] == i__) {
#line 616 "../fortran/wnlsm.f"
	    goto L1060;
#line 616 "../fortran/wnlsm.f"
	}
/*<         J = J + 1 >*/
#line 617 "../fortran/wnlsm.f"
	++j;
/*<         GO TO 1050 >*/
#line 618 "../fortran/wnlsm.f"
	goto L1050;
/*<  1060   IPIVOT(J) = IPIVOT(I) >*/
#line 619 "../fortran/wnlsm.f"
L1060:
#line 619 "../fortran/wnlsm.f"
	ipivot[j] = ipivot[i__];
/*<         IPIVOT(I) = J >*/
#line 620 "../fortran/wnlsm.f"
	ipivot[i__] = j;
/*<         CALL DSWAP(1, X(J), 1, X(I), 1) >*/
#line 621 "../fortran/wnlsm.f"
	dswap_(&c__1, &x[j], &c__1, &x[i__], &c__1);
/*<  1070 CONTINUE >*/
#line 622 "../fortran/wnlsm.f"
/* L1070: */
#line 622 "../fortran/wnlsm.f"
    }

/*     RESCALE THE SOLN USING THE COL SCALING. */
/*<       DO 1080 J=1,N >*/
#line 625 "../fortran/wnlsm.f"
    i__1 = *n;
#line 625 "../fortran/wnlsm.f"
    for (j = 1; j <= i__1; ++j) {
/*<         X(J) = X(J)*D(J) >*/
#line 626 "../fortran/wnlsm.f"
	x[j] *= d__[j];
/*<  1080 CONTINUE >*/
#line 627 "../fortran/wnlsm.f"
/* L1080: */
#line 627 "../fortran/wnlsm.f"
    }
/*     IF (.NOT.(NSOLN.LT.M)) GO TO 1100                           REMK */
/*     DO 1090 I=NSP1,M                                            REMK */
/*<       IF (.NOT.(NIV.LT.M)) GO TO 1100 >*/
#line 630 "../fortran/wnlsm.f"
    if (! (niv < m)) {
#line 630 "../fortran/wnlsm.f"
	goto L1100;
#line 630 "../fortran/wnlsm.f"
    }
/*<       DO 1090 I = NIV1,M >*/
#line 631 "../fortran/wnlsm.f"
    i__1 = m;
#line 631 "../fortran/wnlsm.f"
    for (i__ = niv1; i__ <= i__1; ++i__) {
/*<         T = W(I,NP1) >*/
#line 632 "../fortran/wnlsm.f"
	t = w[i__ + np1 * w_dim1];
/*<         IF (I.LE.ME) T = T/ALAMDA >*/
#line 633 "../fortran/wnlsm.f"
	if (i__ <= me) {
#line 633 "../fortran/wnlsm.f"
	    t /= alamda;
#line 633 "../fortran/wnlsm.f"
	}
/*<         T = (SCALE(I)*T)*T >*/
#line 634 "../fortran/wnlsm.f"
	t = scale[i__] * t * t;
/*<         RNORM = RNORM + T >*/
#line 635 "../fortran/wnlsm.f"
	*rnorm += t;
/*<  1090 CONTINUE >*/
#line 636 "../fortran/wnlsm.f"
/* L1090: */
#line 636 "../fortran/wnlsm.f"
    }
/*<  1100 RNORM = DSQRT(RNORM) >*/
#line 637 "../fortran/wnlsm.f"
L1100:
#line 637 "../fortran/wnlsm.f"
    *rnorm = sqrt(*rnorm);
/*<       GO TO 1210 >*/
#line 638 "../fortran/wnlsm.f"
    goto L1210;

/*     TO SOLVE-SYSTEM */

/*<  1110 CONTINUE >*/
#line 642 "../fortran/wnlsm.f"
L1110:
/*<       IF (.NOT.(DONE)) GO TO 1120 >*/
#line 643 "../fortran/wnlsm.f"
    if (! done) {
#line 643 "../fortran/wnlsm.f"
	goto L1120;
#line 643 "../fortran/wnlsm.f"
    }
/*<       ISOL = 1 >*/
#line 644 "../fortran/wnlsm.f"
    isol = 1;
/*<       GO TO 1130 >*/
#line 645 "../fortran/wnlsm.f"
    goto L1130;
/*<  1120 ISOL = LP1 >*/
#line 646 "../fortran/wnlsm.f"
L1120:
#line 646 "../fortran/wnlsm.f"
    isol = lp1;
/*<  1130 IF (.NOT.(NSOLN.GE.ISOL)) GO TO 1190 >*/
#line 647 "../fortran/wnlsm.f"
L1130:
#line 647 "../fortran/wnlsm.f"
    if (! (nsoln >= isol)) {
#line 647 "../fortran/wnlsm.f"
	goto L1190;
#line 647 "../fortran/wnlsm.f"
    }

/*     COPY RT. HAND SIDE INTO TEMP VECTOR TO USE OVERWRITING METHOD. */
/*<       CALL DCOPY(NIV, W(1,NP1), 1, TEMP, 1) >*/
#line 650 "../fortran/wnlsm.f"
    dcopy_(&niv, &w[np1 * w_dim1 + 1], &c__1, &temp[1], &c__1);
/*<       DO 1180 JJ=ISOL,NSOLN >*/
#line 651 "../fortran/wnlsm.f"
    i__1 = nsoln;
#line 651 "../fortran/wnlsm.f"
    for (jj = isol; jj <= i__1; ++jj) {
/*<         J = NSOLN - JJ + ISOL >*/
#line 652 "../fortran/wnlsm.f"
	j = nsoln - jj + isol;
/*<         IF (.NOT.(J.GT.KRANK)) GO TO 1140 >*/
#line 653 "../fortran/wnlsm.f"
	if (! (j > krank)) {
#line 653 "../fortran/wnlsm.f"
	    goto L1140;
#line 653 "../fortran/wnlsm.f"
	}
/*<         I = NIV - JJ + ISOL >*/
#line 654 "../fortran/wnlsm.f"
	i__ = niv - jj + isol;
/*<         GO TO 1150 >*/
#line 655 "../fortran/wnlsm.f"
	goto L1150;
/*<  1140   I = J >*/
#line 656 "../fortran/wnlsm.f"
L1140:
#line 656 "../fortran/wnlsm.f"
	i__ = j;
/*<  1150   IF (.NOT.(J.GT.KRANK .AND. J.LE.L)) GO TO 1160 >*/
#line 657 "../fortran/wnlsm.f"
L1150:
#line 657 "../fortran/wnlsm.f"
	if (! (j > krank && j <= *l)) {
#line 657 "../fortran/wnlsm.f"
	    goto L1160;
#line 657 "../fortran/wnlsm.f"
	}
/*<         Z(J) = ZERO >*/
#line 658 "../fortran/wnlsm.f"
	z__[j] = zero;
/*<         GO TO 1170 >*/
#line 659 "../fortran/wnlsm.f"
	goto L1170;
/*<  1160   Z(J) = TEMP(I)/W(I,J) >*/
#line 660 "../fortran/wnlsm.f"
L1160:
#line 660 "../fortran/wnlsm.f"
	z__[j] = temp[i__] / w[i__ + j * w_dim1];
/*<         CALL DAXPY(I-1, -Z(J), W(1,J), 1, TEMP, 1) >*/
#line 661 "../fortran/wnlsm.f"
	i__2 = i__ - 1;
#line 661 "../fortran/wnlsm.f"
	d__1 = -z__[j];
#line 661 "../fortran/wnlsm.f"
	daxpy_(&i__2, &d__1, &w[j * w_dim1 + 1], &c__1, &temp[1], &c__1);
/*<  1170   CONTINUE >*/
#line 662 "../fortran/wnlsm.f"
L1170:
/*<  1180 CONTINUE >*/
#line 663 "../fortran/wnlsm.f"
/* L1180: */
#line 663 "../fortran/wnlsm.f"
	;
#line 663 "../fortran/wnlsm.f"
    }
/*<  1190 GO TO 1270 >*/
#line 664 "../fortran/wnlsm.f"
L1190:
#line 664 "../fortran/wnlsm.f"
    goto L1270;
/*<  1200 GO TO IGO986, (40) >*/
#line 665 "../fortran/wnlsm.f"
L1200:
#line 665 "../fortran/wnlsm.f"
    switch (igo986) {
#line 665 "../fortran/wnlsm.f"
	case 0: goto L40;
#line 665 "../fortran/wnlsm.f"
    }
/*<  1210 GO TO IGO980, (90) >*/
#line 666 "../fortran/wnlsm.f"
L1210:
#line 666 "../fortran/wnlsm.f"
    switch (igo980) {
#line 666 "../fortran/wnlsm.f"
	case 0: goto L90;
#line 666 "../fortran/wnlsm.f"
    }
/*<  1220 GO TO IGO991, (30) >*/
#line 667 "../fortran/wnlsm.f"
L1220:
#line 667 "../fortran/wnlsm.f"
    switch (igo991) {
#line 667 "../fortran/wnlsm.f"
	case 0: goto L30;
#line 667 "../fortran/wnlsm.f"
    }
/*<  1230 GO TO IGO998, (10) >*/
#line 668 "../fortran/wnlsm.f"
L1230:
#line 668 "../fortran/wnlsm.f"
    switch (igo998) {
#line 668 "../fortran/wnlsm.f"
	case 0: goto L10;
#line 668 "../fortran/wnlsm.f"
    }
/*<  1240 GO TO IGO995, (20) >*/
#line 669 "../fortran/wnlsm.f"
L1240:
#line 669 "../fortran/wnlsm.f"
    switch (igo995) {
#line 669 "../fortran/wnlsm.f"
	case 0: goto L20;
#line 669 "../fortran/wnlsm.f"
    }
/*<  1250 GO TO IGO983, (60) >*/
#line 670 "../fortran/wnlsm.f"
L1250:
#line 670 "../fortran/wnlsm.f"
    switch (igo983) {
#line 670 "../fortran/wnlsm.f"
	case 0: goto L60;
#line 670 "../fortran/wnlsm.f"
    }
/*<  1260 GO TO IGO977, (220) >*/
#line 671 "../fortran/wnlsm.f"
L1260:
#line 671 "../fortran/wnlsm.f"
    switch (igo977) {
#line 671 "../fortran/wnlsm.f"
	case 0: goto L220;
#line 671 "../fortran/wnlsm.f"
    }
/*<  1270 GO TO IGO958, (310, 1010) >*/
#line 672 "../fortran/wnlsm.f"
L1270:
#line 672 "../fortran/wnlsm.f"
    switch (igo958) {
#line 672 "../fortran/wnlsm.f"
	case 0: goto L310;
#line 672 "../fortran/wnlsm.f"
	case 1: goto L1010;
#line 672 "../fortran/wnlsm.f"
    }
/*<  1280 GO TO IGO897, (880, 900) >*/
#line 673 "../fortran/wnlsm.f"
L1280:
#line 673 "../fortran/wnlsm.f"
    switch (igo897) {
#line 673 "../fortran/wnlsm.f"
	case 0: goto L880;
#line 673 "../fortran/wnlsm.f"
	case 1: goto L900;
#line 673 "../fortran/wnlsm.f"
    }
/*<  1290 GO TO IGO938, (460, 480, 500, 520) >*/
#line 674 "../fortran/wnlsm.f"
L1290:
#line 674 "../fortran/wnlsm.f"
    switch (igo938) {
#line 674 "../fortran/wnlsm.f"
	case 0: goto L460;
#line 674 "../fortran/wnlsm.f"
	case 1: goto L480;
#line 674 "../fortran/wnlsm.f"
	case 2: goto L500;
#line 674 "../fortran/wnlsm.f"
	case 3: goto L520;
#line 674 "../fortran/wnlsm.f"
    }
/*<       END >*/
} /* wnlsm_ */

