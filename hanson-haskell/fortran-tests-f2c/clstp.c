#line 1 "../fortran-tests/clstp.f"
/* ../fortran-tests/clstp.f -- translated by f2c (version 20100827).
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

#line 1 "../fortran-tests/clstp.f"
/* Table of constant values */

static integer c__4 = 4;
static integer c__1 = 1;
static integer c__0 = 0;
static integer c_n1 = -1;
static integer c__5 = 5;
static integer c__3 = 3;

/*<       SUBROUTINE CLSTP(KLOG, COND, ISTAT)                                >*/
/* Subroutine */ int clstp_(integer *klog, doublereal *cond, integer *istat)
{
    /* Format strings */
    static char fmt_99999[] = "(/\002 KA, KE, KG, KI, AND KN MUST ALL BE .LE"
	    ". 5\002,\002 AS REQ\002,\002UIRED BY THE CURRENT SUBPROGRAM DIME"
	    "NSION STATEMENTS.\002)";
    static char fmt_99998[] = "(/\002 CONDA, CONDE, AND CONDG MUST ALL BE .G"
	    "E. ONE.\002)";
    static char fmt_70[] = "";
    static char fmt_110[] = "";
    static char fmt_270[] = "";
    static char fmt_310[] = "";
    static char fmt_470[] = "";
    static char fmt_510[] = "";
    static char fmt_550[] = "";
    static char fmt_99997[] = "(\0020LEAST SQS. RESID.\002,e012.5,2x,\002FOR"
	    " WNNLS( )\002/\002 ERRORS, 1-X(I), FOR WNNLS( ).\002)";
    static char fmt_99996[] = "(4(i4,e012.5))";
    static char fmt_99995[] = "(\0020LEAST SQS. RESID.\002,e012.5,2x,\002FOR"
	    " LSEI( )\002/\002 COMP. RANK OF E, COMP. RANK OF REDUCED A\002,2"
	    "i4/\002 ERRORS, 1-\002,\002X(I), FOR LSEI( ).\002)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    double sqrt(doublereal);
    integer do_fio(integer *, char *, ftnlen);

    /* Local variables */
    integer i__, j, k, l, n;
    doublereal t, w[6240]	/* was [96][65] */, x[64];
    integer ka;
    doublereal gg[1024]	/* was [32][32] */;
    integer ma;
    doublereal hh[1024]	/* was [32][32] */;
    integer ke, kg, me;
    doublereal sa[32];
    integer ki, mg, mi;
    doublereal se[32];
    integer kn;
    doublereal sg[32];
    integer nn, np1;
    doublereal gam;
    integer mdg, mdh, mna, mne;
    doublereal phi, one;
    extern doublereal ran_(integer *);
    integer ngo, mng, mdw;
    doublereal rho, two;
    integer n20100, n20011, n20020, n20130, n20032, n20024, n20016, n20042, 
	    n20050, n20028, n20037, n20046, n20054, n20058, n20063, n20068, 
	    n20073, n20077, n20081, n20085, n20089, n20096, n20104, n20114, 
	    n20118, n20122, n20126;
    doublereal beta;
    integer mode;
    logical done;
    integer jcol;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    integer mepi;
    extern /* Subroutine */ int lsei_(doublereal *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *);
    doublereal ansr;
    integer jpnn;
    doublereal zero;
    integer irow;
    doublereal work[1518];
    integer lout;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    doublereal conda;
    integer icase;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    doublereal conde;
    integer iseed;
    doublereal condg;
    integer mepma;
    doublereal bnorm;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *), dswap_(integer *, doublereal *, integer 
	    *, doublereal *, integer *);
    doublereal gnorm;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    integer iwork[640];
    doublereal dxbyx;
    extern /* Subroutine */ int wnnls_(doublereal *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, doublereal *);
    extern integer i1mach_(integer *);
    doublereal drelpr, rnorme, solerr, rnorml, prgopt[4];

    /* Fortran I/O blocks */
    static cilist io___23 = { 0, 0, 0, fmt_99999, 0 };
    static cilist io___24 = { 0, 0, 0, fmt_99998, 0 };
    static cilist io___85 = { 0, 0, 0, fmt_99997, 0 };
    static cilist io___86 = { 0, 0, 0, fmt_99996, 0 };
    static cilist io___87 = { 0, 0, 0, fmt_99995, 0 };
    static cilist io___88 = { 0, 0, 0, fmt_99996, 0 };


    /* Assigned format variables */
    static char *ngo_fmt;


/*     THE EDITING REQUIRED TO CONVERT THIS SUBROUTINE FROM SINGLE TO */
/*     DOUBLE PRECISION INVOLVES THE FOLLOWING CHARACTER STRING CHANGES. */
/*     USE AN EDITING COMMAND (CHANGE) /STRING-1/(TO)STRING-2/. */
/*     (BEGIN THE CHANGES AT THE LINE WITH C++ IN COLS. 1-3.) */
/*     /REAL (12 BLANKS)/DOUBLE PRECISION/,/DCOPY/DCOPY/,/DDOT/DDOT/, */
/*     /DNRM2/DNRM2/,/DSQRT/DSQRT/,/D0/D0/,/DSCAL/DSCAL/,/DAXPY/DAXPY/, */
/*     /DRELPR/DRELPR/,/DSWAP/DSWAP/ */

/*     REVISED 820305-2000 */
/*     REVISED YYMMDD-HHMM */

/*     THIS SUBROUTINE EXERCISES MOST OF THE MATHEMATICAL FEATURES OF THE */
/*     CONSTRAINED LEAST SQUARES SUBPROGRAMS WNNLS( ) AND LSEI( ). */
/*     THE PROBLEM THAT IS SOLVED HERE IS OF THE FORM */

/*               A*X=B (LEAST SQUARES, A MA BY N), */


/*               SUBJECT TO CONSTRAINTS */

/*               E*X=F      (CONSTRAINT EQUATIONS, ME BY N), */
/*          AND  G*X .GE. H (INEQUALITY CONSTRAINTS, MG BY N). */

/*     THE CLASS OF PROBLEMS THAT IS SOLVED HERE IS GENERATED WITH */
/*     HADAMARD MATRICES OF ORDER=POWER OF 2.  EACH OF THE MATRICES */
/*     A,E, AND G HAVE A SPECIFIED CONDITION NUMBER.  FOR EXAMPLE */
/*     A=HADAMARD MATRIX * DIAGONAL MATRIX * HADAMARD MATRIX. */
/*     DIAGONAL TERMS OF THE DIAGONAL MATRIX ARE CHOSEN SO THAT A */
/*     HAS A GIVEN CONDITION NUMBER.  THE MATRICES E AND G ARE */
/*     CONSTRUCTED IN SIMILIAR WAYS.  FURTHER, THE PROBLEM IS CONSTRUCTED */
/*     SO THAT THE TRUE SOLUTION IS X=(1,...,1) (TRANSPOSED). */
/*     THIS REQUIRES COMPUTING THE RIGHT HAND SIDE VECTORS B,F AND */
/*     H.  THE VECTOR B=A*X+COMPONENT ORTHOGONAL TO COL. SPACE OF */
/*     A, F=E*X, AND H=G*H-SLACK COMPONENTS.  THESE SLACK COMPONENTS */
/*     ARE CHOSEN SO THAT THE FIRST MI OF THE INEQUALITIES ARE */
/*     STRICT INEQUALITIES. */

/*     THE PROBLEMS DIMENSIONS ARE SPECIFIED BY */

/*                     MA = 2**KA */
/*                     ME = 2**KE */
/*                     MG = 2**KG */
/*                     MI = 2**KI */
/*                     N  = 2**KN */

/*     WHERE KA, KE, KG, KI, AND KN ARE INPUT TO THE SUBROUTINE AS */
/*     DISCUSSED BELOW. */

/*     THE SUBROUTINE ARGUMENTS ARE AS FOLLOWS */

/*     I N P U T */

/*     KLOG(*)    - AN INTEGER ARRAY WHOSE DIMENSION IS AT LEAST 5.  THE */
/*                  ENTRIES CORRESPOND TO THE POWERS OF 2 NECESSARY */
/*                  TO SPECIFY THE PROBLEM DIMENSIONS.  REFERRING TO */
/*                  THE ABOVE DISCUSSION, THE ENTRIES OF KLOG(*) */
/*                  SHOULD BE SET AS FOLLOWS */

/*                       KLOG(1) = KA */
/*                       KLOG(2) = KE */
/*                       KLOG(3) = KG */
/*                       KLOG(4) = KI */
/*                       KLOG(5) = KN */

/*                  IF KA, KE, KG, OR KI IS LESS THAN ZERO, THE */
/*                  CORRESPONDING DIMENSION WILL BE SET TO ZERO. */

/*                  KN.LT.0 WILL CAUSE THE SUBROUTINE TO SIMPLY RETURN. */

/*     COND(*)    - AN ARRAY WHOSE DIMENSION IS AT LEAST 3.  THE */
/*                  ENTRIES COND(1), COND(2), AND COND(3) RESPECTIVELY */
/*                  SPECIFY THE CONDITION NUMBER FOR THE LEAST SQUARES */
/*                  MATRIX, THE EQUALITY CONSTRAINT MATRIX, AND THE */
/*                  INEQUALITY CONSTRAINT MATRIX. */

/*     O U T P U T */

/*     ISTAT      - AN INTEGER FLAG WHICH INDICATES WHETHER THE SOLUTION */
/*                  WAS CORRECTLY COMPUTED. */
/*                  =1 NEITHER WNNLS( ) NOR LSEI( ) PASSED THE TEST. */
/*                  =2 WNNLS( ) PASSED BUT LSEI( ) FAILED THE TEST. */
/*                  =3 LSEI( ) PASSED BUT WNNLS( ) FAILED THE TEST. */
/*                  =4 BOTH WNNLS( ) AND LSEI( ) PASSED THE TEST. */

/*     THE DIMENSION STATEMENTS BELOW ARE SET UP TO SOLVE PROBLEMS FOR */
/*     WHICH NONE OF THE ABOVE LOGARITHMS IS GREATER THAN 5.  TO CHANGE */
/*     THESE DIMENSIONS TO SOLVE LARGER PROBLEMS, USE THE FOLLOWING */
/*     FORMULAS */

/*     DIMENSION W(MA+ME+MG,N+MG+1),X(N+MG),HH(MMAX,MMAX),GG(MMAX,MMAX) */
/*     DIMENSION WORK(2*(ME+N)+K+(MG+2)*(N+7)),IWORK(ME+MA+2*MG+N) */
/*     DIMENSION SA(MIN(MA,N)),SE(MIN(ME,N)),SG(MIN(MG,N)) */

/*     WHERE MMAX = MAX(MA,ME,MG,N) */
/*           K    = MAX(MA+MG,N) */

/*     NOTE THAT IF THE DIMENSIONS ARE CHANGED, THE VALUES ASSIGNED TO */
/*     MDW, MDH, AND MDG BELOW MUST BE ALTERED APPROPRIATELY.  THESE */
/*     ARE THE RESPECTIVE ROW DIMENSIONS OF THE ARRAYS W(*,*), HH(*,*), */
/*     AND GG(*,*). */
/* ++ */
/*<        >*/
/*<       DOUBLE PRECISION DNRM2, DDOT, DSQRT >*/
/*<       DOUBLE PRECISION W(96,65), X(64), HH(32,32), GG(32,32) >*/
/*<       DOUBLE PRECISION WORK(1518) >*/
/*<       INTEGER   IWORK(0640) >*/
/*<       DOUBLE PRECISION SA(32), SE(32), SG(32) >*/

