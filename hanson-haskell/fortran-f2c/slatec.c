#line 1 "../fortran/slatec.f"
/* ../fortran/slatec.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/slatec.f"
/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;
static logical c_false = FALSE_;

/*<       SUBROUTINE FDUMP                                                   >*/
/* Subroutine */ int fdump_(void)
{
/*     ABSTRACT */
/*        ***NOTE*** MACHINE DEPENDENT ROUTINE */
/*        FDUMP IS INTENDED TO BE REPLACED BY A LOCALLY WRITTEN */
/*        VERSION WHICH PRODUCES A SYMBOLIC DUMP.  FAILING THIS, */
/*        IT SHOULD BE REPLACED BY A VERSION WHICH PRINTS THE */
/*        SUBPROGRAM NESTING LIST.  NOTE THAT THIS DUMP MUST BE */
/*        PRINTED ON EACH OF UP TO FIVE FILES, AS INDICATED BY THE */
/*        XGETUA ROUTINE.  SEE XSETUA AND XGETUA FOR DETAILS. */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/* END OF ABSTRACT */
/*     LATEST REVISION ---  23 MAY 1979 */

/*<       RETURN >*/
#line 15 "../fortran/slatec.f"
    return 0;
/*<       END >*/
} /* fdump_ */

/*<       FUNCTION J4SAVE(IWHICH,IVALUE,ISET)                                >*/
integer j4save_(integer *iwhich, integer *ivalue, logical *iset)
{
    /* Initialized data */

    static integer iparam[9] = { 0,2,0,10,1,0,0,0,0 };

    /* System generated locals */
    integer ret_val;


/*     ABSTRACT */
/*        J4SAVE SAVES AND RECALLS SEVERAL GLOBAL VARIABLES NEEDED */
/*        BY THE LIBRARY ERROR HANDLING ROUTINES. */

/*     DESCRIPTION OF PARAMETERS */
/*      --INPUT-- */
/*        IWHICH - INDEX OF ITEM DESIRED. */
/*                 = 1 REFERS TO CURRENT ERROR NUMBER. */
/*                 = 2 REFERS TO CURRENT ERROR CONTROL FLAG. */
/*                 = 3 REFERS TO CURRENT UNIT NUMBER TO WHICH ERROR */
/*                     MESSAGES ARE TO BE SENT.  (0 MEANS USE STANDARD.) */
/*                 = 4 REFERS TO THE MAXIMUM NUMBER OF TIMES ANY */
/*                     MESSAGE IS TO BE PRINTED (AS SET BY XERMAX). */
/*                 = 5 REFERS TO THE TOTAL NUMBER OF UNITS TO WHICH */
/*                     EACH ERROR MESSAGE IS TO BE WRITTEN. */
/*                 = 6 REFERS TO THE 2ND UNIT FOR ERROR MESSAGES */
/*                 = 7 REFERS TO THE 3RD UNIT FOR ERROR MESSAGES */
/*                 = 8 REFERS TO THE 4TH UNIT FOR ERROR MESSAGES */
/*                 = 9 REFERS TO THE 5TH UNIT FOR ERROR MESSAGES */
/*        IVALUE - THE VALUE TO BE SET FOR THE IWHICH-TH PARAMETER, */
/*                 IF ISET IS .TRUE. . */
/*        ISET   - IF ISET=.TRUE., THE IWHICH-TH PARAMETER WILL BE */
/*                 GIVEN THE VALUE, IVALUE.  IF ISET=.FALSE., THE */
/*                 IWHICH-TH PARAMETER WILL BE UNCHANGED, AND IVALUE */
/*                 IS A DUMMY PARAMETER. */
/*      --OUTPUT-- */
/*        THE (OLD) VALUE OF THE IWHICH-TH PARAMETER WILL BE RETURNED */
/*        IN THE FUNCTION VALUE, J4SAVE. */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/*     ADAPTED FROM BELL LABORATORIES PORT LIBRARY ERROR HANDLER */
/* END OF ABSTRACT */
/*     LATEST REVISION ---  23 MAY 1979 */

/*<       LOGICAL ISET >*/
/*<       INTEGER IPARAM(9) >*/
/*<       DATA IPARAM(1),IPARAM(2),IPARAM(3),IPARAM(4)/0,2,0,10/ >*/
/*<       DATA IPARAM(5)/1/ >*/
/*<       DATA IPARAM(6),IPARAM(7),IPARAM(8),IPARAM(9)/0,0,0,0/ >*/
/*<       J4SAVE = IPARAM(IWHICH) >*/
#line 59 "../fortran/slatec.f"
    ret_val = iparam[(0 + (0 + (*iwhich - 1 << 2))) / 4];
/*<       IF (ISET) IPARAM(IWHICH) = IVALUE >*/
#line 60 "../fortran/slatec.f"
    if (*iset) {
#line 60 "../fortran/slatec.f"
	iparam[*iwhich - 1] = *ivalue;
#line 60 "../fortran/slatec.f"
    }
/*<       RETURN >*/
#line 61 "../fortran/slatec.f"
    return ret_val;
/*<       END >*/
} /* j4save_ */

