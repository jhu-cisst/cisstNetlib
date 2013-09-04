#line 1 "svdrs.f"
/* svdrs.f -- translated by f2c (version 20100827).
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

#line 1 "svdrs.f"
/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;

/*     SUBROUTINE SVDRS (A, MDA, M1, N1, B, MDB, NB, S, WORK) */

/*  SINGULAR VALUE DECOMPOSITION ALSO TREATING RIGHT SIDE VECTOR. */

/*  The original version of this code was developed by */
/*  Charles L. Lawson and Richard J. Hanson at Jet Propulsion Laboratory */
/*  1974 SEP 25, and published in the book */
/*  "SOLVING LEAST SQUARES PROBLEMS", Prentice-HalL, 1974. */
/*  Revised FEB 1995 to accompany reprinting of the book by SIAM. */
/*     ------------------------------------------------------------------ */
/*  This 1995 version differs from the original 1974 version by adding */
/*  the argument WORK(). */
/*  WORK() provides 2*N1 locations of work space.  Originally S() was */
/*  required to have 3*N1 elements, of which the last 2*N1 were used for */
/*  work space.  Now S() only needs N1 elements. */
/*     ------------------------------------------------------------------ */
/*  This subroutine computes the singular value decomposition of the */
/*  given M1 x N1 matrix, A, and optionally applys the transformations */
/*  from the left to the NB column vectors of the M1 x NB matrix B. */
/*  Either M1 .ge. N1  or  M1 .lt. N1 is permitted. */

/*       The singular value decomposition of A is of the form */

/*                  A  =  U * S * V**t */

/*  where U is M1 x M1 orthogonal, S is M1 x N1 diagonal with the */
/*  diagonal terms nonnegative and ordered from large to small, and */
/*  V is N1 x N1 orthogonal.  Note that these matrices also satisfy */

/*                  S = (U**t) * A * V */

/*       The matrix V is returned in the leading N1 rows and */
/*  columns of the array A(,). */

/*       The singular values, i.e. the diagonal terms of the matrix S, */
/*  are returned in the array S().  If M1 .lt. N1, positions M1+1 */
/*  through N1 of S() will be set to zero. */

/*       The product matrix  G = U**t * B replaces the given matrix B */
/*  in the array B(,). */

/*       If the user wishes to obtain a minimum length least squares */
/*  solution of the linear system */

/*                        A * X ~=~ B */

/*  the solution X can be constructed, following use of this subroutine, */
/*  by computing the sum for i = 1, ..., R of the outer products */

/*          (Col i of V) * (1/S(i)) * (Row i of G) */

/*  Here R denotes the pseudorank of A which the user may choose */
/*  in the range 0 through Min(M1, N1) based on the sizes of the */
/*  singular values. */
/*     ------------------------------------------------------------------ */
/*                    Subroutine Arguments */

/*  A(,)     (In/Out)  On input contains the M1 x N1 matrix A. */
/*           On output contains the N1 x N1 matrix V. */

/*  LDA      (In)  First dimensioning parameter for A(,). */
/*           Require LDA .ge. Max(M1, N1). */

/*  M1       (In)  No. of rows of matrices A, B, and G. */
/*           Require M1 > 0. */

/*  N1       (In)  No. of cols of matrix A, No. of rows and cols of */
/*           matrix V.  Permit M1 .ge. N1  or  M1 .lt. N1. */
/*           Require N1 > 0. */

/*  B(,)     (In/Out)  If NB .gt. 0 this array must contain an */
/*           M1 x NB matrix on input and will contain the */
/*           M1 x NB product matrix, G = (U**t) * B on output. */

/*  LDB      (In)  First dimensioning parameter for B(,). */
/*           Require LDB .ge. M1. */

/*  NB       (In)  No. of cols in the matrices B and G. */
/*           Require NB .ge. 0. */

/*  S()      (Out)  Must be dimensioned at least N1.  On return will */
/*           contain the singular values of A, with the ordering */
/*                S(1) .ge. S(2) .ge. ... .ge. S(N1) .ge. 0. */
/*           If M1 .lt. N1 the singular values indexed from M1+1 */
/*           through N1 will be zero. */
/*           If the given integer arguments are not consistent, this */
/*           subroutine will return immediately, setting S(1) = -1.0. */

