#line 1 "../fortran/xerctl.f"
/* ../fortran/xerctl.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/xerctl.f"
/*<       SUBROUTINE XERCTL(MESSG1,NMESSG,NERR,LEVEL,KONTRL)                 >*/
/* Subroutine */ int xerctl_(integer *messg1, integer *nmessg, integer *nerr, 
	integer *level, integer *kontrl)
{

/*     ABSTRACT */
/*        ALLOWS USER CONTROL OVER HANDLING OF INDIVIDUAL ERRORS. */
/*        JUST AFTER EACH MESSAGE IS RECORDED, BUT BEFORE IT IS */
/*        PROCESSED ANY FURTHER (I.E., BEFORE IT IS PRINTED OR */
/*        A DECISION TO ABORT IS MADE) A CALL IS MADE TO XERCTL. */
/*        IF THE USER HAS PROVIDED HIS OWN VERSION OF XERCTL, HE */
/*        CAN THEN OVERRIDE THE VALUE OF KONTROL USED IN PROCESSING */
/*        THIS MESSAGE BY REDEFINING ITS VALUE. */
/*        KONTRL MAY BE SET TO ANY VALUE FROM -2 TO 2. */
/*        THE MEANINGS FOR KONTRL ARE THE SAME AS IN XSETF, EXCEPT */
/*        THAT THE VALUE OF KONTRL CHANGES ONLY FOR THIS MESSAGE. */
/*        IF KONTRL IS SET TO A VALUE OUTSIDE THE RANGE FROM -2 TO 2, */
/*        IT WILL BE MOVED BACK INTO THAT RANGE. */

/*     DESCRIPTION OF PARAMETERS */

/*      --INPUT-- */
/*        MESSG1 - THE FIRST WORD (ONLY) OF THE ERROR MESSAGE. */
/*        NMESSG - SAME AS IN THE CALL TO XERROR OR XERRWV. */
/*        NERR   - SAME AS IN THE CALL TO XERROR OR XERRWV. */
/*        LEVEL  - SAME AS IN THE CALL TO XERROR OR XERRWV. */
/*        KONTRL - THE CURRENT VALUE OF THE CONTROL FLAG AS SET */
/*                 BY A CALL TO XSETF. */

/*      --OUTPUT-- */
/*        KONTRL - THE NEW VALUE OF KONTRL.  IF KONTRL IS NOT */
/*                 DEFINED, IT WILL REMAIN AT ITS ORIGINAL VALUE. */
/*                 THIS CHANGED VALUE OF CONTROL AFFECTS ONLY */
/*                 THE CURRENT OCCURRENCE OF THE CURRENT MESSAGE. */
/* END OF ABSTRACT */

/*<       RETURN >*/
#line 34 "../fortran/xerctl.f"
    return 0;
/*<       END >*/
} /* xerctl_ */

