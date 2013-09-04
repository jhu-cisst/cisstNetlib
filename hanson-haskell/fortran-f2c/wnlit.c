#line 1 "../fortran/wnlit.f"
/* ../fortran/wnlit.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/wnlit.f"
/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;

/*<        >*/
/* Subroutine */ int wnlit_(doublereal *w, integer *mdw, integer *m, integer *
	n, integer *l, integer *ipivot, integer *itype, doublereal *h__, 
	doublereal *scale, doublereal *rnorm, integer *idope, doublereal *
	dope, logical *done)
{
    /* Initialized data */

    static doublereal tenm3 = .001;
    static doublereal zero = 0.;
    static doublereal one = 1.;

    /* Format strings */
    static char fmt_20[] = "";
    static char fmt_30[] = "";
    static char fmt_40[] = "";
    static char fmt_120[] = "";
    static char fmt_190[] = "";
    static char fmt_200[] = "";
    static char fmt_240[] = "";
    static char fmt_320[] = "";
    static char fmt_330[] = "";

    /* System generated locals */
    integer w_dim1, w_offset, i__1, i__2;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    integer i__, j, k;
    doublereal t;
    integer i1, j1, l1;
    extern /* Subroutine */ int h12_(integer *, integer *, integer *, integer 
	    *, doublereal *, integer *, doublereal *, doublereal *, integer *,
	     integer *, integer *);
    integer ic, lb, me, jj, kk, jp, ir;
    doublereal rn, sn;
    integer jm1, ip1, lp1, np1, max__;
    doublereal tau;
    integer niv, mep1, irp1, krp1, niv1;
    doublereal hbar;
    integer lend, mend;
    doublereal alsq;
    integer igo990, igo993, igo996;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    logical indep;
    integer krank;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *), dswap_(integer *, doublereal *, integer 
	    *, doublereal *, integer *);
    integer itemp;
    extern /* Subroutine */ int drotm_(integer *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *);
    integer nsoln;
    logical recalc;
    extern integer idamax_(integer *, doublereal *, integer *);
    doublereal factor, eanorm, sparam[5];
    extern /* Subroutine */ int drotmg_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

    /* Assigned format variables */
    static char *igo996_fmt, *igo993_fmt, *igo990_fmt;


/*     THE EDITING REQUIRED TO CONVERT THIS SUBROUTINE FROM SINGLE TO */
/*     DOUBLE PRECISION INVOLVES THE FOLLOWING CHARACTER STRING CHANGES. */
/*     USE AN EDITING COMMAND (CHANGE) /STRING-1/(TO)STRING-2/. */
/*     (BEGIN CHANGES AT LINE WITH C++ IN COLS. 1-3.) */
/*     /REAL (12 BLANKS)/DOUBLE PRECISION/,/DCOPY/DCOPY/,/DROTM/DROTM/, */
/*     /DSCAL/DSCAL/,/DSQRT/DSQRT/,                                  REMK */
/*     /DSWAP/DSWAP/,/DMAX1/DMAX1/,/IDAMAX/IDAMAX/,/.D-/.D-/,/D0/D0/ */

/*     THIS IS A COMPANION SUBPROGRAM TO WNNLS( ). */
/*     THE DOCUMENTATION FOR WNNLS( ) HAS MORE COMPLETE */
/*     USAGE INSTRUCTIONS. */

/*     NOTE  THE M BY (N+1) MATRIX W( , ) CONTAINS THE RT. HAND SIDE */
/*           B AS THE (N+1)ST COL. */


/*     TRIANGULARIZE L1 BY L1 SUBSYSTEM, WHERE L1=MIN(M,L), WITH */
/*     COL INTERCHANGES. */
/*     REVISED MARCH 4, 1982 */

/* ++ */
/*<       DOUBLE PRECISION W(MDW,1), H(1), SCALE(1), DOPE(4), SPARAM(5) >*/
/*     DOUBLE PRECISION ALSQ, AMAX, EANORM, FAC, FACTOR, HBAR, ONE, RN */
/*<       DOUBLE PRECISION ALSQ, EANORM, FACTOR, HBAR, ONE, RN >*/
/*<       DOUBLE PRECISION RNORM, SN, T, TAU, TENM3, ZERO >*/
/*<       DOUBLE PRECISION DMAX1 >*/
/*<       INTEGER ITYPE(1), IPIVOT(1), IDOPE(8) >*/
/*<       INTEGER IDAMAX >*/
/*<       LOGICAL INDEP, DONE, RECALC >*/
/*<       DATA TENM3 /1.D-3/, ZERO /0.D0/, ONE /1.D0/ >*/
#line 34 "../fortran/wnlit.f"
    /* Parameter adjustments */
#line 34 "../fortran/wnlit.f"
    w_dim1 = *mdw;
#line 34 "../fortran/wnlit.f"
    w_offset = 1 + w_dim1;
#line 34 "../fortran/wnlit.f"
    w -= w_offset;
#line 34 "../fortran/wnlit.f"
    --ipivot;
#line 34 "../fortran/wnlit.f"
    --itype;
#line 34 "../fortran/wnlit.f"
    --h__;
#line 34 "../fortran/wnlit.f"
    --scale;
#line 34 "../fortran/wnlit.f"
    --idope;
#line 34 "../fortran/wnlit.f"
    --dope;
#line 34 "../fortran/wnlit.f"

#line 34 "../fortran/wnlit.f"
    /* Function Body */

/*<       ME = IDOPE(1) >*/
#line 36 "../fortran/wnlit.f"
    me = idope[1];
/*<       MEP1 = IDOPE(2) >*/
#line 37 "../fortran/wnlit.f"
    mep1 = idope[2];
/*<       KRANK = IDOPE(3) >*/
#line 38 "../fortran/wnlit.f"
    krank = idope[3];
/*<       KRP1 = IDOPE(4) >*/
#line 39 "../fortran/wnlit.f"
    krp1 = idope[4];
/*<       NSOLN = IDOPE(5) >*/
#line 40 "../fortran/wnlit.f"
    nsoln = idope[5];
/*<       NIV = IDOPE(6) >*/
#line 41 "../fortran/wnlit.f"
    niv = idope[6];
/*<       NIV1 = IDOPE(7) >*/
#line 42 "../fortran/wnlit.f"
    niv1 = idope[7];
/*<       L1 = IDOPE(8) >*/
#line 43 "../fortran/wnlit.f"
    l1 = idope[8];

/*<       ALSQ = DOPE(1) >*/
#line 45 "../fortran/wnlit.f"
    alsq = dope[1];
/*<       EANORM = DOPE(2) >*/
#line 46 "../fortran/wnlit.f"
    eanorm = dope[2];
/*     FAC = DOPE(3)                                               REMK */
/*<       TAU = DOPE(4) >*/
#line 48 "../fortran/wnlit.f"
    tau = dope[4];
/*<       NP1 = N + 1 >*/
#line 49 "../fortran/wnlit.f"
    np1 = *n + 1;
/*<       LB = MIN0(M-1,L) >*/
/* Computing MIN */
#line 50 "../fortran/wnlit.f"
    i__1 = *m - 1;
