#line 1 "h12.f"
/* h12.f -- translated by f2c (version 20100827).
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

#line 1 "h12.f"
/*      SUBROUTINE H12 (MODE,LPIVOT,L1,M,U,IUE,UP,C,ICE,ICV,NCV) */

/*  CONSTRUCTION AND/OR APPLICATION OF A SINGLE */
/*  HOUSEHOLDER TRANSFORMATION..     Q = I + U*(U**T)/B */

/*  The original version of this code was developed by */
/*  Charles L. Lawson and Richard J. Hanson at Jet Propulsion Laboratory */
/*  1973 JUN 12, and published in the book */
/*  "SOLVING LEAST SQUARES PROBLEMS", Prentice-HalL, 1974. */
/*  Revised FEB 1995 to accompany reprinting of the book by SIAM. */
/*     ------------------------------------------------------------------ */
/*                     Subroutine Arguments */

/*     MODE   = 1 OR 2   Selects Algorithm H1 to construct and apply a */
/*            Householder transformation, or Algorithm H2 to apply a */
/*            previously constructed transformation. */
/*     LPIVOT IS THE INDEX OF THE PIVOT ELEMENT. */
/*     L1,M   IF L1 .LE. M   THE TRANSFORMATION WILL BE CONSTRUCTED TO */
/*            ZERO ELEMENTS INDEXED FROM L1 THROUGH M.   IF L1 GT. M */
/*            THE SUBROUTINE DOES AN IDENTITY TRANSFORMATION. */
/*     U(),IUE,UP    On entry with MODE = 1, U() contains the pivot */
/*            vector.  IUE is the storage increment between elements. */
/*            On exit when MODE = 1, U() and UP contain quantities */
/*            defining the vector U of the Householder transformation. */
/*            on entry with MODE = 2, U() and UP should contain */
/*            quantities previously computed with MODE = 1.  These will */
/*            not be modified during the entry with MODE = 2. */
/*     C()    ON ENTRY with MODE = 1 or 2, C() CONTAINS A MATRIX WHICH */
/*            WILL BE REGARDED AS A SET OF VECTORS TO WHICH THE */
/*            HOUSEHOLDER TRANSFORMATION IS TO BE APPLIED. */
/*            ON EXIT C() CONTAINS THE SET OF TRANSFORMED VECTORS. */
/*     ICE    STORAGE INCREMENT BETWEEN ELEMENTS OF VECTORS IN C(). */
/*     ICV    STORAGE INCREMENT BETWEEN VECTORS IN C(). */
/*     NCV    NUMBER OF VECTORS IN C() TO BE TRANSFORMED. IF NCV .LE. 0 */
/*            NO OPERATIONS WILL BE DONE ON C(). */
/*     ------------------------------------------------------------------ */
/*<       SUBROUTINE H12 (MODE,LPIVOT,L1,M,U,IUE,UP,C,ICE,ICV,NCV)   >*/
/* Subroutine */ int h12_(integer *mode, integer *lpivot, integer *l1, 
	integer *m, doublereal *u, integer *iue, doublereal *up, doublereal *
	c__, integer *ice, integer *icv, integer *ncv)
{
    /* System generated locals */
    integer u_dim1, u_offset, i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    doublereal b;
    integer i__, j, i2, i3, i4;
    doublereal cl, sm;
    integer incr;
    doublereal clinv;

/*     ------------------------------------------------------------------ */
/*<       integer I, I2, I3, I4, ICE, ICV, INCR, IUE, J >*/
/*<       integer L1, LPIVOT, M, MODE, NCV >*/
/*<       double precision B, C(*), CL, CLINV, ONE, SM >*/
/*     double precision U(IUE,M) */
/*<       double precision U(IUE,*) >*/
/*<       double precision UP >*/
/*<       parameter(ONE = 1.0d0) >*/
/*     ------------------------------------------------------------------ */
/*<       IF (0.GE.LPIVOT.OR.LPIVOT.GE.L1.OR.L1.GT.M) RETURN     >*/
#line 47 "h12.f"
    /* Parameter adjustments */
#line 47 "h12.f"
    u_dim1 = *iue;
#line 47 "h12.f"
    u_offset = 1 + u_dim1;
#line 47 "h12.f"
    u -= u_offset;
#line 47 "h12.f"
    --c__;
#line 47 "h12.f"

#line 47 "h12.f"
    /* Function Body */
#line 47 "h12.f"
    if (0 >= *lpivot || *lpivot >= *l1 || *l1 > *m) {
#line 47 "h12.f"
	return 0;
#line 47 "h12.f"
    }
/*<       CL=abs(U(1,LPIVOT))    >*/
#line 48 "h12.f"
    cl = (d__1 = u[*lpivot * u_dim1 + 1], abs(d__1));
/*<       IF (MODE.EQ.2) GO TO 60    >*/
#line 49 "h12.f"
    if (*mode == 2) {
#line 49 "h12.f"
	goto L60;
#line 49 "h12.f"
    }
/*                            ****** CONSTRUCT THE TRANSFORMATION. ****** */
/*<           DO 10 J=L1,M   >*/
#line 51 "h12.f"
    i__1 = *m;
#line 51 "h12.f"
    for (j = *l1; j <= i__1; ++j) {
/*<    10     CL=MAX(abs(U(1,J)),CL)   >*/
#line 52 "h12.f"
/* L10: */
/* Computing MAX */
#line 52 "h12.f"
	d__2 = (d__1 = u[j * u_dim1 + 1], abs(d__1));
#line 52 "h12.f"
	cl = max(d__2,cl);
#line 52 "h12.f"
    }
/*<       IF (CL) 130,130,20 >*/
#line 53 "h12.f"
    if (cl <= 0.) {
#line 53 "h12.f"
	goto L130;
#line 53 "h12.f"
    } else {
#line 53 "h12.f"
	goto L20;
#line 53 "h12.f"
    }
/*<    20 CLINV=ONE/CL   >*/
#line 54 "h12.f"
L20:
#line 54 "h12.f"
    clinv = 1. / cl;
/*<       SM=(U(1,LPIVOT)*CLINV)**2    >*/
/* Computing 2nd power */
#line 55 "h12.f"
    d__1 = u[*lpivot * u_dim1 + 1] * clinv;
#line 55 "h12.f"
    sm = d__1 * d__1;
/*<           DO 30 J=L1,M   >*/
#line 56 "h12.f"
    i__1 = *m;
#line 56 "h12.f"
    for (j = *l1; j <= i__1; ++j) {
/*<    30     SM=SM+(U(1,J)*CLINV)**2  >*/
#line 57 "h12.f"
/* L30: */
/* Computing 2nd power */
#line 57 "h12.f"
	d__1 = u[j * u_dim1 + 1] * clinv;
#line 57 "h12.f"
	sm += d__1 * d__1;
#line 57 "h12.f"
    }
/*<       CL=CL*SQRT(SM)    >*/
#line 58 "h12.f"
    cl *= sqrt(sm);
/*<       IF (U(1,LPIVOT)) 50,50,40      >*/
#line 59 "h12.f"
    if (u[*lpivot * u_dim1 + 1] <= 0.) {
#line 59 "h12.f"
	goto L50;
#line 59 "h12.f"
    } else {
#line 59 "h12.f"
	goto L40;
#line 59 "h12.f"
    }
/*<    40 CL=-CL >*/
#line 60 "h12.f"
L40:
#line 60 "h12.f"
    cl = -cl;
/*<    50 UP=U(1,LPIVOT)-CL  >*/
#line 61 "h12.f"
L50:
#line 61 "h12.f"
    *up = u[*lpivot * u_dim1 + 1] - cl;
/*<       U(1,LPIVOT)=CL     >*/
#line 62 "h12.f"
    u[*lpivot * u_dim1 + 1] = cl;
/*<       GO TO 70   >*/
#line 63 "h12.f"
    goto L70;
/*            ****** APPLY THE TRANSFORMATION  I+U*(U**T)/B  TO C. ****** */

/*<    60 IF (CL) 130,130,70 >*/
#line 66 "h12.f"
L60:
#line 66 "h12.f"
    if (cl <= 0.) {
#line 66 "h12.f"
	goto L130;
#line 66 "h12.f"
    } else {
#line 66 "h12.f"
	goto L70;
#line 66 "h12.f"
    }
/*<    70 IF (NCV.LE.0) RETURN   >*/
#line 67 "h12.f"
L70:
#line 67 "h12.f"
    if (*ncv <= 0) {
#line 67 "h12.f"
	return 0;
#line 67 "h12.f"
    }
/*<       B= UP*U(1,LPIVOT) >*/
#line 68 "h12.f"
    b = *up * u[*lpivot * u_dim1 + 1];
/*                       B  MUST BE NONPOSITIVE HERE.  IF B = 0., RETURN. */

/*<       IF (B) 80,130,130  >*/
#line 71 "h12.f"
    if (b >= 0.) {
#line 71 "h12.f"
	goto L130;
#line 71 "h12.f"
    } else {
#line 71 "h12.f"
	goto L80;
#line 71 "h12.f"
    }
/*<    80 B=ONE/B    >*/
#line 72 "h12.f"
L80:
#line 72 "h12.f"
    b = 1. / b;
/*<       I2=1-ICV+ICE*(LPIVOT-1)    >*/
#line 73 "h12.f"
    i2 = 1 - *icv + *ice * (*lpivot - 1);
/*<       INCR=ICE*(L1-LPIVOT)   >*/
#line 74 "h12.f"
    incr = *ice * (*l1 - *lpivot);
/*<           DO 120 J=1,NCV >*/
#line 75 "h12.f"
    i__1 = *ncv;
#line 75 "h12.f"
    for (j = 1; j <= i__1; ++j) {
/*<           I2=I2+ICV      >*/
#line 76 "h12.f"
	i2 += *icv;
/*<           I3=I2+INCR     >*/
#line 77 "h12.f"
	i3 = i2 + incr;
/*<           I4=I3  >*/
#line 78 "h12.f"
	i4 = i3;
/*<           SM=C(I2)*UP >*/
#line 79 "h12.f"
	sm = c__[i2] * *up;
/*<               DO 90 I=L1,M   >*/
#line 80 "h12.f"
	i__2 = *m;
#line 80 "h12.f"
	for (i__ = *l1; i__ <= i__2; ++i__) {
/*<               SM=SM+C(I3)*U(1,I) >*/
#line 81 "h12.f"
	    sm += c__[i3] * u[i__ * u_dim1 + 1];
/*<    90         I3=I3+ICE  >*/
#line 82 "h12.f"
/* L90: */
#line 82 "h12.f"
	    i3 += *ice;
#line 82 "h12.f"
	}
/*<           IF (SM) 100,120,100    >*/
#line 83 "h12.f"
	if (sm != 0.) {
#line 83 "h12.f"
	    goto L100;
#line 83 "h12.f"
	} else {
#line 83 "h12.f"
	    goto L120;
#line 83 "h12.f"
	}
/*<   100     SM=SM*B    >*/
#line 84 "h12.f"
L100:
#line 84 "h12.f"
	sm *= b;
/*<           C(I2)=C(I2)+SM*UP >*/
#line 85 "h12.f"
	c__[i2] += sm * *up;
/*<               DO 110 I=L1,M  >*/
#line 86 "h12.f"
	i__2 = *m;
#line 86 "h12.f"
	for (i__ = *l1; i__ <= i__2; ++i__) {
/*<               C(I4)=C(I4)+SM*U(1,I) >*/
#line 87 "h12.f"
	    c__[i4] += sm * u[i__ * u_dim1 + 1];
/*<   110         I4=I4+ICE  >*/
#line 88 "h12.f"
/* L110: */
#line 88 "h12.f"
	    i4 += *ice;
#line 88 "h12.f"
	}
/*<   120     CONTINUE   >*/
#line 89 "h12.f"
L120:
#line 89 "h12.f"
	;
#line 89 "h12.f"
    }
/*<   130 RETURN >*/
#line 90 "h12.f"
L130:
#line 90 "h12.f"
    return 0;
/*<       END    >*/
} /* h12_ */