/*<       FUNCTION NUMXER(NERR)                                              >*/
integer numxer_(integer *nerr)
{
    /* System generated locals */
    integer ret_val;

    /* Local variables */
    extern integer j4save_(integer *, integer *, logical *);


/*     ABSTRACT */
/*        NUMXER RETURNS THE MOST RECENT ERROR NUMBER, */
/*        IN BOTH NUMXER AND THE PARAMETER NERR. */

/*     WRITTEN BY RON JONES, WITH SLATEC COMMON MATH LIBRARY SUBCOMMITTEE */
/* END OF ABSTRACT */
/*     LATEST REVISION ---  7 JUNE 1978 */

/*<       NERR = J4SAVE(1,0,.FALSE.) >*/
#line 73 "../fortran/slatec.f"
    *nerr = j4save_(&c__1, &c__0, &c_false);
/*<       NUMXER = NERR >*/
#line 74 "../fortran/slatec.f"
    ret_val = *nerr;
/*<       RETURN >*/
#line 75 "../fortran/slatec.f"
    return ret_val;
/*<       END >*/
} /* numxer_ */

/*<       SUBROUTINE S88FMT(N,IVALUE,IFMT)                                   >*/
/* Subroutine */ int s88fmt_(integer *n, integer *ivalue, integer *ifmt)
{
    /* Initialized data */

    static struct {
	char e_1[40];
	integer e_2;
	} equiv_6 = { "0   1   2   3   4   5   6   7   8   9   ", 0 };

#define idigit ((integer *)&equiv_6)


    integer it, nt, index;


/*     ABSTRACT */
/*        S88FMT REPLACES IFMT(1), ... ,IFMT(N) WITH THE */
/*        CHARACTERS CORRESPONDING TO THE N LEAST SIGNIFICANT */
/*        DIGITS OF IVALUE. */

/*     TAKEN FROM THE BELL LABORATORIES PORT LIBRARY ERROR HANDLER */
/* END OF ABSTRACT */
/*     LATEST REVISION ---  7 JUNE 1978 */

/*<       DIMENSION IFMT(N),IDIGIT(10) >*/
/*<        >*/
#line 90 "../fortran/slatec.f"
    /* Parameter adjustments */
#line 90 "../fortran/slatec.f"
    --ifmt;
#line 90 "../fortran/slatec.f"

#line 90 "../fortran/slatec.f"
    /* Function Body */
/*<       NT = N >*/
#line 93 "../fortran/slatec.f"
    nt = *n;
/*<       IT = IVALUE >*/
#line 94 "../fortran/slatec.f"
    it = *ivalue;
/*<    10    IF (NT .EQ. 0) RETURN >*/
#line 95 "../fortran/slatec.f"
L10:
#line 95 "../fortran/slatec.f"
    if (nt == 0) {
#line 95 "../fortran/slatec.f"
	return 0;
#line 95 "../fortran/slatec.f"
    }
/*<          INDEX = MOD(IT,10) >*/
#line 96 "../fortran/slatec.f"
    index = it % 10;
/*<          IFMT(NT) = IDIGIT(INDEX+1) >*/
#line 97 "../fortran/slatec.f"
    ifmt[nt] = idigit[index];
/*<          IT = IT/10 >*/
#line 98 "../fortran/slatec.f"
    it /= 10;
/*<          NT = NT - 1 >*/
#line 99 "../fortran/slatec.f"
    --nt;
/*<          GO TO 10 >*/
#line 100 "../fortran/slatec.f"
    goto L10;
/*<       END >*/
} /* s88fmt_ */

