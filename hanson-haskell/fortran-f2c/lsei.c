#line 1 "../fortran/lsei.f"
/* ../fortran/lsei.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran/lsei.f"
/* Table of constant values */

static integer c__67 = 67;
static integer c__1 = 1;
static integer c__0 = 0;
static integer c__68 = 68;
static integer c__36 = 36;
static integer c__54 = 54;
static integer c__2 = 2;
static integer c__38 = 38;
static integer c__52 = 52;

/*     ALGORITHM 587, COLLECTED ALGORITHMS FROM ACM. */
/*     ALGORITHM APPEARED IN ACM-TRANS. MATH. SOFTWARE, VOL. 8, NO. 3, */
/*     SEP., 1982, P.323. */
/*<        >*/
/* Subroutine */ int lsei_(doublereal *w, integer *mdw, integer *me, integer *
	ma, integer *mg, integer *n, doublereal *prgopt, doublereal *x, 
	doublereal *rnorme, doublereal *rnorml, integer *mode, doublereal *ws,
	 integer *ip)
{
    /* Initialized data */

    static doublereal zero = 0.;
    static doublereal drelpr = 0.;
    static doublereal half = .5;
    static doublereal one = 1.;

    /* Format strings */
    static char fmt_90[] = "";

    /* System generated locals */
    integer w_dim1, w_offset, i__1, i__2, i__3;
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    integer i__, j, k, l, m;
    doublereal t;
    integer n1, n2;
    extern /* Subroutine */ int h12_(integer *, integer *, integer *, integer 
	    *, doublereal *, integer *, doublereal *, doublereal *, integer *,
	     integer *, integer *);
    integer ii;
    doublereal rb;
    integer kk, jj;
    doublereal uj, rn, sn, vj, up;
    integer jp1, np1;
    doublereal gam;
    logical cov;
    doublereal tau;
    extern /* Subroutine */ int lsi_(doublereal *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    integer key, mep1, lchk, mend;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    integer link, imax, last, nerr;
    doublereal size;
    integer iopt, next, nopt, igo990;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    integer mdeqc;
    extern doublereal dasum_(integer *, doublereal *, integer *);
    integer nlink;
    extern /* Subroutine */ int dswap_(integer *, doublereal *, integer *, 
	    doublereal *, integer *), dcopy_(integer *, doublereal *, integer 
	    *, doublereal *, integer *);
    doublereal enorm, fnorm, rnmax, snmax;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    doublereal xnrme, dummy, xnorm;
    integer mapke1, kranke, ntimes;
    extern /* Subroutine */ int xerror_(char *, integer *, integer *, integer 
	    *, ftnlen), xerrwv_(char *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, ftnlen);

    /* Assigned format variables */
    static char *igo990_fmt;


/*     DIMENSION W(MDW,N+1),PRGOPT(*),X(N), */
/*     WS(2*(ME+N)+K+(MG+2)*(N+7)),IP(MG+2*N+2) */
/*     ABOVE, K=MAX(MA+MG,N). */

/*     DABSTRACT */

/*     THIS SUBPROGRAM SOLVES A LINEARLY CONSTRAINED LEAST SQUARES */
/*     PROBLEM WITH BOTH EQUALITY AND INEQUALITY CONSTRAINTS, AND, IF THE */
/*     USER REQUESTS, OBTAINS A COVARIANCE MATRIX OF THE SOLUTION */
/*     PARAMETERS. */

/*     SUPPOSE THERE ARE GIVEN MATRICES E, A AND G OF RESPECTIVE */
/*     DIMENSIONS ME BY N, MA BY N AND MG BY N, AND VECTORS F, B AND H OF */
/*     RESPECTIVE LENGTHS ME, MA AND MG.  THIS SUBROUTINE SOLVES THE */
/*     LINEARLY CONSTRAINED LEAST SQUARES PROBLEM */

/*                   EX = F, (E ME BY N) (EQUATIONS TO BE EXACTLY */
/*                                       SATISFIED) */
/*                   AX = B, (A MA BY N) (EQUATIONS TO BE */
/*                                       APPROXIMATELY SATISFIED, */
/*                                       LEAST SQUARES SENSE) */
/*                   GX.GE.H,(G MG BY N) (INEQUALITY CONSTRAINTS) */

/*     THE INEQUALITIES GX.GE.H MEAN THAT EVERY COMPONENT OF THE PRODUCT */
/*     GX MUST BE .GE. THE CORRESPONDING COMPONENT OF H. */

/*     IN CASE THE EQUALITY CONSTRAINTS CANNOT BE SATISFIED, A */
/*     GENERALIZED INVERSE SOLUTION RESIDUAL VECTOR LENGTH IS OBTAINED */
/*     FOR F-EX. THIS IS THE MINIMAL LENGTH POSSIBLE FOR F-EX. */


/*     ANY VALUES ME.GE.0, MA.GE.0, OR MG.GE.0 ARE PERMITTED.  THE */
/*     RANK OF THE MATRIX E IS ESTIMATED DURING THE COMPUTATION. WE CALL */
/*     THIS VALUE KRANKE. IT IS AN OUTPUT PARAMETER IN IP(1) DEFINED */
/*     BELOW. USING A GENERALIZED INVERSE SOLUTION OF EX=F, A REDUCED */
/*     LEAST SQUARES PROBLEM WITH INEQUALITY CONSTRAINTS IS OBTAINED. */
/*     THE TOLERANCES USED IN THESE TESTS FOR DETERMINING THE RANK */
/*     OF E AND THE RANK OF THE REDUCED LEAST SQUARES PROBLEM ARE */
/*     GIVEN IN SANDIA TECH. REPT. SAND 78-1290. THEY CAN BE */
/*     MODIFIED BY THE USER IF NEW VALUES ARE PROVIDED IN */
/*     THE OPTION LIST OF THE ARRAY PRGOPT(*). */

/*     THE EDITING REQUIRED TO CONVERT THIS SUBROUTINE FROM SINGLE TO */
/*     DOUBLE PRECISION INVOLVES THE FOLLOWING CHARACTER STRING CHANGES. */
/*     USE AN EDITING COMMAND (CHANGE) /STRING-1/(TO)STRING-2/. */
/*     (START EDITING AT LINE WITH C++ IN COLS. 1-3.) */
/*     /REAL (12 BLANKS)/DOUBLE PRECISION/,/DASUM/DASUM/,/DDOT/DDOT/, */
/*     /DNRM2/DNRM2/,/ DSQRT/ DSQRT/,/ DABS/ DABS/,/DMAX1/DMAX1/, */
/*     /DCOPY/DCOPY/,/DSCAL/DSCAL/,/DAXPY/DAXPY/,/DSWAP/DSWAP/,/D0/D0/, */
/*     /, DUMMY/,SNGL(DUMMY)/,/DRELPR/DRELPR/ */

/*     WRITTEN BY R. J. HANSON AND K. H. HASKELL.  FOR FURTHER MATH. */
/*     AND ALGORITHMIC DETAILS SEE SANDIA LABORATORIES TECH. REPTS. */
/*     SAND 77-0552, (1978), SAND 78-1290, (1979), AND */
/*     MATH. PROGRAMMING, VOL. 21, (1981), P.98-118. */

/*     THE USER MUST DIMENSION ALL ARRAYS APPEARING IN THE CALL LIST.. */
/*     W(MDW,N+1),PRGOPT(*),X(N),WS(2*(ME+N)+K+(MG+2)*(N+7)),IP(MG+2*N+2) */
/*     WHERE K=MAX(MA+MG,N).  THIS ALLOWS FOR A SOLUTION OF A RANGE OF */
/*     PROBLEMS IN THE GIVEN WORKING SPACE.  THE DIMENSION OF WS(*) */
/*     GIVEN IS A NECESSARY OVERESTIMATE.  ONCE A PARTICULAR PROBLEM */
/*     HAS BEEN RUN, THE OUTPUT PARAMETER IP(3) GIVES THE ACTUAL */
/*     DIMENSION REQUIRED FOR THAT PROBLEM. */

/*     THE PARAMETERS FOR LSEI( ) ARE */

/*     INPUT.. */

/*     W(*,*),MDW,   THE ARRAY W(*,*) IS DOUBLY SUBSCRIPTED WITH */
/*     ME,MA,MG,N    FIRST DIMENSIONING PARAMETER EQUAL TO MDW. */
/*                   FOR THIS DISCUSSION LET US CALL M = ME+MA+MG.  THEN */
/*                   MDW MUST SATISFY MDW.GE.M.  THE CONDITION */
/*                   MDW.LT.M IS AN ERROR. */

/*                   THE ARRAY W(*,*) CONTAINS THE MATRICES AND VECTORS */

/*                                  (E  F) */
/*                                  (A  B) */
/*                                  (G  H) */

/*                   IN ROWS AND COLUMNS 1,...,M AND 1,...,N+1 */
/*                   RESPECTIVELY. */

/*                   THE INTEGERS ME, MA, AND MG ARE THE */
/*                   RESPECTIVE MATRIX ROW DIMENSIONS */
/*                   OF E, A AND G. EACH MATRIX HAS N COLUMNS. */

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

/*                  KEY=1 */
/*                         COMPUTE IN W(*,*) THE N BY N */
/*                  COVARIANCE MATRIX OF THE SOLUTION VARIABLES */
/*                  AS AN OUTPUT PARAMETER.  NOMINALLY THE */
/*                  COVARIANCE MATRIX WILL NOT BE COMPUTED. */
/*                  (THIS REQUIRES NO USER INPUT.) */
/*                  THE DATA SET FOR THIS OPTION IS A SINGLE VALUE. */
/*                  IT MUST BE NONZERO WHEN THE COVARIANCE MATRIX */
/*                  IS DESIRED.  IF IT IS ZERO, THE COVARIANCE */
/*                  MATRIX IS NOT COMPUTED.  WHEN THE COVARIANCE MATRIX */
/*                  IS COMPUTED, THE FIRST DIMENSIONING PARAMETER */
/*                  OF THE ARRAY W(*,*) MUST SATISFY MDW.GE.MAX0(M,N). */

/*                  KEY=2 */
/*                         SCALE THE NONZERO COLUMNS OF THE */
/*                         ENTIRE DATA MATRIX. */
/*                  (E) */
/*                  (A) */
/*                  (G) */

/*                  TO HAVE LENGTH ONE.  THE DATA SET FOR THIS */
/*                  OPTION IS A SINGLE VALUE.  IT MUST BE */
/*                  NONZERO IF UNIT LENGTH COLUMN SCALING */
/*                  IS DESIRED. */

/*                  KEY=3 */
/*                         SCALE COLUMNS OF THE ENTIRE DATA MATRIX */
/*                  (E) */
/*                  (A) */
/*                  (G) */

/*                  WITH A USER-PROVIDED DIAGONAL MATRIX. */
/*                  THE DATA SET FOR THIS OPTION CONSISTS */
/*                  OF THE N DIAGONAL SCALING FACTORS, ONE FOR */
/*                  EACH MATRIX COLUMN. */

/*                  KEY=4 */
/*                         CHANGE THE RANK DETERMINATION TOLERANCE FOR */
/*                  THE EQUALITY CONSTRAINT EQUATIONS FROM */
/*                  THE NOMINAL VALUE OF DSQRT(DRELPR).  THIS QUANTITY CAN */
/*                  BE NO SMALLER THAN DRELPR, THE ARITHMETIC- */
/*                  STORAGE PRECISION.  THE QUANTITY DRELPR IS THE */
/*                  LARGEST POSITIVE NUMBER SUCH THAT T=1.+DRELPR */
/*                  SATISFIES T.EQ.1.  THE QUANTITY USED */
/*                  HERE IS INTERNALLY RESTRICTED TO BE AT */
/*                  LEAST DRELPR.  THE DATA SET FOR THIS OPTION */
/*                  IS THE NEW TOLERANCE. */

/*                  KEY=5 */
/*                         CHANGE THE RANK DETERMINATION TOLERANCE FOR */
/*                  THE REDUCED LEAST SQUARES EQUATIONS FROM */
/*                  THE NOMINAL VALUE OF DSQRT(DRELPR).  THIS QUANTITY CAN */
/*                  BE NO SMALLER THAN DRELPR, THE ARITHMETIC- */
/*                  STORAGE PRECISION.  THE QUANTITY USED */
/*                  HERE IS INTERNALLY RESTRICTED TO BE AT */
/*                  LEAST DRELPR.  THE DATA SET FOR THIS OPTION */
/*                  IS THE NEW TOLERANCE. */

/*                  FOR EXAMPLE, SUPPOSE WE WANT TO CHANGE */
/*                  THE TOLERANCE FOR THE REDUCED LEAST SQUARES */
/*                  PROBLEM, COMPUTE THE COVARIANCE MATRIX OF */
/*                  THE SOLUTION PARAMETERS, AND PROVIDE */
/*                  COLUMN SCALING FOR THE DATA MATRIX.  FOR */
/*                  THESE OPTIONS THE DIMENSION OF PRGOPT(*) */
/*                  MUST BE AT LEAST N+9.  THE FORTRAN STATEMENTS */
/*                  DEFINING THESE OPTIONS WOULD BE AS FOLLOWS. */

/*                  PRGOPT(1)=4 (LINK TO ENTRY 4 IN PRGOPT(*)) */
/*                  PRGOPT(2)=1 (COVARIANCE MATRIX KEY) */
/*                  PRGOPT(3)=1 (COVARIANCE MATRIX WANTED) */

/*                  PRGOPT(4)=7 (LINK TO ENTRY 7 IN PRGOPT(*)) */
/*                  PRGOPT(5)=5 (LEAST SQUARES EQUAS. TOLERANCE KEY) */
/*                  PRGOPT(6)=... (NEW VALUE OF THE TOLERANCE) */

/*                  PRGOPT(7)=N+9 (LINK TO ENTRY N+9 IN PRGOPT(*)) */
/*                  PRGOPT(8)=3 (USER-PROVIDED COLUMN SCALING KEY) */

/*                  CALL DCOPY(N,D,1,PRGOPT(9),1)  (COPY THE N */
/*                    SCALING FACTORS FROM THE USER ARRAY D(*) */
/*                    TO PRGOPT(9)-PRGOPT(N+8)) */

/*                  PRGOPT(N+9)=1 (NO MORE OPTIONS TO CHANGE) */

/*                  THE CONTENTS OF PRGOPT(*) ARE NOT MODIFIED */
/*                  BY THE SUBPROGRAM. */
/*                  THE OPTIONS FOR WNNLS( ) CAN ALSO BE INCLUDED */
/*                  IN THIS ARRAY.  THE VALUES OF KEY RECOGNIZED */
/*                  BY WNNLS( ) ARE 6, 7 AND 8.  THEIR FUNCTIONS */
/*                  ARE DOCUMENTED IN THE USAGE INSTRUCTIONS FOR */
/*                  SUBROUTINE WNNLS( ).  NORMALLY THESE OPTIONS */
/*                  DO NOT NEED TO BE MODIFIED WHEN USING LSEI( ). */

/*     IP(1),       THE AMOUNTS OF WORKING STORAGE ACTUALLY */
/*     IP(2)        ALLOCATED FOR THE WORKING ARRAYS WS(*) AND */
/*                  IP(*), RESPECTIVELY.  THESE QUANTITIES ARE */
/*                  COMPARED WITH THE ACTUAL AMOUNTS OF STORAGE */
/*                  NEEDED BY LSEI( ).  INSUFFICIENT STORAGE */
/*                  ALLOCATED FOR EITHER WS(*) OR IP(*) IS AN */
/*                  ERROR.  THIS FEATURE WAS INCLUDED IN LSEI( ) */
/*                  BECAUSE MISCALCULATING THE STORAGE FORMULAS */
/*                  FOR WS(*) AND IP(*) MIGHT VERY WELL LEAD TO */
/*                  SUBTLE AND HARD-TO-FIND EXECUTION ERRORS. */

/*                  THE LENGTH OF WS(*) MUST BE AT LEAST */

/*                  LW = 2*(ME+N)+K+(MG+2)*(N+7) */


/*                  WHERE K = MAX(MA+MG,N) */
/*                  THIS TEST WILL NOT BE MADE IF IP(1).LE.0. */

/*                  THE LENGTH OF IP(*) MUST BE AT LEAST */

/*                  LIP = MG+2*N+2 */
/*                  THIS TEST WILL NOT BE MADE IF IP(2).LE.0. */

/*     OUTPUT.. */

/*     X(*),RNORME,  THE ARRAY X(*) CONTAINS THE SOLUTION PARAMETERS */
/*     RNORML        IF THE INTEGER OUTPUT FLAG MODE = 0 OR 1. */
/*                   THE DEFINITION OF MODE IS GIVEN DIRECTLY BELOW. */
/*                   WHEN MODE = 0 OR 1, RNORME AND RNORML */
/*                   RESPECTIVELY CONTAIN THE RESIDUAL VECTOR */
/*                   EUCLIDEAN LENGTHS OF F - EX AND B - AX.  WHEN */
/*                   MODE=1 THE EQUALITY CONSTRAINT EQUATIONS EX=F */
/*                   ARE CONTRADICTORY, SO RNORME.NE.0. THE RESIDUAL */
/*                   VECTOR F-EX HAS MINIMAL EUCLIDEAN LENGTH. FOR */
/*                   MODE.GE.2, NONE OF THESE PARAMETERS ARE */
/*                   DEFINED. */

/*     MODE          INTEGER FLAG THAT INDICATES THE SUBPROGRAM */
/*                   STATUS AFTER COMPLETION.  IF MODE.GE.2, NO */
/*                   SOLUTION HAS BEEN COMPUTED. */

/*                   MODE = */

/*                   0  BOTH EQUALITY AND INEQUALITY CONSTRAINTS */
/*                      ARE COMPATIBLE AND HAVE BEEN SATISFIED. */

/*                   1  EQUALITY CONSTRAINTS ARE CONTRADICTORY. */
/*                      A GENERALIZED INVERSE SOLUTION OF EX=F WAS USED */
/*                      TO MINIMIZE THE RESIDUAL VECTOR LENGTH F-EX. */
/*                      IN THIS SENSE, THE SOLUTION IS STILL MEANINGFUL. */

/*                   2  INEQUALITY CONSTRAINTS ARE CONTRADICTORY. */

/*                   3  BOTH EQUALITY AND INEQUALITY CONSTRAINTS */
/*                      ARE CONTRADICTORY. */

/*                   THE FOLLOWING INTERPRETATION OF */
/*                   MODE=1,2 OR 3 MUST BE MADE.  THE */
/*                   SETS CONSISTING OF ALL SOLUTIONS */
/*                   OF THE EQUALITY CONSTRAINTS EX=F */
/*                   AND ALL VECTORS SATISFYING GX.GE.H */
/*                   HAVE NO POINTS ON COMMON.  (IN */
/*                   PARTICULAR THIS DOES NOT SAY THAT */
/*                   EACH INDIVIDUAL SET HAS NO POINTS */
/*                   AT ALL, ALTHOUGH THIS COULD BE THE */
/*                   CASE.) */

/*                   4  USAGE ERROR OCCURRED.  THE VALUE */
/*                      OF MDW IS .LT. ME+MA+MG, MDW IS */
/*                      .LT. N AND A COVARIANCE MATRIX IS */
/*                      REQUESTED, THE OPTION VECTOR */
/*                      PRGOPT(*) IS NOT PROPERLY DEFINED, */
/*                      OR THE LENGTHS OF THE WORKING ARRAYS */
/*                      WS(*) AND IP(*), WHEN SPECIFIED IN */
/*                      IP(1) AND IP(2) RESPECTIVELY, ARE NOT */
/*                      LONG ENOUGH. */

/*     W(*,*)        THE ARRAY W(*,*) CONTAINS THE N BY N SYMMETRIC */
/*                   COVARIANCE MATRIX OF THE SOLUTION PARAMETERS, */
/*                   PROVIDED THIS WAS REQUESTED ON INPUT WITH */
/*                   THE OPTION VECTOR PRGOPT(*) AND THE OUTPUT */
/*                   FLAG IS RETURNED WITH MODE = 0 OR 1. */

/*     IP(*)         THE INTEGER WORKING ARRAY HAS THREE ENTRIES */
/*                   THAT PROVIDE RANK AND WORKING ARRAY LENGTH */
/*                   INFORMATION AFTER COMPLETION. */

/*                      IP(1) = RANK OF EQUALITY CONSTRAINT */
/*                              MATRIX.  DEFINE THIS QUANTITY */
/*                              AS KRANKE. */

/*                      IP(2) = RANK OF REDUCED LEAST SQUARES */
/*                              PROBLEM. */

/*                      IP(3) = THE AMOUNT OF STORAGE IN THE */
/*                              WORKING ARRAY WS(*) THAT WAS */
/*                              ACTUALLY USED BY THE SUBPROGRAM. */
/*                              THE FORMULA GIVEN ABOVE FOR THE LENGTH */
/*                              OF WS(*) IS A NECESSARY OVERESTIMATE. */
/*     USER DESIGNATED */
/*     WORKING ARRAYS.. */

/*     WS(*),IP(*)              THESE ARE RESP. TYPE FLOATING POINT */
/*                              AND TYPE INTEGER WORKING ARRAYS. */
/*                              THEIR REQUIRED MINIMAL LENGTHS ARE */
/*                              GIVEN ABOVE. */


/*     SUBROUTINES CALLED */

/*     LSI           PART OF THIS PACKAGE.  SOLVES A */
/*                   CONSTRAINED LEAST SQUARES PROBLEM WITH */
/*                   INEQUALITY CONSTRAINTS. */

/* ++ */
/*     DDOT,DSCAL,   SUBROUTINES FROM THE BLAS PACKAGE. */
/*     DAXPY,DASUM,  SEE TRANS. MATH. SOFT., VOL. 5, NO. 3, P. 308. */
/*     DCOPY,DNRM2, */
/*     DSWAP */

/*     H12           SUBROUTINE TO CONSTRUCT AND APPLY A */
/*                   HOUSEHOLDER TRANSFORMATION. */

/*     XERROR        FROM SLATEC ERROR PROCESSING PACKAGE. */
/*                   THIS IS DOCUMENTED IN SANDIA TECH. REPT., */
/*                   SAND78-1189. */

/*     SUBROUTINE LSEI(W,MDW,ME,MA,MG,N,PRGOPT,X,RNORME,RNORML,MODE,WS, */
/*    1 IP) */

/*     REVISED OCT. 1, 1981. */

/*<       DOUBLE PRECISION W(MDW,1), PRGOPT(1), X(1), WS(1), RNORME, RNORML >*/
/*<       INTEGER IP(3) >*/
/*<        >*/
/*<       DOUBLE PRECISION DASUM, DDOT, DNRM2, DSQRT, DABS, DMAX1 >*/
/*<       LOGICAL COV >*/
/*<       DATA ZERO /0.D0/, DRELPR /0.D0/, HALF /0.5E0/, ONE /1.D0/ >*/
#line 381 "../fortran/lsei.f"
    /* Parameter adjustments */
#line 381 "../fortran/lsei.f"
    w_dim1 = *mdw;
#line 381 "../fortran/lsei.f"
    w_offset = 1 + w_dim1;
#line 381 "../fortran/lsei.f"
    w -= w_offset;
#line 381 "../fortran/lsei.f"
    --prgopt;
#line 381 "../fortran/lsei.f"
    --x;
#line 381 "../fortran/lsei.f"
    --ws;
#line 381 "../fortran/lsei.f"
    --ip;
#line 381 "../fortran/lsei.f"

#line 381 "../fortran/lsei.f"
    /* Function Body */

/*     CHECK THAT ENOUGH STORAGE WAS ALLOCATED IN WS(*) AND IP(*). */
/*<       IF (.NOT.(IP(1).GT.0)) GO TO 20 >*/
#line 384 "../fortran/lsei.f"
    if (! (ip[1] > 0)) {
#line 384 "../fortran/lsei.f"
	goto L20;
#line 384 "../fortran/lsei.f"
    }
/*<       LCHK = 2*(ME+N) + MAX0(MA+MG,N) + (MG+2)*(N+7) >*/
/* Computing MAX */
#line 385 "../fortran/lsei.f"
    i__1 = *ma + *mg;
#line 385 "../fortran/lsei.f"
    lchk = (*me + *n << 1) + max(i__1,*n) + (*mg + 2) * (*n + 7);
/*<       IF (.NOT.(IP(1).LT.LCHK)) GO TO 10 >*/
#line 386 "../fortran/lsei.f"
    if (! (ip[1] < lchk)) {
#line 386 "../fortran/lsei.f"
	goto L10;
#line 386 "../fortran/lsei.f"
    }
/*<       MODE = 4 >*/
#line 387 "../fortran/lsei.f"
    *mode = 4;
/*<       NERR = 2 >*/
#line 388 "../fortran/lsei.f"
    nerr = 2;
/*<       IOPT = 1 >*/
#line 389 "../fortran/lsei.f"
    iopt = 1;
/*<        >*/
#line 390 "../fortran/lsei.f"
    xerrwv_("LSEI( ), INSUFFICIENT STORAGE ALLOCATED FOR WS(*), NEED LW=I1 B"\
	    "ELOW", &c__67, &nerr, &iopt, &c__1, &lchk, &c__0, &c__0, &dummy, &
	    dummy, (ftnlen)67);
/*<       RETURN >*/
#line 393 "../fortran/lsei.f"
    return 0;
/*<    10 CONTINUE >*/
#line 394 "../fortran/lsei.f"
L10:
/*<    20 IF (.NOT.(IP(2).GT.0)) GO TO 40 >*/
#line 395 "../fortran/lsei.f"
L20:
#line 395 "../fortran/lsei.f"
    if (! (ip[2] > 0)) {
#line 395 "../fortran/lsei.f"
	goto L40;
#line 395 "../fortran/lsei.f"
    }
/*<       LCHK = MG + 2*N + 2 >*/
#line 396 "../fortran/lsei.f"
    lchk = *mg + (*n << 1) + 2;
/*<       IF (.NOT.(IP(2).LT.LCHK)) GO TO 30 >*/
#line 397 "../fortran/lsei.f"
    if (! (ip[2] < lchk)) {
#line 397 "../fortran/lsei.f"
	goto L30;
#line 397 "../fortran/lsei.f"
    }
/*<       MODE = 4 >*/
#line 398 "../fortran/lsei.f"
    *mode = 4;
/*<       NERR = 2 >*/
#line 399 "../fortran/lsei.f"
    nerr = 2;
/*<       IOPT = 1 >*/
#line 400 "../fortran/lsei.f"
    iopt = 1;
/*<        >*/
#line 401 "../fortran/lsei.f"
    xerrwv_("LSEI( ), INSUFFICIENT STORAGE ALLOCATED FOR IP(*), NEED LIP=I1 "\
	    "BELOW", &c__68, &nerr, &iopt, &c__1, &lchk, &c__0, &c__0, &dummy, 
	    &dummy, (ftnlen)68);
/*<       RETURN >*/
#line 404 "../fortran/lsei.f"
    return 0;
/*<    30 CONTINUE >*/
#line 405 "../fortran/lsei.f"
L30:

/*     COMPUTE MACHINE PRECISION=DRELPR ONLY WHEN NECESSARY. */
/*<    40 IF (.NOT.(DRELPR.EQ.ZERO)) GO TO 70 >*/
#line 408 "../fortran/lsei.f"
L40:
#line 408 "../fortran/lsei.f"
    if (! (drelpr == zero)) {
#line 408 "../fortran/lsei.f"
	goto L70;
#line 408 "../fortran/lsei.f"
    }
/*<       DRELPR = ONE >*/
#line 409 "../fortran/lsei.f"
    drelpr = one;
/*<    50 IF (ONE+DRELPR.EQ.ONE) GO TO 60 >*/
#line 410 "../fortran/lsei.f"
L50:
#line 410 "../fortran/lsei.f"
    if (one + drelpr == one) {
#line 410 "../fortran/lsei.f"
	goto L60;
#line 410 "../fortran/lsei.f"
    }
/*<       DRELPR = DRELPR*HALF >*/
#line 411 "../fortran/lsei.f"
    drelpr *= half;
/*<       GO TO 50 >*/
#line 412 "../fortran/lsei.f"
    goto L50;
/*<    60 DRELPR = DRELPR + DRELPR >*/
#line 413 "../fortran/lsei.f"
L60:
#line 413 "../fortran/lsei.f"
    drelpr += drelpr;

/*     COMPUTE NUMBER OF POSSIBLE RIGHT MULTIPLYING HOUSEHOLDER */
/*     TRANSFORMATIONS. */
/*<    70 M = ME + MA + MG >*/
#line 417 "../fortran/lsei.f"
L70:
#line 417 "../fortran/lsei.f"
    m = *me + *ma + *mg;
/*<       MODE = 0 >*/
#line 418 "../fortran/lsei.f"
    *mode = 0;
/*<       IF (N.LE.0 .OR. M.LE.0) RETURN >*/
#line 419 "../fortran/lsei.f"
    if (*n <= 0 || m <= 0) {
#line 419 "../fortran/lsei.f"
	return 0;
#line 419 "../fortran/lsei.f"
    }
/*<       IF (.NOT.(MDW.LT.M)) GO TO 80 >*/
#line 420 "../fortran/lsei.f"
    if (! (*mdw < m)) {
#line 420 "../fortran/lsei.f"
	goto L80;
#line 420 "../fortran/lsei.f"
    }
/*<       NERR = 1 >*/
#line 421 "../fortran/lsei.f"
    nerr = 1;
/*<       IOPT = 1 >*/
#line 422 "../fortran/lsei.f"
    iopt = 1;
/*<        >*/
#line 423 "../fortran/lsei.f"
    xerror_("LSEI( ), MDW.LT.ME+MA+MG IS AN ERROR", &c__36, &nerr, &iopt, (
	    ftnlen)36);
/*<       MODE = 4 >*/
#line 425 "../fortran/lsei.f"
    *mode = 4;
/*<       RETURN >*/
#line 426 "../fortran/lsei.f"
    return 0;
/*<    80 NP1 = N + 1 >*/
#line 427 "../fortran/lsei.f"
L80:
#line 427 "../fortran/lsei.f"
    np1 = *n + 1;
/*<       KRANKE = MIN0(ME,N) >*/
#line 428 "../fortran/lsei.f"
    kranke = min(*me,*n);
/*<       N1 = 2*KRANKE + 1 >*/
#line 429 "../fortran/lsei.f"
    n1 = (kranke << 1) + 1;
/*<       N2 = N1 + N >*/
#line 430 "../fortran/lsei.f"
    n2 = n1 + *n;

/*     PROCESS-OPTION-VECTOR */
/*<       ASSIGN 90 TO IGO990 >*/
#line 433 "../fortran/lsei.f"
    igo990 = 0;
#line 433 "../fortran/lsei.f"
    igo990_fmt = fmt_90;
/*<       GO TO 480 >*/
#line 434 "../fortran/lsei.f"
    goto L480;
/*<    90 IF (.NOT.(COV .AND. MDW.LT.N)) GO TO 100 >*/
#line 435 "../fortran/lsei.f"
L90:
#line 435 "../fortran/lsei.f"
    if (! (cov && *mdw < *n)) {
#line 435 "../fortran/lsei.f"
	goto L100;
#line 435 "../fortran/lsei.f"
    }
/*<       NERR = 2 >*/
#line 436 "../fortran/lsei.f"
    nerr = 2;
/*<       IOPT = 1 >*/
#line 437 "../fortran/lsei.f"
    iopt = 1;
/*<        >*/
#line 438 "../fortran/lsei.f"
    xerror_("LSEI( ), MDW.LT.N, WHEN COV MATRIX NEEDED, IS AN ERROR", &c__54, 
	    &nerr, &iopt, (ftnlen)54);
/*<       MODE = 4 >*/
#line 441 "../fortran/lsei.f"
    *mode = 4;
/*<       RETURN >*/
#line 442 "../fortran/lsei.f"
    return 0;
/*<   100 L = KRANKE >*/
#line 443 "../fortran/lsei.f"
L100:
#line 443 "../fortran/lsei.f"
    l = kranke;

/*     COMPUTE NORM OF EQUALITY CONSTRAINT MATRIX AND RT SIDE. */
/*<       ENORM = ZERO >*/
#line 446 "../fortran/lsei.f"
    enorm = zero;
/*<       DO 110 J=1,N >*/
#line 447 "../fortran/lsei.f"
    i__1 = *n;
#line 447 "../fortran/lsei.f"
    for (j = 1; j <= i__1; ++j) {
/*<         ENORM = DMAX1(ENORM,DASUM(ME,W(1,J),1)) >*/
/* Computing MAX */
#line 448 "../fortran/lsei.f"
	d__1 = enorm, d__2 = dasum_(me, &w[j * w_dim1 + 1], &c__1);
#line 448 "../fortran/lsei.f"
	enorm = max(d__1,d__2);
/*<   110 CONTINUE >*/
#line 449 "../fortran/lsei.f"
/* L110: */
#line 449 "../fortran/lsei.f"
    }
/*<       FNORM = DASUM(ME,W(1,NP1),1) >*/
#line 450 "../fortran/lsei.f"
    fnorm = dasum_(me, &w[np1 * w_dim1 + 1], &c__1);
/*<       IF (.NOT.(L.GT.0)) GO TO 190 >*/
#line 451 "../fortran/lsei.f"
    if (! (l > 0)) {
#line 451 "../fortran/lsei.f"
	goto L190;
#line 451 "../fortran/lsei.f"
    }
/*<       SNMAX = ZERO >*/
#line 452 "../fortran/lsei.f"
    snmax = zero;
/*<       RNMAX = ZERO >*/
#line 453 "../fortran/lsei.f"
    rnmax = zero;
/*<       DO 180 I=1,L >*/
#line 454 "../fortran/lsei.f"
    i__1 = l;
#line 454 "../fortran/lsei.f"
    for (i__ = 1; i__ <= i__1; ++i__) {

/*     COMPUTE MAXIMUM RATIO OF VECTOR LENGTHS. PARTITION */
/*     IS AT COL. I. */
/*<         DO 150 K=I,ME >*/
#line 458 "../fortran/lsei.f"
	i__2 = *me;
#line 458 "../fortran/lsei.f"
	for (k = i__; k <= i__2; ++k) {
/*<           SN = DDOT(N-I+1,W(K,I),MDW,W(K,I),MDW) >*/
#line 459 "../fortran/lsei.f"
	    i__3 = *n - i__ + 1;
#line 459 "../fortran/lsei.f"
	    sn = ddot_(&i__3, &w[k + i__ * w_dim1], mdw, &w[k + i__ * w_dim1],
		     mdw);
/*<           RN = DDOT(I-1,W(K,1),MDW,W(K,1),MDW) >*/
#line 460 "../fortran/lsei.f"
	    i__3 = i__ - 1;
#line 460 "../fortran/lsei.f"
	    rn = ddot_(&i__3, &w[k + w_dim1], mdw, &w[k + w_dim1], mdw);
/*<           IF (.NOT.(RN.EQ.ZERO .AND. SN.GT.SNMAX)) GO TO 120 >*/
#line 461 "../fortran/lsei.f"
	    if (! (rn == zero && sn > snmax)) {
#line 461 "../fortran/lsei.f"
		goto L120;
#line 461 "../fortran/lsei.f"
	    }
/*<           SNMAX = SN >*/
#line 462 "../fortran/lsei.f"
	    snmax = sn;
/*<           IMAX = K >*/
#line 463 "../fortran/lsei.f"
	    imax = k;
/*<           GO TO 140 >*/
#line 464 "../fortran/lsei.f"
	    goto L140;
/*<   120     IF (.NOT.(K.EQ.I .OR. (SN*RNMAX.GT.RN*SNMAX))) GO TO 130 >*/
#line 465 "../fortran/lsei.f"
L120:
#line 465 "../fortran/lsei.f"
	    if (! (k == i__ || sn * rnmax > rn * snmax)) {
#line 465 "../fortran/lsei.f"
		goto L130;
#line 465 "../fortran/lsei.f"
	    }
/*<           SNMAX = SN >*/
#line 466 "../fortran/lsei.f"
	    snmax = sn;
/*<           RNMAX = RN >*/
#line 467 "../fortran/lsei.f"
	    rnmax = rn;
/*<           IMAX = K >*/
#line 468 "../fortran/lsei.f"
	    imax = k;
/*<   130     CONTINUE >*/
#line 469 "../fortran/lsei.f"
L130:
/*<   140     CONTINUE >*/
#line 470 "../fortran/lsei.f"
L140:
/*<   150   CONTINUE >*/
#line 471 "../fortran/lsei.f"
/* L150: */
#line 471 "../fortran/lsei.f"
	    ;
#line 471 "../fortran/lsei.f"
	}

/*     INTERCHANGE ROWS IF NECESSARY. */
/*<         IF (I.NE.IMAX) CALL DSWAP(NP1, W(I,1), MDW, W(IMAX,1), MDW) >*/
#line 474 "../fortran/lsei.f"
	if (i__ != imax) {
#line 474 "../fortran/lsei.f"
	    dswap_(&np1, &w[i__ + w_dim1], mdw, &w[imax + w_dim1], mdw);
#line 474 "../fortran/lsei.f"
	}
/*<         IF (.NOT.(SNMAX.GT.TAU**2*RNMAX)) GO TO 160 >*/
/* Computing 2nd power */
#line 475 "../fortran/lsei.f"
	d__1 = tau;
#line 475 "../fortran/lsei.f"
	if (! (snmax > d__1 * d__1 * rnmax)) {
#line 475 "../fortran/lsei.f"
	    goto L160;
#line 475 "../fortran/lsei.f"
	}

/*     ELIMINATE ELEMS I+1,...,N IN ROW I. */
/*<        >*/
#line 478 "../fortran/lsei.f"
	i__2 = i__ + 1;
#line 478 "../fortran/lsei.f"
	i__3 = m - i__;
#line 478 "../fortran/lsei.f"
	h12_(&c__1, &i__, &i__2, n, &w[i__ + w_dim1], mdw, &ws[i__], &w[i__ + 
		1 + w_dim1], mdw, &c__1, &i__3);
/*<         GO TO 170 >*/
#line 480 "../fortran/lsei.f"
	goto L170;
/*<   160   KRANKE = I - 1 >*/
#line 481 "../fortran/lsei.f"
L160:
#line 481 "../fortran/lsei.f"
	kranke = i__ - 1;
/*<         GO TO 200 >*/
#line 482 "../fortran/lsei.f"
	goto L200;
/*<   170   CONTINUE >*/
#line 483 "../fortran/lsei.f"
L170:
/*<   180 CONTINUE >*/
#line 484 "../fortran/lsei.f"
/* L180: */
#line 484 "../fortran/lsei.f"
	;
#line 484 "../fortran/lsei.f"
    }
/*<   190 CONTINUE >*/
#line 485 "../fortran/lsei.f"
L190:
/*<   200 CONTINUE >*/
#line 486 "../fortran/lsei.f"
L200:

/*     SAVE DIAG. TERMS OF LOWER TRAP. MATRIX. */
/*<       CALL DCOPY(KRANKE, W, MDW+1, WS(KRANKE+1), 1) >*/
#line 489 "../fortran/lsei.f"
    i__1 = *mdw + 1;
#line 489 "../fortran/lsei.f"
    dcopy_(&kranke, &w[w_offset], &i__1, &ws[kranke + 1], &c__1);

/*     USE HOUSEHOLDER TRANS FROM LEFT TO ACHIEVE KRANKE BY KRANKE UPPER */
/*     TRIANGULAR FORM. */
/*<       IF (.NOT.(KRANKE.GT.0 .AND. KRANKE.LT.ME)) GO TO 220 >*/
#line 493 "../fortran/lsei.f"
    if (! (kranke > 0 && kranke < *me)) {
#line 493 "../fortran/lsei.f"
	goto L220;
#line 493 "../fortran/lsei.f"
    }
/*<       DO 210 KK=1,KRANKE >*/
#line 494 "../fortran/lsei.f"
    i__1 = kranke;
#line 494 "../fortran/lsei.f"
    for (kk = 1; kk <= i__1; ++kk) {
/*<         K = KRANKE + 1 - KK >*/
#line 495 "../fortran/lsei.f"
	k = kranke + 1 - kk;

/*     APPLY TRANFORMATION TO MATRIX COLS. 1,...,K-1. */
/*<         CALL H12(1, K, KRANKE+1, ME, W(1,K), 1, UP, W, 1, MDW, K-1) >*/
#line 498 "../fortran/lsei.f"
	i__2 = kranke + 1;
#line 498 "../fortran/lsei.f"
	i__3 = k - 1;
#line 498 "../fortran/lsei.f"
	h12_(&c__1, &k, &i__2, me, &w[k * w_dim1 + 1], &c__1, &up, &w[
		w_offset], &c__1, mdw, &i__3);

/*     APPLY TO RT SIDE VECTOR. */
/*<         CALL H12(2, K, KRANKE+1, ME, W(1,K), 1, UP, W(1,NP1), 1, 1, 1) >*/
#line 501 "../fortran/lsei.f"
	i__2 = kranke + 1;
#line 501 "../fortran/lsei.f"
	h12_(&c__2, &k, &i__2, me, &w[k * w_dim1 + 1], &c__1, &up, &w[np1 * 
		w_dim1 + 1], &c__1, &c__1, &c__1);
/*<   210 CONTINUE >*/
#line 502 "../fortran/lsei.f"
/* L210: */
#line 502 "../fortran/lsei.f"
    }
/*<   220 IF (.NOT.(KRANKE.GT.0)) GO TO 240 >*/
#line 503 "../fortran/lsei.f"
L220:
#line 503 "../fortran/lsei.f"
    if (! (kranke > 0)) {
#line 503 "../fortran/lsei.f"
	goto L240;
#line 503 "../fortran/lsei.f"
    }

/*     SOLVE FOR VARIABLES 1,...,KRANKE IN NEW COORDINATES. */
/*<       CALL DCOPY(KRANKE, W(1,NP1), 1, X, 1) >*/
#line 506 "../fortran/lsei.f"
    dcopy_(&kranke, &w[np1 * w_dim1 + 1], &c__1, &x[1], &c__1);
/*<       DO 230 I=1,KRANKE >*/
#line 507 "../fortran/lsei.f"
    i__1 = kranke;
#line 507 "../fortran/lsei.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         X(I) = (X(I)-DDOT(I-1,W(I,1),MDW,X,1))/W(I,I) >*/
#line 508 "../fortran/lsei.f"
	i__2 = i__ - 1;
#line 508 "../fortran/lsei.f"
	x[i__] = (x[i__] - ddot_(&i__2, &w[i__ + w_dim1], mdw, &x[1], &c__1)) 
		/ w[i__ + i__ * w_dim1];
/*<   230 CONTINUE >*/
#line 509 "../fortran/lsei.f"
/* L230: */
#line 509 "../fortran/lsei.f"
    }

/*     COMPUTE RESIDUALS FOR REDUCED PROBLEM. */
/*<   240 MEP1 = ME + 1 >*/
#line 512 "../fortran/lsei.f"
L240:
#line 512 "../fortran/lsei.f"
    mep1 = *me + 1;
/*<       RNORML = ZERO >*/
#line 513 "../fortran/lsei.f"
    *rnorml = zero;
/*<       IF (.NOT.(ME.LT.M)) GO TO 270 >*/
#line 514 "../fortran/lsei.f"
    if (! (*me < m)) {
#line 514 "../fortran/lsei.f"
	goto L270;
#line 514 "../fortran/lsei.f"
    }
/*<       DO 260 I=MEP1,M >*/
#line 515 "../fortran/lsei.f"
    i__1 = m;
#line 515 "../fortran/lsei.f"
    for (i__ = mep1; i__ <= i__1; ++i__) {
/*<         W(I,NP1) = W(I,NP1) - DDOT(KRANKE,W(I,1),MDW,X,1) >*/
#line 516 "../fortran/lsei.f"
	w[i__ + np1 * w_dim1] -= ddot_(&kranke, &w[i__ + w_dim1], mdw, &x[1], 
		&c__1);
/*<         SN = DDOT(KRANKE,W(I,1),MDW,W(I,1),MDW) >*/
#line 517 "../fortran/lsei.f"
	sn = ddot_(&kranke, &w[i__ + w_dim1], mdw, &w[i__ + w_dim1], mdw);
/*<         RN = DDOT(N-KRANKE,W(I,KRANKE+1),MDW,W(I,KRANKE+1),MDW) >*/
#line 518 "../fortran/lsei.f"
	i__2 = *n - kranke;
#line 518 "../fortran/lsei.f"
	rn = ddot_(&i__2, &w[i__ + (kranke + 1) * w_dim1], mdw, &w[i__ + (
		kranke + 1) * w_dim1], mdw);
/*<         IF (.NOT.(RN.LE.TAU**2*SN .AND. KRANKE.LT.N)) GO TO 250 >*/
/* Computing 2nd power */
#line 519 "../fortran/lsei.f"
	d__1 = tau;
#line 519 "../fortran/lsei.f"
	if (! (rn <= d__1 * d__1 * sn && kranke < *n)) {
#line 519 "../fortran/lsei.f"
	    goto L250;
#line 519 "../fortran/lsei.f"
	}
/*<         W(I,KRANKE+1) = ZERO >*/
#line 520 "../fortran/lsei.f"
	w[i__ + (kranke + 1) * w_dim1] = zero;
/*<         CALL DCOPY(N-KRANKE, W(I,KRANKE+1), 0, W(I,KRANKE+1), MDW) >*/
#line 521 "../fortran/lsei.f"
	i__2 = *n - kranke;
#line 521 "../fortran/lsei.f"
	dcopy_(&i__2, &w[i__ + (kranke + 1) * w_dim1], &c__0, &w[i__ + (
		kranke + 1) * w_dim1], mdw);
/*<   250   CONTINUE >*/
#line 522 "../fortran/lsei.f"
L250:
/*<   260 CONTINUE >*/
#line 523 "../fortran/lsei.f"
/* L260: */
#line 523 "../fortran/lsei.f"
	;
#line 523 "../fortran/lsei.f"
    }

/*     COMPUTE EQUAL. CONSTRAINT EQUAS. RESIDUAL LENGTH. */
/*<   270 RNORME = DNRM2(ME-KRANKE,W(KRANKE+1,NP1),1) >*/
#line 526 "../fortran/lsei.f"
L270:
#line 526 "../fortran/lsei.f"
    i__1 = *me - kranke;
#line 526 "../fortran/lsei.f"
    *rnorme = dnrm2_(&i__1, &w[kranke + 1 + np1 * w_dim1], &c__1);

/*     MOVE REDUCED PROBLEM DATA UPWARD IF KRANKE.LT.ME. */
/*<       IF (.NOT.(KRANKE.LT.ME)) GO TO 290 >*/
#line 529 "../fortran/lsei.f"
    if (! (kranke < *me)) {
#line 529 "../fortran/lsei.f"
	goto L290;
#line 529 "../fortran/lsei.f"
    }
/*<       DO 280 J=1,NP1 >*/
#line 530 "../fortran/lsei.f"
    i__1 = np1;
#line 530 "../fortran/lsei.f"
    for (j = 1; j <= i__1; ++j) {
/*<         CALL DCOPY(M-ME, W(ME+1,J), 1, W(KRANKE+1,J), 1) >*/
#line 531 "../fortran/lsei.f"
	i__2 = m - *me;
#line 531 "../fortran/lsei.f"
	dcopy_(&i__2, &w[*me + 1 + j * w_dim1], &c__1, &w[kranke + 1 + j * 
		w_dim1], &c__1);
/*<   280 CONTINUE >*/
#line 532 "../fortran/lsei.f"
/* L280: */
#line 532 "../fortran/lsei.f"
    }

/*     COMPUTE SOLN OF REDUCED PROBLEM. */
/*<   290  >*/
#line 535 "../fortran/lsei.f"
L290:
#line 535 "../fortran/lsei.f"
    i__1 = *n - kranke;
#line 535 "../fortran/lsei.f"
    lsi_(&w[kranke + 1 + (kranke + 1) * w_dim1], mdw, ma, mg, &i__1, &prgopt[
	    1], &x[kranke + 1], rnorml, mode, &ws[n2], &ip[2]);
/*<       IF (.NOT.(ME.GT.0)) GO TO 330 >*/
#line 537 "../fortran/lsei.f"
    if (! (*me > 0)) {
#line 537 "../fortran/lsei.f"
	goto L330;
#line 537 "../fortran/lsei.f"
    }

/*     TEST FOR CONSISTENCY OF EQUALITY CONSTRAINTS. */
/*<       MDEQC = 0 >*/
#line 540 "../fortran/lsei.f"
    mdeqc = 0;
/*<       XNRME = DASUM(KRANKE,W(1,NP1),1) >*/
#line 541 "../fortran/lsei.f"
    xnrme = dasum_(&kranke, &w[np1 * w_dim1 + 1], &c__1);
/*<       IF (RNORME.GT.TAU*(ENORM*XNRME+FNORM)) MDEQC = 1 >*/
#line 542 "../fortran/lsei.f"
    if (*rnorme > tau * (enorm * xnrme + fnorm)) {
#line 542 "../fortran/lsei.f"
	mdeqc = 1;
#line 542 "../fortran/lsei.f"
    }
/*<       MODE = MODE + MDEQC >*/
#line 543 "../fortran/lsei.f"
    *mode += mdeqc;

/*     CHECK IF SOLN TO EQUAL. CONSTRAINTS SATISFIES INEQUAL. */
/*     CONSTRAINTS WHEN THERE ARE NO DEGREES OF FREEDOM LEFT. */
/*<       IF (.NOT.(KRANKE.EQ.N .AND. MG.GT.0)) GO TO 320 >*/
#line 547 "../fortran/lsei.f"
    if (! (kranke == *n && *mg > 0)) {
#line 547 "../fortran/lsei.f"
	goto L320;
#line 547 "../fortran/lsei.f"
    }
/*<       XNORM = DASUM(N,X,1) >*/
#line 548 "../fortran/lsei.f"
    xnorm = dasum_(n, &x[1], &c__1);
/*<       MAPKE1 = MA + KRANKE + 1 >*/
#line 549 "../fortran/lsei.f"
    mapke1 = *ma + kranke + 1;
/*<       MEND = MA + KRANKE + MG >*/
#line 550 "../fortran/lsei.f"
    mend = *ma + kranke + *mg;
/*<       DO 310 I=MAPKE1,MEND >*/
#line 551 "../fortran/lsei.f"
    i__1 = mend;
#line 551 "../fortran/lsei.f"
    for (i__ = mapke1; i__ <= i__1; ++i__) {
/*<         SIZE = DASUM(N,W(I,1),MDW)*XNORM + DABS(W(I,NP1)) >*/
#line 552 "../fortran/lsei.f"
	size = dasum_(n, &w[i__ + w_dim1], mdw) * xnorm + (d__1 = w[i__ + np1 
		* w_dim1], abs(d__1));
/*<         IF (.NOT.(W(I,NP1).GT.TAU*SIZE)) GO TO 300 >*/
#line 553 "../fortran/lsei.f"
	if (! (w[i__ + np1 * w_dim1] > tau * size)) {
#line 553 "../fortran/lsei.f"
	    goto L300;
#line 553 "../fortran/lsei.f"
	}
/*<         MODE = MODE + 2 >*/
#line 554 "../fortran/lsei.f"
	*mode += 2;
/*<         GO TO 450 >*/
#line 555 "../fortran/lsei.f"
	goto L450;
/*<   300   CONTINUE >*/
#line 556 "../fortran/lsei.f"
L300:
/*<   310 CONTINUE >*/
#line 557 "../fortran/lsei.f"
/* L310: */
#line 557 "../fortran/lsei.f"
	;
#line 557 "../fortran/lsei.f"
    }
/*<   320 CONTINUE >*/
#line 558 "../fortran/lsei.f"
L320:
/*<   330 IF (.NOT.(KRANKE.GT.0)) GO TO 420 >*/
#line 559 "../fortran/lsei.f"
L330:
#line 559 "../fortran/lsei.f"
    if (! (kranke > 0)) {
#line 559 "../fortran/lsei.f"
	goto L420;
#line 559 "../fortran/lsei.f"
    }

/*     REPLACE DIAG. TERMS OF LOWER TRAP. MATRIX. */
/*<       CALL DCOPY(KRANKE, WS(KRANKE+1), 1, W, MDW+1) >*/
#line 562 "../fortran/lsei.f"
    i__1 = *mdw + 1;
#line 562 "../fortran/lsei.f"
    dcopy_(&kranke, &ws[kranke + 1], &c__1, &w[w_offset], &i__1);

/*     REAPPLY TRANS TO PUT SOLN IN ORIGINAL COORDINATES. */
/*<       DO 340 II=1,KRANKE >*/
#line 565 "../fortran/lsei.f"
    i__1 = kranke;
#line 565 "../fortran/lsei.f"
    for (ii = 1; ii <= i__1; ++ii) {
/*<         I = KRANKE + 1 - II >*/
#line 566 "../fortran/lsei.f"
	i__ = kranke + 1 - ii;
/*<         CALL H12(2, I, I+1, N, W(I,1), MDW, WS(I), X, 1, 1, 1) >*/
#line 567 "../fortran/lsei.f"
	i__2 = i__ + 1;
#line 567 "../fortran/lsei.f"
	h12_(&c__2, &i__, &i__2, n, &w[i__ + w_dim1], mdw, &ws[i__], &x[1], &
		c__1, &c__1, &c__1);
/*<   340 CONTINUE >*/
#line 568 "../fortran/lsei.f"
/* L340: */
#line 568 "../fortran/lsei.f"
    }

/*     COMPUTE COV MATRIX OF EQUAL. CONSTRAINED PROBLEM. */
/*<       IF (.NOT.(COV)) GO TO 410 >*/
#line 571 "../fortran/lsei.f"
    if (! cov) {
#line 571 "../fortran/lsei.f"
	goto L410;
#line 571 "../fortran/lsei.f"
    }
/*<       DO 400 JJ=1,KRANKE >*/
#line 572 "../fortran/lsei.f"
    i__1 = kranke;
#line 572 "../fortran/lsei.f"
    for (jj = 1; jj <= i__1; ++jj) {
/*<         J = KRANKE + 1 - JJ >*/
#line 573 "../fortran/lsei.f"
	j = kranke + 1 - jj;
/*<         IF (.NOT.(J.LT.N)) GO TO 390 >*/
#line 574 "../fortran/lsei.f"
	if (! (j < *n)) {
#line 574 "../fortran/lsei.f"
	    goto L390;
#line 574 "../fortran/lsei.f"
	}
/*<         RB = WS(J)*W(J,J) >*/
#line 575 "../fortran/lsei.f"
	rb = ws[j] * w[j + j * w_dim1];
/*<         IF (RB.NE.ZERO) RB = ONE/RB >*/
#line 576 "../fortran/lsei.f"
	if (rb != zero) {
#line 576 "../fortran/lsei.f"
	    rb = one / rb;
#line 576 "../fortran/lsei.f"
	}
/*<         JP1 = J + 1 >*/
#line 577 "../fortran/lsei.f"
	jp1 = j + 1;
/*<         DO 350 I=JP1,N >*/
#line 578 "../fortran/lsei.f"
	i__2 = *n;
#line 578 "../fortran/lsei.f"
	for (i__ = jp1; i__ <= i__2; ++i__) {
/*<           W(I,J) = DDOT(N-J,W(I,JP1),MDW,W(J,JP1),MDW)*RB >*/
#line 579 "../fortran/lsei.f"
	    i__3 = *n - j;
#line 579 "../fortran/lsei.f"
	    w[i__ + j * w_dim1] = ddot_(&i__3, &w[i__ + jp1 * w_dim1], mdw, &
		    w[j + jp1 * w_dim1], mdw) * rb;
/*<   350   CONTINUE >*/
#line 580 "../fortran/lsei.f"
/* L350: */
#line 580 "../fortran/lsei.f"
	}
/*<         GAM = DDOT(N-J,W(JP1,J),1,W(J,JP1),MDW)*RB >*/
#line 581 "../fortran/lsei.f"
	i__2 = *n - j;
#line 581 "../fortran/lsei.f"
	gam = ddot_(&i__2, &w[jp1 + j * w_dim1], &c__1, &w[j + jp1 * w_dim1], 
		mdw) * rb;
/*<         GAM = HALF*GAM >*/
#line 582 "../fortran/lsei.f"
	gam = half * gam;
/*<         CALL DAXPY(N-J, GAM, W(J,JP1), MDW, W(JP1,J), 1) >*/
#line 583 "../fortran/lsei.f"
	i__2 = *n - j;
#line 583 "../fortran/lsei.f"
	daxpy_(&i__2, &gam, &w[j + jp1 * w_dim1], mdw, &w[jp1 + j * w_dim1], &
		c__1);
/*<         DO 370 I=JP1,N >*/
#line 584 "../fortran/lsei.f"
	i__2 = *n;
#line 584 "../fortran/lsei.f"
	for (i__ = jp1; i__ <= i__2; ++i__) {
/*<           DO 360 K=I,N >*/
#line 585 "../fortran/lsei.f"
	    i__3 = *n;
#line 585 "../fortran/lsei.f"
	    for (k = i__; k <= i__3; ++k) {
/*<             W(I,K) = W(I,K) + W(J,I)*W(K,J) + W(I,J)*W(J,K) >*/
#line 586 "../fortran/lsei.f"
		w[i__ + k * w_dim1] = w[i__ + k * w_dim1] + w[j + i__ * 
			w_dim1] * w[k + j * w_dim1] + w[i__ + j * w_dim1] * w[
			j + k * w_dim1];
/*<             W(K,I) = W(I,K) >*/
#line 587 "../fortran/lsei.f"
		w[k + i__ * w_dim1] = w[i__ + k * w_dim1];
/*<   360     CONTINUE >*/
#line 588 "../fortran/lsei.f"
/* L360: */
#line 588 "../fortran/lsei.f"
	    }
/*<   370   CONTINUE >*/
#line 589 "../fortran/lsei.f"
/* L370: */
#line 589 "../fortran/lsei.f"
	}
/*<         UJ = WS(J) >*/
#line 590 "../fortran/lsei.f"
	uj = ws[j];
/*<         VJ = GAM*UJ >*/
#line 591 "../fortran/lsei.f"
	vj = gam * uj;
/*<         W(J,J) = UJ*VJ + UJ*VJ >*/
#line 592 "../fortran/lsei.f"
	w[j + j * w_dim1] = uj * vj + uj * vj;
/*<         DO 380 I=JP1,N >*/
#line 593 "../fortran/lsei.f"
	i__2 = *n;
#line 593 "../fortran/lsei.f"
	for (i__ = jp1; i__ <= i__2; ++i__) {
/*<           W(J,I) = UJ*W(I,J) + VJ*W(J,I) >*/
#line 594 "../fortran/lsei.f"
	    w[j + i__ * w_dim1] = uj * w[i__ + j * w_dim1] + vj * w[j + i__ * 
		    w_dim1];
/*<   380   CONTINUE >*/
#line 595 "../fortran/lsei.f"
/* L380: */
#line 595 "../fortran/lsei.f"
	}
/*<         CALL DCOPY(N-J, W(J,JP1), MDW, W(JP1,J), 1) >*/
#line 596 "../fortran/lsei.f"
	i__2 = *n - j;
#line 596 "../fortran/lsei.f"
	dcopy_(&i__2, &w[j + jp1 * w_dim1], mdw, &w[jp1 + j * w_dim1], &c__1);
/*<   390   CONTINUE >*/
#line 597 "../fortran/lsei.f"
L390:
/*<   400 CONTINUE >*/
#line 598 "../fortran/lsei.f"
/* L400: */
#line 598 "../fortran/lsei.f"
	;
#line 598 "../fortran/lsei.f"
    }
/*<   410 CONTINUE >*/
#line 599 "../fortran/lsei.f"
L410:

/*     APPLY THE SCALING TO THE COVARIANCE MATRIX. */
/*<   420 IF (.NOT.(COV)) GO TO 440 >*/
#line 602 "../fortran/lsei.f"
L420:
#line 602 "../fortran/lsei.f"
    if (! cov) {
#line 602 "../fortran/lsei.f"
	goto L440;
#line 602 "../fortran/lsei.f"
    }
/*<       DO 430 I=1,N >*/
#line 603 "../fortran/lsei.f"
    i__1 = *n;
#line 603 "../fortran/lsei.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         L = N1 + I >*/
#line 604 "../fortran/lsei.f"
	l = n1 + i__;
/*<         CALL DSCAL(N, WS(L-1), W(I,1), MDW) >*/
#line 605 "../fortran/lsei.f"
	dscal_(n, &ws[l - 1], &w[i__ + w_dim1], mdw);
/*<         CALL DSCAL(N, WS(L-1), W(1,I), 1) >*/
#line 606 "../fortran/lsei.f"
	dscal_(n, &ws[l - 1], &w[i__ * w_dim1 + 1], &c__1);
/*<   430 CONTINUE >*/
#line 607 "../fortran/lsei.f"
/* L430: */
#line 607 "../fortran/lsei.f"
    }