#line 50 "../fortran/wnlit.f"
    lb = min(i__1,*l);
/*<       RECALC = .TRUE. >*/
#line 51 "../fortran/wnlit.f"
    recalc = TRUE_;
/*<       RNORM = ZERO >*/
#line 52 "../fortran/wnlit.f"
    *rnorm = zero;
/*<       KRANK = 0 >*/
#line 53 "../fortran/wnlit.f"
    krank = 0;
/*     WE SET FACTOR=1.D0 SO THAT THE HEAVY WEIGHT ALAMDA WILL BE */
/*     INCLUDED IN THE TEST FOR COL INDEPENDENCE. */
/*<       FACTOR = 1.D0 >*/
#line 56 "../fortran/wnlit.f"
    factor = 1.;
/*<       I = 1 >*/
#line 57 "../fortran/wnlit.f"
    i__ = 1;
/*<       IP1 = 2 >*/
#line 58 "../fortran/wnlit.f"
    ip1 = 2;
/*<       LEND = L >*/
#line 59 "../fortran/wnlit.f"
    lend = *l;
/*<    10 IF (.NOT.(I.LE.LB)) GO TO 150 >*/
#line 60 "../fortran/wnlit.f"
L10:
#line 60 "../fortran/wnlit.f"
    if (! (i__ <= lb)) {
#line 60 "../fortran/wnlit.f"
	goto L150;
#line 60 "../fortran/wnlit.f"
    }
/*<       IF (.NOT.(I.LE.ME)) GO TO 130 >*/
#line 61 "../fortran/wnlit.f"
    if (! (i__ <= me)) {
#line 61 "../fortran/wnlit.f"
	goto L130;
#line 61 "../fortran/wnlit.f"
    }

/*     SET IR TO POINT TO THE I-TH ROW. */
/*<       IR = I >*/
#line 64 "../fortran/wnlit.f"
    ir = i__;
/*<       MEND = M >*/
#line 65 "../fortran/wnlit.f"
    mend = *m;
/*<       ASSIGN 20 TO IGO996 >*/
#line 66 "../fortran/wnlit.f"
    igo996 = 0;
#line 66 "../fortran/wnlit.f"
    igo996_fmt = fmt_20;
/*<       GO TO 460 >*/
#line 67 "../fortran/wnlit.f"
    goto L460;

/*     UPDATE-COL-SS-AND-FIND-PIVOT-COL */
/*<    20 ASSIGN 30 TO IGO993 >*/
#line 70 "../fortran/wnlit.f"
L20:
#line 70 "../fortran/wnlit.f"
    igo993 = 0;
#line 70 "../fortran/wnlit.f"
    igo993_fmt = fmt_30;
/*<       GO TO 560 >*/
#line 71 "../fortran/wnlit.f"
    goto L560;

/*     PERFORM-COL-INTERCHANGE */

/*     SET IC TO POINT TO I-TH COL. */
/*<    30 IC = I >*/
#line 76 "../fortran/wnlit.f"
L30:
#line 76 "../fortran/wnlit.f"
    ic = i__;
/*<       ASSIGN 40 TO IGO990 >*/
#line 77 "../fortran/wnlit.f"
    igo990 = 0;
#line 77 "../fortran/wnlit.f"
    igo990_fmt = fmt_40;
/*<       GO TO 520 >*/
#line 78 "../fortran/wnlit.f"
    goto L520;

/*     TEST-INDEP-OF-INCOMING-COL */
/*<    40 IF (.NOT.(INDEP)) GO TO 110 >*/
#line 81 "../fortran/wnlit.f"
L40:
#line 81 "../fortran/wnlit.f"
    if (! indep) {
#line 81 "../fortran/wnlit.f"
	goto L110;
#line 81 "../fortran/wnlit.f"
    }

/*     ELIMINATE I-TH COL BELOW DIAG. USING MOD. GIVENS TRANSFORMATIONS */
/*     APPLIED TO (A B). */
/*<       J = M >*/
#line 85 "../fortran/wnlit.f"
    j = *m;
/*<       DO 100 JJ=IP1,M >*/
#line 86 "../fortran/wnlit.f"
    i__1 = *m;
#line 86 "../fortran/wnlit.f"
    for (jj = ip1; jj <= i__1; ++jj) {
/*<         JM1 = J - 1 >*/
#line 87 "../fortran/wnlit.f"
	jm1 = j - 1;
/*<         JP = JM1 >*/
#line 88 "../fortran/wnlit.f"
	jp = jm1;
/*     WHEN OPERATING NEAR THE ME LINE, USE THE LARGEST ELT.        REMK */
/*     ABOVE IT AS THE PIVOT.                                       REMK */
/*       IF (.NOT.(J.EQ.MEP1)) GO TO 80                             REMK */
/*       IMAX = ME                                                  REMK */
/*       AMAX = SCALE(ME)*W(ME,I)**2                                REMK */
/*  50   IF (.NOT.(JP.GE.I)) GO TO 70                               REMK */
/*       T = SCALE(JP)*W(JP,I)**2                                   REMK */
/*       IF (.NOT.(T.GT.AMAX)) GO TO 60                             REMK */
/*       IMAX = JP                                                  REMK */
/*       AMAX = T                                                   REMK */
/*  60   JP = JP - 1                                                REMK */
/*       GO TO 50                                                   REMK */
/*  70   JP = IMAX                                                  REMK */
/*<         IF (.NOT. (JJ.EQ.M)) GO TO 70 >*/
#line 102 "../fortran/wnlit.f"
	if (! (jj == *m)) {
#line 102 "../fortran/wnlit.f"
	    goto L70;
#line 102 "../fortran/wnlit.f"
	}
/*<         IF (.NOT. (I.LT.MEP1)) GO TO 80 >*/
#line 103 "../fortran/wnlit.f"
	if (! (i__ < mep1)) {
#line 103 "../fortran/wnlit.f"
	    goto L80;
#line 103 "../fortran/wnlit.f"
	}
/*<         J = MEP1 >*/
#line 104 "../fortran/wnlit.f"
	j = mep1;
/*<         JP = I >*/
#line 105 "../fortran/wnlit.f"
	jp = i__;
/*<         T = SCALE(JP)*W(JP,I)**2*TAU**2 >*/
/* Computing 2nd power */
#line 106 "../fortran/wnlit.f"
	d__1 = w[jp + i__ * w_dim1];
/* Computing 2nd power */
#line 106 "../fortran/wnlit.f"
	d__2 = tau;
#line 106 "../fortran/wnlit.f"
	t = scale[jp] * (d__1 * d__1) * (d__2 * d__2);
/*<         IF (.NOT.(T.GT.SCALE(J)*W(J,I)**2)) GO TO 130 >*/
/* Computing 2nd power */
#line 107 "../fortran/wnlit.f"
	d__1 = w[j + i__ * w_dim1];
#line 107 "../fortran/wnlit.f"
	if (! (t > scale[j] * (d__1 * d__1))) {
#line 107 "../fortran/wnlit.f"
	    goto L130;
#line 107 "../fortran/wnlit.f"
	}
/*<         GO TO 80 >*/
#line 108 "../fortran/wnlit.f"
	goto L80;
/*<    70   IF (.NOT.(J.EQ.MEP1)) GO TO 80 >*/
#line 109 "../fortran/wnlit.f"
L70:
#line 109 "../fortran/wnlit.f"
	if (! (j == mep1)) {
#line 109 "../fortran/wnlit.f"
	    goto L80;
#line 109 "../fortran/wnlit.f"
	}
/*<         J = JM1 >*/
#line 110 "../fortran/wnlit.f"
	j = jm1;
/*<         JM1 = J - 1 >*/
#line 111 "../fortran/wnlit.f"
	jm1 = j - 1;
/*<         JP = JM1 >*/
#line 112 "../fortran/wnlit.f"
	jp = jm1;
/*<    80   IF (.NOT.(W(J,I).NE.ZERO)) GO TO 90 >*/
#line 113 "../fortran/wnlit.f"
L80:
#line 113 "../fortran/wnlit.f"
	if (! (w[j + i__ * w_dim1] != zero)) {
#line 113 "../fortran/wnlit.f"
	    goto L90;
#line 113 "../fortran/wnlit.f"
	}
/*<         CALL DROTMG(SCALE(JP), SCALE(J), W(JP,I), W(J,I), SPARAM) >*/
#line 114 "../fortran/wnlit.f"
	drotmg_(&scale[jp], &scale[j], &w[jp + i__ * w_dim1], &w[j + i__ * 
		w_dim1], sparam);
/*<         W(J,I) = ZERO >*/
#line 115 "../fortran/wnlit.f"
	w[j + i__ * w_dim1] = zero;
/*<         CALL DROTM(NP1-I, W(JP,IP1), MDW, W(J,IP1), MDW, SPARAM) >*/
#line 116 "../fortran/wnlit.f"
	i__2 = np1 - i__;
#line 116 "../fortran/wnlit.f"
	drotm_(&i__2, &w[jp + ip1 * w_dim1], mdw, &w[j + ip1 * w_dim1], mdw, 
		sparam);
/*<    90   J = JM1 >*/
#line 117 "../fortran/wnlit.f"
L90:
#line 117 "../fortran/wnlit.f"
	j = jm1;
/*<   100 CONTINUE >*/
#line 118 "../fortran/wnlit.f"
/* L100: */
#line 118 "../fortran/wnlit.f"
    }
