#line 1 "../fortran/xsetun.f"
/* ../fortran/xsetun.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xsetun.f"
/* Table of constant values */

static integer c__3 = 3;
static logical c_true = TRUE_;
static integer c__5 = 5;
static integer c__1 = 1;

/*<       SUBROUTINE XSETUN(IUNIT)                                           >*/
/* Subroutine */ int xsetun_(integer *iunit)
{
    integer junk;
    extern integer j4save_(integer *, integer *, logical *);


/*     ABSTRACT */
/*        XSETUN SETS THE OUTPUT FILE TO WHICH ERROR MESSAGES ARE TO */
/*        BE SENT.  ONLY ONE FILE WILL BE USED.  SEE XSETUA FOR */
/*        HOW TO DECLARE MORE THAN ONE FILE. */

/*     DESCRIPTION OF PARAMETER */
/*      --INPUT-- */
/*        IUNIT - AN INPUT PARAMETER GIVING THE LOGICAL UNIT NUMBER */
/*                TO WHICH ERROR MESSAGES ARE TO BE SENT. */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/* END OF ABSTRACT */
/*     LATEST REVISION ---  7 JUNE 1978 */

/*<       JUNK = J4SAVE(3,IUNIT,.TRUE.) >*/
#line 17 "../fortran/xsetun.f"
    junk = j4save_(&c__3, iunit, &c_true);
/*<       JUNK = J4SAVE(5,1,.TRUE.) >*/
#line 18 "../fortran/xsetun.f"
    junk = j4save_(&c__5, &c__1, &c_true);
/*<       RETURN >*/
#line 19 "../fortran/xsetun.f"
    return 0;
/*<       END >*/
} /* xsetun_ */