/*<   440 CONTINUE >*/
#line 608 "../fortran/lsei.f"
L440:
/*<   450 CONTINUE >*/
#line 609 "../fortran/lsei.f"
L450:

/*     RESCALE SOLN. VECTOR. */
/*<       IF (.NOT.(MODE.LE.1)) GO TO 470 >*/
#line 612 "../fortran/lsei.f"
    if (! (*mode <= 1)) {
#line 612 "../fortran/lsei.f"
	goto L470;
#line 612 "../fortran/lsei.f"
    }
/*<       DO 460 J=1,N >*/
#line 613 "../fortran/lsei.f"
    i__1 = *n;
#line 613 "../fortran/lsei.f"
    for (j = 1; j <= i__1; ++j) {
/*<         L = N1 + J >*/
#line 614 "../fortran/lsei.f"
	l = n1 + j;
/*<         X(J) = X(J)*WS(L-1) >*/
#line 615 "../fortran/lsei.f"
	x[j] *= ws[l - 1];
/*<   460 CONTINUE >*/
#line 616 "../fortran/lsei.f"
/* L460: */
#line 616 "../fortran/lsei.f"
    }
/*<   470 IP(1) = KRANKE >*/
#line 617 "../fortran/lsei.f"
L470:
#line 617 "../fortran/lsei.f"
    ip[1] = kranke;