/*  WORK()  (Scratch)  Work space of total size at least 2*N1. */
/*           Locations 1 thru N1 will hold the off-diagonal terms of */
/*           the bidiagonal matrix for subroutine QRBD.  Locations N1+1 */
/*           thru 2*N1 will save info from one call to the next of */
/*           H12. */
/*     ------------------------------------------------------------------ */
/*  This code gives special treatment to rows and columns that are */
/*  entirely zero.  This causes certain zero sing. vals. to appear as */
/*  exact zeros rather than as about MACHEPS times the largest sing. val. */
/*  It similarly cleans up the associated columns of U and V. */

/*  METHOD.. */
/*   1. EXCHANGE COLS OF A TO PACK NONZERO COLS TO THE LEFT. */
/*      SET N = NO. OF NONZERO COLS. */
/*      USE LOCATIONS A(1,N1),A(1,N1-1),...,A(1,N+1) TO RECORD THE */
/*      COL PERMUTATIONS. */
/*   2. EXCHANGE ROWS OF A TO PACK NONZERO ROWS TO THE TOP. */
/*      QUIT PACKING IF FIND N NONZERO ROWS.  MAKE SAME ROW EXCHANGES */
/*      IN B.  SET M SO THAT ALL NONZERO ROWS OF THE PERMUTED A */
/*      ARE IN FIRST M ROWS.  IF M .LE. N THEN ALL M ROWS ARE */
/*      NONZERO.  IF M .GT. N THEN      THE FIRST N ROWS ARE KNOWN */
/*      TO BE NONZERO,AND ROWS N+1 THRU M MAY BE ZERO OR NONZERO. */
/*   3. APPLY ORIGINAL ALGORITHM TO THE M BY N PROBLEM. */
/*   4. MOVE PERMUTATION RECORD FROM A(,) TO S(I),I=N+1,...,N1. */
/*   5. BUILD V UP FROM  N BY N  TO  N1 BY N1  BY PLACING ONES ON */
/*      THE DIAGONAL AND ZEROS ELSEWHERE.  THIS IS ONLY PARTLY DONE */
/*      EXPLICITLY.  IT IS COMPLETED DURING STEP 6. */
/*   6. EXCHANGE ROWS OF V TO COMPENSATE FOR COL EXCHANGES OF STEP 2. */
/*   7. PLACE ZEROS IN  S(I),I=N+1,N1  TO REPRESENT ZERO SING VALS. */
/*     ------------------------------------------------------------------ */
/*<       subroutine SVDRS (A, MDA, M1, N1, B, MDB, NB, S, WORK)  >*/
/* Subroutine */ int svdrs_(doublereal *a, integer *mda, integer *m1, integer 
	*n1, doublereal *b, integer *mdb, integer *nb, doublereal *s, 
	doublereal *work)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, work_dim1, work_offset, i__1, 
	    i__2, i__3, i__4;
    cilist ci__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    integer i__, j, k, l, m, n;
    doublereal t;
    extern /* Subroutine */ int h12_(integer *, integer *, integer *, integer 
	    *, doublereal *, integer *, doublereal *, doublereal *, integer *,
	     integer *, integer *);
    integer ns, np1, nsp1;
    extern /* Subroutine */ int qrbd_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *, integer *, doublereal *, 
	    integer *, integer *);
    integer ipass;

/*<       integer I, IPASS, J, K, L, M, MDA, MDB, M1 >*/
/*<       integer N, NB, N1, NP1, NS, NSP1 >*/
/*     double precision A(MDA,N1),B(MDB,NB), S(N1) */
/*<       double precision A(MDA, *),B(MDB, *), S( *) >*/
/*<       double precision ONE, T, WORK(N1,2), ZERO >*/
/*<       parameter(ONE = 1.0d0, ZERO = 0.0d0) >*/
/*     -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*                             BEGIN.. SPECIAL FOR ZERO ROWS AND COLS. */

/*                             PACK THE NONZERO COLS TO THE LEFT */

/*<       N=N1   >*/
#line 131 "svdrs.f"
    /* Parameter adjustments */
#line 131 "svdrs.f"
    a_dim1 = *mda;
#line 131 "svdrs.f"
    a_offset = 1 + a_dim1;
#line 131 "svdrs.f"
    a -= a_offset;
#line 131 "svdrs.f"
    work_dim1 = *n1;