/*<       GO TO 140 >*/
#line 119 "../fortran/wnlit.f"
    goto L140;
/*<   110 CONTINUE >*/
#line 120 "../fortran/wnlit.f"
L110:
/*<       IF (.NOT.(LEND.GT.I)) GO TO 130 >*/
#line 121 "../fortran/wnlit.f"
    if (! (lend > i__)) {
#line 121 "../fortran/wnlit.f"
	goto L130;
#line 121 "../fortran/wnlit.f"
    }

/*     COL I IS DEPENDENT. SWAP WITH COL LEND. */
/*<       MAX = LEND >*/
#line 124 "../fortran/wnlit.f"
    max__ = lend;

/*     PERFORM-COL-INTERCHANGE */
/*<       ASSIGN 120 TO IGO993 >*/
#line 127 "../fortran/wnlit.f"
    igo993 = 1;
#line 127 "../fortran/wnlit.f"
    igo993_fmt = fmt_120;
/*<       GO TO 560 >*/
#line 128 "../fortran/wnlit.f"
    goto L560;
/*<   120 CONTINUE >*/
#line 129 "../fortran/wnlit.f"
L120:
/*<       LEND = LEND - 1 >*/
#line 130 "../fortran/wnlit.f"
    --lend;

/*     FIND COL IN REMAINING SET WITH LARGEST SS. */
/*<       MAX = IDAMAX(LEND-I+1,H(I),1) + I - 1 >*/
#line 133 "../fortran/wnlit.f"
    i__1 = lend - i__ + 1;
#line 133 "../fortran/wnlit.f"
    max__ = idamax_(&i__1, &h__[i__], &c__1) + i__ - 1;
/*<       HBAR = H(MAX) >*/
#line 134 "../fortran/wnlit.f"
    hbar = h__[max__];
/*<       GO TO 30 >*/
#line 135 "../fortran/wnlit.f"
    goto L30;
/*<   130 CONTINUE >*/
#line 136 "../fortran/wnlit.f"
L130:
/*<       KRANK = I - 1 >*/
#line 137 "../fortran/wnlit.f"
    krank = i__ - 1;
/*<       GO TO 160 >*/
#line 138 "../fortran/wnlit.f"
    goto L160;
/*<   140 I = IP1 >*/
#line 139 "../fortran/wnlit.f"
L140:
#line 139 "../fortran/wnlit.f"
    i__ = ip1;
/*<       IP1 = IP1 + 1 >*/
#line 140 "../fortran/wnlit.f"
    ++ip1;
/*<       GO TO 10 >*/
#line 141 "../fortran/wnlit.f"
    goto L10;
/*<   150 KRANK = L1 >*/
#line 142 "../fortran/wnlit.f"
L150:
#line 142 "../fortran/wnlit.f"
    krank = l1;
/*<   160 CONTINUE >*/
#line 143 "../fortran/wnlit.f"
L160:
/*<       KRP1 = KRANK + 1 >*/
#line 144 "../fortran/wnlit.f"
    krp1 = krank + 1;
/*<       IF (.NOT.(KRANK.LT.ME)) GO TO 290 >*/
#line 145 "../fortran/wnlit.f"
    if (! (krank < me)) {
#line 145 "../fortran/wnlit.f"
	goto L290;
#line 145 "../fortran/wnlit.f"
    }
/*<       FACTOR = ALSQ >*/
#line 146 "../fortran/wnlit.f"
    factor = alsq;
/*<       DO 170 I=KRP1,ME >*/
#line 147 "../fortran/wnlit.f"
    i__1 = me;
#line 147 "../fortran/wnlit.f"
    for (i__ = krp1; i__ <= i__1; ++i__) {
/*<         IF (L.GT.0) W(I,1) = ZERO >*/
#line 148 "../fortran/wnlit.f"
	if (*l > 0) {
#line 148 "../fortran/wnlit.f"
	    w[i__ + w_dim1] = zero;
#line 148 "../fortran/wnlit.f"
	}
/*<         CALL DCOPY(L, W(I,1), 0, W(I,1), MDW) >*/
#line 149 "../fortran/wnlit.f"
	dcopy_(l, &w[i__ + w_dim1], &c__0, &w[i__ + w_dim1], mdw);
/*<   170 CONTINUE >*/
#line 150 "../fortran/wnlit.f"
/* L170: */
#line 150 "../fortran/wnlit.f"
    }

/*     DETERMINE THE RANK OF THE REMAINING EQUALITY CONSTRAINT */
/*     EQUATIONS BY ELIMINATING WITHIN THE BLOCK OF CONSTRAINED */
/*     VARIABLES.  REMOVE ANY REDUNDANT CONSTRAINTS. */
/*<       IR = KRP1 >*/
#line 155 "../fortran/wnlit.f"
    ir = krp1;