/*     THE FOLLOWING DIMENSION STATEMENTS NEED NOT BE ALTERED TO */
/*     SOLVE LARGER PROBLEMS. */
/*<       DOUBLE PRECISION COND(3), PRGOPT(4) >*/
/*<       INTEGER KLOG(5) >*/
/*<       LOGICAL DONE >*/

/*<       MDW = 96 >*/
#line 119 "../fortran-tests/clstp.f"
    /* Parameter adjustments */
#line 119 "../fortran-tests/clstp.f"
    --cond;
#line 119 "../fortran-tests/clstp.f"
    --klog;
#line 119 "../fortran-tests/clstp.f"

#line 119 "../fortran-tests/clstp.f"
    /* Function Body */
#line 119 "../fortran-tests/clstp.f"
    mdw = 96;
/*<       MDH = 32 >*/
#line 120 "../fortran-tests/clstp.f"
    mdh = 32;
/*<       MDG = 32 >*/
#line 121 "../fortran-tests/clstp.f"
    mdg = 32;
/*<       ZERO = 0.D0 >*/
#line 122 "../fortran-tests/clstp.f"
    zero = 0.;
/*<       ONE = 1.D0 >*/
#line 123 "../fortran-tests/clstp.f"
    one = 1.;
/*<       TWO = 2.D0 >*/
#line 124 "../fortran-tests/clstp.f"
    two = 2.;
/*<       ISTAT = 1 >*/
#line 125 "../fortran-tests/clstp.f"
    *istat = 1;
/*     COMPUTE THE RELATIVE MACHINE PRECISION. */
/*<       DRELPR = ONE >*/
#line 127 "../fortran-tests/clstp.f"
    drelpr = one;
/*<    10 IF (ONE+DRELPR.EQ.ONE) GO TO 20 >*/
#line 128 "../fortran-tests/clstp.f"
L10:
#line 128 "../fortran-tests/clstp.f"
    if (one + drelpr == one) {
#line 128 "../fortran-tests/clstp.f"
	goto L20;
#line 128 "../fortran-tests/clstp.f"
    }
/*<       DRELPR = DRELPR/TWO >*/
#line 129 "../fortran-tests/clstp.f"
    drelpr /= two;
/*<       GO TO 10 >*/
#line 130 "../fortran-tests/clstp.f"
    goto L10;
/*<    20 DRELPR = DRELPR*TWO >*/
#line 131 "../fortran-tests/clstp.f"
L20:
#line 131 "../fortran-tests/clstp.f"
    drelpr *= two;

/*     SET THE OUTPUT UNIT TO WHICH ERROR MESSAGES WILL BE PRINTED. */
/*<       LOUT = I1MACH(4) >*/
#line 134 "../fortran-tests/clstp.f"
    lout = i1mach_(&c__4);

/*     SET UP THE PROBLEM DIMENSIONS */
/*<       KA = KLOG(1) >*/
#line 137 "../fortran-tests/clstp.f"
    ka = klog[1];
/*<       KE = KLOG(2) >*/
#line 138 "../fortran-tests/clstp.f"
    ke = klog[2];
/*<       KG = KLOG(3) >*/
#line 139 "../fortran-tests/clstp.f"
    kg = klog[3];
/*<       KI = KLOG(4) >*/
#line 140 "../fortran-tests/clstp.f"
    ki = klog[4];
/*<       KN = KLOG(5) >*/
#line 141 "../fortran-tests/clstp.f"
    kn = klog[5];
/*<       CONDA = ONE >*/
#line 142 "../fortran-tests/clstp.f"
    conda = one;
/*<       CONDE = ONE >*/
#line 143 "../fortran-tests/clstp.f"
    conde = one;
/*<       CONDG = ONE >*/
#line 144 "../fortran-tests/clstp.f"
    condg = one;
/*<       DONE = KN.LT.0 >*/
#line 145 "../fortran-tests/clstp.f"
    done = kn < 0;
/*<       IF (.NOT.(DONE)) GO TO 30 >*/
#line 146 "../fortran-tests/clstp.f"
    if (! done) {
#line 146 "../fortran-tests/clstp.f"
	goto L30;
#line 146 "../fortran-tests/clstp.f"
    }
/*<       RETURN >*/
#line 147 "../fortran-tests/clstp.f"
    return 0;
/*<    30 MA = 0 >*/
#line 148 "../fortran-tests/clstp.f"
L30:
#line 148 "../fortran-tests/clstp.f"
    ma = 0;
/*<       ME = 0 >*/
#line 149 "../fortran-tests/clstp.f"
    me = 0;
/*<       MG = 0 >*/
#line 150 "../fortran-tests/clstp.f"
    mg = 0;
/*<       N = 0 >*/
#line 151 "../fortran-tests/clstp.f"
    n = 0;

/*     SET NOISE-TO-SIGNAL RATIO PARAMETER FOR LEAST SQUARES EQUAS. */
/*     THIS ESSENTIALLY SPECIFIES THE RATIO */

/*                   NORM(RESIDUAL VECTOR) */
/*                   --------------------- */
/*                       NORM(A*X) */
/*<       ANSR = 0.01 >*/
#line 159 "../fortran-tests/clstp.f"
    ansr = .01f;

/*     SET UP THE CONDITION NUMBERS FOR THE MATRICES A, E, AND G. */
/*<       IF (KA.GE.0) CONDA = COND(1) >*/
#line 162 "../fortran-tests/clstp.f"
    if (ka >= 0) {
#line 162 "../fortran-tests/clstp.f"
	conda = cond[1];
#line 162 "../fortran-tests/clstp.f"
    }
/*<       IF (KE.GE.0) CONDE = COND(2) >*/
#line 163 "../fortran-tests/clstp.f"
    if (ke >= 0) {
#line 163 "../fortran-tests/clstp.f"
	conde = cond[2];
#line 163 "../fortran-tests/clstp.f"
    }
/*<       IF (KG.GE.0) CONDG = COND(3) >*/
#line 164 "../fortran-tests/clstp.f"
    if (kg >= 0) {
#line 164 "../fortran-tests/clstp.f"
	condg = cond[3];
#line 164 "../fortran-tests/clstp.f"
    }

/*     CHECK THE VALIDITY OF THE INPUT */
/*<        >*/
#line 167 "../fortran-tests/clstp.f"
    if (ka <= 5 && ke <= 5 && kg <= 5 && ki <= 5 && kn <= 5) {
#line 167 "../fortran-tests/clstp.f"
	goto L40;
#line 167 "../fortran-tests/clstp.f"
    }
/*<       WRITE (LOUT,99999) >*/
#line 169 "../fortran-tests/clstp.f"
    io___23.ciunit = lout;
#line 169 "../fortran-tests/clstp.f"
    s_wsfe(&io___23);
#line 169 "../fortran-tests/clstp.f"
    e_wsfe();
/*<       RETURN >*/
#line 170 "../fortran-tests/clstp.f"
    return 0;
/*<    40  >*/
#line 171 "../fortran-tests/clstp.f"
L40:
#line 171 "../fortran-tests/clstp.f"
    if (! (conda < one || conde < one || condg < one)) {
#line 171 "../fortran-tests/clstp.f"
	goto L50;
#line 171 "../fortran-tests/clstp.f"
    }
/*<       WRITE (LOUT,99998) >*/
#line 173 "../fortran-tests/clstp.f"
    io___24.ciunit = lout;
#line 173 "../fortran-tests/clstp.f"
    s_wsfe(&io___24);
#line 173 "../fortran-tests/clstp.f"
    e_wsfe();
/*< 99999  >*/
/*< 99998 FORMAT (/46H CONDA, CONDE, AND CONDG MUST ALL BE .GE. ONE.) >*/
/*<       RETURN >*/
#line 177 "../fortran-tests/clstp.f"
    return 0;
/*<    50 CONTINUE >*/
#line 178 "../fortran-tests/clstp.f"
L50:
/*<       ICASE = 1 >*/
#line 179 "../fortran-tests/clstp.f"
    icase = 1;
/*<    60 CONTINUE >*/
#line 180 "../fortran-tests/clstp.f"
L60:
/*<       ISEED = 100001 >*/
#line 181 "../fortran-tests/clstp.f"
    iseed = 100001;
/*<       T = RAN(ISEED) >*/
#line 182 "../fortran-tests/clstp.f"
    t = ran_(&iseed);
/*<       ISEED = 0 >*/
#line 183 "../fortran-tests/clstp.f"
    iseed = 0;

/*     COMPUTE THE PRE-MULTIPLYING HADAMARD MATRIX FOR E. */
/*<       K = KE >*/
#line 186 "../fortran-tests/clstp.f"
    k = ke;
/*<       ASSIGN 70 TO NGO >*/
#line 187 "../fortran-tests/clstp.f"
    ngo = 0;
#line 187 "../fortran-tests/clstp.f"
    ngo_fmt = fmt_70;
/*<       GO TO 900 >*/
#line 188 "../fortran-tests/clstp.f"
    goto L900;
/*<    70 ME = NN >*/
#line 189 "../fortran-tests/clstp.f"
L70:
#line 189 "../fortran-tests/clstp.f"
    me = nn;

/*     SAVE THE HADAMARD MATRIX. */
/*<       J = 1 >*/
#line 192 "../fortran-tests/clstp.f"
    j = 1;
/*<       N20011 = ME >*/
#line 193 "../fortran-tests/clstp.f"
    n20011 = me;
/*<       GO TO 90 >*/
#line 194 "../fortran-tests/clstp.f"
    goto L90;
/*<    80 J = J + 1 >*/
#line 195 "../fortran-tests/clstp.f"
L80:
#line 195 "../fortran-tests/clstp.f"
    ++j;
/*<    90 IF ((N20011-J).LT.0) GO TO 100 >*/
#line 196 "../fortran-tests/clstp.f"
L90:
#line 196 "../fortran-tests/clstp.f"
    if (n20011 - j < 0) {
#line 196 "../fortran-tests/clstp.f"
	goto L100;
#line 196 "../fortran-tests/clstp.f"
    }
/*<       CALL DCOPY(ME, HH(1,J), 1, GG(1,J), 1) >*/
#line 197 "../fortran-tests/clstp.f"
    dcopy_(&me, &hh[(j << 5) - 32], &c__1, &gg[(j << 5) - 32], &c__1);
/*<       GO TO 80 >*/
#line 198 "../fortran-tests/clstp.f"
    goto L80;

/*     NOW FORM THE POST-MULTIPLYING HADAMARD MATRIX. */
/*<   100 K = KN >*/
#line 201 "../fortran-tests/clstp.f"
L100:
#line 201 "../fortran-tests/clstp.f"
    k = kn;
/*<       ASSIGN 110 TO NGO >*/
#line 202 "../fortran-tests/clstp.f"
    ngo = 1;
#line 202 "../fortran-tests/clstp.f"
    ngo_fmt = fmt_110;
/*<       GO TO 900 >*/
#line 203 "../fortran-tests/clstp.f"
    goto L900;
/*<   110 N = NN >*/
#line 204 "../fortran-tests/clstp.f"
L110:
#line 204 "../fortran-tests/clstp.f"
    n = nn;

/*     COMPUTE THE SINGULAR VALUES OF THE MATRIX E. */
/*     DISTRIBUTE THEM UNIFORMLY BETWEEN 1. AND CONDE. */
/*<       SE(1) = CONDE >*/
#line 208 "../fortran-tests/clstp.f"
    se[0] = conde;
