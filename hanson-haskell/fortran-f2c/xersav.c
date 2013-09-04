#line 1 "../fortran/xersav.f"
/* ../fortran/xersav.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xersav.f"
/* Table of constant values */

static integer c__4 = 4;
static integer c__1 = 1;

/*<       SUBROUTINE XERSAV(MESSG,NMESSG,NERR,LEVEL,ICOUNT) >*/
/* Subroutine */ int xersav_(char *messg, integer *nmessg, integer *nerr, 
	integer *level, integer *icount, ftnlen messg_len)
{
    /* Initialized data */

    static integer kount[10] = { 0,0,0,0,0,0,0,0,0,0 };
    static integer kountx = 0;

    /* Format strings */
    static char fmt_10[] = "(\0020          ERROR MESSAGE SUMMARY\002/\002 M"
	    "ESSAGE START             NERR     LEVEL     COUNT\002)";
    static char fmt_15[] = "(1x,a20,3i10)";
    static char fmt_40[] = "(\0020OTHER ERRORS NOT INDIVIDUALLY TABULATED"
	    "=\002,i10)";
    static char fmt_50[] = "(1x)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_cmp(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    integer i__, ii;
    char mes[20];
    integer lun[5], iunit, kunit, nunit;
    extern integer i1mach_(integer *);
    static char mestab[20*10];
    static integer nertab[10], levtab[10];
    extern /* Subroutine */ int xgetua_(integer *, integer *);

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_15, 0 };
    static cilist io___13 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_50, 0 };


/* ***BEGIN PROLOGUE  XERSAV */
/* ***DATE WRITTEN   800319   (YYMMDD) */
/* ***REVISION DATE  820801   (YYMMDD) */
/* ***CATEGORY NO.  Z */
/* ***KEYWORDS  ERROR,XERROR PACKAGE */
/* ***AUTHOR  JONES, R. E., (SNLA) */
/* ***PURPOSE  Records that an error occurred. */
/* ***DESCRIPTION */
/*     Abstract */
/*        Record that this error occurred. */

/*     Description of Parameters */
/*     --Input-- */
/*       MESSG, NMESSG, NERR, LEVEL are as in XERROR, */
/*       except that when NMESSG=0 the tables will be */
/*       dumped and cleared, and when NMESSG is less than zero the */
/*       tables will be dumped and not cleared. */
/*     --Output-- */
/*       ICOUNT will be the number of times this message has */
/*       been seen, or zero if the table has overflowed and */
/*       does not contain this message specifically. */
/*       When NMESSG=0, ICOUNT will not be altered. */

/*     Written by Ron Jones, with SLATEC Common Math Library Subcommittee */
/*     Latest revision ---  19 Mar 1980 */
/* ***REFERENCES  JONES R.E., KAHANER D.K., "XERROR, THE SLATEC ERROR- */
/*                 HANDLING PACKAGE", SAND82-0800, SANDIA LABORATORIES, */
/*                 1982. */
/* ***ROUTINES CALLED  I1MACH,S88FMT,XGETUA */
/* ***END PROLOGUE  XERSAV */
/*<       INTEGER LUN(5) >*/
/*<       CHARACTER*(*) MESSG >*/
/*<       CHARACTER*20 MESTAB(10),MES >*/
/*<       DIMENSION NERTAB(10),LEVTAB(10),KOUNT(10) >*/
/*<       SAVE MESTAB,NERTAB,LEVTAB,KOUNT,KOUNTX >*/
/*     NEXT TWO DATA STATEMENTS ARE NECESSARY TO PROVIDE A BLANK */
/*     ERROR TABLE INITIALLY */
/*<        >*/
/*<       DATA KOUNTX/0/ >*/
/* ***FIRST EXECUTABLE STATEMENT  XERSAV */
/*<       IF (NMESSG.GT.0) GO TO 80 >*/
#line 44 "../fortran/xersav.f"
    if (*nmessg > 0) {
#line 44 "../fortran/xersav.f"
	goto L80;
#line 44 "../fortran/xersav.f"
    }
/*     DUMP THE TABLE */
/*<          IF (KOUNT(1).EQ.0) RETURN >*/
#line 46 "../fortran/xersav.f"
    if (kount[0] == 0) {
#line 46 "../fortran/xersav.f"
	return 0;
#line 46 "../fortran/xersav.f"
    }
/*        PRINT TO EACH UNIT */
/*<          CALL XGETUA(LUN,NUNIT) >*/
#line 48 "../fortran/xersav.f"
    xgetua_(lun, &nunit);
/*<          DO 60 KUNIT=1,NUNIT >*/
#line 49 "../fortran/xersav.f"
    i__1 = nunit;
