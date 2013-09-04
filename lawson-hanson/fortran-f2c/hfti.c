#line 1 "hfti.f"
/* hfti.f -- translated by f2c (version 20100827).
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

#line 1 "hfti.f"
/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;

/*<       SUBROUTINE HFTI (A,MDA,M,N,B,MDB,NB,TAU,KRANK,RNORM,H,G,IP)    >*/
/* Subroutine */ int hfti_(doublereal *a, integer *mda, integer *m, integer *
	n, doublereal *b, integer *mdb, integer *nb, doublereal *tau, integer 
	*krank, doublereal *rnorm, doublereal *h__, doublereal *g, integer *
	ip)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    integer i__, j, k, l;
    extern /* Subroutine */ int h12_(integer *, integer *, integer *, integer 
	    *, doublereal *, integer *, doublereal *, doublereal *, integer *,
	     integer *, integer *);
    integer jb, ii, jj;
    doublereal sm;
    integer ip1, kp1;
    doublereal tmp;
    extern doublereal diff_(doublereal *, doublereal *);
    doublereal hmax;
    integer lmax, ldiag;


/*  SOLVE LEAST SQUARES PROBLEM USING ALGORITHM, HFTI. */
/*  Householder Forward Triangulation with column Interchanges. */

/*  The original version of this code was developed by */
/*  Charles L. Lawson and Richard J. Hanson at Jet Propulsion Laboratory */
/*  1973 JUN 12, and published in the book */
/*  "SOLVING LEAST SQUARES PROBLEMS", Prentice-HalL, 1974. */
/*  Revised FEB 1995 to accompany reprinting of the book by SIAM. */
/*     ------------------------------------------------------------------ */
/*<       integer I, II, IP1, J, JB, JJ, K, KP1, KRANK >*/
/*<       integer L, LDIAG, LMAX, M, MDA, MDB, N, NB >*/
/*     integer IP(N) */
/*     double precision A(MDA,N),B(MDB,NB),H(N),G(N),RNORM(NB) */
/*<       integer IP(*)      >*/
/*<       double precision A(MDA,*),B(MDB, *),H(*),G(*),RNORM( *)   >*/
/*<       double precision DIFF, FACTOR, HMAX, SM, TAU, TMP, ZERO      >*/
/*<       parameter(FACTOR = 0.001d0, ZERO = 0.0d0) >*/
/*     ------------------------------------------------------------------ */

/*<       K=0    >*/
#line 22 "hfti.f"
    /* Parameter adjustments */
#line 22 "hfti.f"
    a_dim1 = *mda;
#line 22 "hfti.f"
    a_offset = 1 + a_dim1;
#line 22 "hfti.f"
    a -= a_offset;
#line 22 "hfti.f"
    b_dim1 = *mdb;
#line 22 "hfti.f"
    b_offset = 1 + b_dim1;
#line 22 "hfti.f"
    b -= b_offset;
#line 22 "hfti.f"
    --rnorm;
#line 22 "hfti.f"
    --h__;
#line 22 "hfti.f"
    --g;
#line 22 "hfti.f"
    --ip;
#line 22 "hfti.f"

#line 22 "hfti.f"
    /* Function Body */
#line 22 "hfti.f"
    k = 0;
/*<       LDIAG=min(M,N)    >*/
#line 23 "hfti.f"
    ldiag = min(*m,*n);
/*<       IF (LDIAG.LE.0) GO TO 270      >*/
#line 24 "hfti.f"
    if (ldiag <= 0) {
#line 24 "hfti.f"
	goto L270;
#line 24 "hfti.f"
    }
/*<           DO 80 J=1,LDIAG    >*/
#line 25 "hfti.f"
    i__1 = ldiag;