#line 131 "svdrs.f"
    work_offset = 1 + work_dim1;
#line 131 "svdrs.f"
    work -= work_offset;
#line 131 "svdrs.f"
    b_dim1 = *mdb;
#line 131 "svdrs.f"
    b_offset = 1 + b_dim1;
#line 131 "svdrs.f"
    b -= b_offset;
#line 131 "svdrs.f"
    --s;
#line 131 "svdrs.f"

#line 131 "svdrs.f"
    /* Function Body */
#line 131 "svdrs.f"
    n = *n1;
/*<       IF (N.LE.0.OR.M1.LE.0) RETURN  >*/
#line 132 "svdrs.f"
    if (n <= 0 || *m1 <= 0) {
#line 132 "svdrs.f"
	return 0;
#line 132 "svdrs.f"
    }
/*<       J=N    >*/
#line 133 "svdrs.f"
    j = n;
/*<    10 CONTINUE   >*/
#line 134 "svdrs.f"
L10:
/*<          DO 20 I=1,M1   >*/
#line 135 "svdrs.f"
    i__1 = *m1;
#line 135 "svdrs.f"
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<             IF (A(I,J) .ne. ZERO) go to 50 >*/
#line 136 "svdrs.f"
	if (a[i__ + j * a_dim1] != 0.) {
#line 136 "svdrs.f"
	    goto L50;
#line 136 "svdrs.f"
	}
/*<    20    CONTINUE   >*/
#line 137 "svdrs.f"
/* L20: */
#line 137 "svdrs.f"
    }

/*           COL J  IS ZERO. EXCHANGE IT WITH COL N. */

/*<          IF (J .ne. N) then >*/
#line 141 "svdrs.f"
    if (j != n) {
/*<             DO 30 I=1,M1   >*/
#line 142 "svdrs.f"
	i__1 = *m1;
#line 142 "svdrs.f"
	for (i__ = 1; i__ <= i__1; ++i__) {
/*<    30       A(I,J)=A(I,N)  >*/
#line 143 "svdrs.f"
/* L30: */
#line 143 "svdrs.f"
	    a[i__ + j * a_dim1] = a[i__ + n * a_dim1];
#line 143 "svdrs.f"
	}
/*<          endif >*/
#line 144 "svdrs.f"
    }
/*<          A(1,N)=J   >*/
#line 145 "svdrs.f"
    a[n * a_dim1 + 1] = (doublereal) j;
/*<          N=N-1  >*/
#line 146 "svdrs.f"
    --n;
/*<    50    CONTINUE   >*/
#line 147 "svdrs.f"
L50:
/*<          J=J-1  >*/
#line 148 "svdrs.f"
    --j;
/*<       IF (J.GE.1) GO TO 10   >*/
#line 149 "svdrs.f"
    if (j >= 1) {
#line 149 "svdrs.f"
	goto L10;
#line 149 "svdrs.f"
    }
/*                             IF N=0 THEN A IS ENTIRELY ZERO AND SVD */
/*                             COMPUTATION CAN BE SKIPPED */
/*<       NS=0   >*/
#line 152 "svdrs.f"
    ns = 0;
/*<       IF (N.EQ.0) GO TO 240  >*/
#line 153 "svdrs.f"
    if (n == 0) {
#line 153 "svdrs.f"
	goto L240;
#line 153 "svdrs.f"
    }
/*                             PACK NONZERO ROWS TO THE TOP */
/*                             QUIT PACKING IF FIND N NONZERO ROWS */
/*<       I=1    >*/
#line 156 "svdrs.f"
    i__ = 1;
/*<       M=M1   >*/
#line 157 "svdrs.f"
    m = *m1;
/*<    60 IF (I.GT.N.OR.I.GE.M) GO TO 150    >*/
#line 158 "svdrs.f"
L60:
#line 158 "svdrs.f"
    if (i__ > n || i__ >= m) {
#line 158 "svdrs.f"
	goto L150;
#line 158 "svdrs.f"
    }
/*<       IF (A(I,I)) 90,70,90   >*/
#line 159 "svdrs.f"
    if (a[i__ + i__ * a_dim1] != 0.) {
#line 159 "svdrs.f"
	goto L90;
#line 159 "svdrs.f"
    } else {
#line 159 "svdrs.f"
	goto L70;
#line 159 "svdrs.f"
    }
