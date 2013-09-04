#line 1 "../fortran/xerprt.f"
/* ../fortran/xerprt.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xerprt.f"
/* Table of constant values */

static integer c__4 = 4;
static integer c__1 = 1;

/*<       SUBROUTINE XERPRT(MESSG,NMESSG) >*/
/* Subroutine */ int xerprt_(char *messg, integer *nmessg, ftnlen messg_len)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    cilist ci__1;

    /* Builtin functions */
    integer i_len(char *, ftnlen), s_wsfe(cilist *), do_fio(integer *, char *,
	     ftnlen), e_wsfe(void);

    /* Local variables */
    integer lun[5], last, ichar, iunit, kunit, nunit;
    extern integer i1mach_(integer *);
    integer lenmes;
    extern /* Subroutine */ int xgetua_(integer *, integer *);

/* ***BEGIN PROLOGUE  XERPRT */
/* ***DATE WRITTEN   790801   (YYMMDD) */
/* ***REVISION DATE  820801   (YYMMDD) */
/* ***CATEGORY NO.  Z */
/* ***KEYWORDS  ERROR,XERROR PACKAGE */
/* ***AUTHOR  JONES, R. E., (SNLA) */
/* ***PURPOSE  Prints error messages. */
/* ***DESCRIPTION */
/*     Abstract */
/*        Print the Hollerith message in MESSG, of length NMESSG, */
/*        on each file indicated by XGETUA. */
/*     Latest revision ---  19 MAR 1980 */
/* ***REFERENCES  JONES R.E., KAHANER D.K., "XERROR, THE SLATEC ERROR- */
/*                 HANDLING PACKAGE", SAND82-0800, SANDIA LABORATORIES, */
/*                 1982. */
/* ***ROUTINES CALLED  I1MACH,S88FMT,XGETUA */
/* ***END PROLOGUE  XERPRT */
/*<       INTEGER LUN(5) >*/
/*<       CHARACTER*(*) MESSG >*/
/*     OBTAIN UNIT NUMBERS AND WRITE LINE TO EACH UNIT */
/* ***FIRST EXECUTABLE STATEMENT  XERPRT */
/*<       CALL XGETUA(LUN,NUNIT) >*/
#line 23 "../fortran/xerprt.f"
    xgetua_(lun, &nunit);
/*<       LENMES = LEN(MESSG) >*/
#line 24 "../fortran/xerprt.f"
    lenmes = i_len(messg, messg_len);
/*<       DO 20 KUNIT=1,NUNIT >*/
#line 25 "../fortran/xerprt.f"
    i__1 = nunit;
#line 25 "../fortran/xerprt.f"
    for (kunit = 1; kunit <= i__1; ++kunit) {
/*<          IUNIT = LUN(KUNIT) >*/
#line 26 "../fortran/xerprt.f"
	iunit = lun[kunit - 1];
/*<          IF (IUNIT.EQ.0) IUNIT = I1MACH(4) >*/
#line 27 "../fortran/xerprt.f"
	if (iunit == 0) {
#line 27 "../fortran/xerprt.f"
	    iunit = i1mach_(&c__4);
#line 27 "../fortran/xerprt.f"
	}
/*<          DO 10 ICHAR=1,LENMES,72 >*/
#line 28 "../fortran/xerprt.f"
	i__2 = lenmes;
#line 28 "../fortran/xerprt.f"
	for (ichar = 1; ichar <= i__2; ichar += 72) {
/*<             LAST = MIN0(ICHAR+71 , LENMES) >*/
/* Computing MIN */
#line 29 "../fortran/xerprt.f"
	    i__3 = ichar + 71;
#line 29 "../fortran/xerprt.f"
	    last = min(i__3,lenmes);
/*<             WRITE (IUNIT,'(1X,A)') MESSG(ICHAR:LAST) >*/
#line 30 "../fortran/xerprt.f"
	    ci__1.cierr = 0;
#line 30 "../fortran/xerprt.f"
	    ci__1.ciunit = iunit;
#line 30 "../fortran/xerprt.f"
	    ci__1.cifmt = "(1X,A)";
#line 30 "../fortran/xerprt.f"
	    s_wsfe(&ci__1);
#line 30 "../fortran/xerprt.f"
	    do_fio(&c__1, messg + (ichar - 1), last - (ichar - 1));
#line 30 "../fortran/xerprt.f"
	    e_wsfe();
/*<    10    CONTINUE >*/
#line 31 "../fortran/xerprt.f"
/* L10: */
#line 31 "../fortran/xerprt.f"
	}
/*<    20 CONTINUE >*/
#line 32 "../fortran/xerprt.f"
/* L20: */
#line 32 "../fortran/xerprt.f"
    }
/*<       RETURN >*/
#line 33 "../fortran/xerprt.f"
    return 0;
/*<       END >*/
} /* xerprt_ */