/*<       MNE = MAX0(1,MIN0(ME,N)) >*/
/* Computing MAX */
#line 209 "../fortran-tests/clstp.f"
    i__1 = 1, i__2 = min(me,n);
#line 209 "../fortran-tests/clstp.f"
    mne = max(i__1,i__2);
/*<       SE(MNE) = ONE >*/
#line 210 "../fortran-tests/clstp.f"
    se[mne - 1] = one;
/*<       I = 2 >*/
#line 211 "../fortran-tests/clstp.f"
    i__ = 2;
/*<       N20016 = MNE - 1 >*/
#line 212 "../fortran-tests/clstp.f"
    n20016 = mne - 1;
/*<       GO TO 130 >*/
#line 213 "../fortran-tests/clstp.f"
    goto L130;
/*<   120 I = I + 1 >*/
#line 214 "../fortran-tests/clstp.f"
L120:
#line 214 "../fortran-tests/clstp.f"
    ++i__;
/*<   130 IF ((N20016-I).LT.0) GO TO 140 >*/
#line 215 "../fortran-tests/clstp.f"
L130:
#line 215 "../fortran-tests/clstp.f"
    if (n20016 - i__ < 0) {
#line 215 "../fortran-tests/clstp.f"
	goto L140;
#line 215 "../fortran-tests/clstp.f"
    }
/*<       SE(I) = ONE + RAN(ISEED)*(CONDE-ONE) >*/
#line 216 "../fortran-tests/clstp.f"
    se[i__ - 1] = one + ran_(&iseed) * (conde - one);
/*<       GO TO 120 >*/
#line 217 "../fortran-tests/clstp.f"
    goto L120;
/*<   140 J = 1 >*/
#line 218 "../fortran-tests/clstp.f"
L140:
#line 218 "../fortran-tests/clstp.f"
    j = 1;
/*<       N20020 = MNE >*/
#line 219 "../fortran-tests/clstp.f"
    n20020 = mne;
/*<       GO TO 160 >*/
#line 220 "../fortran-tests/clstp.f"
    goto L160;
/*<   150 J = J + 1 >*/
#line 221 "../fortran-tests/clstp.f"
L150:
#line 221 "../fortran-tests/clstp.f"
    ++j;
/*<   160 IF ((N20020-J).LT.0) GO TO 170 >*/
#line 222 "../fortran-tests/clstp.f"
L160:
#line 222 "../fortran-tests/clstp.f"
    if (n20020 - j < 0) {
#line 222 "../fortran-tests/clstp.f"
	goto L170;
#line 222 "../fortran-tests/clstp.f"
    }
/*<       CALL DSCAL(ME, SE(J), GG(1,J), 1) >*/
#line 223 "../fortran-tests/clstp.f"
    dscal_(&me, &se[j - 1], &gg[(j << 5) - 32], &c__1);
/*<       GO TO 150 >*/
#line 224 "../fortran-tests/clstp.f"
    goto L150;
/*<   170 J = 1 >*/
#line 225 "../fortran-tests/clstp.f"
L170:
#line 225 "../fortran-tests/clstp.f"
    j = 1;
/*<       N20024 = N >*/
#line 226 "../fortran-tests/clstp.f"
    n20024 = n;
/*<       GO TO 190 >*/
#line 227 "../fortran-tests/clstp.f"
    goto L190;
/*<   180 J = J + 1 >*/
#line 228 "../fortran-tests/clstp.f"
L180:
#line 228 "../fortran-tests/clstp.f"
    ++j;
/*<   190 IF ((N20024-J).LT.0) GO TO 230 >*/
#line 229 "../fortran-tests/clstp.f"
L190:
#line 229 "../fortran-tests/clstp.f"
    if (n20024 - j < 0) {
#line 229 "../fortran-tests/clstp.f"
	goto L230;
#line 229 "../fortran-tests/clstp.f"
    }
/*<       IF (ME.GT.0) W(1,J) = ZERO >*/
#line 230 "../fortran-tests/clstp.f"
    if (me > 0) {
#line 230 "../fortran-tests/clstp.f"
	w[j * 96 - 96] = zero;
#line 230 "../fortran-tests/clstp.f"
    }
/*<       CALL DCOPY(ME, W(1,J), 0, W(1,J), 1) >*/
#line 231 "../fortran-tests/clstp.f"
    dcopy_(&me, &w[j * 96 - 96], &c__0, &w[j * 96 - 96], &c__1);
/*<       I = 1 >*/
#line 232 "../fortran-tests/clstp.f"
    i__ = 1;
/*<       N20028 = MNE >*/
#line 233 "../fortran-tests/clstp.f"
    n20028 = mne;
/*<       GO TO 210 >*/
#line 234 "../fortran-tests/clstp.f"
    goto L210;
/*<   200 I = I + 1 >*/
#line 235 "../fortran-tests/clstp.f"
L200:
#line 235 "../fortran-tests/clstp.f"
    ++i__;
/*<   210 IF ((N20028-I).LT.0) GO TO 220 >*/
#line 236 "../fortran-tests/clstp.f"
L210:
#line 236 "../fortran-tests/clstp.f"
    if (n20028 - i__ < 0) {
#line 236 "../fortran-tests/clstp.f"
	goto L220;
#line 236 "../fortran-tests/clstp.f"
    }
/*<       CALL DAXPY(ME, HH(I,J), GG(1,I), 1, W(1,J), 1) >*/
#line 237 "../fortran-tests/clstp.f"
    daxpy_(&me, &hh[i__ + (j << 5) - 33], &gg[(i__ << 5) - 32], &c__1, &w[j * 
	    96 - 96], &c__1);
/*<       GO TO 200 >*/
#line 238 "../fortran-tests/clstp.f"
    goto L200;
/*<   220 GO TO 180 >*/
#line 239 "../fortran-tests/clstp.f"
L220:
#line 239 "../fortran-tests/clstp.f"
    goto L180;

/*     COMPUTE E*X AND STORE IN W(*,N+1). */
/*<   230 I = 1 >*/
#line 242 "../fortran-tests/clstp.f"
L230:
#line 242 "../fortran-tests/clstp.f"
    i__ = 1;
/*<       N20032 = ME >*/
#line 243 "../fortran-tests/clstp.f"
    n20032 = me;
/*<       GO TO 250 >*/
#line 244 "../fortran-tests/clstp.f"
    goto L250;
/*<   240 I = I + 1 >*/
#line 245 "../fortran-tests/clstp.f"
L240:
#line 245 "../fortran-tests/clstp.f"
    ++i__;
/*<   250 IF ((N20032-I).LT.0) GO TO 260 >*/
#line 246 "../fortran-tests/clstp.f"
L250:
#line 246 "../fortran-tests/clstp.f"
    if (n20032 - i__ < 0) {
#line 246 "../fortran-tests/clstp.f"
	goto L260;
#line 246 "../fortran-tests/clstp.f"
    }
/*<       X(1) = ONE >*/
#line 247 "../fortran-tests/clstp.f"
    x[0] = one;
/*<       W(I,N+1) = DDOT(N,X,0,W(I,1),MDW) >*/
#line 248 "../fortran-tests/clstp.f"
    w[i__ + (n + 1) * 96 - 97] = ddot_(&n, x, &c__0, &w[i__ - 1], &mdw);
/*<       GO TO 240 >*/
#line 249 "../fortran-tests/clstp.f"
    goto L240;

/*     COMPUTE THE PRE-MULTIPLYING HADAMARD MATRIX FOR A. */
/*<   260 K = KA >*/
#line 252 "../fortran-tests/clstp.f"
L260:
#line 252 "../fortran-tests/clstp.f"
    k = ka;
/*<       ASSIGN 270 TO NGO >*/
#line 253 "../fortran-tests/clstp.f"
    ngo = 2;
#line 253 "../fortran-tests/clstp.f"
    ngo_fmt = fmt_270;
/*<       GO TO 900 >*/
#line 254 "../fortran-tests/clstp.f"
    goto L900;
/*<   270 MA = NN >*/
#line 255 "../fortran-tests/clstp.f"
L270:
#line 255 "../fortran-tests/clstp.f"
    ma = nn;

/*     SAVE THE HADAMARD MATRIX. */
/*<       J = 1 >*/
#line 258 "../fortran-tests/clstp.f"
    j = 1;
/*<       N20037 = MA >*/
#line 259 "../fortran-tests/clstp.f"
    n20037 = ma;
/*<       GO TO 290 >*/
#line 260 "../fortran-tests/clstp.f"
    goto L290;
/*<   280 J = J + 1 >*/
#line 261 "../fortran-tests/clstp.f"
L280:
#line 261 "../fortran-tests/clstp.f"
    ++j;
/*<   290 IF ((N20037-J).LT.0) GO TO 300 >*/
#line 262 "../fortran-tests/clstp.f"
L290:
#line 262 "../fortran-tests/clstp.f"
    if (n20037 - j < 0) {
#line 262 "../fortran-tests/clstp.f"
	goto L300;
#line 262 "../fortran-tests/clstp.f"
    }
/*<       CALL DCOPY(MA, HH(1,J), 1, GG(1,J), 1) >*/
#line 263 "../fortran-tests/clstp.f"
    dcopy_(&ma, &hh[(j << 5) - 32], &c__1, &gg[(j << 5) - 32], &c__1);
/*<       GO TO 280 >*/
#line 264 "../fortran-tests/clstp.f"
    goto L280;

/*     NOW FORM THE POST-MULTIPLYING HADAMARD MATRIX. */
/*<   300 K = KN >*/
#line 267 "../fortran-tests/clstp.f"
L300:
#line 267 "../fortran-tests/clstp.f"
    k = kn;
/*<       ASSIGN 310 TO NGO >*/
#line 268 "../fortran-tests/clstp.f"
    ngo = 3;
#line 268 "../fortran-tests/clstp.f"
    ngo_fmt = fmt_310;
/*<       GO TO 900 >*/
#line 269 "../fortran-tests/clstp.f"
    goto L900;
/*<   310 N = NN >*/
#line 270 "../fortran-tests/clstp.f"
L310:
#line 270 "../fortran-tests/clstp.f"
    n = nn;

/*     COMPUTE THE SINGULAR VALUES OF THE MATRIX A. */
/*     DISTRUBUTE THEM UNIFORMLY BETWEEN 1. AND CONDA. */
/*<       SA(1) = CONDA >*/
#line 274 "../fortran-tests/clstp.f"
    sa[0] = conda;
/*<       MNA = MAX0(1,MIN0(MA,N)) >*/
/* Computing MAX */
#line 275 "../fortran-tests/clstp.f"
    i__1 = 1, i__2 = min(ma,n);
#line 275 "../fortran-tests/clstp.f"
    mna = max(i__1,i__2);
/*<       SA(MNA) = ONE >*/
#line 276 "../fortran-tests/clstp.f"
    sa[mna - 1] = one;
/*<       I = 2 >*/
#line 277 "../fortran-tests/clstp.f"
    i__ = 2;
/*<       N20042 = MNA - 1 >*/
#line 278 "../fortran-tests/clstp.f"
    n20042 = mna - 1;
/*<       GO TO 330 >*/
#line 279 "../fortran-tests/clstp.f"
    goto L330;
/*<   320 I = I + 1 >*/
#line 280 "../fortran-tests/clstp.f"
L320:
#line 280 "../fortran-tests/clstp.f"
    ++i__;