#line 25 "hfti.f"
    for (j = 1; j <= i__1; ++j) {
/*<           IF (J.EQ.1) GO TO 20   >*/
#line 26 "hfti.f"
	if (j == 1) {
#line 26 "hfti.f"
	    goto L20;
#line 26 "hfti.f"
	}

/*     UPDATE SQUARED COLUMN LENGTHS AND FIND LMAX */
/*    .. */
/*<           LMAX=J >*/
#line 30 "hfti.f"
	lmax = j;
/*<               DO 10 L=J,N    >*/
#line 31 "hfti.f"
	i__2 = *n;
#line 31 "hfti.f"
	for (l = j; l <= i__2; ++l) {
/*<               H(L)=H(L)-A(J-1,L)**2  >*/
/* Computing 2nd power */
#line 32 "hfti.f"
	    d__1 = a[j - 1 + l * a_dim1];
#line 32 "hfti.f"
	    h__[l] -= d__1 * d__1;
/*<               IF (H(L).GT.H(LMAX)) LMAX=L    >*/
#line 33 "hfti.f"
	    if (h__[l] > h__[lmax]) {
#line 33 "hfti.f"
		lmax = l;
#line 33 "hfti.f"
	    }
/*<    10         CONTINUE   >*/
#line 34 "hfti.f"
/* L10: */
#line 34 "hfti.f"
	}
/*<           IF(DIFF(HMAX+FACTOR*H(LMAX),HMAX)) 20,20,50    >*/
#line 35 "hfti.f"
	d__1 = hmax + h__[lmax] * .001;
#line 35 "hfti.f"
	if (diff_(&d__1, &hmax) <= 0.) {
#line 35 "hfti.f"
	    goto L20;
#line 35 "hfti.f"
	} else {
#line 35 "hfti.f"
	    goto L50;
#line 35 "hfti.f"
	}

/*     COMPUTE SQUARED COLUMN LENGTHS AND FIND LMAX */
/*    .. */
/*<    20     LMAX=J >*/
#line 39 "hfti.f"
L20:
#line 39 "hfti.f"
	lmax = j;
/*<               DO 40 L=J,N    >*/
#line 40 "hfti.f"
	i__2 = *n;
#line 40 "hfti.f"
	for (l = j; l <= i__2; ++l) {
/*<               H(L)=0.    >*/
#line 41 "hfti.f"
	    h__[l] = 0.f;
/*<                   DO 30 I=J,M    >*/
#line 42 "hfti.f"
	    i__3 = *m;
#line 42 "hfti.f"
	    for (i__ = j; i__ <= i__3; ++i__) {
/*<    30             H(L)=H(L)+A(I,L)**2    >*/
#line 43 "hfti.f"
/* L30: */
/* Computing 2nd power */
#line 43 "hfti.f"
		d__1 = a[i__ + l * a_dim1];
#line 43 "hfti.f"
		h__[l] += d__1 * d__1;
#line 43 "hfti.f"
	    }
/*<               IF (H(L).GT.H(LMAX)) LMAX=L    >*/
#line 44 "hfti.f"
	    if (h__[l] > h__[lmax]) {
#line 44 "hfti.f"
		lmax = l;
#line 44 "hfti.f"
	    }
/*<    40         CONTINUE   >*/
#line 45 "hfti.f"
/* L40: */
#line 45 "hfti.f"
	}
/*<           HMAX=H(LMAX)   >*/
#line 46 "hfti.f"
	hmax = h__[lmax];
/*    .. */
/*     LMAX HAS BEEN DETERMINED */

/*     DO COLUMN INTERCHANGES IF NEEDED. */
/*    .. */
/*<    50     CONTINUE   >*/
#line 52 "hfti.f"
L50:
/*<           IP(J)=LMAX     >*/
#line 53 "hfti.f"
	ip[j] = lmax;
/*<           IF (IP(J).EQ.J) GO TO 70   >*/
#line 54 "hfti.f"
	if (ip[j] == j) {
#line 54 "hfti.f"
	    goto L70;
#line 54 "hfti.f"
	}
/*<               DO 60 I=1,M    >*/
#line 55 "hfti.f"
	i__2 = *m;
#line 55 "hfti.f"
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<               TMP=A(I,J) >*/
#line 56 "hfti.f"
	    tmp = a[i__ + j * a_dim1];
/*<               A(I,J)=A(I,LMAX)   >*/
#line 57 "hfti.f"
	    a[i__ + j * a_dim1] = a[i__ + lmax * a_dim1];
/*<    60         A(I,LMAX)=TMP  >*/
#line 58 "hfti.f"
/* L60: */
#line 58 "hfti.f"
	    a[i__ + lmax * a_dim1] = tmp;
#line 58 "hfti.f"
	}
