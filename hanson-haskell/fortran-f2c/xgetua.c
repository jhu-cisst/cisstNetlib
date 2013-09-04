#line 1 "../fortran/xgetua.f"
/* ../fortran/xgetua.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xgetua.f"
/* Table of constant values */

static integer c__5 = 5;
static integer c__0 = 0;
static logical c_false = FALSE_;

/*<       SUBROUTINE XGETUA(IUNIT,N)                                         >*/
/* Subroutine */ int xgetua_(integer *iunit, integer *n)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    integer i__, index;
    extern integer j4save_(integer *, integer *, logical *);


/*     ABSTRACT */
/*        XGETUA MAY BE CALLED TO DETERMINE THE UNIT NUMBER OR NUMBERS */
/*        TO WHICH ERROR MESSAGES ARE BEING SENT. */
/*        THESE UNIT NUMBERS MAY HAVE BEEN SET BY A CALL TO XSETUN, */
/*        OR A CALL TO XSETUA, OR MAY BE A DEFAULT VALUE. */

/*     DESCRIPTION OF PARAMETERS */
/*      --OUTPUT-- */
/*        IUNIT - AN ARRAY OF ONE TO FIVE UNIT NUMBERS, DEPENDING */
/*                ON THE VALUE OF N.  A VALUE OF ZERO REFERS TO THE */
/*                DEFAULT UNIT, AS DEFINED BY THE I1MACH MACHINE */
/*                CONSTANT ROUTINE.  ONLY IUNIT(1),...,IUNIT(N) ARE */
/*                DEFINED BY XGETUA.  THE VALUES OF IUNIT(N+1),..., */
/*                IUNIT(5) ARE NOT DEFINED (FOR N.LT.5) OR ALTERED */
/*                IN ANY WAY BY XGETUA. */
/*        N     - THE NUMBER OF UNITS TO WHICH COPIES OF THE */
/*                ERROR MESSAGES ARE BEING SENT.  N WILL BE IN THE */
/*                RANGE FROM 1 TO 5. */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/* END OF ABSTRACT */

/*<       DIMENSION IUNIT(5) >*/
/*<       N = J4SAVE(5,0,.FALSE.) >*/
#line 26 "../fortran/xgetua.f"
    /* Parameter adjustments */
#line 26 "../fortran/xgetua.f"
    --iunit;
#line 26 "../fortran/xgetua.f"

#line 26 "../fortran/xgetua.f"
    /* Function Body */
#line 26 "../fortran/xgetua.f"
    *n = j4save_(&c__5, &c__0, &c_false);
/*<       DO 30 I=1,N >*/
#line 27 "../fortran/xgetua.f"
    i__1 = *n;
#line 27 "../fortran/xgetua.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<          INDEX = I+4 >*/
#line 28 "../fortran/xgetua.f"
	index = i__ + 4;
/*<          IF (I.EQ.1) INDEX = 3 >*/
#line 29 "../fortran/xgetua.f"
	if (i__ == 1) {
#line 29 "../fortran/xgetua.f"
	    index = 3;
#line 29 "../fortran/xgetua.f"
	}
/*<          IUNIT(I) = J4SAVE(INDEX,0,.FALSE.) >*/
#line 30 "../fortran/xgetua.f"
	iunit[i__] = j4save_(&index, &c__0, &c_false);
/*<    30 CONTINUE >*/
#line 31 "../fortran/xgetua.f"
/* L30: */
#line 31 "../fortran/xgetua.f"
    }
/*<       RETURN >*/
#line 32 "../fortran/xgetua.f"
    return 0;
/*<       END >*/
} /* xgetua_ */