/*<   330 IF ((N20042-I).LT.0) GO TO 340 >*/
#line 281 "../fortran-tests/clstp.f"
L330:
#line 281 "../fortran-tests/clstp.f"
    if (n20042 - i__ < 0) {
#line 281 "../fortran-tests/clstp.f"
	goto L340;
#line 281 "../fortran-tests/clstp.f"
    }
/*<       SA(I) = ONE + RAN(ISEED)*(CONDA-ONE) >*/
#line 282 "../fortran-tests/clstp.f"
    sa[i__ - 1] = one + ran_(&iseed) * (conda - one);
/*<       GO TO 320 >*/
#line 283 "../fortran-tests/clstp.f"
    goto L320;
/*<   340 J = 1 >*/
#line 284 "../fortran-tests/clstp.f"
L340:
#line 284 "../fortran-tests/clstp.f"
    j = 1;
/*<       N20046 = MNA >*/
#line 285 "../fortran-tests/clstp.f"
    n20046 = mna;
/*<       GO TO 360 >*/
#line 286 "../fortran-tests/clstp.f"
    goto L360;
/*<   350 J = J + 1 >*/
#line 287 "../fortran-tests/clstp.f"
L350:
#line 287 "../fortran-tests/clstp.f"
    ++j;
/*<   360 IF ((N20046-J).LT.0) GO TO 370 >*/
#line 288 "../fortran-tests/clstp.f"
L360:
#line 288 "../fortran-tests/clstp.f"
    if (n20046 - j < 0) {
#line 288 "../fortran-tests/clstp.f"
	goto L370;
#line 288 "../fortran-tests/clstp.f"
    }
/*<       CALL DSCAL(MA, SA(J), GG(1,J), 1) >*/
#line 289 "../fortran-tests/clstp.f"
    dscal_(&ma, &sa[j - 1], &gg[(j << 5) - 32], &c__1);
/*<       GO TO 350 >*/
#line 290 "../fortran-tests/clstp.f"
    goto L350;
/*<   370 J = 1 >*/
#line 291 "../fortran-tests/clstp.f"
L370:
#line 291 "../fortran-tests/clstp.f"
    j = 1;
/*<       N20050 = N >*/
#line 292 "../fortran-tests/clstp.f"
    n20050 = n;
/*<       GO TO 390 >*/
#line 293 "../fortran-tests/clstp.f"
    goto L390;
/*<   380 J = J + 1 >*/
#line 294 "../fortran-tests/clstp.f"
L380:
#line 294 "../fortran-tests/clstp.f"
    ++j;
/*<   390 IF ((N20050-J).LT.0) GO TO 430 >*/
#line 295 "../fortran-tests/clstp.f"
L390:
#line 295 "../fortran-tests/clstp.f"
    if (n20050 - j < 0) {
#line 295 "../fortran-tests/clstp.f"
	goto L430;
#line 295 "../fortran-tests/clstp.f"
    }

/*     COMPUTE THE PRODUCT IN PLACE INTO W(*,*). */
/*<       IF (MA.GT.0) W(ME+1,J) = ZERO >*/
#line 298 "../fortran-tests/clstp.f"
    if (ma > 0) {
#line 298 "../fortran-tests/clstp.f"
	w[me + 1 + j * 96 - 97] = zero;
#line 298 "../fortran-tests/clstp.f"
    }
/*<       CALL DCOPY(MA, W(ME+1,J), 0, W(ME+1,J), 1) >*/
#line 299 "../fortran-tests/clstp.f"
    dcopy_(&ma, &w[me + 1 + j * 96 - 97], &c__0, &w[me + 1 + j * 96 - 97], &
	    c__1);
/*<       I = 1 >*/
#line 300 "../fortran-tests/clstp.f"
    i__ = 1;
/*<       N20054 = MNA >*/
#line 301 "../fortran-tests/clstp.f"
    n20054 = mna;
/*<       GO TO 410 >*/
#line 302 "../fortran-tests/clstp.f"
    goto L410;
/*<   400 I = I + 1 >*/
#line 303 "../fortran-tests/clstp.f"
L400:
#line 303 "../fortran-tests/clstp.f"
    ++i__;
/*<   410 IF ((N20054-I).LT.0) GO TO 420 >*/
#line 304 "../fortran-tests/clstp.f"
L410:
#line 304 "../fortran-tests/clstp.f"
    if (n20054 - i__ < 0) {
#line 304 "../fortran-tests/clstp.f"
	goto L420;
#line 304 "../fortran-tests/clstp.f"
    }
/*<       CALL DAXPY(MA, HH(I,J), GG(1,I), 1, W(ME+1,J), 1) >*/
#line 305 "../fortran-tests/clstp.f"
    daxpy_(&ma, &hh[i__ + (j << 5) - 33], &gg[(i__ << 5) - 32], &c__1, &w[me 
	    + 1 + j * 96 - 97], &c__1);
/*<       GO TO 400 >*/
#line 306 "../fortran-tests/clstp.f"
    goto L400;
/*<   420 GO TO 380 >*/
#line 307 "../fortran-tests/clstp.f"
L420:
#line 307 "../fortran-tests/clstp.f"
    goto L380;

/*     COMPUTE A*X AND STORE IN W(*,N+1). */
/*<   430 I = 1 >*/
#line 310 "../fortran-tests/clstp.f"
L430:
#line 310 "../fortran-tests/clstp.f"
    i__ = 1;
/*<       N20058 = MA >*/
#line 311 "../fortran-tests/clstp.f"
    n20058 = ma;
/*<       GO TO 450 >*/
#line 312 "../fortran-tests/clstp.f"
    goto L450;
/*<   440 I = I + 1 >*/
#line 313 "../fortran-tests/clstp.f"
L440:
#line 313 "../fortran-tests/clstp.f"
    ++i__;
/*<   450 IF ((N20058-I).LT.0) GO TO 460 >*/
#line 314 "../fortran-tests/clstp.f"
L450:
#line 314 "../fortran-tests/clstp.f"
    if (n20058 - i__ < 0) {
#line 314 "../fortran-tests/clstp.f"
	goto L460;
#line 314 "../fortran-tests/clstp.f"
    }
/*<       MEPI = ME + I >*/
#line 315 "../fortran-tests/clstp.f"
    mepi = me + i__;
/*<       X(1) = ONE >*/
#line 316 "../fortran-tests/clstp.f"
    x[0] = one;
/*<       W(MEPI,N+1) = DDOT(N,X,0,W(MEPI,1),MDW) >*/
#line 317 "../fortran-tests/clstp.f"
    w[mepi + (n + 1) * 96 - 97] = ddot_(&n, x, &c__0, &w[mepi - 1], &mdw);
/*<       GO TO 440 >*/
#line 318 "../fortran-tests/clstp.f"
    goto L440;
/*<   460 BNORM = DNRM2(MA,W(ME+1,N+1),1) >*/
#line 319 "../fortran-tests/clstp.f"
L460:
#line 319 "../fortran-tests/clstp.f"
    bnorm = dnrm2_(&ma, &w[me + 1 + (n + 1) * 96 - 97], &c__1);

/*     ADD COMPONENTS TO RIGHT SIDE THAT ARE ORTHOGONAL TO COL. */
/*     SPACE OF A. */
/*<       K = KA >*/
#line 323 "../fortran-tests/clstp.f"
    k = ka;
/*<       ASSIGN 470 TO NGO >*/
#line 324 "../fortran-tests/clstp.f"
    ngo = 4;
#line 324 "../fortran-tests/clstp.f"
    ngo_fmt = fmt_470;
/*<       GO TO 900 >*/
#line 325 "../fortran-tests/clstp.f"
    goto L900;
/*<   470 MA = NN >*/
#line 326 "../fortran-tests/clstp.f"
L470:
#line 326 "../fortran-tests/clstp.f"
    ma = nn;
/*<       I = N + 1 >*/
#line 327 "../fortran-tests/clstp.f"
    i__ = n + 1;
/*<       N20063 = MA >*/
#line 328 "../fortran-tests/clstp.f"
    n20063 = ma;
/*<       GO TO 490 >*/
#line 329 "../fortran-tests/clstp.f"
    goto L490;
/*<   480 I = I + 1 >*/
#line 330 "../fortran-tests/clstp.f"
L480:
#line 330 "../fortran-tests/clstp.f"
    ++i__;
/*<   490 IF ((N20063-I).LT.0) GO TO 500 >*/
#line 331 "../fortran-tests/clstp.f"
L490:
#line 331 "../fortran-tests/clstp.f"
    if (n20063 - i__ < 0) {
#line 331 "../fortran-tests/clstp.f"
	goto L500;
#line 331 "../fortran-tests/clstp.f"
    }
/*<       T = RAN(ISEED)*BNORM*ANSR >*/
#line 332 "../fortran-tests/clstp.f"
    t = ran_(&iseed) * bnorm * ansr;
/*<       CALL DAXPY(MA, T, HH(1,I), 1, W(ME+1,N+1), 1) >*/
#line 333 "../fortran-tests/clstp.f"
    daxpy_(&ma, &t, &hh[(i__ << 5) - 32], &c__1, &w[me + 1 + (n + 1) * 96 - 
	    97], &c__1);
/*<       GO TO 480 >*/
#line 334 "../fortran-tests/clstp.f"
    goto L480;

/*     COMPUTE THE PRE-MULTIPLYING HADAMARD MATRIX FOR G. */
/*<   500 K = KG >*/
#line 337 "../fortran-tests/clstp.f"
L500:
#line 337 "../fortran-tests/clstp.f"
    k = kg;
/*<       ASSIGN 510 TO NGO >*/
#line 338 "../fortran-tests/clstp.f"
    ngo = 5;
#line 338 "../fortran-tests/clstp.f"
    ngo_fmt = fmt_510;
/*<       GO TO 900 >*/
#line 339 "../fortran-tests/clstp.f"
    goto L900;
/*<   510 MG = NN >*/
#line 340 "../fortran-tests/clstp.f"
L510:
#line 340 "../fortran-tests/clstp.f"
    mg = nn;

/*     SAVE THE HADAMARD MATRIX. */
/*<       J = 1 >*/
#line 343 "../fortran-tests/clstp.f"
    j = 1;
/*<       N20068 = MG >*/
#line 344 "../fortran-tests/clstp.f"
    n20068 = mg;
/*<       GO TO 530 >*/
#line 345 "../fortran-tests/clstp.f"
    goto L530;
/*<   520 J = J + 1 >*/
#line 346 "../fortran-tests/clstp.f"
L520:
#line 346 "../fortran-tests/clstp.f"
    ++j;
/*<   530 IF ((N20068-J).LT.0) GO TO 540 >*/
#line 347 "../fortran-tests/clstp.f"
L530:
#line 347 "../fortran-tests/clstp.f"
    if (n20068 - j < 0) {
#line 347 "../fortran-tests/clstp.f"
	goto L540;
#line 347 "../fortran-tests/clstp.f"
    }
/*<       CALL DCOPY(MG, HH(1,J), 1, GG(1,J), 1) >*/
#line 348 "../fortran-tests/clstp.f"
    dcopy_(&mg, &hh[(j << 5) - 32], &c__1, &gg[(j << 5) - 32], &c__1);
/*<       GO TO 520 >*/
#line 349 "../fortran-tests/clstp.f"
    goto L520;

/*     NOW FORM THE POST-MULTIPLYING HADAMARD MATRIX. */
/*<   540 K = KN >*/
#line 352 "../fortran-tests/clstp.f"
L540:
#line 352 "../fortran-tests/clstp.f"
    k = kn;