/*<       IP(3) = IP(3) + 2*KRANKE + N >*/
#line 618 "../fortran/lsei.f"
    ip[3] = ip[3] + (kranke << 1) + *n;
/*<       RETURN >*/
#line 619 "../fortran/lsei.f"
    return 0;
/*<   480 CONTINUE >*/
#line 620 "../fortran/lsei.f"
L480:
/*     TO PROCESS-OPTION-VECTOR */

/*     THE NOMINAL TOLERANCE USED IN THE CODE */
/*     FOR THE EQUALITY CONSTRAINT EQUATIONS. */
/*<       TAU = DSQRT(DRELPR) >*/
#line 625 "../fortran/lsei.f"
    tau = sqrt(drelpr);

/*     THE NOMINAL COLUMN SCALING USED IN THE CODE IS */
/*     THE IDENTITY SCALING. */
/*<       WS(N1) = ONE >*/
#line 629 "../fortran/lsei.f"
    ws[n1] = one;
/*<       CALL DCOPY(N, WS(N1), 0, WS(N1), 1) >*/
#line 630 "../fortran/lsei.f"
    dcopy_(n, &ws[n1], &c__0, &ws[n1], &c__1);

/*     NO COVARIANCE MATRIX IS NOMINALLY COMPUTED. */
/*<       COV = .FALSE. >*/
#line 633 "../fortran/lsei.f"
    cov = FALSE_;