#undef idigit


/*<       INTEGER FUNCTION I1MACH(I) >*/
integer i1mach_(integer *i__)
{
    /* Format strings */
    static char fmt_9000[] = "(\0021ERROR    1 IN I1MACH - I OUT OF BOUND"
	    "S\002)";

    /* System generated locals */
    integer ret_val;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    integer imach[16], output;

    /* Fortran I/O blocks */
    static cilist io___9 = { 0, 0, 0, fmt_9000, 0 };


/* ***BEGIN PROLOGUE  I1MACH */
/* ***REVISION DATE  811015   (YYMMDD) */
/* ***CATEGORY NO.  Q */
/* ***KEYWORDS  MACHINE CONSTANTS,INTEGER */
/* ***DATE WRITTEN   1975 */
/* ***AUTHOR FOX P.A.,HALL A.D.,SCHRYER N.L. (BELL LABS) */
/* ***PURPOSE */
/* RETURNS INTEGER MACHINE DEPENDENT CONSTANTS */
/* ***DESCRIPTION */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*   THESE MACHINE CONSTANT ROUTINES MUST BE ACTIVATED FOR */
/*   A PARTICULAR ENVIRONMENT. */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*     I1MACH CAN BE USED TO OBTAIN MACHINE-DEPENDENT PARAMETERS */
/*     FOR THE LOCAL MACHINE ENVIRONMENT.  IT IS A FUNCTION */
/*     SUBROUTINE WITH ONE (INPUT) ARGUMENT, AND CAN BE CALLED */
/*     AS FOLLOWS, FOR EXAMPLE */

/*          K = I1MACH(I) */

/*     WHERE I=1,...,16.  THE (OUTPUT) VALUE OF K ABOVE IS */
/*     DETERMINED BY THE (INPUT) VALUE OF I.  THE RESULTS FOR */
/*     VARIOUS VALUES OF I ARE DISCUSSED BELOW. */

/*  I/O UNIT NUMBERS. */
/*    I1MACH( 1) = THE STANDARD INPUT UNIT. */
/*    I1MACH( 2) = THE STANDARD OUTPUT UNIT. */
/*    I1MACH( 3) = THE STANDARD PUNCH UNIT. */
/*    I1MACH( 4) = THE STANDARD ERROR MESSAGE UNIT. */

/*  WORDS. */
/*    I1MACH( 5) = THE NUMBER OF BITS PER INTEGER STORAGE UNIT. */
/*    I1MACH( 6) = THE NUMBER OF CHARACTERS PER INTEGER STORAGE UNIT. */

/*  INTEGERS. */
/*    ASSUME INTEGERS ARE REPRESENTED IN THE S-DIGIT, BASE-A FORM */

/*               SIGN ( X(S-1)*A**(S-1) + ... + X(1)*A + X(0) ) */

/*               WHERE 0 .LE. X(I) .LT. A FOR I=0,...,S-1. */
/*    I1MACH( 7) = A, THE BASE. */
/*    I1MACH( 8) = S, THE NUMBER OF BASE-A DIGITS. */
/*    I1MACH( 9) = A**S - 1, THE LARGEST MAGNITUDE. */

/*  FLOATING-POINT NUMBERS. */
/*    ASSUME FLOATING-POINT NUMBERS ARE REPRESENTED IN THE T-DIGIT, */
/*    BASE-B FORM */
/*               SIGN (B**E)*( (X(1)/B) + ... + (X(T)/B**T) ) */

/*               WHERE 0 .LE. X(I) .LT. B FOR I=1,...,T, */
/*               0 .LT. X(1), AND EMIN .LE. E .LE. EMAX. */
/*    I1MACH(10) = B, THE BASE. */

/*  SINGLE-PRECISION */
/*    I1MACH(11) = T, THE NUMBER OF BASE-B DIGITS. */
/*    I1MACH(12) = EMIN, THE SMALLEST EXPONENT E. */
/*    I1MACH(13) = EMAX, THE LARGEST EXPONENT E. */

/*  DOUBLE-PRECISION */
/*    I1MACH(14) = T, THE NUMBER OF BASE-B DIGITS. */
/*    I1MACH(15) = EMIN, THE SMALLEST EXPONENT E. */
/*    I1MACH(16) = EMAX, THE LARGEST EXPONENT E. */

/*  TO ALTER THIS FUNCTION FOR A PARTICULAR ENVIRONMENT, */
/*  THE DESIRED SET OF DATA STATEMENTS SHOULD BE ACTIVATED BY */
/*  REMOVING THE C FROM COLUMN 1.  ALSO, THE VALUES OF */
/*  I1MACH(1) - I1MACH(4) SHOULD BE CHECKED FOR CONSISTENCY */
/*  WITH THE LOCAL OPERATING SYSTEM. */

/* ***REFERENCES */
/*  FOX P.A., HALL A.D., SCHRYER N.L.,*FRAMEWORK FOR A PORTABLE LIBRARY*, */
/*  ACM TRANSACTION ON MATHEMATICAL SOFTWARE, VOL. 4, NO. 2, */
/*  JUNE 1978, PP. 177-188. */
/* ***ROUTINES CALLED  XERROR */
/* ***END PROLOGUE  I1MACH */

/*<       INTEGER IMACH(16),OUTPUT >*/

/*     EQUIVALENCE (IMACH(4),OUTPUT) */

/*     MACHINE CONSTANTS FOR THE BURROUGHS 1700 SYSTEM. */

/*     DATA IMACH( 1) /    7 / */
/*     DATA IMACH( 2) /    2 / */
/*     DATA IMACH( 3) /    2 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   36 / */
/*     DATA IMACH( 6) /    4 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   33 / */
/*     DATA IMACH( 9) / Z1FFFFFFFF / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   24 / */
/*     DATA IMACH(12) / -256 / */
/*     DATA IMACH(13) /  255 / */
/*     DATA IMACH(14) /   60 / */
/*     DATA IMACH(15) / -256 / */
/*     DATA IMACH(16) /  255 / */

/*     MACHINE CONSTANTS FOR THE BURROUGHS 5700 SYSTEM. */

/*     DATA IMACH( 1) /   5 / */
/*     DATA IMACH( 2) /   6 / */
/*     DATA IMACH( 3) /   7 / */
/*     DATA IMACH( 4) /   6 / */
/*     DATA IMACH( 5) /  48 / */
/*     DATA IMACH( 6) /   6 / */
/*     DATA IMACH( 7) /   2 / */
/*     DATA IMACH( 8) /  39 / */
/*     DATA IMACH( 9) / O0007777777777777 / */
/*     DATA IMACH(10) /   8 / */
/*     DATA IMACH(11) /  13 / */
/*     DATA IMACH(12) / -50 / */
/*     DATA IMACH(13) /  76 / */
/*     DATA IMACH(14) /  26 / */
/*     DATA IMACH(15) / -50 / */
/*     DATA IMACH(16) /  76 / */

/*     MACHINE CONSTANTS FOR THE BURROUGHS 6700/7700 SYSTEMS. */

/*     DATA IMACH( 1) /   5 / */
/*     DATA IMACH( 2) /   6 / */
/*     DATA IMACH( 3) /   7 / */
/*     DATA IMACH( 4) /   6 / */
/*     DATA IMACH( 5) /  48 / */
/*     DATA IMACH( 6) /   6 / */
/*     DATA IMACH( 7) /   2 / */
/*     DATA IMACH( 8) /  39 / */
/*     DATA IMACH( 9) / O0007777777777777 / */
/*     DATA IMACH(10) /   8 / */
/*     DATA IMACH(11) /  13 / */
/*     DATA IMACH(12) / -50 / */
/*     DATA IMACH(13) /  76 / */
/*     DATA IMACH(14) /  26 / */
/*     DATA IMACH(15) / -32754 / */
/*     DATA IMACH(16) /  32780 / */

/*     MACHINE CONSTANTS FOR THE CDC 6000/7000 SERIES. */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    7 / */
/*     DATA IMACH( 4) /6LOUTPUT/ */
/*     DATA IMACH( 5) /   60 / */
/*     DATA IMACH( 6) /   10 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   48 / */
/*     DATA IMACH( 9) / 00007777777777777777B / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   48 / */
/*     DATA IMACH(12) / -974 / */
/*     DATA IMACH(13) / 1070 / */
/*     DATA IMACH(14) /   96 / */
/*     DATA IMACH(15) / -927 / */
/*     DATA IMACH(16) / 1070 / */

/*     MACHINE CONSTANTS FOR THE CRAY 1 */

/*     DATA IMACH( 1) /   100 / */
/*     DATA IMACH( 2) /   101 / */
/*     DATA IMACH( 3) /   102 / */
/*     DATA IMACH( 4) /   101 / */
/*     DATA IMACH( 5) /    64 / */
/*     DATA IMACH( 6) /     8 / */
/*     DATA IMACH( 7) /     2 / */
/*     DATA IMACH( 8) /    63 / */
/*     DATA IMACH( 9) /  777777777777777777777B / */
/*     DATA IMACH(10) /     2 / */
/*     DATA IMACH(11) /    48 / */
/*     DATA IMACH(12) / -8192 / */
/*     DATA IMACH(13) /  8191 / */
/*     DATA IMACH(14) /    96 / */
/*     DATA IMACH(15) / -8192 / */
/*     DATA IMACH(16) /  8191 / */

/*     MACHINE CONSTANTS FOR THE DATA GENERAL ECLIPSE S/200 */

/*     DATA IMACH( 1) /   11 / */
/*     DATA IMACH( 2) /   12 / */
/*     DATA IMACH( 3) /    8 / */
/*     DATA IMACH( 4) /   10 / */
/*     DATA IMACH( 5) /   16 / */
/*     DATA IMACH( 6) /    2 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   15 / */
/*     DATA IMACH( 9) /32767 / */
/*     DATA IMACH(10) /   16 / */
/*     DATA IMACH(11) /    6 / */
/*     DATA IMACH(12) /  -64 / */
/*     DATA IMACH(13) /   63 / */
/*     DATA IMACH(14) /   14 / */
/*     DATA IMACH(15) /  -64 / */
/*     DATA IMACH(16) /   63 / */

/*     MACHINE CONSTANTS FOR THE HARRIS 220 */

/*     DATA IMACH( 1) /       5 / */
/*     DATA IMACH( 2) /       6 / */
/*     DATA IMACH( 3) /       0 / */
/*     DATA IMACH( 4) /       6 / */
/*     DATA IMACH( 5) /      24 / */
/*     DATA IMACH( 6) /       3 / */
/*     DATA IMACH( 7) /       2 / */
/*     DATA IMACH( 8) /      23 / */
/*     DATA IMACH( 9) / 8388607 / */
/*     DATA IMACH(10) /       2 / */
/*     DATA IMACH(11) /      23 / */
/*     DATA IMACH(12) /    -127 / */
/*     DATA IMACH(13) /     127 / */
/*     DATA IMACH(14) /      38 / */
/*     DATA IMACH(15) /    -127 / */
/*     DATA IMACH(16) /     127 / */

/*     MACHINE CONSTANTS FOR THE HONEYWELL 600/6000 SERIES. */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /   43 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   36 / */
/*     DATA IMACH( 6) /    6 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   35 / */
/*     DATA IMACH( 9) / O377777777777 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   27 / */
/*     DATA IMACH(12) / -127 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   63 / */
/*     DATA IMACH(15) / -127 / */
/*     DATA IMACH(16) /  127 / */

/*     MACHINE CONSTANTS FOR THE HP 2100 */
/*     3 WORD DOUBLE PRECISION OPTION WITH FTN4 */

/*     DATA IMACH(1) /      5/ */
/*     DATA IMACH(2) /      6 / */
/*     DATA IMACH(3) /      4 / */
/*     DATA IMACH(4) /      1 / */
/*     DATA IMACH(5) /     16 / */
/*     DATA IMACH(6) /      2 / */
/*     DATA IMACH(7) /      2 / */
/*     DATA IMACH(8) /     15 / */
/*     DATA IMACH(9) /  32767 / */
/*     DATA IMACH(10)/      2 / */
/*     DATA IMACH(11)/     23 / */
/*     DATA IMACH(12)/   -128 / */
/*     DATA IMACH(13)/    127 / */
/*     DATA IMACH(14)/     39 / */
/*     DATA IMACH(15)/   -128 / */
/*     DATA IMACH(16)/    127 / */

/*     MACHINE CONSTANTS FOR THE HP 2100 */
/*     4 WORD DOUBLE PRECISION OPTION WITH FTN4 */

/*     DATA IMACH(1) /      5 / */
/*     DATA IMACH(2) /      6 / */
/*     DATA IMACH(3) /      4 / */
/*     DATA IMACH(4) /      1 / */
/*     DATA IMACH(5) /     16 / */
/*     DATA IMACH(6) /      2 / */
/*     DATA IMACH(7) /      2 / */
/*     DATA IMACH(8) /     15 / */
/*     DATA IMACH(9) /  32767 / */
/*     DATA IMACH(10)/      2 / */
/*     DATA IMACH(11)/     23 / */
/*     DATA IMACH(12)/   -128 / */
/*     DATA IMACH(13)/    127 / */
/*     DATA IMACH(14)/     55 / */
/*     DATA IMACH(15)/   -128 / */
/*     DATA IMACH(16)/    127 / */

/*     MACHINE CONSTANTS FOR THE IBM 360/370 SERIES, */
/*     THE XEROX SIGMA 5/7/9, THE SEL SYSTEMS 85/86, AND */
/*     THE PERKIN ELMER (INTERDATA) 7/32. */

/*     DATA IMACH( 1) /   5 / */
/*     DATA IMACH( 2) /   6 / */
/*     DATA IMACH( 3) /   7 / */
/*     DATA IMACH( 4) /   6 / */
/*     DATA IMACH( 5) /  32 / */
/*     DATA IMACH( 6) /   4 / */
/*     DATA IMACH( 7) /   2 / */
/*     DATA IMACH( 8) /  31 / */
/*     DATA IMACH( 9) / Z7FFFFFFF / */
/*     DATA IMACH(10) /  16 / */
/*     DATA IMACH(11) /   6 / */
/*     DATA IMACH(12) / -64 / */
/*     DATA IMACH(13) /  63 / */
/*     DATA IMACH(14) /  14 / */
/*     DATA IMACH(15) / -64 / */
/*     DATA IMACH(16) /  63 / */

/*     MACHINE CONSTANTS FOR THE PDP-10 (KA PROCESSOR). */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    5 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   36 / */
/*     DATA IMACH( 6) /    5 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   35 / */
/*     DATA IMACH( 9) / "377777777777 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   27 / */
/*     DATA IMACH(12) / -128 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   54 / */
/*     DATA IMACH(15) / -101 / */
/*     DATA IMACH(16) /  127 / */

/*     MACHINE CONSTANTS FOR THE PDP-10 (KI PROCESSOR). */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    5 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   36 / */
/*     DATA IMACH( 6) /    5 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   35 / */
/*     DATA IMACH( 9) / "377777777777 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   27 / */
/*     DATA IMACH(12) / -128 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   62 / */
/*     DATA IMACH(15) / -128 / */
/*     DATA IMACH(16) /  127 / */

/*     MACHINE CONSTANTS FOR PDP-11 FORTRAN S SUPPORTING */
/*     32-BIT INTEGER ARITHMETIC. */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    5 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   32 / */
/*     DATA IMACH( 6) /    4 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   31 / */
/*     DATA IMACH( 9) / 2147483647 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   24 / */
/*     DATA IMACH(12) / -127 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   56 / */
/*     DATA IMACH(15) / -127 / */
/*     DATA IMACH(16) /  127 / */

/*     MACHINE CONSTANTS FOR PDP-11 FORTRAN S SUPPORTING */
/*     16-BIT INTEGER ARITHMETIC. */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    5 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   16 / */
/*     DATA IMACH( 6) /    2 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   15 / */
/*     DATA IMACH( 9) / 32767 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   24 / */
/*     DATA IMACH(12) / -127 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   56 / */
/*     DATA IMACH(15) / -127 / */
/*     DATA IMACH(16) /  127 / */

/*     MACHINE CONSTANTS FOR THE UNIVAC 1100 SERIES. FTN COMPILER */


/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    1 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   36 / */
/*     DATA IMACH( 6) /    4 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   35 / */
/*     DATA IMACH( 9) / O377777777777 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   27 / */
/*     DATA IMACH(12) / -128 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   60 / */
/*     DATA IMACH(15) /-1024 / */
/*     DATA IMACH(16) / 1023 / */

/*     MACHINE CONSTANTS FOR THE UNIVAC 1100 SERIES. FOR COMPILER */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    7 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   36 / */
/*     DATA IMACH( 6) /    6 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   35 / */
/*     DATA IMACH( 9) / O377777777777 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   27 / */
/*     DATA IMACH(12) / -128 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   60 / */
/*     DATA IMACH(15) /-1024/ */
/*     DATA IMACH(16) / 1023 / */


/*     MACHINE CONSTANTS FOR THE VAX 11/780 */

/*     DATA IMACH(1) /    5 / */
/*     DATA IMACH(2) /    6 / */
/*     DATA IMACH(3) /    5 / */
/*     DATA IMACH(4) /    6 / */
/*     DATA IMACH(5) /   32 / */
/*     DATA IMACH(6) /    4 / */
/*     DATA IMACH(7) /    2 / */
/*     DATA IMACH(8) /   31 / */
/*     DATA IMACH(9) /2147483647 / */
/*     DATA IMACH(10)/    2 / */
/*     DATA IMACH(11)/   24 / */
/*     DATA IMACH(12)/ -127 / */
/*     DATA IMACH(13)/  127 / */
/*     DATA IMACH(14)/   56 / */
/*     DATA IMACH(15)/ -127 / */
/*     DATA IMACH(16)/  127 / */

/* ***FIRST EXECUTABLE STATEMENT  I1MACH */

/*<       IF (I .LT. 1  .OR.  I .GT. 16) GO TO 10 >*/
#line 537 "../fortran/slatec.f"
    if (*i__ < 1 || *i__ > 16) {
#line 537 "../fortran/slatec.f"
	goto L10;
#line 537 "../fortran/slatec.f"
    }

/*<       I1MACH=IMACH(I) >*/
#line 539 "../fortran/slatec.f"
    ret_val = imach[*i__ - 1];
/*<       RETURN >*/
#line 540 "../fortran/slatec.f"
    return ret_val;

/*<    10 CONTINUE >*/
#line 542 "../fortran/slatec.f"
L10:
/*<       WRITE(OUTPUT,9000) >*/
#line 543 "../fortran/slatec.f"
    io___9.ciunit = output;
#line 543 "../fortran/slatec.f"
    s_wsfe(&io___9);
#line 543 "../fortran/slatec.f"
    e_wsfe();
/*< 9000  FORMAT(39H1ERROR    1 IN I1MACH - I OUT OF BOUNDS ) >*/

/*     CALL FDUMP */


/*<       STOP >*/
#line 549 "../fortran/slatec.f"
    s_stop("", (ftnlen)0);
/*<       END >*/
#line 550 "../fortran/slatec.f"
    return ret_val;
} /* i1mach_ */