/*<       ASSIGN 550 TO NGO >*/
#line 353 "../fortran-tests/clstp.f"
    ngo = 6;
#line 353 "../fortran-tests/clstp.f"
    ngo_fmt = fmt_550;
/*<       GO TO 900 >*/
#line 354 "../fortran-tests/clstp.f"
    goto L900;
/*<   550 N = NN >*/
#line 355 "../fortran-tests/clstp.f"
L550:
#line 355 "../fortran-tests/clstp.f"
    n = nn;

/*     COMPUTE THE SINGULAR VALUES OF G. */
/*     DISTRIBUTE THEM UNIFORMLY BETWEEN 1. AND CONDG. */
/*<       SG(1) = CONDG >*/
#line 359 "../fortran-tests/clstp.f"
    sg[0] = condg;
/*<       MNG = MAX0(1,MIN0(MG,N)) >*/
/* Computing MAX */
#line 360 "../fortran-tests/clstp.f"
    i__1 = 1, i__2 = min(mg,n);
#line 360 "../fortran-tests/clstp.f"
    mng = max(i__1,i__2);
/*<       SG(MNG) = ONE >*/
#line 361 "../fortran-tests/clstp.f"
    sg[mng - 1] = one;
/*<       I = 2 >*/
#line 362 "../fortran-tests/clstp.f"
    i__ = 2;
/*<       N20073 = MNG - 1 >*/
#line 363 "../fortran-tests/clstp.f"
    n20073 = mng - 1;
/*<       GO TO 570 >*/
#line 364 "../fortran-tests/clstp.f"
    goto L570;
/*<   560 I = I + 1 >*/
#line 365 "../fortran-tests/clstp.f"
L560:
#line 365 "../fortran-tests/clstp.f"
    ++i__;
/*<   570 IF ((N20073-I).LT.0) GO TO 580 >*/
#line 366 "../fortran-tests/clstp.f"
L570:
#line 366 "../fortran-tests/clstp.f"
    if (n20073 - i__ < 0) {
#line 366 "../fortran-tests/clstp.f"
	goto L580;
#line 366 "../fortran-tests/clstp.f"
    }
/*<       SG(I) = ONE + RAN(ISEED)*(CONDG-ONE) >*/
#line 367 "../fortran-tests/clstp.f"
    sg[i__ - 1] = one + ran_(&iseed) * (condg - one);
/*<       GO TO 560 >*/
#line 368 "../fortran-tests/clstp.f"
    goto L560;
/*<   580 J = 1 >*/
#line 369 "../fortran-tests/clstp.f"
L580:
#line 369 "../fortran-tests/clstp.f"
    j = 1;
/*<       N20077 = MNG >*/
#line 370 "../fortran-tests/clstp.f"
    n20077 = mng;
/*<       GO TO 600 >*/
#line 371 "../fortran-tests/clstp.f"
    goto L600;
/*<   590 J = J + 1 >*/
#line 372 "../fortran-tests/clstp.f"
L590:
#line 372 "../fortran-tests/clstp.f"
    ++j;
/*<   600 IF ((N20077-J).LT.0) GO TO 610 >*/
#line 373 "../fortran-tests/clstp.f"
L600:
#line 373 "../fortran-tests/clstp.f"
    if (n20077 - j < 0) {
#line 373 "../fortran-tests/clstp.f"
	goto L610;
#line 373 "../fortran-tests/clstp.f"
    }
/*<       CALL DSCAL(MG, SG(J), GG(1,J), 1) >*/
#line 374 "../fortran-tests/clstp.f"
    dscal_(&mg, &sg[j - 1], &gg[(j << 5) - 32], &c__1);
/*<       GO TO 590 >*/
#line 375 "../fortran-tests/clstp.f"
    goto L590;
/*<   610 J = 1 >*/
#line 376 "../fortran-tests/clstp.f"
L610:
#line 376 "../fortran-tests/clstp.f"
    j = 1;
/*<       N20081 = N >*/
#line 377 "../fortran-tests/clstp.f"
    n20081 = n;
/*<       GO TO 630 >*/
#line 378 "../fortran-tests/clstp.f"
    goto L630;
/*<   620 J = J + 1 >*/
#line 379 "../fortran-tests/clstp.f"
L620:
#line 379 "../fortran-tests/clstp.f"
    ++j;
/*<   630 IF ((N20081-J).LT.0) GO TO 670 >*/
#line 380 "../fortran-tests/clstp.f"
L630:
#line 380 "../fortran-tests/clstp.f"
    if (n20081 - j < 0) {
#line 380 "../fortran-tests/clstp.f"
	goto L670;
#line 380 "../fortran-tests/clstp.f"
    }
/*<       MEPMA = ME + MA >*/
#line 381 "../fortran-tests/clstp.f"
    mepma = me + ma;
/*<       IF (MG.GT.0) W(MEPMA+1,J) = ZERO >*/
#line 382 "../fortran-tests/clstp.f"
    if (mg > 0) {
#line 382 "../fortran-tests/clstp.f"
	w[mepma + 1 + j * 96 - 97] = zero;
#line 382 "../fortran-tests/clstp.f"
    }
/*<       CALL DCOPY(MG, W(MEPMA+1,J), 0, W(MEPMA+1,J), 1) >*/
#line 383 "../fortran-tests/clstp.f"
    dcopy_(&mg, &w[mepma + 1 + j * 96 - 97], &c__0, &w[mepma + 1 + j * 96 - 
	    97], &c__1);
/*<       I = 1 >*/
#line 384 "../fortran-tests/clstp.f"
    i__ = 1;
/*<       N20085 = MNG >*/
#line 385 "../fortran-tests/clstp.f"
    n20085 = mng;
/*<       GO TO 650 >*/
#line 386 "../fortran-tests/clstp.f"
    goto L650;
/*<   640 I = I + 1 >*/
#line 387 "../fortran-tests/clstp.f"
L640:
#line 387 "../fortran-tests/clstp.f"
    ++i__;
/*<   650 IF ((N20085-I).LT.0) GO TO 660 >*/
#line 388 "../fortran-tests/clstp.f"
L650:
#line 388 "../fortran-tests/clstp.f"
    if (n20085 - i__ < 0) {
#line 388 "../fortran-tests/clstp.f"
	goto L660;
#line 388 "../fortran-tests/clstp.f"
    }
/*<       CALL DAXPY(MG, HH(I,J), GG(1,I), 1, W(MEPMA+1,J), 1) >*/
#line 389 "../fortran-tests/clstp.f"
    daxpy_(&mg, &hh[i__ + (j << 5) - 33], &gg[(i__ << 5) - 32], &c__1, &w[
	    mepma + 1 + j * 96 - 97], &c__1);
/*<       GO TO 640 >*/
#line 390 "../fortran-tests/clstp.f"
    goto L640;
/*<   660 GO TO 620 >*/
#line 391 "../fortran-tests/clstp.f"
L660:
#line 391 "../fortran-tests/clstp.f"
    goto L620;

/*     COMPUTE G*X AND STORE IN W(*,N+1). */
/*<   670 I = 1 >*/
#line 394 "../fortran-tests/clstp.f"
L670:
#line 394 "../fortran-tests/clstp.f"
    i__ = 1;
/*<       N20089 = MG >*/
#line 395 "../fortran-tests/clstp.f"
    n20089 = mg;
/*<       GO TO 690 >*/
#line 396 "../fortran-tests/clstp.f"
    goto L690;
/*<   680 I = I + 1 >*/
#line 397 "../fortran-tests/clstp.f"
L680:
#line 397 "../fortran-tests/clstp.f"
    ++i__;
/*<   690 IF ((N20089-I).LT.0) GO TO 700 >*/
#line 398 "../fortran-tests/clstp.f"
L690:
#line 398 "../fortran-tests/clstp.f"
    if (n20089 - i__ < 0) {
#line 398 "../fortran-tests/clstp.f"
	goto L700;
#line 398 "../fortran-tests/clstp.f"
    }
/*<       IROW = I + MEPMA >*/
#line 399 "../fortran-tests/clstp.f"
    irow = i__ + mepma;
/*<       X(1) = ONE >*/
#line 400 "../fortran-tests/clstp.f"
    x[0] = one;
/*<       W(IROW,N+1) = DDOT(N,X,0,W(IROW,1),MDW) >*/
#line 401 "../fortran-tests/clstp.f"
    w[irow + (n + 1) * 96 - 97] = ddot_(&n, x, &c__0, &w[irow - 1], &mdw);
/*<       GO TO 680 >*/
#line 402 "../fortran-tests/clstp.f"
    goto L680;

/*     MAKE FIRST MI=2**KI OF THE INEQUALITIES STRICT. */
/*<   700 IF (.NOT.(KI.GE.0)) GO TO 710 >*/
#line 405 "../fortran-tests/clstp.f"
L700:
#line 405 "../fortran-tests/clstp.f"
    if (! (ki >= 0)) {
#line 405 "../fortran-tests/clstp.f"
	goto L710;
#line 405 "../fortran-tests/clstp.f"
    }
/*<       MI = 1 >*/
#line 406 "../fortran-tests/clstp.f"
    mi = 1;
/*<       GO TO 720 >*/
#line 407 "../fortran-tests/clstp.f"
    goto L720;
/*<   710 MI = 0 >*/
#line 408 "../fortran-tests/clstp.f"
L710:
#line 408 "../fortran-tests/clstp.f"
    mi = 0;
/*<   720 K = 1 >*/
#line 409 "../fortran-tests/clstp.f"
L720:
#line 409 "../fortran-tests/clstp.f"
    k = 1;
/*<       N20096 = KI >*/
#line 410 "../fortran-tests/clstp.f"
    n20096 = ki;
/*<       GO TO 740 >*/
#line 411 "../fortran-tests/clstp.f"
    goto L740;
/*<   730 K = K + 1 >*/
#line 412 "../fortran-tests/clstp.f"
L730:
#line 412 "../fortran-tests/clstp.f"
    ++k;
/*<   740 IF ((N20096-K).LT.0) GO TO 750 >*/
#line 413 "../fortran-tests/clstp.f"
L740:
#line 413 "../fortran-tests/clstp.f"
    if (n20096 - k < 0) {
#line 413 "../fortran-tests/clstp.f"
	goto L750;
#line 413 "../fortran-tests/clstp.f"
    }
/*<       MI = MI + MI >*/
#line 414 "../fortran-tests/clstp.f"
    mi += mi;
/*<       GO TO 730 >*/
#line 415 "../fortran-tests/clstp.f"
    goto L730;
/*<   750 GNORM = DNRM2(MG,W(MEPMA+1,N+1),1) >*/
#line 416 "../fortran-tests/clstp.f"
L750:
#line 416 "../fortran-tests/clstp.f"
    gnorm = dnrm2_(&mg, &w[mepma + 1 + (n + 1) * 96 - 97], &c__1);
/*<       I = 1 >*/
#line 417 "../fortran-tests/clstp.f"
    i__ = 1;
/*<       N20100 = MIN0(MI,MG) >*/
#line 418 "../fortran-tests/clstp.f"
    n20100 = min(mi,mg);
/*<       GO TO 770 >*/
#line 419 "../fortran-tests/clstp.f"
    goto L770;
/*<   760 I = I + 1 >*/
#line 420 "../fortran-tests/clstp.f"
L760:
#line 420 "../fortran-tests/clstp.f"
    ++i__;
