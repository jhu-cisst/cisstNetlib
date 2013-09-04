#line 1 "../fortran/xerrwv.f"
/* ../fortran/xerrwv.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xerrwv.f"
/* Table of constant values */

static integer c__2 = 2;
static integer c__0 = 0;
static logical c_false = FALSE_;
static integer c__4 = 4;
static integer c__17 = 17;
static integer c__33 = 33;
static integer c__29 = 29;
static integer c__23 = 23;
static integer c__28 = 28;
static integer c__32 = 32;
static integer c__1 = 1;
static logical c_true = TRUE_;
static integer c__57 = 57;
static integer c__13 = 13;
static integer c__35 = 35;

/*<       SUBROUTINE XERRWV(MESSG,NMESSG,NERR,LEVEL,NI,I1,I2,NR,R1,R2)       >*/
/* Subroutine */ int xerrwv_(integer *messg, integer *nmessg, integer *nerr, 
	integer *level, integer *ni, integer *i1, integer *i2, integer *nr, 
	real *r1, real *r2)
{
    /* Format strings */
    static char fmt_22[] = "(11x,\002IN ABOVE MESSAGE, I1=\002,i10)";
    static char fmt_23[] = "(11x,\002IN ABOVE MESSAGE, I2=\002,i10)";
    static char fmt_24[] = "(11x,\002IN ABOVE MESSAGE, R1=\002,e20.10)";
    static char fmt_25[] = "(11x,\002IN ABOVE MESSAGE, R2=\002,e20.10)";
    static char fmt_30[] = "(\002 ERROR NUMBER =\002,i10)";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    integer lun[5], lerr, junk;
    extern /* Subroutine */ int fdump_(void);
    integer iunit, kunit, nunit, kount;
    extern integer i1mach_(integer *), j4save_(integer *, integer *, logical *
	    );
    integer ifatal, llevel;
    extern /* Subroutine */ int xerabt_();
    integer maxmes, lmessg;
    extern /* Subroutine */ int xgetua_(integer *, integer *), xerctl_(
	    integer *, integer *, integer *, integer *, integer *);
    integer lfirst, lkntrl, kdummy;
    extern /* Subroutine */ int xersav_();
    integer mkntrl;
    extern /* Subroutine */ int xerprt_();

    /* Fortran I/O blocks */
    static cilist io___15 = { 0, 0, 0, fmt_22, 0 };
    static cilist io___16 = { 0, 0, 0, fmt_23, 0 };
    static cilist io___17 = { 0, 0, 0, fmt_24, 0 };
    static cilist io___18 = { 0, 0, 0, fmt_25, 0 };
    static cilist io___19 = { 0, 0, 0, fmt_30, 0 };



/*     ABSTRACT */
/*        XERRWV PROCESSES A DIAGNOSTIC MESSAGE, IN A MANNER */
/*        DETERMINED BY THE VALUE OF LEVEL AND THE CURRENT VALUE */
/*        OF THE LIBRARY ERROR CONTROL FLAG, KONTRL. */
/*        (SEE SUBROUTINE XSETF FOR DETAILS.) */
/*        IN ADDITION, UP TO TWO INTEGER VALUES AND TWO REAL */
/*        VALUES MAY BE PRINTED ALONG WITH THE MESSAGE. */

/*     DESCRIPTION OF PARAMETERS */
/*      --INPUT-- */
/*        MESSG - THE HOLLERITH MESSAGE TO BE PROCESSED. */
/*        NMESSG- THE ACTUAL NUMBER OF CHARACTERS IN MESSG. */
/*        NERR  - THE ERROR NUMBER ASSOCIATED WITH THIS MESSAGE. */
/*                NERR MUST NOT BE ZERO. */
/*        LEVEL - ERROR CATEGORY. */
/*                =2 MEANS THIS IS AN UNCONDITIONALLY FATAL ERROR. */
/*                =1 MEANS THIS IS A RECOVERABLE ERROR.  (I.E., IT IS */
/*                   NON-FATAL IF XSETF HAS BEEN APPROPRIATELY CALLED.) */
/*                =0 MEANS THIS IS A WARNING MESSAGE ONLY. */
/*                =-1 MEANS THIS IS A WARNING MESSAGE WHICH IS TO BE */
/*                   PRINTED AT MOST ONCE, REGARDLESS OF HOW MANY */
/*                   TIMES THIS CALL IS EXECUTED. */
/*        NI    - NUMBER OF INTEGER VALUES TO BE PRINTED. (O TO 2) */
/*        I1    - FIRST INTEGER VALUE. */
/*        I2    - SECOND INTEGER VALUE. */
/*        NR    - NUMBER OF REAL VALUES TO BE PRINTED. (0 TO 2) */
/*        R1    - FIRST REAL VALUE. */
/*        R2    - SECOND REAL VALUE. */

/*     EXAMPLES */
/*        CALL XERRWV(29HSMOOTH -- NUM (=I1) WAS ZERO.,29,1,2, */
/*    1   1,NUM,0,0,0.,0.) */
/*        CALL XERRWV(54HQUADXY -- REQUESTED ERROR (R1) LESS THAN MINIMUM */
/*    1 (R2).,54,77,1,0,0,0,2,ERRREQ,ERRMIN) */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/* END OF ABSTRACT */
/*     LATEST REVISION ---  19 MAR 1980 */
/*     REVISED BY K HASKELL TO CHECK INPUT ARGS, 2/18/80 */

/*<       DIMENSION MESSG(NMESSG),LUN(5) >*/
/*     GET FLAGS */
/*<       LKNTRL = J4SAVE(2,0,.FALSE.) >*/
#line 45 "../fortran/xerrwv.f"
    /* Parameter adjustments */
#line 45 "../fortran/xerrwv.f"
    --messg;
#line 45 "../fortran/xerrwv.f"

#line 45 "../fortran/xerrwv.f"
    /* Function Body */
#line 45 "../fortran/xerrwv.f"
    lkntrl = j4save_(&c__2, &c__0, &c_false);
/*<       MAXMES = J4SAVE(4,0,.FALSE.) >*/
#line 46 "../fortran/xerrwv.f"
    maxmes = j4save_(&c__4, &c__0, &c_false);
/*     CHECK FOR VALID INPUT */
/*<       IF (NMESSG.GT.0) GO TO 2 >*/
#line 48 "../fortran/xerrwv.f"
    if (*nmessg > 0) {
#line 48 "../fortran/xerrwv.f"
	goto L2;
#line 48 "../fortran/xerrwv.f"
    }
/*<          IF (LKNTRL.GT.0) CALL XERPRT(17HFATAL ERROR IN...,17) >*/
#line 49 "../fortran/xerrwv.f"
    if (lkntrl > 0) {
#line 49 "../fortran/xerrwv.f"
	xerprt_("FATAL ERROR IN...", &c__17, (ftnlen)17);
#line 49 "../fortran/xerrwv.f"
    }
/*<       CALL XERPRT (33HXERRWV -- NMESSG MUST BE POSITIVE,33) >*/
#line 50 "../fortran/xerrwv.f"
    xerprt_("XERRWV -- NMESSG MUST BE POSITIVE", &c__33, (ftnlen)33);
/*<       IF (LKNTRL.GT.0) CALL FDUMP >*/
#line 51 "../fortran/xerrwv.f"
    if (lkntrl > 0) {
#line 51 "../fortran/xerrwv.f"
	fdump_();
#line 51 "../fortran/xerrwv.f"
    }
/*<        >*/
#line 52 "../fortran/xerrwv.f"
    if (lkntrl > 0) {
#line 52 "../fortran/xerrwv.f"
	xerprt_("JOB ABORT DUE TO FATAL ERROR.", &c__29, (ftnlen)29);
#line 52 "../fortran/xerrwv.f"
    }
/*<       IF (LKNTRL.GT.0) CALL XERSAV(1H ,0,0,0,KDUMMY) >*/
#line 54 "../fortran/xerrwv.f"
    if (lkntrl > 0) {
#line 54 "../fortran/xerrwv.f"
	xersav_(" ", &c__0, &c__0, &c__0, &kdummy, (ftnlen)1);
#line 54 "../fortran/xerrwv.f"
    }
/*<       CALL XERABT (23HXERRWV -- INVALID INPUT,23) >*/
#line 55 "../fortran/xerrwv.f"
    xerabt_("XERRWV -- INVALID INPUT", &c__23, (ftnlen)23);
/*<       RETURN >*/
#line 56 "../fortran/xerrwv.f"
    return 0;
/*<     2 CONTINUE >*/
#line 57 "../fortran/xerrwv.f"
L2:
/*<       IF (NERR.NE.0) GO TO 4 >*/
#line 58 "../fortran/xerrwv.f"
    if (*nerr != 0) {
#line 58 "../fortran/xerrwv.f"
	goto L4;
#line 58 "../fortran/xerrwv.f"
    }
/*<       IF (LKNTRL.GT.0) CALL XERPRT(17HFATAL ERROR IN...,17) >*/
#line 59 "../fortran/xerrwv.f"
    if (lkntrl > 0) {
#line 59 "../fortran/xerrwv.f"
	xerprt_("FATAL ERROR IN...", &c__17, (ftnlen)17);
#line 59 "../fortran/xerrwv.f"
    }
/*<       CALL XERPRT (28HXERRWV -- NERR=0 IS AN ERROR,28) >*/
#line 60 "../fortran/xerrwv.f"
    xerprt_("XERRWV -- NERR=0 IS AN ERROR", &c__28, (ftnlen)28);
/*<       IF (LKNTRL.GT.0) CALL FDUMP >*/
#line 61 "../fortran/xerrwv.f"
    if (lkntrl > 0) {
#line 61 "../fortran/xerrwv.f"
	fdump_();
#line 61 "../fortran/xerrwv.f"
    }
/*<        >*/
#line 62 "../fortran/xerrwv.f"
    if (lkntrl > 0) {
#line 62 "../fortran/xerrwv.f"
	xerprt_("JOB ABORT DUE TO FATAL ERROR.", &c__29, (ftnlen)29);
#line 62 "../fortran/xerrwv.f"
    }
/*<       IF (LKNTRL.GT.0) CALL XERSAV(1H ,0,0,0,KDUMMY) >*/
#line 64 "../fortran/xerrwv.f"
    if (lkntrl > 0) {
#line 64 "../fortran/xerrwv.f"
	xersav_(" ", &c__0, &c__0, &c__0, &kdummy, (ftnlen)1);
#line 64 "../fortran/xerrwv.f"
    }
/*<       CALL XERABT (23HXERRWV -- INVALID INPUT,23) >*/
#line 65 "../fortran/xerrwv.f"
    xerabt_("XERRWV -- INVALID INPUT", &c__23, (ftnlen)23);
/*<       RETURN >*/
#line 66 "../fortran/xerrwv.f"
    return 0;
/*<     4 CONTINUE >*/
#line 67 "../fortran/xerrwv.f"
L4:
/*<       IF ((LEVEL.GE.(-1)).AND.(LEVEL.LE.2)) GO TO 10 >*/
#line 68 "../fortran/xerrwv.f"
    if (*level >= -1 && *level <= 2) {
#line 68 "../fortran/xerrwv.f"
	goto L10;
#line 68 "../fortran/xerrwv.f"
    }
/*<       IF (LKNTRL.GT.0) CALL XERPRT(17HFATAL ERROR IN...,17) >*/
#line 69 "../fortran/xerrwv.f"
    if (lkntrl > 0) {
#line 69 "../fortran/xerrwv.f"
	xerprt_("FATAL ERROR IN...", &c__17, (ftnlen)17);
#line 69 "../fortran/xerrwv.f"
    }
/*<       CALL XERPRT (32HXERRWV -- INVALID VALUE OF LEVEL,32) >*/
#line 70 "../fortran/xerrwv.f"
    xerprt_("XERRWV -- INVALID VALUE OF LEVEL", &c__32, (ftnlen)32);
/*<          IF (LKNTRL.GT.0) CALL FDUMP >*/
#line 71 "../fortran/xerrwv.f"
    if (lkntrl > 0) {
#line 71 "../fortran/xerrwv.f"
	fdump_();
#line 71 "../fortran/xerrwv.f"
    }
/*<        >*/
#line 72 "../fortran/xerrwv.f"
    if (lkntrl > 0) {
#line 72 "../fortran/xerrwv.f"
	xerprt_("JOB ABORT DUE TO FATAL ERROR.", &c__29, (ftnlen)29);
#line 72 "../fortran/xerrwv.f"
    }
/*<          IF (LKNTRL.GT.0) CALL XERSAV(1H ,0,0,0,KDUMMY) >*/
#line 74 "../fortran/xerrwv.f"
    if (lkntrl > 0) {
#line 74 "../fortran/xerrwv.f"
	xersav_(" ", &c__0, &c__0, &c__0, &kdummy, (ftnlen)1);
#line 74 "../fortran/xerrwv.f"
    }
/*<          CALL XERABT(23HXERROR -- INVALID INPUT,23) >*/
#line 75 "../fortran/xerrwv.f"
    xerabt_("XERROR -- INVALID INPUT", &c__23, (ftnlen)23);
/*<          RETURN >*/
#line 76 "../fortran/xerrwv.f"
    return 0;
/*<    10 CONTINUE >*/
#line 77 "../fortran/xerrwv.f"
L10:
/*     RECORD MESSAGE */
/*<       JUNK = J4SAVE(1,NERR,.TRUE.) >*/
#line 79 "../fortran/xerrwv.f"
    junk = j4save_(&c__1, nerr, &c_true);
/*<       CALL XERSAV(MESSG,NMESSG,NERR,LEVEL,KOUNT) >*/
#line 80 "../fortran/xerrwv.f"
    xersav_(&messg[1], nmessg, nerr, level, &kount);
/*     LET USER OVERRIDE */
/*<       LFIRST = MESSG(1) >*/
#line 82 "../fortran/xerrwv.f"
    lfirst = messg[1];
/*<       LMESSG = NMESSG >*/
#line 83 "../fortran/xerrwv.f"
    lmessg = *nmessg;
/*<       LERR = NERR >*/
#line 84 "../fortran/xerrwv.f"
    lerr = *nerr;
/*<       LLEVEL = LEVEL >*/
#line 85 "../fortran/xerrwv.f"
    llevel = *level;
/*<       CALL XERCTL(LFIRST,LMESSG,LERR,LLEVEL,LKNTRL) >*/
#line 86 "../fortran/xerrwv.f"
    xerctl_(&lfirst, &lmessg, &lerr, &llevel, &lkntrl);
/*     RESET TO ORIGINAL VALUES */
/*<       LMESSG = NMESSG >*/
#line 88 "../fortran/xerrwv.f"
    lmessg = *nmessg;
/*<       LERR = NERR >*/
#line 89 "../fortran/xerrwv.f"
    lerr = *nerr;
/*<       LLEVEL = LEVEL >*/
#line 90 "../fortran/xerrwv.f"
    llevel = *level;
/*<       LKNTRL = MAX0(-2,MIN0(2,LKNTRL)) >*/
/* Computing MAX */
#line 91 "../fortran/xerrwv.f"
    i__1 = -2, i__2 = min(2,lkntrl);
#line 91 "../fortran/xerrwv.f"
    lkntrl = max(i__1,i__2);
/*<       MKNTRL = IABS(LKNTRL) >*/
#line 92 "../fortran/xerrwv.f"
    mkntrl = abs(lkntrl);
/*     DECIDE WHETHER TO PRINT MESSAGE */
/*<       IF ((LLEVEL.LT.2).AND.(LKNTRL.EQ.0)) GO TO 100 >*/
#line 94 "../fortran/xerrwv.f"
    if (llevel < 2 && lkntrl == 0) {
#line 94 "../fortran/xerrwv.f"
	goto L100;
#line 94 "../fortran/xerrwv.f"
    }
/*<        >*/
#line 95 "../fortran/xerrwv.f"
    if (llevel == -1 && kount > min(1,maxmes) || llevel == 0 && kount > 
	    maxmes || llevel == 1 && kount > maxmes && mkntrl == 1 || llevel 
	    == 2 && kount > max(1,maxmes)) {
#line 95 "../fortran/xerrwv.f"
	goto L100;
#line 95 "../fortran/xerrwv.f"
    }
/*<          IF (LKNTRL.LE.0) GO TO 20 >*/
#line 99 "../fortran/xerrwv.f"
    if (lkntrl <= 0) {
#line 99 "../fortran/xerrwv.f"
	goto L20;
#line 99 "../fortran/xerrwv.f"
    }
/*<             CALL XERPRT(1H ,1) >*/
#line 100 "../fortran/xerrwv.f"
    xerprt_(" ", &c__1, (ftnlen)1);
/*           INTRODUCTION */
/*<        >*/
#line 102 "../fortran/xerrwv.f"
    if (llevel == -1) {
#line 102 "../fortran/xerrwv.f"
	xerprt_("WARNING MESSAGE...THIS MESSAGE WILL ONLY BE PRINTED ONCE.", &
		c__57, (ftnlen)57);
#line 102 "../fortran/xerrwv.f"
    }
/*<             IF (LLEVEL.EQ.0) CALL XERPRT(13HWARNING IN...,13) >*/
#line 104 "../fortran/xerrwv.f"
    if (llevel == 0) {
#line 104 "../fortran/xerrwv.f"
	xerprt_("WARNING IN...", &c__13, (ftnlen)13);
#line 104 "../fortran/xerrwv.f"
    }
/*<        >*/
#line 105 "../fortran/xerrwv.f"
    if (llevel == 1) {
#line 105 "../fortran/xerrwv.f"
	xerprt_("RECOVERABLE ERROR IN...", &c__23, (ftnlen)23);
#line 105 "../fortran/xerrwv.f"
    }
/*<             IF (LLEVEL.EQ.2) CALL XERPRT(17HFATAL ERROR IN...,17) >*/
#line 107 "../fortran/xerrwv.f"
    if (llevel == 2) {
#line 107 "../fortran/xerrwv.f"
	xerprt_("FATAL ERROR IN...", &c__17, (ftnlen)17);
#line 107 "../fortran/xerrwv.f"
    }
/*<    20    CONTINUE >*/
#line 108 "../fortran/xerrwv.f"
L20:
/*        MESSAGE */
/*<          CALL XERPRT(MESSG,LMESSG) >*/
#line 110 "../fortran/xerrwv.f"
    xerprt_(&messg[1], &lmessg);
/*<          CALL XGETUA(LUN,NUNIT) >*/
#line 111 "../fortran/xerrwv.f"
    xgetua_(lun, &nunit);
/*<          DO 50 KUNIT=1,NUNIT >*/
#line 112 "../fortran/xerrwv.f"
    i__1 = nunit;
#line 112 "../fortran/xerrwv.f"
    for (kunit = 1; kunit <= i__1; ++kunit) {
/*<             IUNIT = LUN(KUNIT) >*/
#line 113 "../fortran/xerrwv.f"
	iunit = lun[kunit - 1];
/*<             IF (IUNIT.EQ.0) IUNIT = I1MACH(4) >*/
#line 114 "../fortran/xerrwv.f"
	if (iunit == 0) {
#line 114 "../fortran/xerrwv.f"
	    iunit = i1mach_(&c__4);
#line 114 "../fortran/xerrwv.f"
	}
/*<             IF (NI.GE.1) WRITE (IUNIT,22) I1 >*/
#line 115 "../fortran/xerrwv.f"
	if (*ni >= 1) {
#line 115 "../fortran/xerrwv.f"
	    io___15.ciunit = iunit;
#line 115 "../fortran/xerrwv.f"
	    s_wsfe(&io___15);
#line 115 "../fortran/xerrwv.f"
	    do_fio(&c__1, (char *)&(*i1), (ftnlen)sizeof(integer));
#line 115 "../fortran/xerrwv.f"
	    e_wsfe();
#line 115 "../fortran/xerrwv.f"
	}
/*<             IF (NI.GE.2) WRITE (IUNIT,23) I2 >*/
#line 116 "../fortran/xerrwv.f"
	if (*ni >= 2) {
#line 116 "../fortran/xerrwv.f"
	    io___16.ciunit = iunit;
#line 116 "../fortran/xerrwv.f"
	    s_wsfe(&io___16);
#line 116 "../fortran/xerrwv.f"
	    do_fio(&c__1, (char *)&(*i2), (ftnlen)sizeof(integer));
#line 116 "../fortran/xerrwv.f"
	    e_wsfe();
#line 116 "../fortran/xerrwv.f"
	}
/*<             IF (NR.GE.1) WRITE (IUNIT,24) R1 >*/
#line 117 "../fortran/xerrwv.f"
	if (*nr >= 1) {
#line 117 "../fortran/xerrwv.f"
	    io___17.ciunit = iunit;
#line 117 "../fortran/xerrwv.f"
	    s_wsfe(&io___17);
#line 117 "../fortran/xerrwv.f"
	    do_fio(&c__1, (char *)&(*r1), (ftnlen)sizeof(real));
#line 117 "../fortran/xerrwv.f"
	    e_wsfe();
#line 117 "../fortran/xerrwv.f"
	}
/*<             IF (NR.GE.2) WRITE (IUNIT,25) R2 >*/
#line 118 "../fortran/xerrwv.f"
	if (*nr >= 2) {
#line 118 "../fortran/xerrwv.f"
	    io___18.ciunit = iunit;
#line 118 "../fortran/xerrwv.f"
	    s_wsfe(&io___18);
#line 118 "../fortran/xerrwv.f"
	    do_fio(&c__1, (char *)&(*r2), (ftnlen)sizeof(real));
#line 118 "../fortran/xerrwv.f"
	    e_wsfe();
#line 118 "../fortran/xerrwv.f"
	}
/*<    22       FORMAT (11X,21HIN ABOVE MESSAGE, I1=,I10) >*/
/*<    23       FORMAT (11X,21HIN ABOVE MESSAGE, I2=,I10) >*/
/*<    24       FORMAT (11X,21HIN ABOVE MESSAGE, R1=,E20.10) >*/
/*<    25       FORMAT (11X,21HIN ABOVE MESSAGE, R2=,E20.10) >*/
/*<             IF (LKNTRL.LE.0) GO TO 40 >*/
#line 123 "../fortran/xerrwv.f"
	if (lkntrl <= 0) {
#line 123 "../fortran/xerrwv.f"
	    goto L40;
#line 123 "../fortran/xerrwv.f"
	}
/*              ERROR NUMBER */
/*<                WRITE (IUNIT,30) LERR >*/
#line 125 "../fortran/xerrwv.f"
	io___19.ciunit = iunit;
#line 125 "../fortran/xerrwv.f"
	s_wsfe(&io___19);
#line 125 "../fortran/xerrwv.f"
	do_fio(&c__1, (char *)&lerr, (ftnlen)sizeof(integer));
#line 125 "../fortran/xerrwv.f"
	e_wsfe();
/*<    30          FORMAT (15H ERROR NUMBER =,I10) >*/
/*<    40       CONTINUE >*/
#line 127 "../fortran/xerrwv.f"
L40:
/*<    50    CONTINUE >*/
#line 128 "../fortran/xerrwv.f"
/* L50: */
#line 128 "../fortran/xerrwv.f"
	;
#line 128 "../fortran/xerrwv.f"
    }
/*        TRACE-BACK */
/*<          CALL FDUMP >*/
#line 130 "../fortran/xerrwv.f"
    fdump_();
/*<   100 CONTINUE >*/
#line 131 "../fortran/xerrwv.f"
L100:
/*<       IFATAL = 0 >*/
#line 132 "../fortran/xerrwv.f"
    ifatal = 0;
/*<        >*/
#line 133 "../fortran/xerrwv.f"
    if (llevel == 2 || llevel == 1 && mkntrl == 2) {
#line 133 "../fortran/xerrwv.f"
	ifatal = 1;
#line 133 "../fortran/xerrwv.f"
    }
/*     QUIT HERE IF MESSAGE IS NOT FATAL */
/*<       IF (IFATAL.LE.0) RETURN >*/
#line 136 "../fortran/xerrwv.f"
    if (ifatal <= 0) {
#line 136 "../fortran/xerrwv.f"
	return 0;
#line 136 "../fortran/xerrwv.f"
    }
/*<       IF (LKNTRL.LE.0) GO TO 120 >*/
#line 137 "../fortran/xerrwv.f"
    if (lkntrl <= 0) {
#line 137 "../fortran/xerrwv.f"
	goto L120;
#line 137 "../fortran/xerrwv.f"
    }
/*        PRINT REASON FOR ABORT */
/*<        >*/
#line 139 "../fortran/xerrwv.f"
    if (llevel == 1) {
#line 139 "../fortran/xerrwv.f"
	xerprt_("JOB ABORT DUE TO UNRECOVERED ERROR.", &c__35, (ftnlen)35);
#line 139 "../fortran/xerrwv.f"
    }
/*<        >*/
#line 141 "../fortran/xerrwv.f"
    if (llevel == 2) {
#line 141 "../fortran/xerrwv.f"
	xerprt_("JOB ABORT DUE TO FATAL ERROR.", &c__29, (ftnlen)29);
#line 141 "../fortran/xerrwv.f"
    }
/*        PRINT ERROR SUMMARY */
/*<          CALL XERSAV(1H ,0,0,0,KDUMMY) >*/
#line 144 "../fortran/xerrwv.f"
    xersav_(" ", &c__0, &c__0, &c__0, &kdummy, (ftnlen)1);
/*<   120 CONTINUE >*/
#line 145 "../fortran/xerrwv.f"
L120:
/*     ABORT */
/*<       IF ((LLEVEL.EQ.2).AND.(KOUNT.GT.MAX0(1,MAXMES))) LMESSG = 0 >*/
#line 147 "../fortran/xerrwv.f"
    if (llevel == 2 && kount > max(1,maxmes)) {
#line 147 "../fortran/xerrwv.f"
	lmessg = 0;
#line 147 "../fortran/xerrwv.f"
    }
/*<       CALL XERABT(MESSG,LMESSG) >*/
#line 148 "../fortran/xerrwv.f"
    xerabt_(&messg[1], &lmessg);
/*<       RETURN >*/
#line 149 "../fortran/xerrwv.f"
    return 0;
/*<       END >*/
} /* xerrwv_ */

