#line 1 "../fortran/drotm.f"
/* ../fortran/drotm.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/drotm.f"
/*<       SUBROUTINE DROTM (N,DX,INCX,DY,INCY,DPARAM) >*/
/* Subroutine */ int drotm_(integer *n, doublereal *dx, integer *incx, 
	doublereal *dy, integer *incy, doublereal *dparam)
{
    /* Initialized data */

    static doublereal zero = 0.;
    static doublereal two = 2.;

    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    integer i__;
    doublereal w, z__;
    integer kx, ky;
    doublereal dh11, dh12, dh22, dh21, dflag;
    integer nsteps;


/*     APPLY THE MODIFIED GIVENS TRANSFORMATION, H, TO THE 2 BY N MATRIX */

/*     (DX**T) , WHERE **T INDICATES TRANSPOSE. THE ELEMENTS OF DX ARE IN */
/*     (DY**T) */

/*     DX(LX+I*INCX), I = 0 TO N-1, WHERE LX = 1 IF INCX .GE. 0, ELSE */
/*     LX = (-INCX)*N, AND SIMILARLY FOR SY USING LY AND INCY. */
/*     WITH DPARAM(1)=DFLAG, H HAS ONE OF THE FOLLOWING FORMS.. */

/*     DFLAG=-1.D0     DFLAG=0.D0        DFLAG=1.D0     DFLAG=-2.D0 */

/*       (DH11  DH12)    (1.D0  DH12)    (DH11  1.D0)    (1.D0  0.D0) */
/*     H=(          )    (          )    (          )    (          ) */
/*       (DH21  DH22),   (DH21  1.D0),   (-1.D0 DH22),   (0.D0  1.D0). */
/*     SEE DROTMG FOR A DESCRIPTION OF DATA STORAGE IN DPARAM. */

/*<        >*/
/*<       DIMENSION DX(1),DY(1),DPARAM(5) >*/
/*<       DATA ZERO,TWO/0.D0,2.D0/ >*/
#line 22 "../fortran/drotm.f"
    /* Parameter adjustments */
#line 22 "../fortran/drotm.f"
    --dparam;
#line 22 "../fortran/drotm.f"
    --dy;
#line 22 "../fortran/drotm.f"
    --dx;
#line 22 "../fortran/drotm.f"

#line 22 "../fortran/drotm.f"
    /* Function Body */

/*<       DFLAG=DPARAM(1) >*/
#line 24 "../fortran/drotm.f"
    dflag = dparam[1];
/*<       IF(N .LE. 0 .OR.(DFLAG+TWO.EQ.ZERO)) GO TO 140 >*/
#line 25 "../fortran/drotm.f"
    if (*n <= 0 || dflag + two == zero) {
#line 25 "../fortran/drotm.f"
	goto L140;
#line 25 "../fortran/drotm.f"
    }
/*<           IF(.NOT.(INCX.EQ.INCY.AND. INCX .GT.0)) GO TO 70 >*/
#line 26 "../fortran/drotm.f"
    if (! (*incx == *incy && *incx > 0)) {
#line 26 "../fortran/drotm.f"
	goto L70;
#line 26 "../fortran/drotm.f"
    }

/*<                NSTEPS=N*INCX >*/
#line 28 "../fortran/drotm.f"
    nsteps = *n * *incx;
/*<                IF(DFLAG) 50,10,30 >*/
#line 29 "../fortran/drotm.f"
    if (dflag < 0.) {
#line 29 "../fortran/drotm.f"
	goto L50;
#line 29 "../fortran/drotm.f"
    } else if (dflag == 0) {
#line 29 "../fortran/drotm.f"
	goto L10;
#line 29 "../fortran/drotm.f"
    } else {
#line 29 "../fortran/drotm.f"
	goto L30;
#line 29 "../fortran/drotm.f"
    }
/*<    10          CONTINUE >*/
#line 30 "../fortran/drotm.f"
L10:
/*<                DH12=DPARAM(4) >*/
#line 31 "../fortran/drotm.f"
    dh12 = dparam[4];
/*<                DH21=DPARAM(3) >*/
#line 32 "../fortran/drotm.f"
    dh21 = dparam[3];
/*<                     DO 20 I=1,NSTEPS,INCX >*/
#line 33 "../fortran/drotm.f"
    i__1 = nsteps;
#line 33 "../fortran/drotm.f"
    i__2 = *incx;
#line 33 "../fortran/drotm.f"
    for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
/*<                     W=DX(I) >*/
#line 34 "../fortran/drotm.f"
	w = dx[i__];
/*<                     Z=DY(I) >*/
#line 35 "../fortran/drotm.f"
	z__ = dy[i__];
/*<                     DX(I)=W+Z*DH12 >*/
#line 36 "../fortran/drotm.f"
	dx[i__] = w + z__ * dh12;
/*<                     DY(I)=W*DH21+Z >*/
#line 37 "../fortran/drotm.f"
	dy[i__] = w * dh21 + z__;
/*<    20               CONTINUE >*/
#line 38 "../fortran/drotm.f"
/* L20: */
#line 38 "../fortran/drotm.f"
    }