/*     DEFINE BOUND FOR NUMBER OF OPTIONS TO CHANGE. */
/*<       NOPT = 1000 >*/
#line 636 "../fortran/lsei.f"
    nopt = 1000;
/*<       NTIMES = 0 >*/
#line 637 "../fortran/lsei.f"
    ntimes = 0;

/*     DEFINE BOUND FOR POSITIVE VALUES OF LINK. */
/*<       NLINK = 100000 >*/
#line 640 "../fortran/lsei.f"
    nlink = 100000;
/*<       LAST = 1 >*/
#line 641 "../fortran/lsei.f"
    last = 1;
/*<       LINK = PRGOPT(1) >*/
#line 642 "../fortran/lsei.f"
    link = (integer) prgopt[1];
/*<       IF (.NOT.(LINK.LE.0 .OR. LINK.GT.NLINK)) GO TO 490 >*/
#line 643 "../fortran/lsei.f"
    if (! (link <= 0 || link > nlink)) {
#line 643 "../fortran/lsei.f"
	goto L490;
#line 643 "../fortran/lsei.f"
    }
/*<       NERR = 3 >*/
#line 644 "../fortran/lsei.f"
    nerr = 3;
/*<       IOPT = 1 >*/
#line 645 "../fortran/lsei.f"
    iopt = 1;
