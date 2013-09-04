#line 1 "../fortran/xerclr.f"
/* ../fortran/xerclr.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xerclr.f"
/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;
static logical c_true = TRUE_;

/*<       SUBROUTINE XERCLR                                                  >*/
/* Subroutine */ int xerclr_(void)
{
    integer junk;
    extern integer j4save_(integer *, integer *, logical *);


/*     ABSTRACT */
/*        THIS ROUTINE SIMPLY RESETS THE CURRENT ERROR NUMBER TO ZERO. */
/*        THIS MAY BE NECESSARY TO DO IN ORDER TO DETERMINE THAT */
/*        A CERTAIN ERROR HAS OCCURRED AGAIN SINCE THE LAST TIME */
/*        NUMXER WAS REFERENCED. */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/* END OF ABSTRACT */
/*     LATEST REVISION ---  7 JUNE 1978 */

/*<       JUNK = J4SAVE(1,0,.TRUE.) >*/
#line 13 "../fortran/xerclr.f"
    junk = j4save_(&c__1, &c__0, &c_true);
/*<       RETURN >*/
#line 14 "../fortran/xerclr.f"
    return 0;
/*<       END >*/
} /* xerclr_ */