/*<                GO TO 140 >*/
#line 39 "../fortran/drotm.f"
    goto L140;
/*<    30          CONTINUE >*/
#line 40 "../fortran/drotm.f"
L30:
/*<                DH11=DPARAM(2) >*/
#line 41 "../fortran/drotm.f"
    dh11 = dparam[2];
/*<                DH22=DPARAM(5) >*/
#line 42 "../fortran/drotm.f"
    dh22 = dparam[5];
/*<                     DO 40 I=1,NSTEPS,INCX >*/
#line 43 "../fortran/drotm.f"
    i__2 = nsteps;
#line 43 "../fortran/drotm.f"
    i__1 = *incx;
#line 43 "../fortran/drotm.f"
    for (i__ = 1; i__1 < 0 ? i__ >= i__2 : i__ <= i__2; i__ += i__1) {
/*<                     W=DX(I) >*/
#line 44 "../fortran/drotm.f"
	w = dx[i__];
/*<                     Z=DY(I) >*/
#line 45 "../fortran/drotm.f"
	z__ = dy[i__];
/*<                     DX(I)=W*DH11+Z >*/
#line 46 "../fortran/drotm.f"
	dx[i__] = w * dh11 + z__;
/*<                     DY(I)=-W+DH22*Z >*/
#line 47 "../fortran/drotm.f"
	dy[i__] = -w + dh22 * z__;
/*<    40               CONTINUE >*/
#line 48 "../fortran/drotm.f"
/* L40: */
#line 48 "../fortran/drotm.f"
    }
/*<                GO TO 140 >*/
#line 49 "../fortran/drotm.f"
    goto L140;
/*<    50          CONTINUE >*/
#line 50 "../fortran/drotm.f"
L50:
/*<                DH11=DPARAM(2) >*/
#line 51 "../fortran/drotm.f"
    dh11 = dparam[2];
/*<                DH12=DPARAM(4) >*/
#line 52 "../fortran/drotm.f"
    dh12 = dparam[4];
/*<                DH21=DPARAM(3) >*/
#line 53 "../fortran/drotm.f"
    dh21 = dparam[3];
/*<                DH22=DPARAM(5) >*/
#line 54 "../fortran/drotm.f"
    dh22 = dparam[5];
/*<                     DO 60 I=1,NSTEPS,INCX >*/
#line 55 "../fortran/drotm.f"
    i__1 = nsteps;
#line 55 "../fortran/drotm.f"
    i__2 = *incx;
#line 55 "../fortran/drotm.f"
    for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
/*<                     W=DX(I) >*/
#line 56 "../fortran/drotm.f"
	w = dx[i__];
/*<                     Z=DY(I) >*/
#line 57 "../fortran/drotm.f"
	z__ = dy[i__];
/*<                     DX(I)=W*DH11+Z*DH12 >*/
#line 58 "../fortran/drotm.f"
	dx[i__] = w * dh11 + z__ * dh12;
/*<                     DY(I)=W*DH21+Z*DH22 >*/
#line 59 "../fortran/drotm.f"
	dy[i__] = w * dh21 + z__ * dh22;
/*<    60               CONTINUE >*/
#line 60 "../fortran/drotm.f"
/* L60: */
#line 60 "../fortran/drotm.f"
    }
/*<                GO TO 140 >*/
#line 61 "../fortran/drotm.f"
    goto L140;
/*<    70     CONTINUE >*/
#line 62 "../fortran/drotm.f"
L70:
/*<           KX=1 >*/
#line 63 "../fortran/drotm.f"
    kx = 1;
/*<           KY=1 >*/
#line 64 "../fortran/drotm.f"
    ky = 1;
/*<           IF(INCX .LT. 0) KX=1+(1-N)*INCX >*/
#line 65 "../fortran/drotm.f"
    if (*incx < 0) {
#line 65 "../fortran/drotm.f"
	kx = (1 - *n) * *incx + 1;
#line 65 "../fortran/drotm.f"
    }
/*<           IF(INCY .LT. 0) KY=1+(1-N)*INCY >*/
#line 66 "../fortran/drotm.f"
    if (*incy < 0) {
#line 66 "../fortran/drotm.f"
	ky = (1 - *n) * *incy + 1;
#line 66 "../fortran/drotm.f"
    }

/*<           IF(DFLAG)120,80,100 >*/
#line 68 "../fortran/drotm.f"
    if (dflag < 0.) {
#line 68 "../fortran/drotm.f"
	goto L120;
#line 68 "../fortran/drotm.f"
    } else if (dflag == 0) {
#line 68 "../fortran/drotm.f"
	goto L80;
#line 68 "../fortran/drotm.f"
    } else {
#line 68 "../fortran/drotm.f"
	goto L100;
#line 68 "../fortran/drotm.f"
    }
/*<    80     CONTINUE >*/
#line 69 "../fortran/drotm.f"
L80:
/*<           DH12=DPARAM(4) >*/
#line 70 "../fortran/drotm.f"
    dh12 = dparam[4];
