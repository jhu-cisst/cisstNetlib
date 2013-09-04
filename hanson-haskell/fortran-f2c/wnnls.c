#line 1 "../fortran/wnnls.f"
/* ../fortran/wnnls.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/wnnls.f"
/* Table of constant values */

static integer c__70 = 70;
static integer c__1 = 1;
static integer c__0 = 0;
static integer c__72 = 72;
static integer c__44 = 44;
static integer c__39 = 39;

/*<        >*/
/* Subroutine */ int wnnls_(doublereal *w, integer *mdw, integer *me, integer 
	*ma, integer *n, integer *l, doublereal *prgopt, doublereal *x, 
	doublereal *rnorm, integer *mode, integer *iwork, doublereal *work)
{
    /* System generated locals */
    integer w_dim1, w_offset;

    /* Local variables */
    integer l1, l2, l3, l4, l5, lw, liw, nerr, iopt;
    doublereal dummy;
    extern /* Subroutine */ int wnlsm_(doublereal *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), xerror_(char *, integer *, integer *, integer *, 
	    ftnlen), xerrwv_(char *, integer *, integer *, integer *, integer 
	    *, integer *, integer *, integer *, doublereal *, doublereal *, 
	    ftnlen);


/*     DIMENSION W(MDW,N+1),PRGOPT(*),X(N),IWORK(M+N),WORK(M+5*N) */

/*     ABSTRACT */

/*     THIS SUBPROGRAM SOLVES A LINEARLY CONSTRAINED LEAST SQUARES */
/*     PROBLEM.  SUPPOSE THERE ARE GIVEN MATRICES E AND A OF */
/*     RESPECTIVE DIMENSIONS ME BY N AND MA BY N, AND VECTORS F */
/*     AND B OF RESPECTIVE LENGTHS ME AND MA.  THIS SUBROUTINE */
/*     SOLVES THE PROBLEM */

/*               EX = F, (EQUATIONS TO BE EXACTLY SATISFIED) */

/*               AX = B, (EQUATIONS TO BE APPROXIMATELY SATISFIED, */
/*                        IN THE LEAST SQUARES SENSE) */

/*               SUBJECT TO COMPONENTS L+1,...,N NONNEGATIVE */

/*     ANY VALUES ME.GE.0, MA.GE.0 AND 0.LE. L .LE.N ARE PERMITTED. */

/*     THE PROBLEM IS REPOSED AS PROBLEM WNNLS */

/*               (WT*E)X = (WT*F) */
/*               (   A)    (   B), (LEAST SQUARES) */
/*               SUBJECT TO COMPONENTS L+1,...,N NONNEGATIVE. */

/*     THE SUBPROGRAM CHOOSES THE HEAVY WEIGHT (OR PENALTY PARAMETER) WT. */

/*     THE PARAMETERS FOR WNNLS ARE */

/*     INPUT.. */

/*     W(*,*),MDW,  THE ARRAY W(*,*) IS DOUBLE SUBSCRIPTED WITH FIRST */
/*     ME,MA,N,L    DIMENSIONING PARAMETER EQUAL TO MDW.  FOR THIS */
/*                  DISCUSSION LET US CALL M = ME + MA.  THEN MDW */
/*                  MUST SATISFY MDW.GE.M.  THE CONDITION MDW.LT.M */
/*                  IS AN ERROR. */

/*                  THE ARRAY W(*,*) CONTAINS THE MATRICES AND VECTORS */

/*                       (E  F) */
/*                       (A  B) */

/*                  IN ROWS AND COLUMNS 1,...,M AND 1,...,N+1 */
/*                  RESPECTIVELY.  COLUMNS 1,...,L CORRESPOND TO */
/*                  UNCONSTRAINED VARIABLES X(1),...,X(L).  THE */
/*                  REMAINING VARIABLES ARE CONSTRAINED TO BE */
/*                  NONNEGATIVE.  THE CONDITION L.LT.0 .OR. L.GT.N IS */
/*                  AN ERROR. */

/*     PRGOPT(*)    THIS ARRAY IS THE OPTION VECTOR. */
/*                  IF THE USER IS SATISFIED WITH THE NOMINAL */
/*                  SUBPROGRAM FEATURES SET */

/*                  PRGOPT(1)=1 (OR PRGOPT(1)=1.0) */

/*                  OTHERWISE PRGOPT(*) IS A LINKED LIST CONSISTING OF */
/*                  GROUPS OF DATA OF THE FOLLOWING FORM */

/*                  LINK */
/*                  KEY */
/*                  DATA SET */

/*                  THE PARAMETERS LINK AND KEY ARE EACH ONE WORD. */
/*                  THE DATA SET CAN BE COMPRISED OF SEVERAL WORDS. */
/*                  THE NUMBER OF ITEMS DEPENDS ON THE VALUE OF KEY. */
/*                  THE VALUE OF LINK POINTS TO THE FIRST */
/*                  ENTRY OF THE NEXT GROUP OF DATA WITHIN */
/*                  PRGOPT(*).  THE EXCEPTION IS WHEN THERE ARE */
/*                  NO MORE OPTIONS TO CHANGE.  IN THAT */
/*                  CASE LINK=1 AND THE VALUES KEY AND DATA SET */
/*                  ARE NOT REFERENCED. THE GENERAL LAYOUT OF */
/*                  PRGOPT(*) IS AS FOLLOWS. */

/*               ...PRGOPT(1)=LINK1 (LINK TO FIRST ENTRY OF NEXT GROUP) */
/*               .  PRGOPT(2)=KEY1 (KEY TO THE OPTION CHANGE) */
/*               .  PRGOPT(3)=DATA VALUE (DATA VALUE FOR THIS CHANGE) */
/*               .       . */
/*               .       . */
/*               .       . */
/*               ...PRGOPT(LINK1)=LINK2 (LINK TO THE FIRST ENTRY OF */
/*               .                       NEXT GROUP) */
/*               .  PRGOPT(LINK1+1)=KEY2 (KEY TO THE OPTION CHANGE) */
/*               .  PRGOPT(LINK1+2)=DATA VALUE */
/*               ...     . */
/*               .       . */
/*               .       . */
/*               ...PRGOPT(LINK)=1 (NO MORE OPTIONS TO CHANGE) */

/*                  VALUES OF LINK THAT ARE NONPOSITIVE ARE ERRORS. */
/*                  A VALUE OF LINK.GT.NLINK=100000 IS ALSO AN ERROR. */
/*                  THIS HELPS PREVENT USING INVALID BUT POSITIVE */
/*                  VALUES OF LINK THAT WILL PROBABLY EXTEND */
/*                  BEYOND THE PROGRAM LIMITS OF PRGOPT(*). */
/*                  UNRECOGNIZED VALUES OF KEY ARE IGNORED.  THE */
/*                  ORDER OF THE OPTIONS IS ARBITRARY AND ANY NUMBER */
/*                  OF OPTIONS CAN BE CHANGED WITH THE FOLLOWING */
/*                  RESTRICTION.  TO PREVENT CYCLING IN THE */
/*                  PROCESSING OF THE OPTION ARRAY A COUNT OF THE */
/*                  NUMBER OF OPTIONS CHANGED IS MAINTAINED. */
/*                  WHENEVER THIS COUNT EXCEEDS NOPT=1000 AN ERROR */
/*                  MESSAGE IS PRINTED AND THE SUBPROGRAM RETURNS. */

/*                  OPTIONS.. */

/*                  KEY=6 */
/*                         SCALE THE NONZERO COLUMNS OF THE */
/*                  ENTIRE DATA MATRIX */
/*                  (E) */
/*                  (A) */
/*                  TO HAVE LENGTH ONE.  THE DATA SET FOR */
/*                  THIS OPTION IS A SINGLE VALUE.  IT MUST */
/*                  BE NONZERO IF UNIT LENGTH COLUMN SCALING IS */
/*                  DESIRED. */

/*                  KEY=7 */
/*                         SCALE COLUMNS OF THE ENTIRE DATA MATRIX */
/*                  (E) */
/*                  (A) */
/*                  WITH A USER-PROVIDED DIAGONAL MATRIX. */
/*                  THE DATA SET FOR THIS OPTION CONSISTS */
/*                  OF THE N DIAGONAL SCALING FACTORS, ONE FOR */
/*                  EACH MATRIX COLUMN. */

/*                  KEY=8 */
/*                         CHANGE THE RANK DETERMINATION TOLERANCE FROM */
/*                  THE NOMINAL VALUE OF DSQRT(EPS).  THIS QUANTITY CAN */
/*                  BE NO SMALLER THAN EPS, THE ARITHMETIC- */
/*                  STORAGE PRECISION.  THE QUANTITY USED */
/*                  HERE IS INTERNALLY RESTRICTED TO BE AT */
/*                  LEAST EPS.  THE DATA SET FOR THIS OPTION */
/*                  IS THE NEW TOLERANCE. */

/*                  KEY=9 */
/*                         CHANGE THE BLOW-UP PARAMETER FROM THE */
/*                  NOMINAL VALUE OF DSQRT(EPS).  THE RECIPROCAL OF */
/*                  THIS PARAMETER IS USED IN REJECTING SOLUTION */
/*                  COMPONENTS AS TOO LARGE WHEN A VARIABLE IS */
/*                  FIRST BROUGHT INTO THE ACTIVE SET.  TOO LARGE */
/*                  MEANS THAT THE PROPOSED COMPONENT TIMES THE */
/*                  RECIPROCAL OF THE PARAMETERIS NOT LESS THAN */
/*                  THE RATIO OF THE NORMS OF THE RIGHT-SIDE */
/*                  VECTOR AND THE DATA MATRIX. */
/*                  THIS PARAMETER CAN BE NO SMALLER THAN EPS, */
/*                  THE ARITHMETIC-STORAGE PRECISION. */

/*                  FOR EXAMPLE, SUPPOSE WE WANT TO PROVIDE */
/*                  A DIAGONAL MATRIX TO SCALE THE PROBLEM */
/*                  MATRIX AND CHANGE THE TOLERANCE USED FOR */
/*                  DETERMINING LINEAR DEPENDENCE OF DROPPED COL */
/*                  VECTORS.  FOR THESE OPTIONS THE DIMENSIONS OF */
/*                  PRGOPT(*) MUST BE AT LEAST N+6.  THE FORTRAN */
/*                  STATEMENTS DEFINING THESE OPTIONS WOULD */
/*                  BE AS FOLLOWS. */

/*                  PRGOPT(1)=N+3 (LINK TO ENTRY N+3 IN PRGOPT(*)) */
/*                  PRGOPT(2)=7 (USER-PROVIDED SCALING KEY) */

/*                  CALL DCOPY(N,D,1,PRGOPT(3),1) (COPY THE N */
/*                  SCALING FACTORS FROM A USER ARRAY CALLED D(*) */
/*                  INTO PRGOPT(3)-PRGOPT(N+2)) */

/*                  PRGOPT(N+3)=N+6 (LINK TO ENTRY N+6 OF PRGOPT(*)) */
/*                  PRGOPT(N+4)=8 (LINEAR DEPENDENCE TOLERANCE KEY) */
/*                  PRGOPT(N+5)=... (NEW VALUE OF THE TOLERANCE) */

/*                  PRGOPT(N+6)=1 (NO MORE OPTIONS TO CHANGE) */

/*     IWORK(1),    THE AMOUNTS OF WORKING STORAGE ACTUALLY ALLOCATED */
/*     IWORK(2)     FOR THE WORKING ARRAYS WORK(*) AND IWORK(*), */
/*                  RESPECTIVELY.  THESE QUANTITIES ARE COMPARED WITH */
/*                  THE ACTUAL AMOUNTS OF STORAGE NEEDED FOR WNNLS( ). */
/*                  INSUFFICIENT STORAGE ALLOCATED FOR EITHER WORK(*) */
/*                  OR IWORK(*) IS CONSIDERED AN ERROR.  THIS FEATURE */
/*                  WAS INCLUDED IN WNNLS( ) BECAUSE MISCALCULATING */
/*                  THE STORAGE FORMULAS FOR WORK(*) AND IWORK(*) */
/*                  MIGHT VERY WELL LEAD TO SUBTLE AND HARD-TO-FIND */
/*                  EXECUTION ERRORS. */

/*                  THE LENGTH OF WORK(*) MUST BE AT LEAST */

/*                  LW = ME+MA+5*N */
/*                  THIS TEST WILL NOT BE MADE IF IWORK(1).LE.0. */

/*                  THE LENGTH OF IWORK(*) MUST BE AT LEAST */

/*                  LIW = ME+MA+N */
/*                  THIS TEST WILL NOT BE MADE IF IWORK(2).LE.0. */

/*     OUTPUT.. */

/*     X(*)         AN ARRAY DIMENSIONED AT LEAST N, WHICH WILL */
/*                  CONTAIN THE N COMPONENTS OF THE SOLUTION VECTOR */
/*                  ON OUTPUT. */

/*     RNORM        THE RESIDUAL NORM OF THE SOLUTION.  THE VALUE OF */
/*                  RNORM CONTAINS THE RESIDUAL VECTOR LENGTH OF THE */
/*                  EQUALITY CONSTRAINTS AND LEAST SQUARES EQUATIONS. */

/*     MODE         THE VALUE OF MODE INDICATES THE SUCCESS OR FAILURE */
/*                  OF THE SUBPROGRAM. */

/*                  MODE = 0  SUBPROGRAM COMPLETED SUCCESSFULLY. */

/*                       = 1  MAX. NUMBER OF ITERATIONS (EQUAL TO */
/*                            3*(N-L)) EXCEEDED. NEARLY ALL PROBLEMS */
/*                            SHOULD COMPLETE IN FEWER THAN THIS */
/*                            NUMBER OF ITERATIONS. AN APPROXIMATE */
/*                            SOLUTION AND ITS CORRESPONDING RESIDUAL */
/*                            VECTOR LENGTH ARE IN X(*) AND RNORM. */

/*                       = 2  USAGE ERROR OCCURRED.  THE OFFENDING */
/*                            CONDITION IS NOTED WITH THE ERROR */
/*                            PROCESSING SUBPROGRAM, XERROR( ). */

/*     USER-DESIGNATED */
/*     WORKING ARRAYS.. */

/*     WORK(*)      A WORKING ARRAY OF LENGTH AT LEAST */
/*                  M + 5*N. */

/*     IWORK(*)     AN INTEGER-VALUED WORKING ARRAY OF LENGTH AT LEAST */
/*                  M+N. */

/*     THE EDITING REQUIRED TO CONVERT THIS SUBROUTINE FROM SINGLE TO */
/*     DOUBLE PRECISION INVOLVES THE FOLLOWING CHARACTER STRING CHANGES. */
/*     USE AN EDITING COMMAND (CHANGE) /STRING-1/(TO)STRING-2/. */
/*     (START AT LINE WITH C++ IN COLS. 1-3.) */
/*     /REAL (12 BLANKS)/DOUBLE PRECISION/,/, DUMMY/,SNGL(DUMMY)/ */

/*     WRITTEN BY KAREN H. HASKELL, SANDIA LABORATORIES, */
/*     AND R.J. HANSON, SANDIA LABORATORIES. */
/*     REVISED FEB.25, 1982. */

/*     SUBROUTINES CALLED BY WNNLS( ) */

/* ++ */
/*     WNLSM         COMPANION SUBROUTINE TO WNNLS( ), WHERE */
/*                   MOST OF THE COMPUTATION TAKES PLACE. */

/*     XERROR,XERRWV FROM SLATEC ERROR PROCESSING PACKAGE. */
/*                   THIS IS DOCUMENTED IN SANDIA TECH. REPT., */
/*                   SAND78-1189. */

/*     REFERENCES */

/*     1. SOLVING LEAST SQUARES PROBLEMS, BY C.L. LAWSON */
/*        AND R.J. HANSON.  PRENTICE-HALL, INC. (1974). */

/*     2. BASIC LINEAR ALGEBRA SUBPROGRAMS FOR FORTRAN USAGE, BY */
/*        C.L. LAWSON, R.J. HANSON, D.R. KINCAID, AND F.T. KROGH. */
/*        TOMS, V. 5, NO. 3, P. 308.  ALSO AVAILABLE AS */
/*        SANDIA TECHNICAL REPORT NO. SAND77-0898. */

/*     3. AN ALGORITHM FOR LINEAR LEAST SQUARES WITH EQUALITY */
/*        AND NONNEGATIVITY CONSTRAINTS, BY K.H. HASKELL AND */
/*        R.J. HANSON.  AVAILABLE AS SANDIA TECHNICAL REPORT NO. */
/*        SAND77-0552, AND MATH. PROGRAMMING, VOL. 21, (1981), P. 98-118. */

/*     4. SLATEC COMMON MATH. LIBRARY ERROR HANDLING */
/*        PACKAGE.  BY R. E. JONES.  AVAILABLE AS SANDIA */
/*        TECHNICAL REPORT SAND78-1189. */

/*<       DOUBLE PRECISION  DUMMY, W(MDW,1), PRGOPT(1), X(1), WORK(1), RNORM >*/
/*<       INTEGER IWORK(1) >*/


/*<       MODE = 0 >*/
#line 270 "../fortran/wnnls.f"
    /* Parameter adjustments */
#line 270 "../fortran/wnnls.f"
    w_dim1 = *mdw;
#line 270 "../fortran/wnnls.f"
    w_offset = 1 + w_dim1;
#line 270 "../fortran/wnnls.f"
    w -= w_offset;
#line 270 "../fortran/wnnls.f"
    --prgopt;
#line 270 "../fortran/wnnls.f"
    --x;
#line 270 "../fortran/wnnls.f"
    --iwork;
#line 270 "../fortran/wnnls.f"
    --work;
#line 270 "../fortran/wnnls.f"

#line 270 "../fortran/wnnls.f"
    /* Function Body */
#line 270 "../fortran/wnnls.f"
    *mode = 0;
/*<       IF (MA+ME.LE.0 .OR. N.LE.0) RETURN >*/
#line 271 "../fortran/wnnls.f"
    if (*ma + *me <= 0 || *n <= 0) {
#line 271 "../fortran/wnnls.f"
	return 0;
#line 271 "../fortran/wnnls.f"
    }
/*<       IF (.NOT.(IWORK(1).GT.0)) GO TO 20 >*/
#line 272 "../fortran/wnnls.f"
    if (! (iwork[1] > 0)) {
#line 272 "../fortran/wnnls.f"
	goto L20;
#line 272 "../fortran/wnnls.f"
    }
/*<       LW = ME + MA + 5*N >*/
#line 273 "../fortran/wnnls.f"
    lw = *me + *ma + *n * 5;
/*<       IF (.NOT.(IWORK(1).LT.LW)) GO TO 10 >*/
#line 274 "../fortran/wnnls.f"
    if (! (iwork[1] < lw)) {
#line 274 "../fortran/wnnls.f"
	goto L10;
#line 274 "../fortran/wnnls.f"
    }
/*<       NERR = 2 >*/
#line 275 "../fortran/wnnls.f"
    nerr = 2;
/*<       IOPT = 1 >*/
#line 276 "../fortran/wnnls.f"
    iopt = 1;
/*<        >*/
#line 277 "../fortran/wnnls.f"
    xerrwv_("WNNLS( ), INSUFFICIENT STORAGE ALLOCATED FOR WORK(*), NEED LW=I"\
	    "1 BELOW", &c__70, &nerr, &iopt, &c__1, &lw, &c__0, &c__0, &dummy, 
	    &dummy, (ftnlen)70);
/*<       MODE = 2 >*/
#line 279 "../fortran/wnnls.f"
    *mode = 2;
/*<       RETURN >*/
#line 280 "../fortran/wnnls.f"
    return 0;
/*<    10 CONTINUE >*/
#line 281 "../fortran/wnnls.f"
L10:
/*<    20 IF (.NOT.(IWORK(2).GT.0)) GO TO 40 >*/
#line 282 "../fortran/wnnls.f"
L20:
#line 282 "../fortran/wnnls.f"
    if (! (iwork[2] > 0)) {
#line 282 "../fortran/wnnls.f"
	goto L40;
#line 282 "../fortran/wnnls.f"
    }
/*<       LIW = ME + MA + N >*/
#line 283 "../fortran/wnnls.f"
    liw = *me + *ma + *n;
/*<       IF (.NOT.(IWORK(2).LT.LIW)) GO TO 30 >*/
#line 284 "../fortran/wnnls.f"
    if (! (iwork[2] < liw)) {
#line 284 "../fortran/wnnls.f"
	goto L30;
#line 284 "../fortran/wnnls.f"
    }
/*<       NERR = 2 >*/
#line 285 "../fortran/wnnls.f"
    nerr = 2;
/*<       IOPT = 1 >*/
#line 286 "../fortran/wnnls.f"
    iopt = 1;
/*<        >*/
#line 287 "../fortran/wnnls.f"
    xerrwv_("WNNLS( ), INSUFFICIENT STORAGE ALLOCATED FOR IWORK(*), NEED LIW"\
	    "=I1 BELOW", &c__72, &nerr, &iopt, &c__1, &liw, &c__0, &c__0, &
	    dummy, &dummy, (ftnlen)72);
/*<       MODE = 2 >*/
#line 289 "../fortran/wnnls.f"
    *mode = 2;
/*<       RETURN >*/
#line 290 "../fortran/wnnls.f"
    return 0;
/*<    30 CONTINUE >*/
#line 291 "../fortran/wnnls.f"
L30:
/*<    40 IF (.NOT.(MDW.LT.ME+MA)) GO TO 50 >*/
#line 292 "../fortran/wnnls.f"
L40:
#line 292 "../fortran/wnnls.f"
    if (! (*mdw < *me + *ma)) {
#line 292 "../fortran/wnnls.f"
	goto L50;
#line 292 "../fortran/wnnls.f"
    }
/*<       NERR = 1 >*/
#line 293 "../fortran/wnnls.f"
    nerr = 1;
/*<       IOPT = 1 >*/
#line 294 "../fortran/wnnls.f"
    iopt = 1;
/*<        >*/
#line 295 "../fortran/wnnls.f"
    xerror_("WNNLS( ), THE VALUE MDW.LT.ME+MA IS AN ERROR", &c__44, &nerr, &
	    iopt, (ftnlen)44);
/*<       MODE = 2 >*/
#line 297 "../fortran/wnnls.f"
    *mode = 2;
/*<       RETURN >*/
#line 298 "../fortran/wnnls.f"
    return 0;
/*<    50 IF (0.LE.L .AND. L.LE.N) GO TO 60 >*/
#line 299 "../fortran/wnnls.f"
L50:
#line 299 "../fortran/wnnls.f"
    if (0 <= *l && *l <= *n) {
#line 299 "../fortran/wnnls.f"
	goto L60;
#line 299 "../fortran/wnnls.f"
    }
/*<       NERR = 2 >*/
#line 300 "../fortran/wnnls.f"
    nerr = 2;
/*<       IOPT = 1 >*/
#line 301 "../fortran/wnnls.f"
    iopt = 1;
/*<        >*/
#line 302 "../fortran/wnnls.f"
    xerror_("WNNLS( ), L.LE.0.AND.L.LE.N IS REQUIRED", &c__39, &nerr, &iopt, (
	    ftnlen)39);
/*<       MODE = 2 >*/
#line 304 "../fortran/wnnls.f"
    *mode = 2;
/*<       RETURN >*/
#line 305 "../fortran/wnnls.f"
    return 0;

/*     THE PURPOSE OF THIS SUBROUTINE IS TO BREAK UP THE ARRAYS */
/*     WORK(*) AND IWORK(*) INTO SEPARATE WORK ARRAYS */
/*     REQUIRED BY THE MAIN SUBROUTINE WNLSM( ). */

/*<    60 L1 = N + 1 >*/
#line 311 "../fortran/wnnls.f"
L60:
#line 311 "../fortran/wnnls.f"
    l1 = *n + 1;
/*<       L2 = L1 + N >*/
#line 312 "../fortran/wnnls.f"
    l2 = l1 + *n;
/*<       L3 = L2 + ME + MA >*/
#line 313 "../fortran/wnnls.f"
    l3 = l2 + *me + *ma;
/*<       L4 = L3 + N >*/
#line 314 "../fortran/wnnls.f"
    l4 = l3 + *n;
/*<       L5 = L4 + N >*/
#line 315 "../fortran/wnnls.f"
    l5 = l4 + *n;

/*<        >*/
#line 317 "../fortran/wnnls.f"
    wnlsm_(&w[w_offset], mdw, me, ma, n, l, &prgopt[1], &x[1], rnorm, mode, &
	    iwork[1], &iwork[l1], &work[1], &work[l1], &work[l2], &work[l3], &
	    work[l4], &work[l5]);
/*<       RETURN >*/
#line 320 "../fortran/wnnls.f"
    return 0;
/*<       END >*/
} /* wnnls_ */