/*<           H(LMAX)=H(J)   >*/
#line 59 "hfti.f"
	h__[lmax] = h__[j];

/*     COMPUTE THE J-TH TRANSFORMATION AND APPLY IT TO A AND B. */
/*    .. */
/*<    70     CALL H12 (1,J,J+1,M,A(1,J),1,H(J),A(1,J+1),1,MDA,N-J)  >*/
#line 63 "hfti.f"
L70:
#line 63 "hfti.f"
	i__2 = j + 1;
#line 63 "hfti.f"
	i__3 = *n - j;
#line 63 "hfti.f"
	h12_(&c__1, &j, &i__2, m, &a[j * a_dim1 + 1], &c__1, &h__[j], &a[(j + 
		1) * a_dim1 + 1], &c__1, mda, &i__3);
/*<    80     CALL H12 (2,J,J+1,M,A(1,J),1,H(J),B,1,MDB,NB)      >*/
#line 64 "hfti.f"
/* L80: */
#line 64 "hfti.f"
	i__2 = j + 1;
#line 64 "hfti.f"
	h12_(&c__2, &j, &i__2, m, &a[j * a_dim1 + 1], &c__1, &h__[j], &b[
		b_offset], &c__1, mdb, nb);
#line 64 "hfti.f"
    }

/*     DETERMINE THE PSEUDORANK, K, USING THE TOLERANCE, TAU. */
/*    .. */
/*<           DO 90 J=1,LDIAG    >*/
#line 68 "hfti.f"
    i__2 = ldiag;
#line 68 "hfti.f"
    for (j = 1; j <= i__2; ++j) {
/*<           IF (ABS(A(J,J)).LE.TAU) GO TO 100      >*/
#line 69 "hfti.f"
	if ((d__1 = a[j + j * a_dim1], abs(d__1)) <= *tau) {
#line 69 "hfti.f"
	    goto L100;
#line 69 "hfti.f"
	}
/*<    90     CONTINUE   >*/
#line 70 "hfti.f"
/* L90: */
#line 70 "hfti.f"
    }
/*<       K=LDIAG    >*/
#line 71 "hfti.f"
    k = ldiag;
/*<       GO TO 110  >*/
#line 72 "hfti.f"
    goto L110;
/*<   100 K=J-1  >*/
#line 73 "hfti.f"
L100:
#line 73 "hfti.f"
    k = j - 1;
/*<   110 KP1=K+1    >*/
#line 74 "hfti.f"
L110:
#line 74 "hfti.f"
    kp1 = k + 1;

/*     COMPUTE THE NORMS OF THE RESIDUAL VECTORS. */

/*<       IF (NB.LE.0) GO TO 140 >*/
#line 78 "hfti.f"
    if (*nb <= 0) {
#line 78 "hfti.f"
	goto L140;
#line 78 "hfti.f"
    }
/*<           DO 130 JB=1,NB >*/
#line 79 "hfti.f"
    i__2 = *nb;
#line 79 "hfti.f"
    for (jb = 1; jb <= i__2; ++jb) {
/*<           TMP=ZERO      >*/
#line 80 "hfti.f"
	tmp = 0.;
/*<           IF (KP1.GT.M) GO TO 130    >*/
#line 81 "hfti.f"
	if (kp1 > *m) {
#line 81 "hfti.f"
	    goto L130;
#line 81 "hfti.f"
	}
/*<               DO 120 I=KP1,M >*/
#line 82 "hfti.f"
	i__1 = *m;
#line 82 "hfti.f"
	for (i__ = kp1; i__ <= i__1; ++i__) {
/*<   120         TMP=TMP+B(I,JB)**2     >*/
#line 83 "hfti.f"
/* L120: */
/* Computing 2nd power */
#line 83 "hfti.f"
	    d__1 = b[i__ + jb * b_dim1];
#line 83 "hfti.f"
	    tmp += d__1 * d__1;
#line 83 "hfti.f"
	}
/*<   130     RNORM(JB)=SQRT(TMP)    >*/
#line 84 "hfti.f"
L130:
#line 84 "hfti.f"
	rnorm[jb] = sqrt(tmp);
#line 84 "hfti.f"
    }
