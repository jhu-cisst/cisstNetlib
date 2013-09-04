#line 1 "../fortran/xerror.f"
/* ../fortran/xerror.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xerror.f"
/* Table of constant values */

static integer c__2 = 2;
static integer c__0 = 0;
static logical c_false = FALSE_;
static integer c__17 = 17;
static integer c__33 = 33;
static integer c__29 = 29;
static integer c__23 = 23;
static integer c__28 = 28;
static integer c__32 = 32;
static real c_b48 = 0.f;

/*<       SUBROUTINE XERROR(MESSG,NMESSG,NERR,LEVEL)                         >*/
/* Subroutine */ int xerror_(integer *messg, integer *nmessg, integer *nerr, 
	integer *level)
{
    extern /* Subroutine */ int fdump_(void);
    extern integer j4save_(integer *, integer *, logical *);
    extern /* Subroutine */ int xerabt_(char *, integer *, ftnlen);
    integer lkntrl, kdummy;
    extern /* Subroutine */ int xersav_(char *, integer *, integer *, integer 
	    *, integer *, ftnlen), xerprt_(char *, integer *, ftnlen), 
	    xerrwv_(integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, real *, real *);


/*     ABSTRACT */
/*        XERROR PROCESSES A DIAGNOSTIC MESSAGE, IN A MANNER */
/*        DETERMINED BY THE VALUE OF LEVEL AND THE CURRENT VALUE */
/*        OF THE LIBRARY ERROR CONTROL FLAG, KONTRL. */
/*        (SEE SUBROUTINE XSETF FOR DETAILS.) */

/*     DESCRIPTION OF PARAMETERS */
/*      --INPUT-- */
/*        MESSG - THE HOLLERITH MESSAGE TO BE PROCESSED, CONTAINING */
/*                NO MORE THAN 72 CHARACTERS. */
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

/*     EXAMPLES */
/*        CALL XERROR(23HSMOOTH -- NUM WAS ZERO.,23,1,2) */
/*        CALL XERROR(43HINTEG  -- LESS THAN FULL ACCURACY ACHIEVED., */
/*                    43,2,1) */
/*        CALL XERROR(65HROOTER -- ACTUAL ZERO OF F FOUND BEFORE INTERVAL */
/*    1 FULLY COLLAPSED.,65,3,0) */
/*        CALL XERROR(39HEXP    -- UNDERFLOWS BEING SET TO ZERO.,39,1,-1) */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/* END OF ABSTRACT */
/*     REVISED BY K HASKELL TO CHECK INPUT ARGS, 2/18/80 */

/*<       DIMENSION MESSG(NMESSG) >*/
/*     CHECK FOR VALID INPUT */
/*<       LKNTRL = J4SAVE (2,0,.FALSE.) >*/
#line 39 "../fortran/xerror.f"
    /* Parameter adjustments */
#line 39 "../fortran/xerror.f"
    --messg;
#line 39 "../fortran/xerror.f"

#line 39 "../fortran/xerror.f"
    /* Function Body */
#line 39 "../fortran/xerror.f"
    lkntrl = j4save_(&c__2, &c__0, &c_false);
/*<       IF (NMESSG.GT.0) GO TO 10 >*/
#line 40 "../fortran/xerror.f"
    if (*nmessg > 0) {
#line 40 "../fortran/xerror.f"
	goto L10;
#line 40 "../fortran/xerror.f"
    }
/*<       IF (LKNTRL.GT.0) CALL XERPRT(17HFATAL ERROR IN...,17) >*/
#line 41 "../fortran/xerror.f"
    if (lkntrl > 0) {
#line 41 "../fortran/xerror.f"
	xerprt_("FATAL ERROR IN...", &c__17, (ftnlen)17);
#line 41 "../fortran/xerror.f"
    }
/*<       CALL XERPRT (33HXERROR -- NMESSG MUST BE POSITIVE,33) >*/
#line 42 "../fortran/xerror.f"
    xerprt_("XERROR -- NMESSG MUST BE POSITIVE", &c__33, (ftnlen)33);
/*<       IF (LKNTRL.GT.0) CALL FDUMP >*/
#line 43 "../fortran/xerror.f"
    if (lkntrl > 0) {
#line 43 "../fortran/xerror.f"
	fdump_();
#line 43 "../fortran/xerror.f"
    }
/*<        >*/
#line 44 "../fortran/xerror.f"
    if (lkntrl > 0) {
#line 44 "../fortran/xerror.f"
	xerprt_("JOB ABORT DUE TO FATAL ERROR.", &c__29, (ftnlen)29);
#line 44 "../fortran/xerror.f"
    }
/*<       IF (LKNTRL.GT.0) CALL XERSAV (1H ,0,0,0,KDUMMY) >*/
#line 46 "../fortran/xerror.f"
    if (lkntrl > 0) {
#line 46 "../fortran/xerror.f"
	xersav_(" ", &c__0, &c__0, &c__0, &kdummy, (ftnlen)1);
#line 46 "../fortran/xerror.f"
    }
/*<       CALL XERABT (23HXERROR -- INVALID INPUT,23) >*/
#line 47 "../fortran/xerror.f"
    xerabt_("XERROR -- INVALID INPUT", &c__23, (ftnlen)23);
/*<       RETURN >*/
#line 48 "../fortran/xerror.f"
    return 0;
/*<    10 CONTINUE >*/
#line 49 "../fortran/xerror.f"
L10:
/*<       IF (NERR.NE.0) GO TO 15 >*/
#line 50 "../fortran/xerror.f"
    if (*nerr != 0) {
#line 50 "../fortran/xerror.f"
	goto L15;
#line 50 "../fortran/xerror.f"
    }
/*<       IF (LKNTRL.GT.0) CALL XERPRT(17HFATAL ERROR IN...,17) >*/
#line 51 "../fortran/xerror.f"
    if (lkntrl > 0) {
#line 51 "../fortran/xerror.f"
	xerprt_("FATAL ERROR IN...", &c__17, (ftnlen)17);
#line 51 "../fortran/xerror.f"
    }
/*<       CALL XERPRT (28HXERROR -- NERR=0 IS AN ERROR,28) >*/
#line 52 "../fortran/xerror.f"
    xerprt_("XERROR -- NERR=0 IS AN ERROR", &c__28, (ftnlen)28);
/*<       IF (LKNTRL.GT.0) CALL FDUMP >*/
#line 53 "../fortran/xerror.f"
    if (lkntrl > 0) {
#line 53 "../fortran/xerror.f"
	fdump_();
#line 53 "../fortran/xerror.f"
    }
/*<        >*/
#line 54 "../fortran/xerror.f"
    if (lkntrl > 0) {
#line 54 "../fortran/xerror.f"
	xerprt_("JOB ABORT DUE TO FATAL ERROR.", &c__29, (ftnlen)29);
#line 54 "../fortran/xerror.f"
    }
/*<       IF (LKNTRL.GT.0) CALL XERSAV (1H ,0,0,0,KDUMMY) >*/
#line 56 "../fortran/xerror.f"
    if (lkntrl > 0) {
#line 56 "../fortran/xerror.f"
	xersav_(" ", &c__0, &c__0, &c__0, &kdummy, (ftnlen)1);
#line 56 "../fortran/xerror.f"
    }
/*<       CALL XERABT (23HXERROR -- INVALID INPUT,23) >*/
#line 57 "../fortran/xerror.f"
    xerabt_("XERROR -- INVALID INPUT", &c__23, (ftnlen)23);
/*<       RETURN >*/
#line 58 "../fortran/xerror.f"
    return 0;
/*<    15 CONTINUE >*/
#line 59 "../fortran/xerror.f"
L15:
/*<       IF ((LEVEL.GE.(-1)).AND.(LEVEL.LE.2)) GO TO 20 >*/
#line 60 "../fortran/xerror.f"
    if (*level >= -1 && *level <= 2) {
#line 60 "../fortran/xerror.f"
	goto L20;
#line 60 "../fortran/xerror.f"
    }
/*<       IF (LKNTRL.GT.0) CALL XERPRT(17HFATAL ERROR IN...,17) >*/
#line 61 "../fortran/xerror.f"
    if (lkntrl > 0) {
#line 61 "../fortran/xerror.f"
	xerprt_("FATAL ERROR IN...", &c__17, (ftnlen)17);
#line 61 "../fortran/xerror.f"
    }
/*<       CALL XERPRT (32HXERROR -- INVALID VALUE OF LEVEL,32) >*/
#line 62 "../fortran/xerror.f"
    xerprt_("XERROR -- INVALID VALUE OF LEVEL", &c__32, (ftnlen)32);
/*<       IF (LKNTRL.GT.0) CALL FDUMP >*/
#line 63 "../fortran/xerror.f"
    if (lkntrl > 0) {
#line 63 "../fortran/xerror.f"
	fdump_();
#line 63 "../fortran/xerror.f"
    }
/*<        >*/
#line 64 "../fortran/xerror.f"
    if (lkntrl > 0) {
#line 64 "../fortran/xerror.f"
	xerprt_("JOB ABORT DUE TO FATAL ERROR.", &c__29, (ftnlen)29);
#line 64 "../fortran/xerror.f"
    }
/*<       IF (LKNTRL.GT.0) CALL XERSAV (1H ,0,0,0,KDUMMY) >*/
#line 66 "../fortran/xerror.f"
    if (lkntrl > 0) {
#line 66 "../fortran/xerror.f"
	xersav_(" ", &c__0, &c__0, &c__0, &kdummy, (ftnlen)1);
#line 66 "../fortran/xerror.f"
    }
/*<       CALL XERABT (23HXERROR -- INVALID INPUT,23) >*/
#line 67 "../fortran/xerror.f"
    xerabt_("XERROR -- INVALID INPUT", &c__23, (ftnlen)23);
/*<       RETURN >*/
#line 68 "../fortran/xerror.f"
    return 0;
/*<    20 CONTINUE >*/
#line 69 "../fortran/xerror.f"
L20:
/*<       CALL XERRWV(MESSG,NMESSG,NERR,LEVEL,0,0,0,0,0.,0.) >*/
#line 70 "../fortran/xerror.f"
    xerrwv_(&messg[1], nmessg, nerr, level, &c__0, &c__0, &c__0, &c__0, &
	    c_b48, &c_b48);
/*<       RETURN >*/
#line 71 "../fortran/xerror.f"
    return 0;
/*<       END >*/
} /* xerror_ */