/*<       IF (.NOT. (L.LT.N)) GO TO 245 >*/
#line 156 "../fortran/wnlit.f"
    if (! (*l < *n)) {
#line 156 "../fortran/wnlit.f"
	goto L245;
#line 156 "../fortran/wnlit.f"
    }
/*<       LP1 = L + 1 >*/
#line 157 "../fortran/wnlit.f"
    lp1 = *l + 1;
/*<       RECALC = .TRUE. >*/
#line 158 "../fortran/wnlit.f"
    recalc = TRUE_;
/*<       LB = MIN0(L+ME-KRANK,N) >*/
/* Computing MIN */
#line 159 "../fortran/wnlit.f"
    i__1 = *l + me - krank;
#line 159 "../fortran/wnlit.f"
    lb = min(i__1,*n);
/*<       I = LP1 >*/
#line 160 "../fortran/wnlit.f"
    i__ = lp1;
/*<       IP1 = I + 1 >*/
#line 161 "../fortran/wnlit.f"
    ip1 = i__ + 1;
/*<   180 IF (.NOT.(I.LE.LB)) GO TO 280 >*/
#line 162 "../fortran/wnlit.f"
L180:
#line 162 "../fortran/wnlit.f"
    if (! (i__ <= lb)) {
#line 162 "../fortran/wnlit.f"
	goto L280;
#line 162 "../fortran/wnlit.f"
    }
/*<       IR = KRANK + I - L >*/
#line 163 "../fortran/wnlit.f"
    ir = krank + i__ - *l;
/*<       LEND = N >*/
#line 164 "../fortran/wnlit.f"
    lend = *n;
/*<       MEND = ME >*/
#line 165 "../fortran/wnlit.f"
    mend = me;
/*<       ASSIGN 190 TO IGO996 >*/
#line 166 "../fortran/wnlit.f"
    igo996 = 1;
#line 166 "../fortran/wnlit.f"
    igo996_fmt = fmt_190;
/*<       GO TO 460 >*/
#line 167 "../fortran/wnlit.f"
    goto L460;

/*     UPDATE-COL-SS-AND-FIND-PIVOT-COL */
/*<   190 ASSIGN 200 TO IGO993 >*/
#line 170 "../fortran/wnlit.f"
L190:
#line 170 "../fortran/wnlit.f"
    igo993 = 2;
#line 170 "../fortran/wnlit.f"
    igo993_fmt = fmt_200;
/*<       GO TO 560 >*/
#line 171 "../fortran/wnlit.f"
    goto L560;

/*     PERFORM-COL-INTERCHANGE */

/*     ELIMINATE ELEMENTS IN THE I-TH COL. */
/*<   200 J = ME >*/
#line 176 "../fortran/wnlit.f"
L200:
#line 176 "../fortran/wnlit.f"
    j = me;
/*<   210 IF (.NOT.(J.GT.IR)) GO TO 230 >*/
#line 177 "../fortran/wnlit.f"
L210:
#line 177 "../fortran/wnlit.f"
    if (! (j > ir)) {
#line 177 "../fortran/wnlit.f"
	goto L230;
#line 177 "../fortran/wnlit.f"
    }
/*<       JM1 = J - 1 >*/
#line 178 "../fortran/wnlit.f"
    jm1 = j - 1;
/*<       IF (.NOT.(W(J,I).NE.ZERO)) GO TO 220 >*/
#line 179 "../fortran/wnlit.f"
    if (! (w[j + i__ * w_dim1] != zero)) {
#line 179 "../fortran/wnlit.f"
	goto L220;
#line 179 "../fortran/wnlit.f"
    }
/*<       CALL DROTMG(SCALE(JM1), SCALE(J), W(JM1,I), W(J,I), SPARAM) >*/
#line 180 "../fortran/wnlit.f"
    drotmg_(&scale[jm1], &scale[j], &w[jm1 + i__ * w_dim1], &w[j + i__ * 
	    w_dim1], sparam);
/*<       W(J,I) = ZERO >*/
#line 181 "../fortran/wnlit.f"
    w[j + i__ * w_dim1] = zero;
/*<       CALL DROTM(NP1-I, W(JM1,IP1), MDW, W(J,IP1), MDW, SPARAM) >*/
#line 182 "../fortran/wnlit.f"
    i__1 = np1 - i__;
#line 182 "../fortran/wnlit.f"
    drotm_(&i__1, &w[jm1 + ip1 * w_dim1], mdw, &w[j + ip1 * w_dim1], mdw, 
	    sparam);
/*<   220 J = JM1 >*/
#line 183 "../fortran/wnlit.f"
L220:
#line 183 "../fortran/wnlit.f"
    j = jm1;
/*<       GO TO 210 >*/
#line 184 "../fortran/wnlit.f"
    goto L210;

/*     SET IC=I=COL BEING ELIMINATED */
/*<   230 IC = I >*/
#line 187 "../fortran/wnlit.f"
L230:
#line 187 "../fortran/wnlit.f"
    ic = i__;
/*<       ASSIGN 240 TO IGO990 >*/
#line 188 "../fortran/wnlit.f"
    igo990 = 1;
#line 188 "../fortran/wnlit.f"
    igo990_fmt = fmt_240;
/*<       GO TO 520 >*/
#line 189 "../fortran/wnlit.f"
    goto L520;

/*     TEST-INDEP-OF-INCOMING-COL */
/*<   240 IF (INDEP) GO TO 270 >*/
#line 192 "../fortran/wnlit.f"
L240:
#line 192 "../fortran/wnlit.f"
    if (indep) {
#line 192 "../fortran/wnlit.f"
	goto L270;
#line 192 "../fortran/wnlit.f"
    }

/*     REMOVE ANY REDUNDANT OR DEPENDENT EQUALITY CONSTRAINTS. */
/*<   245 CONTINUE >*/
#line 195 "../fortran/wnlit.f"
L245:
/*<       JJ = IR >*/
#line 196 "../fortran/wnlit.f"
    jj = ir;
/*<   250 IF (.NOT.(IR.LE.ME)) GO TO 260 >*/
#line 197 "../fortran/wnlit.f"
L250:
#line 197 "../fortran/wnlit.f"
    if (! (ir <= me)) {
#line 197 "../fortran/wnlit.f"
	goto L260;
#line 197 "../fortran/wnlit.f"
    }
/*<       W(IR,1) = ZERO >*/
#line 198 "../fortran/wnlit.f"
    w[ir + w_dim1] = zero;
/*<       CALL DCOPY(N, W(IR,1), 0, W(IR,1), MDW) >*/
#line 199 "../fortran/wnlit.f"
    dcopy_(n, &w[ir + w_dim1], &c__0, &w[ir + w_dim1], mdw);
/*<       RNORM = RNORM + (SCALE(IR)*W(IR,NP1)/ALSQ)*W(IR,NP1) >*/
#line 200 "../fortran/wnlit.f"
    *rnorm += scale[ir] * w[ir + np1 * w_dim1] / alsq * w[ir + np1 * w_dim1];
/*<       W(IR,NP1) = ZERO >*/
#line 201 "../fortran/wnlit.f"
    w[ir + np1 * w_dim1] = zero;