/*<   140 CONTINUE   >*/
#line 85 "hfti.f"
L140:
/*                                           SPECIAL FOR PSEUDORANK = 0 */
/*<       IF (K.GT.0) GO TO 160  >*/
#line 87 "hfti.f"
    if (k > 0) {
#line 87 "hfti.f"
	goto L160;
#line 87 "hfti.f"
    }
/*<       IF (NB.LE.0) GO TO 270 >*/
#line 88 "hfti.f"
    if (*nb <= 0) {
#line 88 "hfti.f"
	goto L270;
#line 88 "hfti.f"
    }
/*<           DO 150 JB=1,NB >*/
#line 89 "hfti.f"
    i__2 = *nb;
#line 89 "hfti.f"
    for (jb = 1; jb <= i__2; ++jb) {
/*<               DO 150 I=1,N   >*/
#line 90 "hfti.f"
	i__1 = *n;
#line 90 "hfti.f"
	for (i__ = 1; i__ <= i__1; ++i__) {
/*<   150         B(I,JB)=ZERO  >*/
#line 91 "hfti.f"
/* L150: */
#line 91 "hfti.f"
	    b[i__ + jb * b_dim1] = 0.;
#line 91 "hfti.f"
	}
#line 91 "hfti.f"
    }
/*<       GO TO 270  >*/
#line 92 "hfti.f"
    goto L270;

/*     IF THE PSEUDORANK IS LESS THAN N COMPUTE HOUSEHOLDER */
/*     DECOMPOSITION OF FIRST K ROWS. */
/*    .. */
/*<   160 IF (K.EQ.N) GO TO 180  >*/
#line 97 "hfti.f"
L160:
#line 97 "hfti.f"
    if (k == *n) {
#line 97 "hfti.f"
	goto L180;
#line 97 "hfti.f"
    }
/*<           DO 170 II=1,K  >*/
#line 98 "hfti.f"
    i__1 = k;
#line 98 "hfti.f"
    for (ii = 1; ii <= i__1; ++ii) {
/*<           I=KP1-II   >*/
#line 99 "hfti.f"
	i__ = kp1 - ii;
/*<   170     CALL H12 (1,I,KP1,N,A(I,1),MDA,G(I),A,MDA,1,I-1)   >*/
#line 100 "hfti.f"
/* L170: */
#line 100 "hfti.f"
	i__2 = i__ - 1;
#line 100 "hfti.f"
	h12_(&c__1, &i__, &kp1, n, &a[i__ + a_dim1], mda, &g[i__], &a[
		a_offset], mda, &c__1, &i__2);
#line 100 "hfti.f"
    }
/*<   180 CONTINUE   >*/
#line 101 "hfti.f"
L180:


/*<       IF (NB.LE.0) GO TO 270 >*/
#line 104 "hfti.f"
    if (*nb <= 0) {
#line 104 "hfti.f"
	goto L270;
#line 104 "hfti.f"
    }
/*<           DO 260 JB=1,NB >*/
#line 105 "hfti.f"
    i__2 = *nb;