#line 49 "../fortran/xersav.f"
    for (kunit = 1; kunit <= i__1; ++kunit) {
/*<             IUNIT = LUN(KUNIT) >*/
#line 50 "../fortran/xersav.f"
	iunit = lun[kunit - 1];
/*<             IF (IUNIT.EQ.0) IUNIT = I1MACH(4) >*/
#line 51 "../fortran/xersav.f"
	if (iunit == 0) {
#line 51 "../fortran/xersav.f"
	    iunit = i1mach_(&c__4);
#line 51 "../fortran/xersav.f"
	}
/*           PRINT TABLE HEADER */
/*<             WRITE (IUNIT,10) >*/
#line 53 "../fortran/xersav.f"
	io___7.ciunit = iunit;
#line 53 "../fortran/xersav.f"
	s_wsfe(&io___7);
#line 53 "../fortran/xersav.f"
	e_wsfe();
/*<    10  >*/
/*           PRINT BODY OF TABLE */
/*<             DO 20 I=1,10 >*/
#line 57 "../fortran/xersav.f"
	for (i__ = 1; i__ <= 10; ++i__) {
/*<                IF (KOUNT(I).EQ.0) GO TO 30 >*/
#line 58 "../fortran/xersav.f"
	    if (kount[i__ - 1] == 0) {
#line 58 "../fortran/xersav.f"
		goto L30;
#line 58 "../fortran/xersav.f"
	    }
/*<                WRITE (IUNIT,15) MESTAB(I),NERTAB(I),LEVTAB(I),KOUNT(I) >*/
#line 59 "../fortran/xersav.f"
	    io___9.ciunit = iunit;
#line 59 "../fortran/xersav.f"
	    s_wsfe(&io___9);
#line 59 "../fortran/xersav.f"
	    do_fio(&c__1, mestab + (i__ - 1) * 20, (ftnlen)20);
#line 59 "../fortran/xersav.f"
	    do_fio(&c__1, (char *)&nertab[i__ - 1], (ftnlen)sizeof(integer));
#line 59 "../fortran/xersav.f"
	    do_fio(&c__1, (char *)&levtab[i__ - 1], (ftnlen)sizeof(integer));
#line 59 "../fortran/xersav.f"
	    do_fio(&c__1, (char *)&kount[i__ - 1], (ftnlen)sizeof(integer));
#line 59 "../fortran/xersav.f"
	    e_wsfe();
/*<    15          FORMAT (1X,A20,3I10) >*/
/*<    20       CONTINUE >*/
#line 61 "../fortran/xersav.f"
/* L20: */
#line 61 "../fortran/xersav.f"
	}
/*<    30       CONTINUE >*/
#line 62 "../fortran/xersav.f"
L30:
/*           PRINT NUMBER OF OTHER ERRORS */
/*<             IF (KOUNTX.NE.0) WRITE (IUNIT,40) KOUNTX >*/
#line 64 "../fortran/xersav.f"
	if (kountx != 0) {
#line 64 "../fortran/xersav.f"
	    io___13.ciunit = iunit;
#line 64 "../fortran/xersav.f"
	    s_wsfe(&io___13);
#line 64 "../fortran/xersav.f"
	    do_fio(&c__1, (char *)&kountx, (ftnlen)sizeof(integer));
#line 64 "../fortran/xersav.f"
	    e_wsfe();
#line 64 "../fortran/xersav.f"
	}
/*<    40       FORMAT (41H0OTHER ERRORS NOT INDIVIDUALLY TABULATED=,I10) >*/
/*<             WRITE (IUNIT,50) >*/
#line 66 "../fortran/xersav.f"
	io___14.ciunit = iunit;
#line 66 "../fortran/xersav.f"
	s_wsfe(&io___14);
#line 66 "../fortran/xersav.f"
	e_wsfe();
/*<    50       FORMAT (1X) >*/
/*<    60    CONTINUE >*/
#line 68 "../fortran/xersav.f"
/* L60: */
#line 68 "../fortran/xersav.f"
    }
/*<          IF (NMESSG.LT.0) RETURN >*/
#line 69 "../fortran/xersav.f"
    if (*nmessg < 0) {
#line 69 "../fortran/xersav.f"
	return 0;
#line 69 "../fortran/xersav.f"
    }
/*        CLEAR THE ERROR TABLES */
/*<          DO 70 I=1,10 >*/
#line 71 "../fortran/xersav.f"
    for (i__ = 1; i__ <= 10; ++i__) {
/*<    70       KOUNT(I) = 0 >*/
#line 72 "../fortran/xersav.f"
/* L70: */
#line 72 "../fortran/xersav.f"
	kount[i__ - 1] = 0;
#line 72 "../fortran/xersav.f"
    }