/*<       SCALE(IR) = ONE >*/
#line 202 "../fortran/wnlit.f"
    scale[ir] = one;
/*     RECLASSIFY THE ZEROED ROW AS A LEAST SQUARES EQUATION. */
/*<       ITYPE(IR) = 1 >*/
#line 204 "../fortran/wnlit.f"
    itype[ir] = 1;
/*<       IR = IR + 1 >*/
#line 205 "../fortran/wnlit.f"
    ++ir;
/*<       GO TO 250 >*/
#line 206 "../fortran/wnlit.f"
    goto L250;

/*     REDUCE ME TO REFLECT ANY DISCOVERED DEPENDENT EQUALITY */
/*     CONSTRAINTS. */
/*<   260 CONTINUE >*/
#line 210 "../fortran/wnlit.f"
L260:
/*<       ME = JJ - 1 >*/
#line 211 "../fortran/wnlit.f"
    me = jj - 1;
/*<       MEP1 = ME + 1 >*/
#line 212 "../fortran/wnlit.f"
    mep1 = me + 1;
/*<       GO TO 300 >*/
#line 213 "../fortran/wnlit.f"
    goto L300;
/*<   270 I = IP1 >*/
#line 214 "../fortran/wnlit.f"
L270:
#line 214 "../fortran/wnlit.f"
    i__ = ip1;
/*<       IP1 = IP1 + 1 >*/
#line 215 "../fortran/wnlit.f"
    ++ip1;
/*<       GO TO 180 >*/
#line 216 "../fortran/wnlit.f"
    goto L180;
/*<   280 CONTINUE >*/
#line 217 "../fortran/wnlit.f"
L280:
/*<   290 CONTINUE >*/
#line 218 "../fortran/wnlit.f"
L290:
/*<   300 CONTINUE >*/
#line 219 "../fortran/wnlit.f"
L300:
/*<       IF (.NOT.(KRANK.LT.L1)) GO TO 420 >*/
#line 220 "../fortran/wnlit.f"
    if (! (krank < l1)) {
#line 220 "../fortran/wnlit.f"
	goto L420;
#line 220 "../fortran/wnlit.f"
    }

/*     TRY TO DETERMINE THE VARIABLES KRANK+1 THROUGH L1 FROM THE */
/*     LEAST SQUARES EQUATIONS.  CONTINUE THE TRIANGULARIZATION WITH */
/*     PIVOT ELEMENT W(MEP1,I). */

/*<       RECALC = .TRUE. >*/
#line 226 "../fortran/wnlit.f"
    recalc = TRUE_;

/*     SET FACTOR=ALSQ TO REMOVE EFFECT OF HEAVY WEIGHT FROM */
/*     TEST FOR COL INDEPENDENCE. */
/*<       FACTOR = ALSQ >*/
#line 230 "../fortran/wnlit.f"
    factor = alsq;
/*<       KK = KRP1 >*/
#line 231 "../fortran/wnlit.f"
    kk = krp1;
/*<       I = KK >*/
#line 232 "../fortran/wnlit.f"
    i__ = kk;
/*<       IP1 = I + 1 >*/
#line 233 "../fortran/wnlit.f"
    ip1 = i__ + 1;
/*<   310 IF (.NOT.(I.LE.L1)) GO TO 410 >*/
#line 234 "../fortran/wnlit.f"
L310:
#line 234 "../fortran/wnlit.f"
    if (! (i__ <= l1)) {
#line 234 "../fortran/wnlit.f"
	goto L410;
#line 234 "../fortran/wnlit.f"
    }

/*     SET IR TO POINT TO THE MEP1-ST ROW. */
/*<       IR = MEP1 >*/
#line 237 "../fortran/wnlit.f"
    ir = mep1;
/*<       LEND = L >*/
#line 238 "../fortran/wnlit.f"
    lend = *l;
/*<       MEND = M >*/
#line 239 "../fortran/wnlit.f"
    mend = *m;
/*<       ASSIGN 320 TO IGO996 >*/
#line 240 "../fortran/wnlit.f"
    igo996 = 2;
#line 240 "../fortran/wnlit.f"
    igo996_fmt = fmt_320;
/*<       GO TO 460 >*/
#line 241 "../fortran/wnlit.f"
    goto L460;

/*     UPDATE-COL-SS-AND-FIND-PIVOT-COL */
/*<   320 ASSIGN 330 TO IGO993 >*/
#line 244 "../fortran/wnlit.f"
L320:
#line 244 "../fortran/wnlit.f"
    igo993 = 3;
#line 244 "../fortran/wnlit.f"
    igo993_fmt = fmt_330;
/*<       GO TO 560 >*/
#line 245 "../fortran/wnlit.f"
    goto L560;

/*     PERFORM-COL-INTERCHANGE */

/*     ELIMINATE I-TH COL BELOW THE IR-TH ELEMENT. */
/*<   330 IRP1 = IR + 1 >*/
#line 250 "../fortran/wnlit.f"
L330:
#line 250 "../fortran/wnlit.f"
    irp1 = ir + 1;
/*<       IF (.NOT.(IRP1.LE.M)) GO TO 355 >*/
#line 251 "../fortran/wnlit.f"
    if (! (irp1 <= *m)) {
#line 251 "../fortran/wnlit.f"
	goto L355;
#line 251 "../fortran/wnlit.f"
    }
/*<       J = M >*/
#line 252 "../fortran/wnlit.f"
    j = *m;
/*<       DO 350 JJ=IRP1,M >*/
#line 253 "../fortran/wnlit.f"
    i__1 = *m;
#line 253 "../fortran/wnlit.f"
    for (jj = irp1; jj <= i__1; ++jj) {
/*<         JM1 = J - 1 >*/
#line 254 "../fortran/wnlit.f"
	jm1 = j - 1;
/*<         IF (.NOT.(W(J,I).NE.ZERO)) GO TO 340 >*/
#line 255 "../fortran/wnlit.f"
	if (! (w[j + i__ * w_dim1] != zero)) {
#line 255 "../fortran/wnlit.f"
	    goto L340;
#line 255 "../fortran/wnlit.f"
	}
/*<         CALL DROTMG(SCALE(JM1), SCALE(J), W(JM1,I), W(J,I), SPARAM) >*/
#line 256 "../fortran/wnlit.f"
	drotmg_(&scale[jm1], &scale[j], &w[jm1 + i__ * w_dim1], &w[j + i__ * 
		w_dim1], sparam);
/*<         W(J,I) = ZERO >*/
#line 257 "../fortran/wnlit.f"
	w[j + i__ * w_dim1] = zero;
/*<         CALL DROTM(NP1-I, W(JM1,IP1), MDW, W(J,IP1), MDW, SPARAM) >*/
#line 258 "../fortran/wnlit.f"
	i__2 = np1 - i__;
#line 258 "../fortran/wnlit.f"
	drotm_(&i__2, &w[jm1 + ip1 * w_dim1], mdw, &w[j + ip1 * w_dim1], mdw, 
		sparam);
/*<   340   J = JM1 >*/
#line 259 "../fortran/wnlit.f"
L340:
#line 259 "../fortran/wnlit.f"
	j = jm1;
/*<   350 CONTINUE >*/
#line 260 "../fortran/wnlit.f"
/* L350: */
#line 260 "../fortran/wnlit.f"
    }
