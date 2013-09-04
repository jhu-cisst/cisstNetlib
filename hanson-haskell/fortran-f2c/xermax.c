#line 1 "../fortran/xermax.f"
/* ../fortran/xermax.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xermax.f"
/* Table of constant values */

static integer c__4 = 4;
static logical c_true = TRUE_;

/*<       SUBROUTINE XERMAX(MAX)                                             >*/
/* Subroutine */ int xermax_(integer *max__)
{
    integer junk;
    extern integer j4save_(integer *, integer *, logical *);


/*     ABSTRACT */
/*        XERMAX SETS THE MAXIMUM NUMBER OF TIMES ANY MESSAGE */
/*        IS TO BE PRINTED.  THAT IS, NON-FATAL MESSAGES ARE */
/*        NOT TO BE PRINTED AFTER THEY HAVE OCCURED MAX TIMES. */
/*        SUCH NON-FATAL MESSAGES MAY BE PRINTED LESS THAN */
/*        MAX TIMES EVEN IF THEY OCCUR MAX TIMES, IF ERROR */
/*        SUPPRESSION MODE (KONTRL=0) IS EVER IN EFFECT. */

/*        THE DEFAULT VALUE FOR MAX IS 10. */

/*     DESCRIPTION OF PARAMETER */
/*      --INPUT-- */
/*        MAX - THE MAXIMUM NUMBER OF TIMES ANY ONE MESSAGE */
/*              IS TO BE PRINTED. */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/* END OF ABSTRACT */
/*     LATEST REVISION ---  7 JUNE 1978 */

/*<       JUNK = J4SAVE(4,MAX,.TRUE.) >*/
#line 22 "../fortran/xermax.f"
    junk = j4save_(&c__4, max__, &c_true);
/*<       RETURN >*/
#line 23 "../fortran/xermax.f"
    return 0;
/*<       END >*/
} /* xermax_ */

