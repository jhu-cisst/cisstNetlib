#line 1 "../fortran/xerabt.f"
/* ../fortran/xerabt.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xerabt.f"
/*<       SUBROUTINE XERABT(MESSG,NMESSG)                                    >*/
/* Subroutine */ int xerabt_(integer *messg, integer *nmessg)
{
    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);


/*     ABSTRACT */
/*        ***NOTE*** MACHINE DEPENDENT ROUTINE */
/*        XERABT ABORTS THE EXECUTION OF THE PROGRAM. */
/*        THE ERROR MESSAGE CAUSING THE ABORT IS GIVEN IN THE CALLING */
/*        SEQUENCE IN CASE ONE NEEDS IT FOR PRINTING ON A DAYFILE, */
/*        FOR EXAMPLE. */

/*     DESCRIPTION OF PARAMETERS */
/*        MESSG AND NMESSG ARE AS IN XERROR, EXCEPT THAT NMESSG MAY */
/*        BE ZERO, IN WHICH CASE NO MESSAGE IS BEING SUPPLIED. */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/* END OF ABSTRACT */
/*     LATEST REVISION ---  7 JUNE 1978 */

/*<       DIMENSION MESSG(NMESSG) >*/
/*<       IF (.TRUE.) STOP >*/
#line 19 "../fortran/xerabt.f"
    /* Parameter adjustments */
#line 19 "../fortran/xerabt.f"
    --messg;
#line 19 "../fortran/xerabt.f"

#line 19 "../fortran/xerabt.f"
    /* Function Body */
#line 19 "../fortran/xerabt.f"
    if (TRUE_) {
#line 19 "../fortran/xerabt.f"
	s_stop("", (ftnlen)0);
#line 19 "../fortran/xerabt.f"
    }
/*<       RETURN >*/
#line 20 "../fortran/xerabt.f"
    return 0;
/*<       END >*/
} /* xerabt_ */