/*<   355 CONTINUE >*/
#line 261 "../fortran/wnlit.f"
L355:

/*     TEST IF NEW PIVOT ELEMENT IS NEAR ZERO. IF SO, THE COL IS */
/*     DEPENDENT. */
/*<       T = SCALE(IR)*W(IR,I)**2 >*/
/* Computing 2nd power */
#line 265 "../fortran/wnlit.f"
    d__1 = w[ir + i__ * w_dim1];
#line 265 "../fortran/wnlit.f"
    t = scale[ir] * (d__1 * d__1);
/*<       INDEP = T.GT.TAU**2*EANORM**2 >*/
/* Computing 2nd power */
#line 266 "../fortran/wnlit.f"
    d__1 = tau;
/* Computing 2nd power */
#line 266 "../fortran/wnlit.f"
    d__2 = eanorm;
#line 266 "../fortran/wnlit.f"
    indep = t > d__1 * d__1 * (d__2 * d__2);
/*<       IF (.NOT.INDEP) GO TO 380 >*/
#line 267 "../fortran/wnlit.f"
    if (! indep) {
#line 267 "../fortran/wnlit.f"
	goto L380;
#line 267 "../fortran/wnlit.f"
    }

/*     COL TEST PASSED. NOW MUST PASS ROW NORM TEST TO BE CLASSIFIED */
/*     AS INDEPENDENT. */
/*<       RN = ZERO >*/
#line 271 "../fortran/wnlit.f"
    rn = zero;
/*<       DO 370 I1=IR,M >*/
#line 272 "../fortran/wnlit.f"
    i__1 = *m;
#line 272 "../fortran/wnlit.f"
    for (i1 = ir; i1 <= i__1; ++i1) {
/*<         DO 360 J1=IP1,N >*/
#line 273 "../fortran/wnlit.f"
	i__2 = *n;
#line 273 "../fortran/wnlit.f"
	for (j1 = ip1; j1 <= i__2; ++j1) {
/*<           RN = DMAX1(RN,SCALE(I1)*W(I1,J1)**2) >*/
/* Computing MAX */
/* Computing 2nd power */
#line 274 "../fortran/wnlit.f"
	    d__3 = w[i1 + j1 * w_dim1];
#line 274 "../fortran/wnlit.f"
	    d__1 = rn, d__2 = scale[i1] * (d__3 * d__3);
#line 274 "../fortran/wnlit.f"
	    rn = max(d__1,d__2);
/*<   360   CONTINUE >*/
#line 275 "../fortran/wnlit.f"
/* L360: */
#line 275 "../fortran/wnlit.f"
	}
/*<   370 CONTINUE >*/
#line 276 "../fortran/wnlit.f"
/* L370: */
#line 276 "../fortran/wnlit.f"
    }
/*<       INDEP = T.GT.TAU**2*RN >*/
/* Computing 2nd power */
#line 277 "../fortran/wnlit.f"
    d__1 = tau;
#line 277 "../fortran/wnlit.f"
    indep = t > d__1 * d__1 * rn;

/*     IF INDEPENDENT, SWAP THE IR-TH AND KRP1-ST ROWS TO MAINTAIN THE */
/*     TRIANGULAR FORM.  UPDATE THE RANK INDICATOR KRANK AND THE */
/*     EQUALITY CONSTRAINT POINTER ME. */
/*<   380 IF (.NOT.(INDEP)) GO TO 390 >*/
#line 282 "../fortran/wnlit.f"
L380:
#line 282 "../fortran/wnlit.f"
    if (! indep) {
#line 282 "../fortran/wnlit.f"
	goto L390;
#line 282 "../fortran/wnlit.f"
    }
/*<       CALL DSWAP(NP1, W(KRP1,1), MDW, W(IR,1), MDW) >*/
#line 283 "../fortran/wnlit.f"
    dswap_(&np1, &w[krp1 + w_dim1], mdw, &w[ir + w_dim1], mdw);
/*<       CALL DSWAP(1, SCALE(KRP1), 1, SCALE(IR), 1) >*/
#line 284 "../fortran/wnlit.f"
    dswap_(&c__1, &scale[krp1], &c__1, &scale[ir], &c__1);
/*     RECLASSIFY THE LEAST SQ. EQUATION AS AN EQUALITY CONSTRAINT AND */
/*     RESCALE IT. */
/*<       ITYPE(IR) = 0 >*/
#line 287 "../fortran/wnlit.f"
    itype[ir] = 0;
/*<       T = DSQRT(SCALE(KRP1)) >*/
#line 288 "../fortran/wnlit.f"
    t = sqrt(scale[krp1]);
/*<       CALL DSCAL(NP1, T, W(KRP1,1), MDW) >*/
#line 289 "../fortran/wnlit.f"
    dscal_(&np1, &t, &w[krp1 + w_dim1], mdw);
/*<       SCALE(KRP1) = ALSQ >*/
#line 290 "../fortran/wnlit.f"
    scale[krp1] = alsq;
/*<       ME = MEP1 >*/
#line 291 "../fortran/wnlit.f"
    me = mep1;
/*<       MEP1 = ME + 1 >*/
#line 292 "../fortran/wnlit.f"
    mep1 = me + 1;
/*<       KRANK = KRP1 >*/
#line 293 "../fortran/wnlit.f"
    krank = krp1;
/*<       KRP1 = KRANK + 1 >*/
#line 294 "../fortran/wnlit.f"
    krp1 = krank + 1;
/*<       GO TO 400 >*/
#line 295 "../fortran/wnlit.f"
    goto L400;
/*<   390 GO TO 430 >*/
#line 296 "../fortran/wnlit.f"
L390:
#line 296 "../fortran/wnlit.f"
    goto L430;
/*<   400 I = IP1 >*/
#line 297 "../fortran/wnlit.f"
L400:
#line 297 "../fortran/wnlit.f"
    i__ = ip1;
/*<       IP1 = IP1 + 1 >*/
#line 298 "../fortran/wnlit.f"
    ++ip1;
/*<       GO TO 310 >*/
#line 299 "../fortran/wnlit.f"
    goto L310;
/*<   410 CONTINUE >*/
#line 300 "../fortran/wnlit.f"
L410:
/*<   420 CONTINUE >*/
#line 301 "../fortran/wnlit.f"
L420:
/*<   430 CONTINUE >*/
#line 302 "../fortran/wnlit.f"
L430:

/*     IF PSEUDORANK IS LESS THAN L, APPLY HOUSEHOLDER TRANS. */
/*     FROM RIGHT. */
/*<       IF (.NOT.(KRANK.LT.L)) GO TO 450 >*/
#line 306 "../fortran/wnlit.f"
    if (! (krank < *l)) {
#line 306 "../fortran/wnlit.f"
	goto L450;
#line 306 "../fortran/wnlit.f"
    }
/*<       DO 440 I=1,KRANK >*/
#line 307 "../fortran/wnlit.f"
    i__1 = krank;