/*<    70     DO 80 J=1,N    >*/
#line 160 "svdrs.f"
L70:
#line 160 "svdrs.f"
    i__1 = n;
#line 160 "svdrs.f"
    for (j = 1; j <= i__1; ++j) {
/*<           IF (A(I,J)) 90,80,90   >*/
#line 161 "svdrs.f"
	if (a[i__ + j * a_dim1] != 0.) {
#line 161 "svdrs.f"
	    goto L90;
#line 161 "svdrs.f"
	} else {
#line 161 "svdrs.f"
	    goto L80;
#line 161 "svdrs.f"
	}
/*<    80     CONTINUE   >*/
#line 162 "svdrs.f"
L80:
#line 162 "svdrs.f"
	;
#line 162 "svdrs.f"
    }
/*<       GO TO 100  >*/
#line 163 "svdrs.f"
    goto L100;
/*<    90 I=I+1  >*/
#line 164 "svdrs.f"
L90:
#line 164 "svdrs.f"
    ++i__;
/*<       GO TO 60   >*/
#line 165 "svdrs.f"
    goto L60;
/*                             ROW I IS ZERO */
/*                             EXCHANGE ROWS I AND M */
/*<   100 IF(NB.LE.0) GO TO 115  >*/
#line 168 "svdrs.f"
L100:
#line 168 "svdrs.f"
    if (*nb <= 0) {
#line 168 "svdrs.f"
	goto L115;
#line 168 "svdrs.f"
    }
/*<           DO 110 J=1,NB  >*/
#line 169 "svdrs.f"
    i__1 = *nb;
#line 169 "svdrs.f"
    for (j = 1; j <= i__1; ++j) {
/*<           T=B(I,J)   >*/
#line 170 "svdrs.f"
	t = b[i__ + j * b_dim1];
/*<           B(I,J)=B(M,J)  >*/
#line 171 "svdrs.f"
	b[i__ + j * b_dim1] = b[m + j * b_dim1];
/*<   110     B(M,J)=T   >*/
#line 172 "svdrs.f"
/* L110: */
#line 172 "svdrs.f"
	b[m + j * b_dim1] = t;
#line 172 "svdrs.f"
    }
/*<   115     DO 120 J=1,N   >*/
#line 173 "svdrs.f"
L115:
#line 173 "svdrs.f"
    i__1 = n;
#line 173 "svdrs.f"
    for (j = 1; j <= i__1; ++j) {
/*<   120     A(I,J)=A(M,J)  >*/
#line 174 "svdrs.f"
/* L120: */
#line 174 "svdrs.f"
	a[i__ + j * a_dim1] = a[m + j * a_dim1];
#line 174 "svdrs.f"
    }
/*<       IF (M.GT.N) GO TO 140  >*/
#line 175 "svdrs.f"
    if (m > n) {
#line 175 "svdrs.f"
	goto L140;
#line 175 "svdrs.f"
    }
/*<           DO 130 J=1,N   >*/
#line 176 "svdrs.f"
    i__1 = n;
#line 176 "svdrs.f"
    for (j = 1; j <= i__1; ++j) {
/*<   130     A(M,J)=ZERO    >*/
#line 177 "svdrs.f"
/* L130: */
#line 177 "svdrs.f"
	a[m + j * a_dim1] = 0.;
#line 177 "svdrs.f"
    }
/*<   140 CONTINUE   >*/
#line 178 "svdrs.f"
L140:
/*                             EXCHANGE IS FINISHED */
/*<       M=M-1  >*/
#line 180 "svdrs.f"
    --m;
/*<       GO TO 60   >*/
#line 181 "svdrs.f"
    goto L60;

/*<   150 CONTINUE   >*/
#line 183 "svdrs.f"
L150:
/*                             END.. SPECIAL FOR ZERO ROWS AND COLUMNS */
/*                             BEGIN.. SVD ALGORITHM */
/*     METHOD.. */
/*     (1)     REDUCE THE MATRIX TO UPPER BIDIAGONAL FORM WITH */
/*     HOUSEHOLDER TRANSFORMATIONS. */
/*          H(N)...H(1)AQ(1)...Q(N-2) = (D**T,0)**T */
/*     WHERE D IS UPPER BIDIAGONAL. */

/*     (2)     APPLY H(N)...H(1) TO B.  HERE H(N)...H(1)*B REPLACES B */
/*     IN STORAGE. */

