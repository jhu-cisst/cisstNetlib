#line 1 "g1.f"
/* g1.f -- translated by f2c (version 20100827).
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

#line 1 "g1.f"
/*<       SUBROUTINE G1 (A,B,CTERM,STERM,SIG)    >*/
/* Subroutine */ int g1_(doublereal *a, doublereal *b, doublereal *cterm, 
	doublereal *sterm, doublereal *sig)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal), d_sign(doublereal *, doublereal *);

    /* Local variables */
    doublereal xr, yr;


/*     COMPUTE ORTHOGONAL ROTATION MATRIX.. */

/*  The original version of this code was developed by */
/*  Charles L. Lawson and Richard J. Hanson at Jet Propulsion Laboratory */
/*  1973 JUN 12, and published in the book */
/*  "SOLVING LEAST SQUARES PROBLEMS", Prentice-HalL, 1974. */
/*  Revised FEB 1995 to accompany reprinting of the book by SIAM. */

/*     COMPUTE.. MATRIX   (C, S) SO THAT (C, S)(A) = (SQRT(A**2+B**2)) */
/*                        (-S,C)         (-S,C)(B)   (   0          ) */
/*     COMPUTE SIG = SQRT(A**2+B**2) */
/*        SIG IS COMPUTED LAST TO ALLOW FOR THE POSSIBILITY THAT */
/*        SIG MAY BE IN THE SAME LOCATION AS A OR B . */
/*     ------------------------------------------------------------------ */
/*<       double precision A, B, CTERM, ONE, SIG, STERM, XR, YR, ZERO >*/
/*<       parameter(ONE = 1.0d0, ZERO = 0.0d0) >*/
/*     ------------------------------------------------------------------ */
/*<       if (abs(A) .gt. abs(B)) then >*/
#line 20 "g1.f"
    if (abs(*a) > abs(*b)) {
/*<          XR=B/A >*/
#line 21 "g1.f"
	xr = *b / *a;
/*<          YR=sqrt(ONE+XR**2) >*/
/* Computing 2nd power */
#line 22 "g1.f"
	d__1 = xr;
#line 22 "g1.f"
	yr = sqrt(d__1 * d__1 + 1.);
/*<          CTERM=sign(ONE/YR,A) >*/
#line 23 "g1.f"
	d__1 = 1. / yr;
#line 23 "g1.f"
	*cterm = d_sign(&d__1, a);
/*<          STERM=CTERM*XR >*/
#line 24 "g1.f"
	*sterm = *cterm * xr;
/*<          SIG=abs(A)*YR      >*/
#line 25 "g1.f"
	*sig = abs(*a) * yr;
/*<          RETURN >*/
#line 26 "g1.f"
	return 0;
/*<       endif >*/
#line 27 "g1.f"
    }
/*<       if (B .ne. ZERO) then >*/
#line 29 "g1.f"
    if (*b != 0.) {
/*<          XR=A/B >*/
#line 30 "g1.f"
	xr = *a / *b;
/*<          YR=sqrt(ONE+XR**2) >*/
/* Computing 2nd power */
#line 31 "g1.f"
	d__1 = xr;
#line 31 "g1.f"
	yr = sqrt(d__1 * d__1 + 1.);
/*<          STERM=sign(ONE/YR,B) >*/
#line 32 "g1.f"
	d__1 = 1. / yr;
#line 32 "g1.f"
	*sterm = d_sign(&d__1, b);
/*<          CTERM=STERM*XR >*/
#line 33 "g1.f"
	*cterm = *sterm * xr;
/*<          SIG=abs(B)*YR      >*/
#line 34 "g1.f"
	*sig = abs(*b) * yr;
/*<          RETURN >*/
#line 35 "g1.f"
	return 0;
/*<       endif >*/
#line 36 "g1.f"
    }
/*<       SIG=ZERO   >*/
#line 38 "g1.f"
    *sig = 0.;
/*<       CTERM=ZERO   >*/
#line 39 "g1.f"
    *cterm = 0.;
/*<       STERM=ONE    >*/
#line 40 "g1.f"
    *sterm = 1.;
/*<       RETURN >*/
#line 41 "g1.f"
    return 0;
/*<       END    >*/
} /* g1_ */

