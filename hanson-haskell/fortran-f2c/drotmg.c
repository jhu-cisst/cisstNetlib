#line 1 "../fortran/drotmg.f"
/* ../fortran/drotmg.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/drotmg.f"
/*<       SUBROUTINE DROTMG (DD1,DD2,DX1,DY1,DPARAM) >*/
/* Subroutine */ int drotmg_(doublereal *dd1, doublereal *dd2, doublereal *
	dx1, doublereal *dy1, doublereal *dparam)
{
    /* Initialized data */

    static doublereal zero = 0.;
    static doublereal one = 1.;
    static doublereal two = 2.;
    static doublereal gam = 4096.;
    static doublereal gamsq = 16777216.;
    static doublereal rgamsq = 5.9604645e-8;

    /* Format strings */
    static char fmt_120[] = "";
    static char fmt_150[] = "";
    static char fmt_180[] = "";
    static char fmt_210[] = "";

    /* System generated locals */
    doublereal d__1;

    /* Local variables */
    doublereal du, dp1, dp2, dq2, dq1, dh11, dh21, dh12, dh22;
    integer igo;
    doublereal dflag, dtemp;

    /* Assigned format variables */
    static char *igo_fmt;


/*     CONSTRUCT THE MODIFIED GIVENS TRANSFORMATION MATRIX H WHICH ZEROS */
/*     THE SECOND COMPONENT OF THE 2-VECTOR  (DSQRT(DD1)*DX1,DSQRT(DD2)* */
/*     DY2)**T. */
/*     WITH DPARAM(1)=DFLAG, H HAS ONE OF THE FOLLOWING FORMS.. */

/*     DFLAG=-1.D0     DFLAG=0.D0        DFLAG=1.D0     DFLAG=-2.D0 */

/*       (DH11  DH12)    (1.D0  DH12)    (DH11  1.D0)    (1.D0  0.D0) */
/*     H=(          )    (          )    (          )    (          ) */
/*       (DH21  DH22),   (DH21  1.D0),   (-1.D0 DH22),   (0.D0  1.D0). */
/*     LOCATIONS 2-4 OF DPARAM CONTAIN DH11, DH21, DH12, AND DH22 */
/*     RESPECTIVELY. (VALUES OF 1.D0, -1.D0, OR 0.D0 IMPLIED BY THE */
/*     VALUE OF DPARAM(1) ARE NOT STORED IN DPARAM.) */

/*     THE VALUES OF GAMSQ AND RGAMSQ SET IN THE DATA STATEMENT MAY BE */
/*     INEXACT.  THIS IS OK AS THEY ARE ONLY USED FOR TESTING THE SIZE */
/*     OF DD1 AND DD2.  ALL ACTUAL SCALING OF DATA IS DONE USING GAM. */

/*<        >*/
/*<       DIMENSION DPARAM(5) >*/

/*<       DATA ZERO,ONE,TWO /0.D0,1.D0,2.D0/ >*/
#line 26 "../fortran/drotmg.f"
    /* Parameter adjustments */
#line 26 "../fortran/drotmg.f"
    --dparam;
#line 26 "../fortran/drotmg.f"

#line 26 "../fortran/drotmg.f"
    /* Function Body */
/*<       DATA GAM,GAMSQ,RGAMSQ/4096.D0,16777216.D0,5.9604645D-8/ >*/
/*<       IF(.NOT. DD1 .LT. ZERO) GO TO 10 >*/
#line 28 "../fortran/drotmg.f"
    if (! (*dd1 < zero)) {
#line 28 "../fortran/drotmg.f"
	goto L10;
#line 28 "../fortran/drotmg.f"
    }
/*       GO ZERO-H-D-AND-DX1.. */
/*<           GO TO 60 >*/
#line 30 "../fortran/drotmg.f"
    goto L60;
/*<    10 CONTINUE >*/
#line 31 "../fortran/drotmg.f"
L10:
/*     CASE-DD1-NONNEGATIVE */
/*<       DP2=DD2*DY1 >*/
#line 33 "../fortran/drotmg.f"
    dp2 = *dd2 * *dy1;
/*<       IF(.NOT. DP2 .EQ. ZERO) GO TO 20 >*/
#line 34 "../fortran/drotmg.f"
    if (! (dp2 == zero)) {
#line 34 "../fortran/drotmg.f"
	goto L20;
#line 34 "../fortran/drotmg.f"
    }
/*<           DFLAG=-TWO >*/
#line 35 "../fortran/drotmg.f"
    dflag = -two;
/*<           GO TO 260 >*/
#line 36 "../fortran/drotmg.f"
    goto L260;
/*     REGULAR-CASE.. */
/*<    20 CONTINUE >*/
#line 38 "../fortran/drotmg.f"
L20:
/*<       DP1=DD1*DX1 >*/
#line 39 "../fortran/drotmg.f"
    dp1 = *dd1 * *dx1;
/*<       DQ2=DP2*DY1 >*/
#line 40 "../fortran/drotmg.f"
    dq2 = dp2 * *dy1;
/*<       DQ1=DP1*DX1 >*/
#line 41 "../fortran/drotmg.f"
    dq1 = dp1 * *dx1;

/*<       IF(.NOT. DABS(DQ1) .GT. DABS(DQ2)) GO TO 40 >*/
#line 43 "../fortran/drotmg.f"
    if (! (abs(dq1) > abs(dq2))) {
#line 43 "../fortran/drotmg.f"
	goto L40;
#line 43 "../fortran/drotmg.f"
    }
/*<           DH21=-DY1/DX1 >*/
#line 44 "../fortran/drotmg.f"
    dh21 = -(*dy1) / *dx1;
/*<           DH12=DP2/DP1 >*/
#line 45 "../fortran/drotmg.f"
    dh12 = dp2 / dp1;

/*<           DU=ONE-DH12*DH21 >*/
#line 47 "../fortran/drotmg.f"
    du = one - dh12 * dh21;

/*<           IF(.NOT. DU .LE. ZERO) GO TO 30 >*/
#line 49 "../fortran/drotmg.f"
    if (! (du <= zero)) {
#line 49 "../fortran/drotmg.f"
	goto L30;
#line 49 "../fortran/drotmg.f"
    }
/*         GO ZERO-H-D-AND-DX1.. */
/*<                GO TO 60 >*/
#line 51 "../fortran/drotmg.f"
    goto L60;
/*<    30     CONTINUE >*/
#line 52 "../fortran/drotmg.f"
L30:
/*<                DFLAG=ZERO >*/
#line 53 "../fortran/drotmg.f"
    dflag = zero;
/*<                DD1=DD1/DU >*/
#line 54 "../fortran/drotmg.f"
    *dd1 /= du;
/*<                DD2=DD2/DU >*/
#line 55 "../fortran/drotmg.f"
    *dd2 /= du;
/*<                DX1=DX1*DU >*/
#line 56 "../fortran/drotmg.f"
    *dx1 *= du;
/*         GO SCALE-CHECK.. */
/*<                GO TO 100 >*/
#line 58 "../fortran/drotmg.f"
    goto L100;
/*<    40 CONTINUE >*/
#line 59 "../fortran/drotmg.f"
L40:
/*<           IF(.NOT. DQ2 .LT. ZERO) GO TO 50 >*/
#line 60 "../fortran/drotmg.f"
    if (! (dq2 < zero)) {
#line 60 "../fortran/drotmg.f"
	goto L50;
#line 60 "../fortran/drotmg.f"
    }
/*         GO ZERO-H-D-AND-DX1.. */
/*<                GO TO 60 >*/
#line 62 "../fortran/drotmg.f"
    goto L60;
/*<    50     CONTINUE >*/
#line 63 "../fortran/drotmg.f"
L50:
/*<                DFLAG=ONE >*/
#line 64 "../fortran/drotmg.f"
    dflag = one;
/*<                DH11=DP1/DP2 >*/
#line 65 "../fortran/drotmg.f"
    dh11 = dp1 / dp2;
/*<                DH22=DX1/DY1 >*/
#line 66 "../fortran/drotmg.f"
    dh22 = *dx1 / *dy1;
/*<                DU=ONE+DH11*DH22 >*/
#line 67 "../fortran/drotmg.f"
    du = one + dh11 * dh22;
/*<                DTEMP=DD2/DU >*/
#line 68 "../fortran/drotmg.f"
    dtemp = *dd2 / du;
/*<                DD2=DD1/DU >*/
#line 69 "../fortran/drotmg.f"
    *dd2 = *dd1 / du;
/*<                DD1=DTEMP >*/
#line 70 "../fortran/drotmg.f"
    *dd1 = dtemp;
/*<                DX1=DY1*DU >*/
#line 71 "../fortran/drotmg.f"
    *dx1 = *dy1 * du;
/*         GO SCALE-CHECK */
/*<                GO TO 100 >*/
#line 73 "../fortran/drotmg.f"
    goto L100;
/*     PROCEDURE..ZERO-H-D-AND-DX1.. */
/*<    60 CONTINUE >*/
#line 75 "../fortran/drotmg.f"
L60:
/*<           DFLAG=-ONE >*/
#line 76 "../fortran/drotmg.f"
    dflag = -one;
/*<           DH11=ZERO >*/
#line 77 "../fortran/drotmg.f"
    dh11 = zero;
/*<           DH12=ZERO >*/
#line 78 "../fortran/drotmg.f"
    dh12 = zero;
/*<           DH21=ZERO >*/
#line 79 "../fortran/drotmg.f"
    dh21 = zero;
/*<           DH22=ZERO >*/
#line 80 "../fortran/drotmg.f"
    dh22 = zero;

/*<           DD1=ZERO >*/
#line 82 "../fortran/drotmg.f"
    *dd1 = zero;
/*<           DD2=ZERO >*/
#line 83 "../fortran/drotmg.f"
    *dd2 = zero;
/*<           DX1=ZERO >*/
#line 84 "../fortran/drotmg.f"
    *dx1 = zero;
/*         RETURN.. */
/*<           GO TO 220 >*/
#line 86 "../fortran/drotmg.f"
    goto L220;
/*     PROCEDURE..FIX-H.. */
/*<    70 CONTINUE >*/
#line 88 "../fortran/drotmg.f"
L70:
/*<       IF(.NOT. DFLAG .GE. ZERO) GO TO 90 >*/
#line 89 "../fortran/drotmg.f"
    if (! (dflag >= zero)) {
#line 89 "../fortran/drotmg.f"
	goto L90;
#line 89 "../fortran/drotmg.f"
    }

/*<           IF(.NOT. DFLAG .EQ. ZERO) GO TO 80 >*/
#line 91 "../fortran/drotmg.f"
    if (! (dflag == zero)) {
#line 91 "../fortran/drotmg.f"
	goto L80;
#line 91 "../fortran/drotmg.f"
    }
/*<           DH11=ONE >*/
#line 92 "../fortran/drotmg.f"
    dh11 = one;
/*<           DH22=ONE >*/
#line 93 "../fortran/drotmg.f"
    dh22 = one;
/*<           DFLAG=-ONE >*/
#line 94 "../fortran/drotmg.f"
    dflag = -one;
/*<           GO TO 90 >*/
#line 95 "../fortran/drotmg.f"
    goto L90;
/*<    80     CONTINUE >*/
#line 96 "../fortran/drotmg.f"
L80:
/*<           DH21=-ONE >*/
#line 97 "../fortran/drotmg.f"
    dh21 = -one;
/*<           DH12=ONE >*/
#line 98 "../fortran/drotmg.f"
    dh12 = one;
/*<           DFLAG=-ONE >*/
#line 99 "../fortran/drotmg.f"
    dflag = -one;
/*<    90 CONTINUE >*/
#line 100 "../fortran/drotmg.f"
L90:
/*<       GO TO IGO,(120,150,180,210) >*/
#line 101 "../fortran/drotmg.f"
    switch (igo) {
#line 101 "../fortran/drotmg.f"
	case 0: goto L120;
#line 101 "../fortran/drotmg.f"
	case 1: goto L150;
#line 101 "../fortran/drotmg.f"
	case 2: goto L180;
#line 101 "../fortran/drotmg.f"
	case 3: goto L210;
#line 101 "../fortran/drotmg.f"
    }
/*     PROCEDURE..SCALE-CHECK */
/*<   100 CONTINUE >*/
#line 103 "../fortran/drotmg.f"
L100:
/*<   110     CONTINUE >*/
#line 104 "../fortran/drotmg.f"
L110:
/*<           IF(.NOT. DD1 .LE. RGAMSQ) GO TO 130 >*/
#line 105 "../fortran/drotmg.f"
    if (! (*dd1 <= rgamsq)) {
#line 105 "../fortran/drotmg.f"
	goto L130;
#line 105 "../fortran/drotmg.f"
    }
/*<                IF(DD1 .EQ. ZERO) GO TO 160 >*/
#line 106 "../fortran/drotmg.f"
    if (*dd1 == zero) {
#line 106 "../fortran/drotmg.f"
	goto L160;
#line 106 "../fortran/drotmg.f"
    }
/*<                ASSIGN 120 TO IGO >*/
#line 107 "../fortran/drotmg.f"
    igo = 0;
#line 107 "../fortran/drotmg.f"
    igo_fmt = fmt_120;
/*              FIX-H.. */
/*<                GO TO 70 >*/
#line 109 "../fortran/drotmg.f"
    goto L70;
/*<   120          CONTINUE >*/
#line 110 "../fortran/drotmg.f"
L120:
/*<                DD1=DD1*GAM**2 >*/
/* Computing 2nd power */
#line 111 "../fortran/drotmg.f"
    d__1 = gam;
#line 111 "../fortran/drotmg.f"
    *dd1 *= d__1 * d__1;
/*<                DX1=DX1/GAM >*/
#line 112 "../fortran/drotmg.f"
    *dx1 /= gam;
/*<                DH11=DH11/GAM >*/
#line 113 "../fortran/drotmg.f"
    dh11 /= gam;
/*<                DH12=DH12/GAM >*/
#line 114 "../fortran/drotmg.f"
    dh12 /= gam;
/*<           GO TO 110 >*/
#line 115 "../fortran/drotmg.f"
    goto L110;
/*<   130 CONTINUE >*/
#line 116 "../fortran/drotmg.f"
L130:
/*<   140     CONTINUE >*/
#line 117 "../fortran/drotmg.f"
L140:
/*<           IF(.NOT. DD1 .GE. GAMSQ) GO TO 160 >*/
#line 118 "../fortran/drotmg.f"
    if (! (*dd1 >= gamsq)) {
#line 118 "../fortran/drotmg.f"
	goto L160;
#line 118 "../fortran/drotmg.f"
    }
/*<                ASSIGN 150 TO IGO >*/
#line 119 "../fortran/drotmg.f"
    igo = 1;
#line 119 "../fortran/drotmg.f"
    igo_fmt = fmt_150;
/*              FIX-H.. */
/*<                GO TO 70 >*/
#line 121 "../fortran/drotmg.f"
    goto L70;
/*<   150          CONTINUE >*/
#line 122 "../fortran/drotmg.f"
L150:
/*<                DD1=DD1/GAM**2 >*/
/* Computing 2nd power */
#line 123 "../fortran/drotmg.f"
    d__1 = gam;
#line 123 "../fortran/drotmg.f"
    *dd1 /= d__1 * d__1;
/*<                DX1=DX1*GAM >*/
#line 124 "../fortran/drotmg.f"
    *dx1 *= gam;
/*<                DH11=DH11*GAM >*/
#line 125 "../fortran/drotmg.f"
    dh11 *= gam;
/*<                DH12=DH12*GAM >*/
#line 126 "../fortran/drotmg.f"
    dh12 *= gam;
/*<           GO TO 140 >*/
#line 127 "../fortran/drotmg.f"
    goto L140;
/*<   160 CONTINUE >*/
#line 128 "../fortran/drotmg.f"
L160:
/*<   170     CONTINUE >*/
#line 129 "../fortran/drotmg.f"
L170:
/*<           IF(.NOT. DABS(DD2) .LE. RGAMSQ) GO TO 190 >*/
#line 130 "../fortran/drotmg.f"
    if (! (abs(*dd2) <= rgamsq)) {
#line 130 "../fortran/drotmg.f"
	goto L190;
#line 130 "../fortran/drotmg.f"
    }
/*<                IF(DD2 .EQ. ZERO) GO TO 220 >*/
#line 131 "../fortran/drotmg.f"
    if (*dd2 == zero) {
#line 131 "../fortran/drotmg.f"
	goto L220;
#line 131 "../fortran/drotmg.f"
    }
/*<                ASSIGN 180 TO IGO >*/
#line 132 "../fortran/drotmg.f"
    igo = 2;
#line 132 "../fortran/drotmg.f"
    igo_fmt = fmt_180;
/*              FIX-H.. */
/*<                GO TO 70 >*/
#line 134 "../fortran/drotmg.f"
    goto L70;
/*<   180          CONTINUE >*/
#line 135 "../fortran/drotmg.f"
L180:
/*<                DD2=DD2*GAM**2 >*/
/* Computing 2nd power */
#line 136 "../fortran/drotmg.f"
    d__1 = gam;
#line 136 "../fortran/drotmg.f"
    *dd2 *= d__1 * d__1;
/*<                DH21=DH21/GAM >*/
#line 137 "../fortran/drotmg.f"
    dh21 /= gam;
/*<                DH22=DH22/GAM >*/
#line 138 "../fortran/drotmg.f"
    dh22 /= gam;
/*<           GO TO 170 >*/
#line 139 "../fortran/drotmg.f"
    goto L170;
/*<   190 CONTINUE >*/
#line 140 "../fortran/drotmg.f"
L190:
/*<   200     CONTINUE >*/
#line 141 "../fortran/drotmg.f"
L200:
/*<           IF(.NOT. DABS(DD2) .GE. GAMSQ) GO TO 220 >*/
#line 142 "../fortran/drotmg.f"
    if (! (abs(*dd2) >= gamsq)) {
#line 142 "../fortran/drotmg.f"
	goto L220;
#line 142 "../fortran/drotmg.f"
    }
/*<                ASSIGN 210 TO IGO >*/
#line 143 "../fortran/drotmg.f"
    igo = 3;
#line 143 "../fortran/drotmg.f"
    igo_fmt = fmt_210;
/*              FIX-H.. */
/*<                GO TO 70 >*/
#line 145 "../fortran/drotmg.f"
    goto L70;
/*<   210          CONTINUE >*/
#line 146 "../fortran/drotmg.f"
L210:
/*<                DD2=DD2/GAM**2 >*/
/* Computing 2nd power */
#line 147 "../fortran/drotmg.f"
    d__1 = gam;
#line 147 "../fortran/drotmg.f"
    *dd2 /= d__1 * d__1;
/*<                DH21=DH21*GAM >*/
#line 148 "../fortran/drotmg.f"
    dh21 *= gam;
/*<                DH22=DH22*GAM >*/
#line 149 "../fortran/drotmg.f"
    dh22 *= gam;
/*<           GO TO 200 >*/
#line 150 "../fortran/drotmg.f"
    goto L200;
/*<   220 CONTINUE >*/
#line 151 "../fortran/drotmg.f"
L220:
/*<           IF(DFLAG)250,230,240 >*/
#line 152 "../fortran/drotmg.f"
    if (dflag < 0.) {
#line 152 "../fortran/drotmg.f"
	goto L250;
#line 152 "../fortran/drotmg.f"
    } else if (dflag == 0) {
#line 152 "../fortran/drotmg.f"
	goto L230;
#line 152 "../fortran/drotmg.f"
    } else {
#line 152 "../fortran/drotmg.f"
	goto L240;
#line 152 "../fortran/drotmg.f"
    }
/*<   230     CONTINUE >*/
#line 153 "../fortran/drotmg.f"
L230:
/*<                DPARAM(3)=DH21 >*/
#line 154 "../fortran/drotmg.f"
    dparam[3] = dh21;
/*<                DPARAM(4)=DH12 >*/
#line 155 "../fortran/drotmg.f"
    dparam[4] = dh12;
/*<                GO TO 260 >*/
#line 156 "../fortran/drotmg.f"
    goto L260;
/*<   240     CONTINUE >*/
#line 157 "../fortran/drotmg.f"
L240:
/*<                DPARAM(2)=DH11 >*/
#line 158 "../fortran/drotmg.f"
    dparam[2] = dh11;
/*<                DPARAM(5)=DH22 >*/
#line 159 "../fortran/drotmg.f"
    dparam[5] = dh22;
/*<                GO TO 260 >*/
#line 160 "../fortran/drotmg.f"
    goto L260;
/*<   250     CONTINUE >*/
#line 161 "../fortran/drotmg.f"
L250:
/*<                DPARAM(2)=DH11 >*/
#line 162 "../fortran/drotmg.f"
    dparam[2] = dh11;
/*<                DPARAM(3)=DH21 >*/
#line 163 "../fortran/drotmg.f"
    dparam[3] = dh21;
/*<                DPARAM(4)=DH12 >*/
#line 164 "../fortran/drotmg.f"
    dparam[4] = dh12;
/*<                DPARAM(5)=DH22 >*/
#line 165 "../fortran/drotmg.f"
    dparam[5] = dh22;
/*<   260 CONTINUE >*/
#line 166 "../fortran/drotmg.f"
L260:
/*<           DPARAM(1)=DFLAG >*/
#line 167 "../fortran/drotmg.f"
    dparam[1] = dflag;
/*<           RETURN >*/
#line 168 "../fortran/drotmg.f"
    return 0;
/*<       END >*/
} /* drotmg_ */