/*     (3)     THE MATRIX PRODUCT W= Q(1)...Q(N-2) OVERWRITES THE FIRST */
/*     N ROWS OF A IN STORAGE. */

/*     (4)     AN SVD FOR D IS COMPUTED.  HERE K ROTATIONS RI AND PI ARE */
/*     COMPUTED SO THAT */
/*          RK...R1*D*P1**(T)...PK**(T) = DIAG(S1,...,SM) */
/*     TO WORKING ACCURACY.  THE SI ARE NONNEGATIVE AND NONINCREASING. */
/*     HERE RK...R1*B OVERWRITES B IN STORAGE WHILE */
/*     A*P1**(T)...PK**(T)  OVERWRITES A IN STORAGE. */

/*     (5)     IT FOLLOWS THAT,WITH THE PROPER DEFINITIONS, */
/*     U**(T)*B OVERWRITES B, WHILE V OVERWRITES THE FIRST N ROW AND */
/*     COLUMNS OF A. */

/*<       L=min(M,N)    >*/
#line 209 "svdrs.f"
    l = min(m,n);
/*             THE FOLLOWING LOOP REDUCES A TO UPPER BIDIAGONAL AND */
/*             ALSO APPLIES THE PREMULTIPLYING TRANSFORMATIONS TO B. */

/*<           DO 170 J=1,L   >*/
#line 213 "svdrs.f"
    i__1 = l;
#line 213 "svdrs.f"
    for (j = 1; j <= i__1; ++j) {
/*<           IF (J.GE.M) GO TO 160      >*/
#line 214 "svdrs.f"
	if (j >= m) {
#line 214 "svdrs.f"
	    goto L160;
#line 214 "svdrs.f"
	}
/*<           CALL H12 (1,J,J+1,M,A(1,J),1,T,A(1,J+1),1,MDA,N-J) >*/
#line 215 "svdrs.f"
	i__2 = j + 1;
#line 215 "svdrs.f"
	i__3 = n - j;
#line 215 "svdrs.f"
	h12_(&c__1, &j, &i__2, &m, &a[j * a_dim1 + 1], &c__1, &t, &a[(j + 1) *
		 a_dim1 + 1], &c__1, mda, &i__3);
/*<           CALL H12 (2,J,J+1,M,A(1,J),1,T,B,1,MDB,NB) >*/
#line 216 "svdrs.f"
	i__2 = j + 1;
#line 216 "svdrs.f"
	h12_(&c__2, &j, &i__2, &m, &a[j * a_dim1 + 1], &c__1, &t, &b[b_offset]
		, &c__1, mdb, nb);
/*<   160     IF (J.GE.N-1) GO TO 170    >*/
#line 217 "svdrs.f"
L160:
#line 217 "svdrs.f"
	if (j >= n - 1) {
#line 217 "svdrs.f"
	    goto L170;
#line 217 "svdrs.f"
	}
/*<           CALL H12 (1,J+1,J+2,N,A(J,1),MDA,work(J,2),A(J+1,1),MDA,1,M-J) >*/
#line 218 "svdrs.f"
	i__2 = j + 1;
#line 218 "svdrs.f"
	i__3 = j + 2;
#line 218 "svdrs.f"
	i__4 = m - j;
#line 218 "svdrs.f"
	h12_(&c__1, &i__2, &i__3, &n, &a[j + a_dim1], mda, &work[j + (
		work_dim1 << 1)], &a[j + 1 + a_dim1], mda, &c__1, &i__4);
/*<   170     CONTINUE   >*/
#line 219 "svdrs.f"
L170:
#line 219 "svdrs.f"
	;
#line 219 "svdrs.f"
    }

/*     COPY THE BIDIAGONAL MATRIX INTO S() and WORK() FOR QRBD. */
/* 1986 Jan 8. C. L. Lawson. Changed N to L in following 2 statements. */
/*<       IF (L.EQ.1) GO TO 190  >*/
#line 223 "svdrs.f"
    if (l == 1) {
#line 223 "svdrs.f"
	goto L190;
#line 223 "svdrs.f"
    }
/*<           DO 180 J=2,L   >*/
#line 224 "svdrs.f"
    i__1 = l;
