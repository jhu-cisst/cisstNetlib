#line 1 "../fortran/xgetf.f"
/* ../fortran/xgetf.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xgetf.f"
/* Table of constant values */

static integer c__2 = 2;
static integer c__0 = 0;
static logical c_false = FALSE_;

/*<       SUBROUTINE XGETF(KONTRL)                                           >*/
/* Subroutine */ int xgetf_(integer *kontrl)
{
    extern integer j4save_(integer *, integer *, logical *);


/*     ABSTRACT */
/*        XGETF RETURNS THE CURRENT VALUE OF THE ERROR CONTROL FLAG */
/*        IN KONTRL.  SEE SUBROUTINE XSETF FOR FLAG VALUE MEANINGS. */
/*        (KONTRL IS AN OUTPUT PARAMETER ONLY.) */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/* END OF ABSTRACT */
/*     LATEST REVISION ---  7 JUNE 1978 */

/*<       KONTRL = J4SAVE(2,0,.FALSE.) >*/
#line 12 "../fortran/xgetf.f"
    *kontrl = j4save_(&c__2, &c__0, &c_false);
/*<       RETURN >*/
#line 13 "../fortran/xgetf.f"
    return 0;
/*<       END >*/
} /* xgetf_ */