#line 307 "../fortran/wnlit.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         J = KRP1 - I >*/
#line 308 "../fortran/wnlit.f"
	j = krp1 - i__;
/*<         CALL H12(1, J, KRP1, L, W(J,1), MDW, H(J), W, MDW, 1, J-1) >*/
#line 309 "../fortran/wnlit.f"
	i__2 = j - 1;
#line 309 "../fortran/wnlit.f"
	h12_(&c__1, &j, &krp1, l, &w[j + w_dim1], mdw, &h__[j], &w[w_offset], 
		mdw, &c__1, &i__2);
/*<   440 CONTINUE >*/
#line 310 "../fortran/wnlit.f"
/* L440: */
#line 310 "../fortran/wnlit.f"
    }
/*<   450 NIV = KRANK + NSOLN - L >*/
#line 311 "../fortran/wnlit.f"
L450:
#line 311 "../fortran/wnlit.f"
    niv = krank + nsoln - *l;
/*<       NIV1 = NIV + 1 >*/
#line 312 "../fortran/wnlit.f"
    niv1 = niv + 1;
/*<       IF (L.EQ.N) DONE = .TRUE. >*/
#line 313 "../fortran/wnlit.f"
    if (*l == *n) {
#line 313 "../fortran/wnlit.f"
	*done = TRUE_;
#line 313 "../fortran/wnlit.f"
    }

/*  END OF INITIAL TRIANGULARIZATION. */
/*<       IDOPE(1) = ME >*/
#line 316 "../fortran/wnlit.f"
    idope[1] = me;
/*<       IDOPE(2) = MEP1 >*/
#line 317 "../fortran/wnlit.f"
    idope[2] = mep1;
/*<       IDOPE(3) = KRANK >*/
#line 318 "../fortran/wnlit.f"
    idope[3] = krank;
/*<       IDOPE(4) = KRP1 >*/
#line 319 "../fortran/wnlit.f"
    idope[4] = krp1;
/*<       IDOPE(5) = NSOLN >*/
#line 320 "../fortran/wnlit.f"
    idope[5] = nsoln;
/*<       IDOPE(6) = NIV >*/
#line 321 "../fortran/wnlit.f"
    idope[6] = niv;
/*<       IDOPE(7) = NIV1 >*/
#line 322 "../fortran/wnlit.f"
    idope[7] = niv1;
/*<       IDOPE(8) = L1 >*/
#line 323 "../fortran/wnlit.f"
    idope[8] = l1;
/*<       RETURN >*/
#line 324 "../fortran/wnlit.f"
    return 0;
/*<   460 CONTINUE >*/
#line 325 "../fortran/wnlit.f"
L460:

/*     TO UPDATE-COL-SS-AND-FIND-PIVOT-COL */

/*     THE COL SS VECTOR WILL BE UPDATED AT EACH STEP. WHEN */
/*     NUMERICALLY NECESSARY, THESE VALUES WILL BE RECOMPUTED. */

/*<       IF (.NOT.(IR.NE.1 .AND. (.NOT.RECALC))) GO TO 480 >*/
#line 332 "../fortran/wnlit.f"
    if (! (ir != 1 && ! recalc)) {
#line 332 "../fortran/wnlit.f"
	goto L480;
#line 332 "../fortran/wnlit.f"
    }
/*     UPDATE COL SS =SUM OF SQUARES. */
/*<       DO 470 J=I,LEND >*/
#line 334 "../fortran/wnlit.f"
    i__1 = lend;
#line 334 "../fortran/wnlit.f"
    for (j = i__; j <= i__1; ++j) {
/*<         H(J) = H(J) - SCALE(IR-1)*W(IR-1,J)**2 >*/
/* Computing 2nd power */
#line 335 "../fortran/wnlit.f"
	d__1 = w[ir - 1 + j * w_dim1];
#line 335 "../fortran/wnlit.f"
	h__[j] -= scale[ir - 1] * (d__1 * d__1);
/*<   470 CONTINUE >*/
#line 336 "../fortran/wnlit.f"
/* L470: */
#line 336 "../fortran/wnlit.f"
    }

/*     TEST FOR NUMERICAL ACCURACY. */
/*<       MAX = IDAMAX(LEND-I+1,H(I),1) + I - 1 >*/
#line 339 "../fortran/wnlit.f"
    i__1 = lend - i__ + 1;
#line 339 "../fortran/wnlit.f"
    max__ = idamax_(&i__1, &h__[i__], &c__1) + i__ - 1;
/*<       RECALC = HBAR + TENM3*H(MAX).EQ.HBAR >*/
#line 340 "../fortran/wnlit.f"
    recalc = hbar + tenm3 * h__[max__] == hbar;

/*     IF REQUIRED, RECALCULATE COL SS, USING ROWS IR THROUGH MEND. */
/*<   480 IF (.NOT.(RECALC)) GO TO 510 >*/
#line 343 "../fortran/wnlit.f"
L480:
#line 343 "../fortran/wnlit.f"
    if (! recalc) {
#line 343 "../fortran/wnlit.f"
	goto L510;
#line 343 "../fortran/wnlit.f"
    }
/*<       DO 500 J=I,LEND >*/
#line 344 "../fortran/wnlit.f"
    i__1 = lend;
#line 344 "../fortran/wnlit.f"
    for (j = i__; j <= i__1; ++j) {
/*<         H(J) = ZERO >*/
#line 345 "../fortran/wnlit.f"
	h__[j] = zero;
/*<         DO 490 K=IR,MEND >*/
#line 346 "../fortran/wnlit.f"
	i__2 = mend;
#line 346 "../fortran/wnlit.f"
	for (k = ir; k <= i__2; ++k) {
/*<           H(J) = H(J) + SCALE(K)*W(K,J)**2 >*/
/* Computing 2nd power */
#line 347 "../fortran/wnlit.f"
	    d__1 = w[k + j * w_dim1];
#line 347 "../fortran/wnlit.f"
	    h__[j] += scale[k] * (d__1 * d__1);
/*<   490   CONTINUE >*/
#line 348 "../fortran/wnlit.f"
/* L490: */
#line 348 "../fortran/wnlit.f"
	}
/*<   500 CONTINUE >*/
#line 349 "../fortran/wnlit.f"
/* L500: */
#line 349 "../fortran/wnlit.f"
    }

/*     FIND COL WITH LARGEST SS. */
/*<       MAX = IDAMAX(LEND-I+1,H(I),1) + I - 1 >*/
#line 352 "../fortran/wnlit.f"
    i__1 = lend - i__ + 1;
#line 352 "../fortran/wnlit.f"
    max__ = idamax_(&i__1, &h__[i__], &c__1) + i__ - 1;
/*<       HBAR = H(MAX) >*/
#line 353 "../fortran/wnlit.f"
    hbar = h__[max__];
/*<   510 GO TO 600 >*/
#line 354 "../fortran/wnlit.f"
L510:
#line 354 "../fortran/wnlit.f"
    goto L600;
/*<   520 CONTINUE >*/
#line 355 "../fortran/wnlit.f"
L520:

/*     TO TEST-INDEP-OF-INCOMING-COL */