/*<          KOUNTX = 0 >*/
#line 73 "../fortran/xersav.f"
    kountx = 0;
/*<          RETURN >*/
#line 74 "../fortran/xersav.f"
    return 0;
/*<    80 CONTINUE >*/
#line 75 "../fortran/xersav.f"
L80:
/*     PROCESS A MESSAGE... */
/*     SEARCH FOR THIS MESSG, OR ELSE AN EMPTY SLOT FOR THIS MESSG, */
/*     OR ELSE DETERMINE THAT THE ERROR TABLE IS FULL. */
/*<       MES = MESSG >*/
#line 79 "../fortran/xersav.f"
    s_copy(mes, messg, (ftnlen)20, messg_len);
/*<       DO 90 I=1,10 >*/
#line 80 "../fortran/xersav.f"
    for (i__ = 1; i__ <= 10; ++i__) {
/*<          II = I >*/
#line 81 "../fortran/xersav.f"
	ii = i__;
/*<          IF (KOUNT(I).EQ.0) GO TO 110 >*/
#line 82 "../fortran/xersav.f"
	if (kount[i__ - 1] == 0) {
#line 82 "../fortran/xersav.f"
	    goto L110;
#line 82 "../fortran/xersav.f"
	}
/*<          IF (MES.NE.MESTAB(I)) GO TO 90 >*/
#line 83 "../fortran/xersav.f"
	if (s_cmp(mes, mestab + (i__ - 1) * 20, (ftnlen)20, (ftnlen)20) != 0) 
		{
#line 83 "../fortran/xersav.f"
	    goto L90;
#line 83 "../fortran/xersav.f"
	}
/*<          IF (NERR.NE.NERTAB(I)) GO TO 90 >*/
#line 84 "../fortran/xersav.f"
	if (*nerr != nertab[i__ - 1]) {
#line 84 "../fortran/xersav.f"
	    goto L90;
#line 84 "../fortran/xersav.f"
	}
/*<          IF (LEVEL.NE.LEVTAB(I)) GO TO 90 >*/
#line 85 "../fortran/xersav.f"
	if (*level != levtab[i__ - 1]) {
#line 85 "../fortran/xersav.f"
	    goto L90;
#line 85 "../fortran/xersav.f"
	}
/*<          GO TO 100 >*/
#line 86 "../fortran/xersav.f"
	goto L100;
/*<    90 CONTINUE >*/
#line 87 "../fortran/xersav.f"
L90:
#line 87 "../fortran/xersav.f"
	;
#line 87 "../fortran/xersav.f"
    }
/*     THREE POSSIBLE CASES... */
/*     TABLE IS FULL */
/*<          KOUNTX = KOUNTX+1 >*/
#line 90 "../fortran/xersav.f"
    ++kountx;
/*<          ICOUNT = 1 >*/
#line 91 "../fortran/xersav.f"
    *icount = 1;
/*<          RETURN >*/
#line 92 "../fortran/xersav.f"
    return 0;
/*     MESSAGE FOUND IN TABLE */
/*<   100    KOUNT(II) = KOUNT(II) + 1 >*/
#line 94 "../fortran/xersav.f"
L100:
#line 94 "../fortran/xersav.f"
    ++kount[ii - 1];
/*<          ICOUNT = KOUNT(II) >*/
#line 95 "../fortran/xersav.f"
    *icount = kount[ii - 1];
/*<          RETURN >*/
#line 96 "../fortran/xersav.f"
    return 0;
/*     EMPTY SLOT FOUND FOR NEW MESSAGE */
/*<   110    MESTAB(II) = MES >*/
#line 98 "../fortran/xersav.f"
L110:
#line 98 "../fortran/xersav.f"
    s_copy(mestab + (ii - 1) * 20, mes, (ftnlen)20, (ftnlen)20);
/*<          NERTAB(II) = NERR >*/
#line 99 "../fortran/xersav.f"
    nertab[ii - 1] = *nerr;
/*<          LEVTAB(II) = LEVEL >*/
#line 100 "../fortran/xersav.f"
    levtab[ii - 1] = *level;
/*<          KOUNT(II)  = 1 >*/
#line 101 "../fortran/xersav.f"
    kount[ii - 1] = 1;
/*<          ICOUNT = 1 >*/
#line 102 "../fortran/xersav.f"
    *icount = 1;
/*<          RETURN >*/
#line 103 "../fortran/xersav.f"
    return 0;
/*<       END >*/
} /* xersav_ */