/*<        >*/
#line 646 "../fortran/lsei.f"
    xerror_("LSEI( ) THE OPTION VECTOR IS UNDEFINED", &c__38, &nerr, &iopt, (
	    ftnlen)38);
/*<       MODE = 4 >*/
#line 648 "../fortran/lsei.f"
    *mode = 4;
/*<       RETURN >*/
#line 649 "../fortran/lsei.f"
    return 0;
/*<   490 IF (.NOT.(LINK.GT.1)) GO TO 540 >*/
#line 650 "../fortran/lsei.f"
L490:
#line 650 "../fortran/lsei.f"
    if (! (link > 1)) {
#line 650 "../fortran/lsei.f"
	goto L540;
#line 650 "../fortran/lsei.f"
    }
/*<       NTIMES = NTIMES + 1 >*/
#line 651 "../fortran/lsei.f"
    ++ntimes;
/*<       IF (.NOT.(NTIMES.GT.NOPT)) GO TO 500 >*/
#line 652 "../fortran/lsei.f"
    if (! (ntimes > nopt)) {
#line 652 "../fortran/lsei.f"
	goto L500;
#line 652 "../fortran/lsei.f"
    }
/*<       NERR = 3 >*/
#line 653 "../fortran/lsei.f"
    nerr = 3;
