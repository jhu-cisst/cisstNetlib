#line 1 "../fortran/xgetun.f"
/* ../fortran/xgetun.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xgetun.f"
/* Table of constant values */

static integer c__3 = 3;
static integer c__0 = 0;
static logical c_false = FALSE_;

/*<       SUBROUTINE XGETUN(IUNIT)                                           >*/
/* Subroutine */ int xgetun_(integer *iunit)
{
    extern integer j4save_(integer *, integer *, logical *);


/*     ABSTRACT */
/*        XGETUN GETS THE (FIRST) OUTPUT FILE TO WHICH ERROR MESSAGES */
/*        ARE BEING SENT.  TO FIND OUT IF MORE THAN ONE FILE IS BEING */
/*        USED, ONE MUST USE THE XGETUA ROUTINE. */

/*     DESCRIPTION OF PARAMETER */
/*      --OUTPUT-- */
/*        IUNIT - THE LOGICAL UNIT NUMBER OF THE  (FIRST) UNIT TO */
/*                WHICH ERROR MESSAGES ARE BEING SENT. */
/*                A VALUE OF ZERO MEANS THAT THE DEFAULT FILE, AS */
/*                DEFINED BY THE I1MACH ROUTINE, IS BEING USED. */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/* END OF ABSTRACT */
/*     LATEST REVISION --- 23 MAY 1979 */

/*<       IUNIT = J4SAVE(3,0,.FALSE.) >*/
#line 19 "../fortran/xgetun.f"
    *iunit = j4save_(&c__3, &c__0, &c_false);
/*<       RETURN >*/
#line 20 "../fortran/xgetun.f"
    return 0;
/*<       END >*/
} /* xgetun_ */

