#line 1 "../fortran/xerdmp.f"
/* ../fortran/xerdmp.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xerdmp.f"
/* Table of constant values */

static integer c__0 = 0;

/*<       SUBROUTINE XERDMP                                                  >*/
/* Subroutine */ int xerdmp_(void)
{
    integer kount;
    extern /* Subroutine */ int xersav_(char *, integer *, integer *, integer 
	    *, integer *, ftnlen);


/*     ABSTRACT */
/*        XERDMP PRINTS AN ERROR TABLE SHOWING ALL ERRORS WHICH */
/*        HAVE OCCURRED DURING THE CURRENT EXECUTION, OR SINCE XERDMP */
/*        WAS LAST CALLED.  AFTER PRINTING, THE ERROR TABLE IS CLEARED, */
/*        AND IF PROGRAM EXECUTION IS CONTINUED ACCUMULATION OF THE */
/*        ERROR TABLE BEGINS AT ZERO. */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/* END OF ABSTRACT */
/*     LATEST REVISION ---  7 JUNE 1978 */

/*<       CALL XERSAV(1H ,0,0,0,KOUNT) >*/
#line 14 "../fortran/xerdmp.f"
    xersav_(" ", &c__0, &c__0, &c__0, &kount, (ftnlen)1);
/*<       RETURN >*/
#line 15 "../fortran/xerdmp.f"
    return 0;
/*<       END >*/
} /* xerdmp_ */