/*<   770 IF ((N20100-I).LT.0) GO TO 780 >*/
#line 421 "../fortran-tests/clstp.f"
L770:
#line 421 "../fortran-tests/clstp.f"
    if (n20100 - i__ < 0) {
#line 421 "../fortran-tests/clstp.f"
	goto L780;
#line 421 "../fortran-tests/clstp.f"
    }
/*<       IROW = I + MEPMA >*/
#line 422 "../fortran-tests/clstp.f"
    irow = i__ + mepma;
/*<       W(IROW,N+1) = W(IROW,N+1) - RAN(ISEED)*GNORM >*/
#line 423 "../fortran-tests/clstp.f"
    w[irow + (n + 1) * 96 - 97] -= ran_(&iseed) * gnorm;
/*<       GO TO 760 >*/
#line 424 "../fortran-tests/clstp.f"
    goto L760;

/*     OBTAIN THE CONSTRAINED LEAST SQUARES SOLUTION. */

/*     NOTE THE LENGTHS OF THE WORK ARRAYS IN IWORK(*). */
/*<   780 IWORK(1) = 1518 >*/
#line 429 "../fortran-tests/clstp.f"
L780:
#line 429 "../fortran-tests/clstp.f"
    iwork[0] = 1518;
/*<       IWORK(2) = 0640 >*/
#line 430 "../fortran-tests/clstp.f"
    iwork[1] = 640;
/*<       IF (.NOT.(ICASE.EQ.1)) GO TO 810 >*/
#line 431 "../fortran-tests/clstp.f"
    if (! (icase == 1)) {
#line 431 "../fortran-tests/clstp.f"
	goto L810;
#line 431 "../fortran-tests/clstp.f"
    }

/*     EXCHANGE POSITIONS OF THE ROWS (A B) AND (G H). */
/*<       NP1 = N + 1 >*/
#line 434 "../fortran-tests/clstp.f"
    np1 = n + 1;
/*<       DO 790 J=1,NP1 >*/
#line 435 "../fortran-tests/clstp.f"
    i__1 = np1;
#line 435 "../fortran-tests/clstp.f"
    for (j = 1; j <= i__1; ++j) {
/*<         IROW = ME + (MA+MG+2)/2 >*/
#line 436 "../fortran-tests/clstp.f"
	irow = me + (ma + mg + 2) / 2;
/*<         CALL DSWAP((MA+MG+1)/2, W(ME+1,J), 1, W(IROW,J), -1) >*/
#line 437 "../fortran-tests/clstp.f"
	i__2 = (ma + mg + 1) / 2;
#line 437 "../fortran-tests/clstp.f"
	dswap_(&i__2, &w[me + 1 + j * 96 - 97], &c__1, &w[irow + j * 96 - 97],
		 &c_n1);
/*<   790 CONTINUE >*/
#line 438 "../fortran-tests/clstp.f"
/* L790: */
#line 438 "../fortran-tests/clstp.f"
    }

/*     MOVE RT-SIDE TO W(*,N+MG+1). */
/*<       JCOL = N + MG + 1 >*/
#line 441 "../fortran-tests/clstp.f"
    jcol = n + mg + 1;
/*<       CALL DCOPY(ME+MA+MG, W(1,N+1), 1, W(1,JCOL), 1) >*/
#line 442 "../fortran-tests/clstp.f"
    i__1 = me + ma + mg;
#line 442 "../fortran-tests/clstp.f"
    dcopy_(&i__1, &w[(n + 1) * 96 - 96], &c__1, &w[jcol * 96 - 96], &c__1);

/*     PUT IN SLACK VARIABLE COLS. AS REQUIRED. */
/*<       IF (.NOT.(MG.GT.0)) GO TO 800 >*/
#line 445 "../fortran-tests/clstp.f"
    if (! (mg > 0)) {
#line 445 "../fortran-tests/clstp.f"
	goto L800;
#line 445 "../fortran-tests/clstp.f"
    }
/*<       W(1,N+1) = ZERO >*/
#line 446 "../fortran-tests/clstp.f"
    w[(n + 1) * 96 - 96] = zero;
/*<       CALL DCOPY(MDW*MG, W(1,N+1), 0, W(1,N+1), 1) >*/
#line 447 "../fortran-tests/clstp.f"
    i__1 = mdw * mg;
#line 447 "../fortran-tests/clstp.f"
    dcopy_(&i__1, &w[(n + 1) * 96 - 96], &c__0, &w[(n + 1) * 96 - 96], &c__1);
/*<       W(ME+1,N+1) = -ONE >*/
#line 448 "../fortran-tests/clstp.f"
    w[me + 1 + (n + 1) * 96 - 97] = -one;
/*<       CALL DCOPY(MG, W(ME+1,N+1), 0, W(ME+1,N+1), MDW+1) >*/
#line 449 "../fortran-tests/clstp.f"
    i__1 = mdw + 1;
#line 449 "../fortran-tests/clstp.f"
    dcopy_(&mg, &w[me + 1 + (n + 1) * 96 - 97], &c__0, &w[me + 1 + (n + 1) * 
	    96 - 97], &i__1);
/*<   800 CONTINUE >*/
#line 450 "../fortran-tests/clstp.f"
L800:

/*     SET THE OPTION (NUMBER 6) FOR WNNLS( ) TO SCALE THE */
/*     COLUMNS OF THE MATRIX TO HAVE UNIT LENGTH. */
/*<       PRGOPT(1) = 4 >*/
#line 454 "../fortran-tests/clstp.f"
    prgopt[0] = 4.;
/*<       PRGOPT(2) = 6 >*/
#line 455 "../fortran-tests/clstp.f"
    prgopt[1] = 6.;
/*<       PRGOPT(3) = 1 >*/
#line 456 "../fortran-tests/clstp.f"
    prgopt[2] = 1.;
/*<       PRGOPT(4) = 1 >*/
#line 457 "../fortran-tests/clstp.f"
    prgopt[3] = 1.;
/*<        >*/
#line 458 "../fortran-tests/clstp.f"
    i__1 = me + mg;
#line 458 "../fortran-tests/clstp.f"
    i__2 = n + mg;
#line 458 "../fortran-tests/clstp.f"
    wnnls_(w, &mdw, &i__1, &ma, &i__2, &n, prgopt, x, &rnorml, &mode, iwork, 
	    work);
/*<       GO TO 820 >*/
#line 460 "../fortran-tests/clstp.f"
    goto L820;
/*<   810 CONTINUE >*/
#line 461 "../fortran-tests/clstp.f"
L810:

/*     SET THE OPTION (NUMBER 2) FOR LSEI( ) TO SCALE THE */
/*     COLUMNS OF THE MATRIX TO HAVE UNIT LENGTH. */
/*<       PRGOPT(1) = 4 >*/
#line 465 "../fortran-tests/clstp.f"
    prgopt[0] = 4.;
/*<       PRGOPT(2) = 2 >*/
#line 466 "../fortran-tests/clstp.f"
    prgopt[1] = 2.;
/*<       PRGOPT(3) = 1 >*/
#line 467 "../fortran-tests/clstp.f"
    prgopt[2] = 1.;
/*<       PRGOPT(4) = 1 >*/
#line 468 "../fortran-tests/clstp.f"
    prgopt[3] = 1.;
/*<        >*/
#line 469 "../fortran-tests/clstp.f"
    lsei_(w, &mdw, &me, &ma, &mg, &n, prgopt, x, &rnorme, &rnorml, &mode, 
	    work, iwork);
/*<   820 CONTINUE >*/
#line 471 "../fortran-tests/clstp.f"
L820:

/*     COMPUTE THE RESIDUAL SUM OF SQUARES OF ERRORS. */
/*<       SOLERR = ZERO >*/
#line 474 "../fortran-tests/clstp.f"
    solerr = zero;
/*<       I = 1 >*/
#line 475 "../fortran-tests/clstp.f"
    i__ = 1;
/*<       N20104 = N >*/
#line 476 "../fortran-tests/clstp.f"
    n20104 = n;
/*<       GO TO 840 >*/
#line 477 "../fortran-tests/clstp.f"
    goto L840;
/*<   830 I = I + 1 >*/
#line 478 "../fortran-tests/clstp.f"
L830:
#line 478 "../fortran-tests/clstp.f"
    ++i__;
/*<   840 IF ((N20104-I).LT.0) GO TO 850 >*/
#line 479 "../fortran-tests/clstp.f"
L840:
#line 479 "../fortran-tests/clstp.f"
    if (n20104 - i__ < 0) {
#line 479 "../fortran-tests/clstp.f"
	goto L850;
#line 479 "../fortran-tests/clstp.f"
    }
/*<       X(I) = ONE - X(I) >*/
#line 480 "../fortran-tests/clstp.f"
    x[i__ - 1] = one - x[i__ - 1];
/*<       SOLERR = SOLERR + X(I)**2 >*/
/* Computing 2nd power */
#line 481 "../fortran-tests/clstp.f"
    d__1 = x[i__ - 1];
#line 481 "../fortran-tests/clstp.f"
    solerr += d__1 * d__1;
/*<       GO TO 830 >*/
#line 482 "../fortran-tests/clstp.f"
    goto L830;
/*<   850 SOLERR = DSQRT(SOLERR) >*/
#line 483 "../fortran-tests/clstp.f"
L850:
#line 483 "../fortran-tests/clstp.f"
    solerr = sqrt(solerr);

/*     TEST SIZE OF ERROR (REF. LAWSON-HANSON, PAGE 51 AND CH. 16) */
/*<       PHI = 100. >*/
#line 486 "../fortran-tests/clstp.f"
    phi = 100.f;
/*<       T = N >*/
#line 487 "../fortran-tests/clstp.f"
    t = (doublereal) n;
/*<       DXBYX = SOLERR/DSQRT(T) >*/
#line 488 "../fortran-tests/clstp.f"
    dxbyx = solerr / sqrt(t);
/*<       RHO = ONE >*/
#line 489 "../fortran-tests/clstp.f"
    rho = one;
/*<       IF (BNORM.NE.ZERO) RHO = RNORML/BNORM >*/
#line 490 "../fortran-tests/clstp.f"
    if (bnorm != zero) {
#line 490 "../fortran-tests/clstp.f"
	rho = rnorml / bnorm;
#line 490 "../fortran-tests/clstp.f"
    }
/*<       GAM = (6*MAX0(MA,N)-3*MIN0(MA,N))*MIN0(MA,N) >*/
#line 491 "../fortran-tests/clstp.f"
    gam = (doublereal) ((max(ma,n) * 6 - min(ma,n) * 3) * min(ma,n));
/*<       BETA = CONDA*(ONE+CONDA*RHO)*GAM*PHI >*/
#line 492 "../fortran-tests/clstp.f"
    beta = conda * (one + conda * rho) * gam * phi;
/*<       IF (.NOT.(DXBYX+BETA.EQ.BETA)) GO TO 860 >*/
#line 493 "../fortran-tests/clstp.f"
    if (! (dxbyx + beta == beta)) {
#line 493 "../fortran-tests/clstp.f"
	goto L860;
#line 493 "../fortran-tests/clstp.f"
    }
/*<       ISTAT = ISTAT + ICASE >*/
#line 494 "../fortran-tests/clstp.f"
    *istat += icase;
/*<       GO TO 870 >*/
#line 495 "../fortran-tests/clstp.f"
    goto L870;
/*<   860 CONTINUE >*/
#line 496 "../fortran-tests/clstp.f"
L860:
/*<       IF (MA.EQ.0 .AND. MODE.EQ.0) ISTAT = ISTAT + ICASE >*/
#line 497 "../fortran-tests/clstp.f"
    if (ma == 0 && mode == 0) {
#line 497 "../fortran-tests/clstp.f"
	*istat += icase;
#line 497 "../fortran-tests/clstp.f"
    }