#line 105 "hfti.f"
    for (jb = 1; jb <= i__2; ++jb) {

/*     SOLVE THE K BY K TRIANGULAR SYSTEM. */
/*    .. */
/*<               DO 210 L=1,K   >*/
#line 109 "hfti.f"
	i__1 = k;
#line 109 "hfti.f"
	for (l = 1; l <= i__1; ++l) {
/*<               SM=ZERO   >*/
#line 110 "hfti.f"
	    sm = 0.;
/*<               I=KP1-L    >*/
#line 111 "hfti.f"
	    i__ = kp1 - l;
/*<               IF (I.EQ.K) GO TO 200  >*/
#line 112 "hfti.f"
	    if (i__ == k) {
#line 112 "hfti.f"
		goto L200;
#line 112 "hfti.f"
	    }
/*<               IP1=I+1    >*/
#line 113 "hfti.f"
	    ip1 = i__ + 1;
/*<                   DO 190 J=IP1,K     >*/
#line 114 "hfti.f"
	    i__3 = k;
#line 114 "hfti.f"
	    for (j = ip1; j <= i__3; ++j) {
/*<   190             SM=SM+A(I,J)*B(J,JB) >*/
#line 115 "hfti.f"
/* L190: */
#line 115 "hfti.f"
		sm += a[i__ + j * a_dim1] * b[j + jb * b_dim1];
#line 115 "hfti.f"
	    }
/*<   200         continue >*/
#line 116 "hfti.f"
L200:
/*<   210         B(I,JB)=(B(I,JB)-SM)/A(I,I)   >*/
#line 117 "hfti.f"
/* L210: */
#line 117 "hfti.f"
	    b[i__ + jb * b_dim1] = (b[i__ + jb * b_dim1] - sm) / a[i__ + i__ *
		     a_dim1];
#line 117 "hfti.f"
	}

/*     COMPLETE COMPUTATION OF SOLUTION VECTOR. */
/*    .. */
/*<           IF (K.EQ.N) GO TO 240      >*/
#line 121 "hfti.f"
	if (k == *n) {
#line 121 "hfti.f"
	    goto L240;
#line 121 "hfti.f"
	}
/*<               DO 220 J=KP1,N >*/
#line 122 "hfti.f"
	i__1 = *n;
#line 122 "hfti.f"
	for (j = kp1; j <= i__1; ++j) {
/*<   220         B(J,JB)=ZERO  >*/
#line 123 "hfti.f"
/* L220: */
#line 123 "hfti.f"
	    b[j + jb * b_dim1] = 0.;
#line 123 "hfti.f"
	}
/*<               DO 230 I=1,K   >*/
#line 124 "hfti.f"
	i__1 = k;
#line 124 "hfti.f"
	for (i__ = 1; i__ <= i__1; ++i__) {
/*<   230         CALL H12 (2,I,KP1,N,A(I,1),MDA,G(I),B(1,JB),1,MDB,1)   >*/
#line 125 "hfti.f"
/* L230: */
#line 125 "hfti.f"
	    h12_(&c__2, &i__, &kp1, n, &a[i__ + a_dim1], mda, &g[i__], &b[jb *
		     b_dim1 + 1], &c__1, mdb, &c__1);
#line 125 "hfti.f"
	}

/*      RE-ORDER THE SOLUTION VECTOR TO COMPENSATE FOR THE */
/*      COLUMN INTERCHANGES. */
/*    .. */
/*<   240         DO 250 JJ=1,LDIAG      >*/
#line 130 "hfti.f"
L240:
#line 130 "hfti.f"
	i__1 = ldiag;
#line 130 "hfti.f"
	for (jj = 1; jj <= i__1; ++jj) {
/*<               J=LDIAG+1-JJ   >*/
#line 131 "hfti.f"
	    j = ldiag + 1 - jj;
/*<               IF (IP(J).EQ.J) GO TO 250  >*/
#line 132 "hfti.f"
	    if (ip[j] == j) {
#line 132 "hfti.f"
		goto L250;
#line 132 "hfti.f"
	    }
/*<               L=IP(J)    >*/
#line 133 "hfti.f"
	    l = ip[j];
/*<               TMP=B(L,JB)    >*/
#line 134 "hfti.f"
	    tmp = b[l + jb * b_dim1];
/*<               B(L,JB)=B(J,JB)    >*/
#line 135 "hfti.f"
	    b[l + jb * b_dim1] = b[j + jb * b_dim1];
/*<               B(J,JB)=TMP    >*/
#line 136 "hfti.f"
	    b[j + jb * b_dim1] = tmp;
/*<   250         CONTINUE   >*/
#line 137 "hfti.f"
L250:
#line 137 "hfti.f"
	    ;
#line 137 "hfti.f"
	}
/*<   260     CONTINUE   >*/
#line 138 "hfti.f"
/* L260: */
#line 138 "hfti.f"
    }
/*    .. */
/*     THE SOLUTION VECTORS, X, ARE NOW */
/*     IN THE FIRST  N  ROWS OF THE ARRAY B(,). */

/*<   270 KRANK=K    >*/
#line 143 "hfti.f"
L270:
#line 143 "hfti.f"
    *krank = k;
/*<       RETURN >*/
#line 144 "hfti.f"
    return 0;
/*<       END   >*/
} /* hfti_ */

