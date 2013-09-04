#line 1 "../fortran/xsetf.f"
/* ../fortran/xsetf.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xsetf.f"
/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static logical c_true = TRUE_;

/* DECK XSETF */
/*<       SUBROUTINE XSETF (KONTRL) >*/
/* Subroutine */ int xsetf_(integer *kontrl)
{
    /* System generated locals */
    address a__1[2];
    integer i__1[2];
    char ch__1[27];
    icilist ici__1;

    /* Builtin functions */
    integer s_wsfi(icilist *), do_fio(integer *, char *, ftnlen), e_wsfi(void)
	    ;
    /* Subroutine */ int s_cat(char *, char **, integer *, integer *, ftnlen);

    /* Local variables */
    integer junk;
    char xern1[8];
    extern integer j4save_(integer *, integer *, logical *);
    extern /* Subroutine */ int xermsg_(char *, char *, char *, integer *, 
	    integer *, ftnlen, ftnlen, ftnlen);

/* ***BEGIN PROLOGUE  XSETF */
/* ***PURPOSE  Set the error control flag. */
/* ***LIBRARY   SLATEC (XERROR) */
/* ***CATEGORY  R3A */
/* ***TYPE      ALL (XSETF-A) */
/* ***KEYWORDS  ERROR, XERROR */
/* ***AUTHOR  Jones, R. E., (SNLA) */
/* ***DESCRIPTION */

/*     Abstract */
/*        XSETF sets the error control flag value to KONTRL. */
/*        (KONTRL is an input parameter only.) */
/*        The following table shows how each message is treated, */
/*        depending on the values of KONTRL and LEVEL.  (See XERMSG */
/*        for description of LEVEL.) */

/*        If KONTRL is zero or negative, no information other than the */
/*        message itself (including numeric values, if any) will be */
/*        printed.  If KONTRL is positive, introductory messages, */
/*        trace-backs, etc., will be printed in addition to the message. */

/*              ABS(KONTRL) */
/*        LEVEL        0              1              2 */
/*        value */
/*          2        fatal          fatal          fatal */

/*          1     not printed      printed         fatal */

/*          0     not printed      printed        printed */

/*         -1     not printed      printed        printed */
/*                                  only           only */
/*                                  once           once */

/* ***REFERENCES  R. E. Jones and D. K. Kahaner, XERROR, the SLATEC */
/*                 Error-handling Package, SAND82-0800, Sandia */
/*                 Laboratories, 1982. */
/* ***ROUTINES CALLED  J4SAVE, XERMSG */
/* ***REVISION HISTORY  (YYMMDD) */
/*   790801  DATE WRITTEN */
/*   890531  Changed all specific intrinsics to generic.  (WRB) */
/*   890531  REVISION DATE from Version 3.2 */
/*   891214  Prologue converted to Version 4.0 format.  (BAB) */
/*   900510  Change call to XERRWV to XERMSG.  (RWC) */
/*   920501  Reformatted the REFERENCES section.  (WRB) */
/* ***END PROLOGUE  XSETF */
/*<       CHARACTER *8 XERN1 >*/
/* ***FIRST EXECUTABLE STATEMENT  XSETF */
/*<       IF (ABS(KONTRL) .GT. 2) THEN >*/
#line 51 "../fortran/xsetf.f"
    if (abs(*kontrl) > 2) {
/*<          WRITE (XERN1, '(I8)') KONTRL >*/
#line 52 "../fortran/xsetf.f"
	ici__1.icierr = 0;
#line 52 "../fortran/xsetf.f"
	ici__1.icirnum = 1;
#line 52 "../fortran/xsetf.f"
	ici__1.icirlen = 8;
#line 52 "../fortran/xsetf.f"
	ici__1.iciunit = xern1;
#line 52 "../fortran/xsetf.f"
	ici__1.icifmt = "(I8)";
#line 52 "../fortran/xsetf.f"
	s_wsfi(&ici__1);
#line 52 "../fortran/xsetf.f"
	do_fio(&c__1, (char *)&(*kontrl), (ftnlen)sizeof(integer));
#line 52 "../fortran/xsetf.f"
	e_wsfi();
/*<        >*/
/* Writing concatenation */
#line 53 "../fortran/xsetf.f"
	i__1[0] = 19, a__1[0] = "INVALID ARGUMENT = ";
#line 53 "../fortran/xsetf.f"
	i__1[1] = 8, a__1[1] = xern1;
#line 53 "../fortran/xsetf.f"
	s_cat(ch__1, a__1, i__1, &c__2, (ftnlen)27);
#line 53 "../fortran/xsetf.f"
	xermsg_("SLATEC", "XSETF", ch__1, &c__1, &c__2, (ftnlen)6, (ftnlen)5, 
		(ftnlen)27);
/*<          RETURN >*/
#line 55 "../fortran/xsetf.f"
	return 0;
/*<       ENDIF >*/
#line 56 "../fortran/xsetf.f"
    }

/*<       JUNK = J4SAVE(2,KONTRL,.TRUE.) >*/
#line 58 "../fortran/xsetf.f"
    junk = j4save_(&c__2, kontrl, &c_true);
/*<       RETURN >*/
#line 59 "../fortran/xsetf.f"
    return 0;
/*<       END >*/
} /* xsetf_ */