/*<   870 CONTINUE >*/
#line 498 "../fortran-tests/clstp.f"
L870:
/*<       IF (.NOT.(ICASE.EQ.1)) GO TO 880 >*/
#line 499 "../fortran-tests/clstp.f"
    if (! (icase == 1)) {
#line 499 "../fortran-tests/clstp.f"
	goto L880;
#line 499 "../fortran-tests/clstp.f"
    }
/*<       WRITE (LOUT,99997) RNORML >*/
#line 500 "../fortran-tests/clstp.f"
    io___85.ciunit = lout;
#line 500 "../fortran-tests/clstp.f"
    s_wsfe(&io___85);
#line 500 "../fortran-tests/clstp.f"
    do_fio(&c__1, (char *)&rnorml, (ftnlen)sizeof(doublereal));
#line 500 "../fortran-tests/clstp.f"
    e_wsfe();
/*< 99997  >*/
/*<       WRITE (LOUT,99996) (I,X(I),I=1,N) >*/
#line 503 "../fortran-tests/clstp.f"
    io___86.ciunit = lout;
#line 503 "../fortran-tests/clstp.f"
    s_wsfe(&io___86);
#line 503 "../fortran-tests/clstp.f"
    i__1 = n;
#line 503 "../fortran-tests/clstp.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
#line 503 "../fortran-tests/clstp.f"
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
#line 503 "../fortran-tests/clstp.f"
	do_fio(&c__1, (char *)&x[i__ - 1], (ftnlen)sizeof(doublereal));
#line 503 "../fortran-tests/clstp.f"
    }
#line 503 "../fortran-tests/clstp.f"
    e_wsfe();
/*< 99996 FORMAT (4(I4, E012.5)) >*/
/*<       GO TO 890 >*/
#line 505 "../fortran-tests/clstp.f"
    goto L890;
/*<   880 CONTINUE >*/
#line 506 "../fortran-tests/clstp.f"
L880:
/*<       WRITE (LOUT,99995) RNORML, IWORK(1), IWORK(2) >*/
#line 507 "../fortran-tests/clstp.f"
    io___87.ciunit = lout;
#line 507 "../fortran-tests/clstp.f"
    s_wsfe(&io___87);
#line 507 "../fortran-tests/clstp.f"
    do_fio(&c__1, (char *)&rnorml, (ftnlen)sizeof(doublereal));
#line 507 "../fortran-tests/clstp.f"
    do_fio(&c__1, (char *)&iwork[0], (ftnlen)sizeof(integer));
#line 507 "../fortran-tests/clstp.f"
    do_fio(&c__1, (char *)&iwork[1], (ftnlen)sizeof(integer));
#line 507 "../fortran-tests/clstp.f"
    e_wsfe();
/*< 99995  >*/
/*<       WRITE (LOUT,99996) (I,X(I),I=1,N) >*/
#line 511 "../fortran-tests/clstp.f"
    io___88.ciunit = lout;
#line 511 "../fortran-tests/clstp.f"
    s_wsfe(&io___88);
#line 511 "../fortran-tests/clstp.f"
    i__1 = n;
#line 511 "../fortran-tests/clstp.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
#line 511 "../fortran-tests/clstp.f"
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
#line 511 "../fortran-tests/clstp.f"
	do_fio(&c__1, (char *)&x[i__ - 1], (ftnlen)sizeof(doublereal));
#line 511 "../fortran-tests/clstp.f"
    }
#line 511 "../fortran-tests/clstp.f"
    e_wsfe();
/*<   890 CONTINUE >*/
#line 512 "../fortran-tests/clstp.f"
L890:
/*<       IF (ICASE.EQ.2) RETURN >*/
#line 513 "../fortran-tests/clstp.f"
    if (icase == 2) {
#line 513 "../fortran-tests/clstp.f"
	return 0;
#line 513 "../fortran-tests/clstp.f"
    }
/*<       ICASE = 2 >*/
#line 514 "../fortran-tests/clstp.f"
    icase = 2;
/*<       GO TO 60 >*/
#line 515 "../fortran-tests/clstp.f"
    goto L60;

/*     PROCEDURE (GET HADAMARD MATRIX) */
/*<   900 NN = 0 >*/
#line 518 "../fortran-tests/clstp.f"
L900:
#line 518 "../fortran-tests/clstp.f"
    nn = 0;
/*<       IF (.NOT.(K.GE.0)) GO TO 940 >*/
#line 519 "../fortran-tests/clstp.f"
    if (! (k >= 0)) {
#line 519 "../fortran-tests/clstp.f"
	goto L940;
#line 519 "../fortran-tests/clstp.f"
    }
/*<       NN = 1 >*/
#line 520 "../fortran-tests/clstp.f"
    nn = 1;
/*<       I = 1 >*/
#line 521 "../fortran-tests/clstp.f"
    i__ = 1;
/*<       N20114 = K >*/
#line 522 "../fortran-tests/clstp.f"
    n20114 = k;
/*<       GO TO 920 >*/
#line 523 "../fortran-tests/clstp.f"
    goto L920;
/*<   910 I = I + 1 >*/
#line 524 "../fortran-tests/clstp.f"
L910:
#line 524 "../fortran-tests/clstp.f"
    ++i__;
/*<   920 IF ((N20114-I).LT.0) GO TO 930 >*/
#line 525 "../fortran-tests/clstp.f"
L920:
#line 525 "../fortran-tests/clstp.f"
    if (n20114 - i__ < 0) {
#line 525 "../fortran-tests/clstp.f"
	goto L930;
#line 525 "../fortran-tests/clstp.f"
    }
/*<       NN = NN + NN >*/
#line 526 "../fortran-tests/clstp.f"
    nn += nn;
/*<       GO TO 910 >*/
#line 527 "../fortran-tests/clstp.f"
    goto L910;
/*<   930 GO TO 950 >*/
#line 528 "../fortran-tests/clstp.f"
L930:
#line 528 "../fortran-tests/clstp.f"
    goto L950;
/*<   940 NN = 0 >*/
#line 529 "../fortran-tests/clstp.f"
L940:
#line 529 "../fortran-tests/clstp.f"
    nn = 0;
/*<       GO TO 1080 >*/
#line 530 "../fortran-tests/clstp.f"
    goto L1080;

/*     PLACE THE SYMMETRIC HADAMARD MATRIX IN THE ARRAY HH(*,*). */
/*<   950 HH(1,1) = ONE >*/
#line 533 "../fortran-tests/clstp.f"
L950:
#line 533 "../fortran-tests/clstp.f"
    hh[0] = one;
/*<       NN = 1 >*/
#line 534 "../fortran-tests/clstp.f"
    nn = 1;
/*<       L = 1 >*/
#line 535 "../fortran-tests/clstp.f"
    l = 1;
/*<       N20118 = K >*/
#line 536 "../fortran-tests/clstp.f"
    n20118 = k;
/*<       GO TO 970 >*/
#line 537 "../fortran-tests/clstp.f"
    goto L970;
/*<   960 L = L + 1 >*/
#line 538 "../fortran-tests/clstp.f"
L960:
#line 538 "../fortran-tests/clstp.f"
    ++l;
/*<   970 IF ((N20118-L).LT.0) GO TO 1040 >*/
#line 539 "../fortran-tests/clstp.f"
L970:
#line 539 "../fortran-tests/clstp.f"
    if (n20118 - l < 0) {
#line 539 "../fortran-tests/clstp.f"
	goto L1040;
#line 539 "../fortran-tests/clstp.f"
    }
/*<       J = 1 >*/
#line 540 "../fortran-tests/clstp.f"
    j = 1;
/*<       N20122 = NN >*/
#line 541 "../fortran-tests/clstp.f"
    n20122 = nn;
/*<       GO TO 990 >*/
#line 542 "../fortran-tests/clstp.f"
    goto L990;
/*<   980 J = J + 1 >*/
#line 543 "../fortran-tests/clstp.f"
L980:
#line 543 "../fortran-tests/clstp.f"
    ++j;
/*<   990 IF ((N20122-J).LT.0) GO TO 1000 >*/
#line 544 "../fortran-tests/clstp.f"
L990:
#line 544 "../fortran-tests/clstp.f"
    if (n20122 - j < 0) {
#line 544 "../fortran-tests/clstp.f"
	goto L1000;
#line 544 "../fortran-tests/clstp.f"
    }
/*<       CALL DCOPY(NN, HH(1,J), 1, HH(NN+1,J), 1) >*/
#line 545 "../fortran-tests/clstp.f"
    dcopy_(&nn, &hh[(j << 5) - 32], &c__1, &hh[nn + 1 + (j << 5) - 33], &c__1)
	    ;
/*<       GO TO 980 >*/
#line 546 "../fortran-tests/clstp.f"
    goto L980;
/*<  1000 J = 1 >*/
#line 547 "../fortran-tests/clstp.f"
L1000:
#line 547 "../fortran-tests/clstp.f"
    j = 1;
/*<       N20126 = NN >*/
#line 548 "../fortran-tests/clstp.f"
    n20126 = nn;
/*<       GO TO 1020 >*/
#line 549 "../fortran-tests/clstp.f"
    goto L1020;
/*<  1010 J = J + 1 >*/
#line 550 "../fortran-tests/clstp.f"
L1010:
#line 550 "../fortran-tests/clstp.f"
    ++j;
/*<  1020 IF ((N20126-J).LT.0) GO TO 1030 >*/
#line 551 "../fortran-tests/clstp.f"
L1020:
#line 551 "../fortran-tests/clstp.f"
    if (n20126 - j < 0) {
#line 551 "../fortran-tests/clstp.f"
	goto L1030;
#line 551 "../fortran-tests/clstp.f"
    }
/*<       JPNN = J + NN >*/
#line 552 "../fortran-tests/clstp.f"
    jpnn = j + nn;
/*<       CALL DCOPY(2*NN, HH(1,J), 1, HH(1,JPNN), 1) >*/
#line 553 "../fortran-tests/clstp.f"
    i__1 = nn << 1;
#line 553 "../fortran-tests/clstp.f"
    dcopy_(&i__1, &hh[(j << 5) - 32], &c__1, &hh[(jpnn << 5) - 32], &c__1);
/*<       CALL DSCAL(NN, -ONE, HH(NN+1,JPNN), 1) >*/
#line 554 "../fortran-tests/clstp.f"
    d__1 = -one;
#line 554 "../fortran-tests/clstp.f"
    dscal_(&nn, &d__1, &hh[nn + 1 + (jpnn << 5) - 33], &c__1);
/*<       GO TO 1010 >*/
#line 555 "../fortran-tests/clstp.f"
    goto L1010;
/*<  1030 NN = NN + NN >*/
#line 556 "../fortran-tests/clstp.f"
L1030:
#line 556 "../fortran-tests/clstp.f"
    nn += nn;
/*<       GO TO 960 >*/
#line 557 "../fortran-tests/clstp.f"
    goto L960;

/*     MAKE THE MATRIX ORTHOGONAL BY SCALING THE ENTRIES. */
/*<  1040 T = NN >*/
#line 560 "../fortran-tests/clstp.f"
L1040:
#line 560 "../fortran-tests/clstp.f"
    t = (doublereal) nn;
/*<       T = ONE/DSQRT(T) >*/
#line 561 "../fortran-tests/clstp.f"
    t = one / sqrt(t);