/*<       IOPT = 1 >*/
#line 654 "../fortran/lsei.f"
    iopt = 1;
/*<        >*/
#line 655 "../fortran/lsei.f"
    xerror_("LSEI( ). THE LINKS IN THE OPTION VECTOR ARE CYCLING.", &c__52, &
	    nerr, &iopt, (ftnlen)52);
/*<       MODE = 4 >*/
#line 658 "../fortran/lsei.f"
    *mode = 4;
/*<       RETURN >*/
#line 659 "../fortran/lsei.f"
    return 0;
/*<   500 KEY = PRGOPT(LAST+1) >*/
#line 660 "../fortran/lsei.f"
L500:
#line 660 "../fortran/lsei.f"
    key = (integer) prgopt[last + 1];
/*<       IF (KEY.EQ.1) COV = PRGOPT(LAST+2).NE.ZERO >*/
#line 661 "../fortran/lsei.f"
    if (key == 1) {
#line 661 "../fortran/lsei.f"
	cov = prgopt[last + 2] != zero;
#line 661 "../fortran/lsei.f"
    }
/*<       IF (.NOT.(KEY.EQ.2 .AND. PRGOPT(LAST+2).NE.ZERO)) GO TO 520 >*/
#line 662 "../fortran/lsei.f"
    if (! (key == 2 && prgopt[last + 2] != zero)) {
#line 662 "../fortran/lsei.f"
	goto L520;
#line 662 "../fortran/lsei.f"
    }