/*<           DH21=DPARAM(3) >*/
#line 71 "../fortran/drotm.f"
    dh21 = dparam[3];
/*<                DO 90 I=1,N >*/
#line 72 "../fortran/drotm.f"
    i__2 = *n;
#line 72 "../fortran/drotm.f"
    for (i__ = 1; i__ <= i__2; ++i__) {
/*<                W=DX(KX) >*/
#line 73 "../fortran/drotm.f"
	w = dx[kx];
/*<                Z=DY(KY) >*/
#line 74 "../fortran/drotm.f"
	z__ = dy[ky];
/*<                DX(KX)=W+Z*DH12 >*/
#line 75 "../fortran/drotm.f"
	dx[kx] = w + z__ * dh12;
/*<                DY(KY)=W*DH21+Z >*/
#line 76 "../fortran/drotm.f"
	dy[ky] = w * dh21 + z__;
/*<                KX=KX+INCX >*/
#line 77 "../fortran/drotm.f"
	kx += *incx;
/*<                KY=KY+INCY >*/
#line 78 "../fortran/drotm.f"
	ky += *incy;
/*<    90          CONTINUE >*/
#line 79 "../fortran/drotm.f"
/* L90: */
#line 79 "../fortran/drotm.f"
    }
/*<           GO TO 140 >*/
#line 80 "../fortran/drotm.f"
    goto L140;
/*<   100     CONTINUE >*/
#line 81 "../fortran/drotm.f"
L100:
/*<           DH11=DPARAM(2) >*/
#line 82 "../fortran/drotm.f"
    dh11 = dparam[2];
/*<           DH22=DPARAM(5) >*/
#line 83 "../fortran/drotm.f"
    dh22 = dparam[5];
/*<                DO 110 I=1,N >*/
#line 84 "../fortran/drotm.f"
    i__2 = *n;
#line 84 "../fortran/drotm.f"
    for (i__ = 1; i__ <= i__2; ++i__) {
/*<                W=DX(KX) >*/
#line 85 "../fortran/drotm.f"
	w = dx[kx];
/*<                Z=DY(KY) >*/
#line 86 "../fortran/drotm.f"
	z__ = dy[ky];
/*<                DX(KX)=W*DH11+Z >*/
#line 87 "../fortran/drotm.f"
	dx[kx] = w * dh11 + z__;
/*<                DY(KY)=-W+DH22*Z >*/
#line 88 "../fortran/drotm.f"
	dy[ky] = -w + dh22 * z__;
/*<                KX=KX+INCX >*/
#line 89 "../fortran/drotm.f"
	kx += *incx;
/*<                KY=KY+INCY >*/
#line 90 "../fortran/drotm.f"
	ky += *incy;
/*<   110          CONTINUE >*/
#line 91 "../fortran/drotm.f"
/* L110: */
#line 91 "../fortran/drotm.f"
    }
/*<           GO TO 140 >*/
#line 92 "../fortran/drotm.f"
    goto L140;
/*<   120     CONTINUE >*/
#line 93 "../fortran/drotm.f"
L120:
/*<           DH11=DPARAM(2) >*/
#line 94 "../fortran/drotm.f"
    dh11 = dparam[2];
/*<           DH12=DPARAM(4) >*/
#line 95 "../fortran/drotm.f"
    dh12 = dparam[4];
/*<           DH21=DPARAM(3) >*/
#line 96 "../fortran/drotm.f"
    dh21 = dparam[3];
/*<           DH22=DPARAM(5) >*/
#line 97 "../fortran/drotm.f"
    dh22 = dparam[5];
/*<                DO 130 I=1,N >*/
#line 98 "../fortran/drotm.f"
    i__2 = *n;
#line 98 "../fortran/drotm.f"
    for (i__ = 1; i__ <= i__2; ++i__) {
/*<                W=DX(KX) >*/
#line 99 "../fortran/drotm.f"
	w = dx[kx];
/*<                Z=DY(KY) >*/
#line 100 "../fortran/drotm.f"
	z__ = dy[ky];
/*<                DX(KX)=W*DH11+Z*DH12 >*/
#line 101 "../fortran/drotm.f"
	dx[kx] = w * dh11 + z__ * dh12;
/*<                DY(KY)=W*DH21+Z*DH22 >*/
#line 102 "../fortran/drotm.f"
	dy[ky] = w * dh21 + z__ * dh22;
/*<                KX=KX+INCX >*/
#line 103 "../fortran/drotm.f"
	kx += *incx;
/*<                KY=KY+INCY >*/
#line 104 "../fortran/drotm.f"
	ky += *incy;
/*<   130          CONTINUE >*/
#line 105 "../fortran/drotm.f"
/* L130: */
#line 105 "../fortran/drotm.f"
    }
/*<   140     CONTINUE >*/
#line 106 "../fortran/drotm.f"
L140:
/*<           RETURN >*/
#line 107 "../fortran/drotm.f"
    return 0;
/*<           END >*/
} /* drotm_ */