/*<       J = 1 >*/
#line 562 "../fortran-tests/clstp.f"
    j = 1;
/*<       N20130 = NN >*/
#line 563 "../fortran-tests/clstp.f"
    n20130 = nn;
/*<       GO TO 1060 >*/
#line 564 "../fortran-tests/clstp.f"
    goto L1060;
/*<  1050 J = J + 1 >*/
#line 565 "../fortran-tests/clstp.f"
L1050:
#line 565 "../fortran-tests/clstp.f"
    ++j;
/*<  1060 IF ((N20130-J).LT.0) GO TO 1070 >*/
#line 566 "../fortran-tests/clstp.f"
L1060:
#line 566 "../fortran-tests/clstp.f"
    if (n20130 - j < 0) {
#line 566 "../fortran-tests/clstp.f"
	goto L1070;
#line 566 "../fortran-tests/clstp.f"
    }
/*<       CALL DSCAL(NN, T, HH(1,J), 1) >*/
#line 567 "../fortran-tests/clstp.f"
    dscal_(&nn, &t, &hh[(j << 5) - 32], &c__1);
/*<       GO TO 1050 >*/
#line 568 "../fortran-tests/clstp.f"
    goto L1050;
/*<  1070 CONTINUE >*/
#line 569 "../fortran-tests/clstp.f"
L1070:
/*<  1080 GO TO NGO, (70, 110, 270, 310, 470, 510, 550) >*/
#line 570 "../fortran-tests/clstp.f"
L1080:
#line 570 "../fortran-tests/clstp.f"
    switch (ngo) {
#line 570 "../fortran-tests/clstp.f"
	case 0: goto L70;
#line 570 "../fortran-tests/clstp.f"
	case 1: goto L110;
#line 570 "../fortran-tests/clstp.f"
	case 2: goto L270;
#line 570 "../fortran-tests/clstp.f"
	case 3: goto L310;
#line 570 "../fortran-tests/clstp.f"
	case 4: goto L470;
#line 570 "../fortran-tests/clstp.f"
	case 5: goto L510;
#line 570 "../fortran-tests/clstp.f"
	case 6: goto L550;
#line 570 "../fortran-tests/clstp.f"
    }
/*<       END >*/
} /* clstp_ */

/*     PROGRAM CLSTST (INPUT,OUTPUT,TAPE5=INPUT,TAPE6=OUTPUT)            MAN   10 */
/*                                                                       MAN   20 */
/*     TO CONVERT THE CONSTRAINED LEAST SQUARES PACKAGE OF SUBPROGRAMS   MAN   30 */
/*     TO DOUBLE PRECISION, FOLLOW THE EDITING INSTRUCTIONS NEAR THE     MAN   40 */
/*     BEGINNING OF THE FOLLOWING SUBPROGRAMS                            MAN   50 */
/*     LSEI(), LSI(), LPDP(), WNNLS(), WNLSM(), WNLIT(),                 MAN   60 */
/*     HFTI(), H12(), DIFF(), AND THE TESTING SUBPROGRAM CLSTP().        MAN   70 */
/*     REVISED 820305-2000                                               MAN   80 */
/*     REVISED YYMMDD-HHMM                                               MAN   90 */
/*                                                                       MAN  100 */
/*                                                                       MAN  110 */
/*     CHANGE STRING /DOUBLE PRECISION /DOUBLE PRECISION/, AND           MAN  120 */
/*     CHANGE STRING /E12/D12/                                           MAN  130 */
/*<       DOUBLE PRECISION COND(3)                                           >*/
/* Main program */ int MAIN__(void)
{
    /* Format strings */
    static char fmt_99999[] = "(5i5)";
    static char fmt_99998[] = "(3f10.0)";
    static char fmt_99997[] = "(/////\002 KLOG(*) ARRAY = \002,5i5/\002 COND"
	    "(*) ARRAY = \002,3e12.4)";
    static char fmt_99996[] = "(/\002 FROM CLSTP( ), ISTAT =\002,i2,2x,\002("
	    "ISTAT=4 IS GOOD\002/27x,\002 ISTAT=1,2,3 MAY BE BAD)\002)";

    /* Builtin functions */
    integer s_rsfe(cilist *), do_fio(integer *, char *, ftnlen), e_rsfe(void),
	     s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    integer i__, lin;
    doublereal cond[3];
    logical done;
    integer klog[5], lout, istat;
    extern /* Subroutine */ int clstp_(integer *, doublereal *, integer *);
    extern integer i1mach_(integer *);

    /* Fortran I/O blocks */
    static cilist io___98 = { 0, 0, 0, fmt_99999, 0 };
    static cilist io___102 = { 0, 0, 0, fmt_99998, 0 };
    static cilist io___104 = { 0, 0, 0, fmt_99997, 0 };
    static cilist io___106 = { 0, 0, 0, fmt_99996, 0 };


/*<       INTEGER   KLOG(5)                                                  >*/
/*<       LOGICAL DONE                                                       >*/
/*                                                                       MAN  170 */
/*<       LIN = 5                                                            >*/
#line 590 "../fortran-tests/clstp.f"
    lin = 5;
/*<       LOUT = I1MACH(4)                                                   >*/
#line 591 "../fortran-tests/clstp.f"
    lout = i1mach_(&c__4);
/*                                                                       MAN  200 */
/*                                                                       MAN  210 */
/*     READ IN THE LOGS OF THE VARIOUS DIMENSIONS.                       MAN  220 */
/*<    10 READ (LIN,99999) (KLOG(I),I=1,5)                                   >*/
#line 595 "../fortran-tests/clstp.f"
L10:
#line 595 "../fortran-tests/clstp.f"
    io___98.ciunit = lin;
#line 595 "../fortran-tests/clstp.f"
    s_rsfe(&io___98);
#line 595 "../fortran-tests/clstp.f"
    for (i__ = 1; i__ <= 5; ++i__) {
#line 595 "../fortran-tests/clstp.f"
	do_fio(&c__1, (char *)&klog[i__ - 1], (ftnlen)sizeof(integer));
#line 595 "../fortran-tests/clstp.f"
    }
#line 595 "../fortran-tests/clstp.f"
    e_rsfe();
/*< 99999 FORMAT (5I5)                                                       >*/
/*<       DONE = KLOG(5).LT.0                                                >*/
#line 597 "../fortran-tests/clstp.f"
    done = klog[4] < 0;
/*<       IF (.NOT.(DONE)) GO TO 20                                          >*/
#line 598 "../fortran-tests/clstp.f"
    if (! done) {
#line 598 "../fortran-tests/clstp.f"
	goto L20;
#line 598 "../fortran-tests/clstp.f"
    }
/*<       GO TO 30                                                           >*/
#line 599 "../fortran-tests/clstp.f"
    goto L30;
/*                                                                       MAN  280 */
/*     READ THE CONDITION NUMBERS FOR THE THREE MATRICES.                MAN  290 */
/*<    20 READ (LIN,99998) (COND(I),I=1,3)                                   >*/
#line 602 "../fortran-tests/clstp.f"
L20:
#line 602 "../fortran-tests/clstp.f"
    io___102.ciunit = lin;
#line 602 "../fortran-tests/clstp.f"
    s_rsfe(&io___102);
#line 602 "../fortran-tests/clstp.f"
    for (i__ = 1; i__ <= 3; ++i__) {
#line 602 "../fortran-tests/clstp.f"
	do_fio(&c__1, (char *)&cond[i__ - 1], (ftnlen)sizeof(doublereal));
#line 602 "../fortran-tests/clstp.f"
    }
#line 602 "../fortran-tests/clstp.f"
    e_rsfe();
/*< 99998 FORMAT (3F10.0)                                                    >*/
/*                                                                       MAN  320 */
/*<       WRITE (LOUT,99997) KLOG, COND                                      >*/
#line 605 "../fortran-tests/clstp.f"
    io___104.ciunit = lout;
#line 605 "../fortran-tests/clstp.f"
    s_wsfe(&io___104);
#line 605 "../fortran-tests/clstp.f"
    do_fio(&c__5, (char *)&klog[0], (ftnlen)sizeof(integer));
#line 605 "../fortran-tests/clstp.f"
    do_fio(&c__3, (char *)&cond[0], (ftnlen)sizeof(doublereal));
#line 605 "../fortran-tests/clstp.f"
    e_wsfe();
/*< 99997  >*/
/*                                                                       MAN  360 */
/*     CALL TESTING SUBPROGRAM TO FORM CONSTRAINED LEAST SQUARES         MAN  370 */
/*     SYSTEM AND SOLVE IT.                                              MAN  380 */
/*<       CALL CLSTP(KLOG, COND, ISTAT)                                      >*/
#line 611 "../fortran-tests/clstp.f"
    clstp_(klog, cond, &istat);
/*                                                                       MAN  400 */
/*<       WRITE (LOUT,99996) ISTAT                                           >*/
#line 613 "../fortran-tests/clstp.f"
    io___106.ciunit = lout;
#line 613 "../fortran-tests/clstp.f"
    s_wsfe(&io___106);
#line 613 "../fortran-tests/clstp.f"
    do_fio(&c__1, (char *)&istat, (ftnlen)sizeof(integer));
#line 613 "../fortran-tests/clstp.f"
    e_wsfe();
/*< 99996  >*/
/*                                                                       MAN  440 */
/*<       GO TO 10                                                           >*/
#line 617 "../fortran-tests/clstp.f"
    goto L10;
/*<    30 STOP                                                               >*/
#line 618 "../fortran-tests/clstp.f"
L30:
#line 618 "../fortran-tests/clstp.f"
    s_stop("", (ftnlen)0);
/*<       END                                                                >*/
#line 619 "../fortran-tests/clstp.f"
    return 0;
} /* MAIN__ */

/*<       REAL FUNCTION RAN(K)                                               >*/
doublereal ran_(integer *k)
{
    /* Initialized data */

    static integer iy = 100001;

    /* System generated locals */
    real ret_val;


/*     RANDOM NUMBER GENERATOR - BASED ON ALGORITHM 266 */
/*      BY PIKE AND HILL (MODIFIED BY HANSSON) */
/*      COLLECTED ALG. FROM CACM. */

/*     THIS SUBPROGRAM IS INTENDED FOR USE ON COMPUTERS WITH */
/*      FIXED POINT WORDLENGTH OF AT LEAST 29 BITS.  IT IS */
/*      BEST IF THE FLOATING POINT SIGNIFICAND HAS AT MOST */
/*      29 BITS. */

/*<       INTEGER IY,K >*/
/*<       DATA IY/100001/ >*/

/*<       IF(K.GT.0) IY = K >*/
#line 635 "../fortran-tests/clstp.f"
    if (*k > 0) {
#line 635 "../fortran-tests/clstp.f"
	iy = *k;
#line 635 "../fortran-tests/clstp.f"
    }
/*<       IY = IY * 125 >*/
#line 636 "../fortran-tests/clstp.f"
    iy *= 125;
/*<       IY = IY - (IY/2796203) * 2796203 >*/
#line 637 "../fortran-tests/clstp.f"
    iy -= iy / 2796203 * 2796203;
/*<       RAN = FLOAT(IY) / 2796203.0E0 >*/
#line 638 "../fortran-tests/clstp.f"
    ret_val = (real) iy / 2796203.f;
/*<       RETURN >*/
#line 639 "../fortran-tests/clstp.f"
    return ret_val;
/*     ---------- LAST CARD OF RAN ---------- */
/*<       END >*/
} /* ran_ */