/*<       DO 510 J=1,N >*/
#line 663 "../fortran/lsei.f"
    i__1 = *n;
#line 663 "../fortran/lsei.f"
    for (j = 1; j <= i__1; ++j) {
/*<         T = DNRM2(M,W(1,J),1) >*/
#line 664 "../fortran/lsei.f"
	t = dnrm2_(&m, &w[j * w_dim1 + 1], &c__1);
/*<         IF (T.NE.ZERO) T = ONE/T >*/
#line 665 "../fortran/lsei.f"
	if (t != zero) {
#line 665 "../fortran/lsei.f"
	    t = one / t;
#line 665 "../fortran/lsei.f"
	}
/*<         L = N1 + J >*/
#line 666 "../fortran/lsei.f"
	l = n1 + j;
/*<         WS(L-1) = T >*/
#line 667 "../fortran/lsei.f"
	ws[l - 1] = t;
/*<   510 CONTINUE >*/
#line 668 "../fortran/lsei.f"
/* L510: */
#line 668 "../fortran/lsei.f"
    }
/*<   520 IF (KEY.EQ.3) CALL DCOPY(N, PRGOPT(LAST+2), 1, WS(N1), 1) >*/
#line 669 "../fortran/lsei.f"
L520:
#line 669 "../fortran/lsei.f"
    if (key == 3) {
#line 669 "../fortran/lsei.f"
	dcopy_(n, &prgopt[last + 2], &c__1, &ws[n1], &c__1);
#line 669 "../fortran/lsei.f"
    }