#line 224 "svdrs.f"
    for (j = 2; j <= i__1; ++j) {
/*<           S(J)=A(J,J)  >*/
#line 225 "svdrs.f"
	s[j] = a[j + j * a_dim1];
/*<   180     WORK(J,1)=A(J-1,J)    >*/
#line 226 "svdrs.f"
/* L180: */
#line 226 "svdrs.f"
	work[j + work_dim1] = a[j - 1 + j * a_dim1];
#line 226 "svdrs.f"
    }
/*<   190 S(1)=A(1,1)      >*/
#line 227 "svdrs.f"
L190:
#line 227 "svdrs.f"
    s[1] = a[a_dim1 + 1];

/*<       NS=N   >*/
#line 229 "svdrs.f"
    ns = n;
/*<       IF (M.GE.N) GO TO 200  >*/
#line 230 "svdrs.f"
    if (m >= n) {
#line 230 "svdrs.f"
	goto L200;
#line 230 "svdrs.f"
    }
/*<       NS=M+1 >*/
#line 231 "svdrs.f"
    ns = m + 1;
/*<       S(NS)=ZERO   >*/
#line 232 "svdrs.f"
    s[ns] = 0.;
/*<       WORK(NS,1)=A(M,M+1)   >*/
#line 233 "svdrs.f"
    work[ns + work_dim1] = a[m + (m + 1) * a_dim1];
/*<   200 CONTINUE   >*/
#line 234 "svdrs.f"
L200:

/*     CONSTRUCT THE EXPLICIT N BY N PRODUCT MATRIX, W=Q1*Q2*...*QL*I */
/*     IN THE ARRAY A(). */

/*<           DO 230 K=1,N   >*/
#line 239 "svdrs.f"
    i__1 = n;
#line 239 "svdrs.f"
    for (k = 1; k <= i__1; ++k) {
/*<           I=N+1-K    >*/
#line 240 "svdrs.f"
	i__ = n + 1 - k;
/*<           IF (I .GT. min(M,N-2)) GO TO 210      >*/
/* Computing MIN */
#line 241 "svdrs.f"
	i__2 = m, i__3 = n - 2;
#line 241 "svdrs.f"
	if (i__ > min(i__2,i__3)) {
#line 241 "svdrs.f"
	    goto L210;
#line 241 "svdrs.f"
	}
/*<           CALL H12 (2,I+1,I+2,N,A(I,1),MDA,WORK(I,2),A(1,I+1),1,MDA,N-I) >*/
#line 242 "svdrs.f"
	i__2 = i__ + 1;
#line 242 "svdrs.f"
	i__3 = i__ + 2;
#line 242 "svdrs.f"
	i__4 = n - i__;
#line 242 "svdrs.f"
	h12_(&c__2, &i__2, &i__3, &n, &a[i__ + a_dim1], mda, &work[i__ + (
		work_dim1 << 1)], &a[(i__ + 1) * a_dim1 + 1], &c__1, mda, &
		i__4);
/*<   210         DO 220 J=1,N   >*/
#line 243 "svdrs.f"
L210:
#line 243 "svdrs.f"
	i__2 = n;
#line 243 "svdrs.f"
	for (j = 1; j <= i__2; ++j) {
/*<   220         A(I,J)=ZERO    >*/
#line 244 "svdrs.f"
/* L220: */
#line 244 "svdrs.f"
	    a[i__ + j * a_dim1] = 0.;
#line 244 "svdrs.f"
	}
/*<   230     A(I,I)=ONE     >*/
#line 245 "svdrs.f"
/* L230: */
#line 245 "svdrs.f"
	a[i__ + i__ * a_dim1] = 1.;
#line 245 "svdrs.f"
    }

/*          COMPUTE THE SVD OF THE BIDIAGONAL MATRIX */

/*<       CALL QRBD (IPASS,S(1),WORK(1,1),NS,A,MDA,N,B,MDB,NB)    >*/
#line 249 "svdrs.f"
    qrbd_(&ipass, &s[1], &work[work_dim1 + 1], &ns, &a[a_offset], mda, &n, &b[
	    b_offset], mdb, nb);