/*     TEST THE COL IC TO DETERMINE IF IT IS LINEARLY INDEPENDENT */
/*     OF THE COLS ALREADY IN THE BASIS.  IN THE INIT TRI */
/*     STEP, WE USUALLY WANT THE HEAVY WEIGHT ALAMDA TO */
/*     BE INCLUDED IN THE TEST FOR INDEPENDENCE.  IN THIS CASE THE */
/*     VALUE OF FACTOR WILL HAVE BEEN SET TO 1.D0 BEFORE THIS */
/*     PROCEDURE IS INVOKED.  IN THE POTENTIALLY RANK DEFICIENT */
/*     PROBLEM, THE VALUE OF FACTOR WILL HAVE BEEN */
/*     SET TO ALSQ=ALAMDA**2 TO REMOVE THE EFFECT OF THE HEAVY WEIGHT */
/*     FROM THE TEST FOR INDEPENDENCE. */

/*     WRITE NEW COL AS PARTITIONED VECTOR */
/*             (A1)  NUMBER OF COMPONENTS IN SOLN SO FAR = NIV */
/*             (A2)  M-NIV COMPONENTS */
/*     AND COMPUTE  SN = INVERSE WEIGHTED LENGTH OF A1 */
/*                  RN = INVERSE WEIGHTED LENGTH OF A2 */
/*     CALL THE COL INDEPENDENT WHEN RN .GT. TAU*SN */
/*<       SN = ZERO >*/
#line 375 "../fortran/wnlit.f"
    sn = zero;
/*<       RN = ZERO >*/
#line 376 "../fortran/wnlit.f"
    rn = zero;
/*<       DO 550 J=1,MEND >*/
#line 377 "../fortran/wnlit.f"
    i__1 = mend;
#line 377 "../fortran/wnlit.f"
    for (j = 1; j <= i__1; ++j) {
/*<         T = SCALE(J) >*/
#line 378 "../fortran/wnlit.f"
	t = scale[j];
/*<         IF (J.LE.ME) T = T/FACTOR >*/
#line 379 "../fortran/wnlit.f"
	if (j <= me) {
#line 379 "../fortran/wnlit.f"
	    t /= factor;
#line 379 "../fortran/wnlit.f"
	}
/*<         T = T*W(J,IC)**2 >*/
/* Computing 2nd power */
#line 380 "../fortran/wnlit.f"
	d__1 = w[j + ic * w_dim1];
#line 380 "../fortran/wnlit.f"
	t *= d__1 * d__1;
/*<         IF (.NOT.(J.LT.IR)) GO TO 530 >*/
#line 381 "../fortran/wnlit.f"
	if (! (j < ir)) {
#line 381 "../fortran/wnlit.f"
	    goto L530;
#line 381 "../fortran/wnlit.f"
	}
/*<         SN = SN + T >*/
#line 382 "../fortran/wnlit.f"
	sn += t;
/*<         GO TO 540 >*/
#line 383 "../fortran/wnlit.f"
	goto L540;
/*<   530   RN = RN + T >*/
#line 384 "../fortran/wnlit.f"
L530:
#line 384 "../fortran/wnlit.f"
	rn += t;
/*<   540   CONTINUE >*/
#line 385 "../fortran/wnlit.f"
L540:
/*<   550 CONTINUE >*/
#line 386 "../fortran/wnlit.f"
/* L550: */
#line 386 "../fortran/wnlit.f"
	;
#line 386 "../fortran/wnlit.f"
    }
/*<       INDEP = RN.GT.TAU**2*SN >*/
/* Computing 2nd power */
#line 387 "../fortran/wnlit.f"
    d__1 = tau;
#line 387 "../fortran/wnlit.f"
    indep = rn > d__1 * d__1 * sn;
/*<       GO TO 590 >*/
#line 388 "../fortran/wnlit.f"
    goto L590;
/*<   560 CONTINUE >*/
#line 389 "../fortran/wnlit.f"
L560:

/*     TO PERFORM-COL-INTERCHANGE */

/*<       IF (.NOT.(MAX.NE.I)) GO TO 570 >*/
#line 393 "../fortran/wnlit.f"
    if (! (max__ != i__)) {
#line 393 "../fortran/wnlit.f"
	goto L570;
#line 393 "../fortran/wnlit.f"
    }
/*     EXCHANGE ELEMENTS OF PERMUTED INDEX VECTOR AND PERFORM COL */
/*     INTERCHANGES. */
/*<       ITEMP = IPIVOT(I) >*/
#line 396 "../fortran/wnlit.f"
    itemp = ipivot[i__];
/*<       IPIVOT(I) = IPIVOT(MAX) >*/
#line 397 "../fortran/wnlit.f"
    ipivot[i__] = ipivot[max__];
/*<       IPIVOT(MAX) = ITEMP >*/
#line 398 "../fortran/wnlit.f"
    ipivot[max__] = itemp;
/*<       CALL DSWAP(M, W(1,MAX), 1, W(1,I), 1) >*/
#line 399 "../fortran/wnlit.f"
    dswap_(m, &w[max__ * w_dim1 + 1], &c__1, &w[i__ * w_dim1 + 1], &c__1);
/*<       T = H(MAX) >*/
#line 400 "../fortran/wnlit.f"
    t = h__[max__];
/*<       H(MAX) = H(I) >*/
#line 401 "../fortran/wnlit.f"
    h__[max__] = h__[i__];
/*<       H(I) = T >*/
#line 402 "../fortran/wnlit.f"
    h__[i__] = t;
/*<   570 GO TO 580 >*/
#line 403 "../fortran/wnlit.f"
L570:
#line 403 "../fortran/wnlit.f"
    goto L580;
/*<   580 GO TO IGO993, (30, 200, 330, 120) >*/
#line 404 "../fortran/wnlit.f"
L580:
#line 404 "../fortran/wnlit.f"
    switch (igo993) {
#line 404 "../fortran/wnlit.f"
	case 0: goto L30;
#line 404 "../fortran/wnlit.f"
	case 1: goto L120;
#line 404 "../fortran/wnlit.f"
	case 2: goto L200;
#line 404 "../fortran/wnlit.f"
	case 3: goto L330;
#line 404 "../fortran/wnlit.f"
    }
/*<   590 GO TO IGO990, (40, 240) >*/
#line 405 "../fortran/wnlit.f"
L590:
#line 405 "../fortran/wnlit.f"
    switch (igo990) {
#line 405 "../fortran/wnlit.f"
	case 0: goto L40;
#line 405 "../fortran/wnlit.f"
	case 1: goto L240;
#line 405 "../fortran/wnlit.f"
    }
/*<   600 GO TO IGO996, (20, 190, 320) >*/
#line 406 "../fortran/wnlit.f"
L600:
#line 406 "../fortran/wnlit.f"
    switch (igo996) {
#line 406 "../fortran/wnlit.f"
	case 0: goto L20;
#line 406 "../fortran/wnlit.f"
	case 1: goto L190;
#line 406 "../fortran/wnlit.f"
	case 2: goto L320;
#line 406 "../fortran/wnlit.f"
    }
/*<       END >*/
} /* wnlit_ */