/*<       IF (KEY.EQ.4) TAU = DMAX1(DRELPR,PRGOPT(LAST+2)) >*/
#line 670 "../fortran/lsei.f"
    if (key == 4) {
/* Computing MAX */
#line 670 "../fortran/lsei.f"
	d__1 = drelpr, d__2 = prgopt[last + 2];
#line 670 "../fortran/lsei.f"
	tau = max(d__1,d__2);
#line 670 "../fortran/lsei.f"
    }
/*<       NEXT = PRGOPT(LINK) >*/
#line 671 "../fortran/lsei.f"
    next = (integer) prgopt[link];
/*<       IF (.NOT.(NEXT.LE.0 .OR. NEXT.GT.NLINK)) GO TO 530 >*/
#line 672 "../fortran/lsei.f"
    if (! (next <= 0 || next > nlink)) {
#line 672 "../fortran/lsei.f"
	goto L530;
#line 672 "../fortran/lsei.f"
    }
/*<       NERR = 3 >*/
#line 673 "../fortran/lsei.f"
    nerr = 3;
/*<       IOPT = 1 >*/
#line 674 "../fortran/lsei.f"
    iopt = 1;
/*<        >*/
#line 675 "../fortran/lsei.f"
    xerror_("LSEI( ) THE OPTION VECTOR IS UNDEFINED", &c__38, &nerr, &iopt, (
	    ftnlen)38);
/*<       MODE = 4 >*/
#line 677 "../fortran/lsei.f"
    *mode = 4;
/*<       RETURN >*/
#line 678 "../fortran/lsei.f"
    return 0;
/*<   530 LAST = LINK >*/
#line 679 "../fortran/lsei.f"
L530:
#line 679 "../fortran/lsei.f"
    last = link;
/*<       LINK = NEXT >*/
#line 680 "../fortran/lsei.f"
    link = next;
/*<       GO TO 490 >*/
#line 681 "../fortran/lsei.f"
    goto L490;
/*<   540 DO 550 J=1,N >*/
#line 682 "../fortran/lsei.f"
L540:
#line 682 "../fortran/lsei.f"
    i__1 = *n;
#line 682 "../fortran/lsei.f"
    for (j = 1; j <= i__1; ++j) {
/*<         L = N1 + J >*/
#line 683 "../fortran/lsei.f"
	l = n1 + j;
/*<         CALL DSCAL(M, WS(L-1), W(1,J), 1) >*/
#line 684 "../fortran/lsei.f"
	dscal_(&m, &ws[l - 1], &w[j * w_dim1 + 1], &c__1);
/*<   550 CONTINUE >*/
#line 685 "../fortran/lsei.f"
/* L550: */
#line 685 "../fortran/lsei.f"
    }
/*<       GO TO 560 >*/
#line 686 "../fortran/lsei.f"
    goto L560;
/*<   560 GO TO IGO990, (90) >*/
#line 687 "../fortran/lsei.f"
L560:
#line 687 "../fortran/lsei.f"
    switch (igo990) {
#line 687 "../fortran/lsei.f"
	case 0: goto L90;
#line 687 "../fortran/lsei.f"
    }
/*<       END >*/
} /* lsei_ */