/*<       if(IPASS .eq. 2) then >*/
#line 251 "svdrs.f"
    if (ipass == 2) {
/*<        >*/
#line 252 "svdrs.f"
	ci__1.cierr = 0;
#line 252 "svdrs.f"
	ci__1.ciunit = 6;
#line 252 "svdrs.f"
	ci__1.cifmt = "(/a)";
#line 252 "svdrs.f"
	s_wsfe(&ci__1);
#line 252 "svdrs.f"
	do_fio(&c__1, " FULL ACCURACY NOT ATTAINED IN BIDIAGONAL SVD", (
		ftnlen)45);
#line 252 "svdrs.f"
	e_wsfe();
/*<       endif >*/
#line 254 "svdrs.f"
    }
/*<   240 CONTINUE   >*/
#line 256 "svdrs.f"
L240:
/*<       IF (NS.GE.N) GO TO 260 >*/
#line 257 "svdrs.f"
    if (ns >= n) {
#line 257 "svdrs.f"
	goto L260;
#line 257 "svdrs.f"
    }
/*<       NSP1=NS+1  >*/
#line 258 "svdrs.f"
    nsp1 = ns + 1;
/*<           DO 250 J=NSP1,N    >*/
#line 259 "svdrs.f"
    i__1 = n;
#line 259 "svdrs.f"
    for (j = nsp1; j <= i__1; ++j) {
/*<   250     S(J)=ZERO    >*/
#line 260 "svdrs.f"
/* L250: */
#line 260 "svdrs.f"
	s[j] = 0.;
#line 260 "svdrs.f"
    }
/*<   260 CONTINUE   >*/
#line 261 "svdrs.f"
L260:
/*<       IF (N.EQ.N1) RETURN    >*/
#line 262 "svdrs.f"
    if (n == *n1) {
#line 262 "svdrs.f"
	return 0;
#line 262 "svdrs.f"
    }
/*<       NP1=N+1    >*/
#line 263 "svdrs.f"
    np1 = n + 1;
/*                                  MOVE RECORD OF PERMUTATIONS */
/*                                  AND STORE ZEROS */
/*<           DO 280 J=NP1,N1    >*/
#line 266 "svdrs.f"
    i__1 = *n1;
#line 266 "svdrs.f"
    for (j = np1; j <= i__1; ++j) {
/*<           S(J)=A(1,J)  >*/
#line 267 "svdrs.f"
	s[j] = a[j * a_dim1 + 1];
/*<               DO 270 I=1,N   >*/
#line 268 "svdrs.f"
	i__2 = n;
#line 268 "svdrs.f"
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<   270         A(I,J)=ZERO    >*/
#line 269 "svdrs.f"
/* L270: */
#line 269 "svdrs.f"
	    a[i__ + j * a_dim1] = 0.;
#line 269 "svdrs.f"
	}
/*<   280     CONTINUE   >*/
#line 270 "svdrs.f"
/* L280: */
#line 270 "svdrs.f"
    }
/*                             PERMUTE ROWS AND SET ZERO SINGULAR VALUES. */
/*<           DO 300 K=NP1,N1    >*/
#line 272 "svdrs.f"
    i__1 = *n1;
#line 272 "svdrs.f"
    for (k = np1; k <= i__1; ++k) {
/*<           I=S(K)   >*/
#line 273 "svdrs.f"
	i__ = (integer) s[k];
/*<           S(K)=ZERO    >*/
#line 274 "svdrs.f"
	s[k] = 0.;
/*<               DO 290 J=1,N1  >*/
#line 275 "svdrs.f"
	i__2 = *n1;
#line 275 "svdrs.f"
	for (j = 1; j <= i__2; ++j) {
/*<               A(K,J)=A(I,J)  >*/
#line 276 "svdrs.f"
	    a[k + j * a_dim1] = a[i__ + j * a_dim1];
/*<   290         A(I,J)=ZERO    >*/
#line 277 "svdrs.f"
/* L290: */
#line 277 "svdrs.f"
	    a[i__ + j * a_dim1] = 0.;
#line 277 "svdrs.f"
	}
/*<           A(I,K)=ONE     >*/
#line 278 "svdrs.f"
	a[i__ + k * a_dim1] = 1.;
/*<   300     CONTINUE   >*/
#line 279 "svdrs.f"
/* L300: */
#line 279 "svdrs.f"
    }
/*                             END.. SPECIAL FOR ZERO ROWS AND COLUMNS */
/*<       RETURN >*/
#line 281 "svdrs.f"
    return 0;
/*<       END    >*/
} /* svdrs_ */

