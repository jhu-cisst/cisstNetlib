#line 1 "../fortran/xsetua.f"
/* ../fortran/xsetua.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xsetua.f"
/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static logical c_true = TRUE_;
static integer c__5 = 5;

/* DECK XSETUA */
/*<       SUBROUTINE XSETUA (IUNITA, N) >*/
/* Subroutine */ int xsetua_(integer *iunita, integer *n)
{
    /* System generated locals */
    address a__1[2];
    integer i__1[2], i__2;
    char ch__1[37];
    icilist ici__1;

    /* Builtin functions */
    integer s_wsfi(icilist *), do_fio(integer *, char *, ftnlen), e_wsfi(void)
	    ;
    /* Subroutine */ int s_cat(char *, char **, integer *, integer *, ftnlen);

    /* Local variables */
    integer i__, junk;
    char xern1[8];
    integer index;
    extern integer j4save_(integer *, integer *, logical *);
    extern /* Subroutine */ int xermsg_(char *, char *, char *, integer *, 
	    integer *, ftnlen, ftnlen, ftnlen);

/* ***BEGIN PROLOGUE  XSETUA */
/* ***PURPOSE  Set logical unit numbers (up to 5) to which error */
/*            messages are to be sent. */
/* ***LIBRARY   SLATEC (XERROR) */
/* ***CATEGORY  R3B */
/* ***TYPE      ALL (XSETUA-A) */
/* ***KEYWORDS  ERROR, XERROR */
/* ***AUTHOR  Jones, R. E., (SNLA) */
/* ***DESCRIPTION */

/*     Abstract */
/*        XSETUA may be called to declare a list of up to five */
/*        logical units, each of which is to receive a copy of */
/*        each error message processed by this package. */
/*        The purpose of XSETUA is to allow simultaneous printing */
/*        of each error message on, say, a main output file, */
/*        an interactive terminal, and other files such as graphics */
/*        communication files. */

/*     Description of Parameters */
/*      --Input-- */
/*        IUNIT - an array of up to five unit numbers. */
/*                Normally these numbers should all be different */
/*                (but duplicates are not prohibited.) */
/*        N     - the number of unit numbers provided in IUNIT */
/*                must have 1 .LE. N .LE. 5. */

/* ***REFERENCES  R. E. Jones and D. K. Kahaner, XERROR, the SLATEC */
/*                 Error-handling Package, SAND82-0800, Sandia */
/*                 Laboratories, 1982. */
/* ***ROUTINES CALLED  J4SAVE, XERMSG */
/* ***REVISION HISTORY  (YYMMDD) */
/*   790801  DATE WRITTEN */
/*   861211  REVISION DATE from Version 3.2 */
/*   891214  Prologue converted to Version 4.0 format.  (BAB) */
/*   900510  Change call to XERRWV to XERMSG.  (RWC) */
/*   920501  Reformatted the REFERENCES section.  (WRB) */
/* ***END PROLOGUE  XSETUA */
/*<       DIMENSION IUNITA(5) >*/
/*<       CHARACTER *8 XERN1 >*/
/* ***FIRST EXECUTABLE STATEMENT  XSETUA */

/*<       IF (N.LT.1 .OR. N.GT.5) THEN >*/
#line 45 "../fortran/xsetua.f"
    /* Parameter adjustments */
#line 45 "../fortran/xsetua.f"
    --iunita;
#line 45 "../fortran/xsetua.f"

#line 45 "../fortran/xsetua.f"
    /* Function Body */
#line 45 "../fortran/xsetua.f"
    if (*n < 1 || *n > 5) {
/*<          WRITE (XERN1, '(I8)') N >*/
#line 46 "../fortran/xsetua.f"
	ici__1.icierr = 0;
#line 46 "../fortran/xsetua.f"
	ici__1.icirnum = 1;
#line 46 "../fortran/xsetua.f"
	ici__1.icirlen = 8;
#line 46 "../fortran/xsetua.f"
	ici__1.iciunit = xern1;
#line 46 "../fortran/xsetua.f"
	ici__1.icifmt = "(I8)";
#line 46 "../fortran/xsetua.f"
	s_wsfi(&ici__1);
#line 46 "../fortran/xsetua.f"
	do_fio(&c__1, (char *)&(*n), (ftnlen)sizeof(integer));
#line 46 "../fortran/xsetua.f"
	e_wsfi();
/*<        >*/
/* Writing concatenation */
#line 47 "../fortran/xsetua.f"
	i__1[0] = 29, a__1[0] = "INVALID NUMBER OF UNITS, N = ";
#line 47 "../fortran/xsetua.f"
	i__1[1] = 8, a__1[1] = xern1;
#line 47 "../fortran/xsetua.f"
	s_cat(ch__1, a__1, i__1, &c__2, (ftnlen)37);
#line 47 "../fortran/xsetua.f"
	xermsg_("SLATEC", "XSETUA", ch__1, &c__1, &c__2, (ftnlen)6, (ftnlen)6,
		 (ftnlen)37);
/*<          RETURN >*/
#line 49 "../fortran/xsetua.f"
	return 0;
/*<       ENDIF >*/
#line 50 "../fortran/xsetua.f"
    }

/*<       DO 10 I=1,N >*/
#line 52 "../fortran/xsetua.f"
    i__2 = *n;
#line 52 "../fortran/xsetua.f"
    for (i__ = 1; i__ <= i__2; ++i__) {
/*<          INDEX = I+4 >*/
#line 53 "../fortran/xsetua.f"
	index = i__ + 4;
/*<          IF (I.EQ.1) INDEX = 3 >*/
#line 54 "../fortran/xsetua.f"
	if (i__ == 1) {
#line 54 "../fortran/xsetua.f"
	    index = 3;
#line 54 "../fortran/xsetua.f"
	}
/*<          JUNK = J4SAVE(INDEX,IUNITA(I),.TRUE.) >*/
#line 55 "../fortran/xsetua.f"
	junk = j4save_(&index, &iunita[i__], &c_true);
/*<    10 CONTINUE >*/
#line 56 "../fortran/xsetua.f"
/* L10: */
#line 56 "../fortran/xsetua.f"
    }
/*<       JUNK = J4SAVE(5,N,.TRUE.) >*/
#line 57 "../fortran/xsetua.f"
    junk = j4save_(&c__5, n, &c_true);
/*<       RETURN >*/
#line 58 "../fortran/xsetua.f"
    return 0;
/*<       END >*/
} /* xsetua_ */

