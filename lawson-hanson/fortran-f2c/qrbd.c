#line 1 "qrbd.f"
/* qrbd.f -- translated by f2c (version 20100827).
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

#line 1 "qrbd.f"
/*     SUBROUTINE QRBD (IPASS,Q,E,NN,V,MDV,NRV,C,MDC,NCC) */

/*  QR ALGORITHM FOR SINGULAR VALUES OF A BIDIAGONAL MATRIX. */

/*  The original version of this code was developed by */
/*  Charles L. Lawson and Richard J. Hanson at Jet Propulsion Laboratory */
/*  1973 JUN 12, and published in the book */
/*  "SOLVING LEAST SQUARES PROBLEMS", Prentice-HalL, 1974. */
/*  Revised FEB 1995 to accompany reprinting of the book by SIAM. */
/*     ------------------------------------------------------------------ */
/*     THE BIDIAGONAL MATRIX */

/*                       (Q1,E2,0...    ) */
/*                       (   Q2,E3,0... ) */
/*                D=     (       .      ) */
/*                       (         .   0) */
/*                       (           .EN) */
/*                       (          0,QN) */

/*                 IS PRE AND POST MULTIPLIED BY */
/*                 ELEMENTARY ROTATION MATRICES */
/*                 RI AND PI SO THAT */

/*                 RK...R1*D*P1**(T)...PK**(T) = DIAG(S1,...,SN) */

/*                 TO WITHIN WORKING ACCURACY. */

/*  1. EI AND QI OCCUPY E(I) AND Q(I) AS INPUT. */

/*  2. RM...R1*C REPLACES 'C' IN STORAGE AS OUTPUT. */

/*  3. V*P1**(T)...PM**(T) REPLACES 'V' IN STORAGE AS OUTPUT. */

/*  4. SI OCCUPIES Q(I) AS OUTPUT. */

/*  5. THE SI'S ARE NONINCREASING AND NONNEGATIVE. */

/*     THIS CODE IS BASED ON THE PAPER AND 'ALGOL' CODE.. */
/* REF.. */
/*  1. REINSCH,C.H. AND GOLUB,G.H. 'SINGULAR VALUE DECOMPOSITION */
/*     AND LEAST SQUARES SOLUTIONS' (NUMER. MATH.), VOL. 14,(1970). */

/*     ------------------------------------------------------------------ */
/*<       SUBROUTINE QRBD (IPASS,Q,E,NN,V,MDV,NRV,C,MDC,NCC)     >*/
/* Subroutine */ int qrbd_(integer *ipass, doublereal *q, doublereal *e, 
	integer *nn, doublereal *v, integer *mdv, integer *nrv, doublereal *
	c__, integer *mdc, integer *ncc)
{
    /* System generated locals */
    integer c_dim1, c_offset, v_dim1, v_offset, i__1, i__2, i__3;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    doublereal f, g, h__;
    integer i__, j, k, l, n;
    doublereal t, x, y, z__;
    extern /* Subroutine */ int g1_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    integer n10, ii, kk;
    doublereal cs;
    integer ll;
    doublereal sn;
    integer lp1;
    extern doublereal diff_(doublereal *, doublereal *);
    logical fail;
    doublereal temp;
    integer nqrs;
    logical wntv;
    doublereal small, dnorm;
    logical havers;

/*     ------------------------------------------------------------------ */
/*<       integer MDC, MDV, NCC, NN, NRV >*/
/*     double precision C(MDC,NCC), E(NN), Q(NN),V(MDV,NN) */
/*<       double precision C(MDC,*  ), E(* ), Q(* ),V(MDV,* ) >*/
/*<       integer I, II, IPASS, J, K, KK, L, LL, LP1, N, N10, NQRS >*/
/*<       double precision CS, DIFF, DNORM, F, G, H, SMALL >*/
/*<       double precision ONE, SN, T, TEMP, TWO, X, Y, Z, ZERO >*/
/*<       logical WNTV ,HAVERS,FAIL      >*/
/*<       parameter(ONE = 1.0d0, TWO = 2.0d0, ZERO = 0.0d0) >*/
/*     ------------------------------------------------------------------ */
/*<       N=NN   >*/
#line 56 "qrbd.f"
    /* Parameter adjustments */
#line 56 "qrbd.f"
    --q;
#line 56 "qrbd.f"
    --e;
#line 56 "qrbd.f"
    v_dim1 = *mdv;
#line 56 "qrbd.f"
    v_offset = 1 + v_dim1;
#line 56 "qrbd.f"
    v -= v_offset;
#line 56 "qrbd.f"
    c_dim1 = *mdc;
#line 56 "qrbd.f"
    c_offset = 1 + c_dim1;
#line 56 "qrbd.f"
    c__ -= c_offset;
#line 56 "qrbd.f"

#line 56 "qrbd.f"
    /* Function Body */
#line 56 "qrbd.f"
    n = *nn;
/*<       IPASS=1    >*/
#line 57 "qrbd.f"
    *ipass = 1;
/*<       IF (N.LE.0) RETURN >*/
#line 58 "qrbd.f"
    if (n <= 0) {
#line 58 "qrbd.f"
	return 0;
#line 58 "qrbd.f"
    }
/*<       N10=10*N   >*/
#line 59 "qrbd.f"
    n10 = n * 10;
/*<       WNTV=NRV.GT.0      >*/
#line 60 "qrbd.f"
    wntv = *nrv > 0;
/*<       HAVERS=NCC.GT.0    >*/
#line 61 "qrbd.f"
    havers = *ncc > 0;
/*<       FAIL=.FALSE.   >*/
#line 62 "qrbd.f"
    fail = FALSE_;
/*<       NQRS=0 >*/
#line 63 "qrbd.f"
    nqrs = 0;
/*<       E(1)=ZERO  >*/
#line 64 "qrbd.f"
    e[1] = 0.;
/*<       DNORM=ZERO >*/
#line 65 "qrbd.f"
    dnorm = 0.;
/*<            DO 10 J=1,N   >*/
#line 66 "qrbd.f"
    i__1 = n;
#line 66 "qrbd.f"
    for (j = 1; j <= i__1; ++j) {
/*<    10      DNORM=max(abs(Q(J))+abs(E(J)),DNORM)    >*/
#line 67 "qrbd.f"
/* L10: */
/* Computing MAX */
#line 67 "qrbd.f"
	d__3 = (d__1 = q[j], abs(d__1)) + (d__2 = e[j], abs(d__2));
#line 67 "qrbd.f"
	dnorm = max(d__3,dnorm);
#line 67 "qrbd.f"
    }
/*<            DO 200 KK=1,N >*/
#line 68 "qrbd.f"
    i__1 = n;
#line 68 "qrbd.f"
    for (kk = 1; kk <= i__1; ++kk) {
/*<            K=N+1-KK      >*/
#line 69 "qrbd.f"
	k = n + 1 - kk;

/*     TEST FOR SPLITTING OR RANK DEFICIENCIES.. */
/*         FIRST MAKE TEST FOR LAST DIAGONAL TERM, Q(K), BEING SMALL. */
/*<    20       IF(K.EQ.1) GO TO 50      >*/
#line 73 "qrbd.f"
L20:
#line 73 "qrbd.f"
	if (k == 1) {
#line 73 "qrbd.f"
	    goto L50;
#line 73 "qrbd.f"
	}
/*<             IF(DIFF(DNORM+Q(K),DNORM) .ne. ZERO) go to 50 >*/
#line 74 "qrbd.f"
	d__1 = dnorm + q[k];
#line 74 "qrbd.f"
	if (diff_(&d__1, &dnorm) != 0.) {
#line 74 "qrbd.f"
	    goto L50;
#line 74 "qrbd.f"
	}

/*     SINCE Q(K) IS SMALL WE WILL MAKE A SPECIAL PASS TO */
/*     TRANSFORM E(K) TO ZERO. */

/*<            CS=ZERO   >*/
#line 79 "qrbd.f"
	cs = 0.;
/*<            SN=-ONE   >*/
#line 80 "qrbd.f"
	sn = -1.;
/*<                 DO 40 II=2,K >*/
#line 81 "qrbd.f"
	i__2 = k;
#line 81 "qrbd.f"
	for (ii = 2; ii <= i__2; ++ii) {
/*<                 I=K+1-II >*/
#line 82 "qrbd.f"
	    i__ = k + 1 - ii;
/*<                 F=-SN*E(I+1) >*/
#line 83 "qrbd.f"
	    f = -sn * e[i__ + 1];
/*<                 E(I+1)=CS*E(I+1)     >*/
#line 84 "qrbd.f"
	    e[i__ + 1] = cs * e[i__ + 1];
/*<                 CALL G1 (Q(I),F,CS,SN,Q(I))      >*/
#line 85 "qrbd.f"
	    g1_(&q[i__], &f, &cs, &sn, &q[i__]);
/*         TRANSFORMATION CONSTRUCTED TO ZERO POSITION (I,K). */

/*<                 IF (.NOT.WNTV) GO TO 40  >*/
#line 88 "qrbd.f"
	    if (! wntv) {
#line 88 "qrbd.f"
		goto L40;
#line 88 "qrbd.f"
	    }
/*<                      DO 30 J=1,NRV   >*/
#line 89 "qrbd.f"
	    i__3 = *nrv;
#line 89 "qrbd.f"
	    for (j = 1; j <= i__3; ++j) {

/*                          Apply procedure G2 (CS,SN,V(J,I),V(J,K)) */

/*<                         TEMP = V(J,I) >*/
#line 93 "qrbd.f"
		temp = v[j + i__ * v_dim1];
/*<                         V(J,I) = CS*TEMP + SN*V(J,K) >*/
#line 94 "qrbd.f"
		v[j + i__ * v_dim1] = cs * temp + sn * v[j + k * v_dim1];
/*<                         V(J,K) =-SN*TEMP + CS*V(J,K) >*/
#line 95 "qrbd.f"
		v[j + k * v_dim1] = -sn * temp + cs * v[j + k * v_dim1];
/*<    30                continue >*/
#line 96 "qrbd.f"
/* L30: */
#line 96 "qrbd.f"
	    }
/*              ACCUMULATE RT. TRANSFORMATIONS IN V. */

/*<    40           CONTINUE >*/
#line 99 "qrbd.f"
L40:
#line 99 "qrbd.f"
	    ;
#line 99 "qrbd.f"
	}

/*         THE MATRIX IS NOW BIDIAGONAL, AND OF LOWER ORDER */
/*         SINCE E(K) .EQ. ZERO.. */

/*<    50           DO 60 LL=1,K >*/
#line 104 "qrbd.f"
L50:
#line 104 "qrbd.f"
	i__2 = k;
#line 104 "qrbd.f"
	for (ll = 1; ll <= i__2; ++ll) {
/*<                   L=K+1-LL >*/
#line 105 "qrbd.f"
	    l = k + 1 - ll;
/*<                   IF(DIFF(DNORM+E(L),DNORM) .eq. ZERO) go to 100 >*/
#line 106 "qrbd.f"
	    d__1 = dnorm + e[l];
#line 106 "qrbd.f"
	    if (diff_(&d__1, &dnorm) == 0.) {
#line 106 "qrbd.f"
		goto L100;
#line 106 "qrbd.f"
	    }
/*<                   IF(DIFF(DNORM+Q(L-1),DNORM) .eq. ZERO) go to 70 >*/
#line 107 "qrbd.f"
	    d__1 = dnorm + q[l - 1];
#line 107 "qrbd.f"
	    if (diff_(&d__1, &dnorm) == 0.) {
#line 107 "qrbd.f"
		goto L70;
#line 107 "qrbd.f"
	    }
/*<    60           CONTINUE >*/
#line 108 "qrbd.f"
/* L60: */
#line 108 "qrbd.f"
	}
/*     THIS LOOP CAN'T COMPLETE SINCE E(1) = ZERO. */

/*<            GO TO 100     >*/
#line 111 "qrbd.f"
	goto L100;

/*         CANCELLATION OF E(L), L.GT.1. */
/*<    70      CS=ZERO   >*/
#line 114 "qrbd.f"
L70:
#line 114 "qrbd.f"
	cs = 0.;
/*<            SN=-ONE   >*/
#line 115 "qrbd.f"
	sn = -1.;
/*<                 DO 90 I=L,K  >*/
#line 116 "qrbd.f"
	i__2 = k;
#line 116 "qrbd.f"
	for (i__ = l; i__ <= i__2; ++i__) {
/*<                 F=-SN*E(I)   >*/
#line 117 "qrbd.f"
	    f = -sn * e[i__];
/*<                 E(I)=CS*E(I) >*/
#line 118 "qrbd.f"
	    e[i__] = cs * e[i__];
/*<                 IF(DIFF(DNORM+F,DNORM) .eq. ZERO) go to 100 >*/
#line 119 "qrbd.f"
	    d__1 = dnorm + f;
#line 119 "qrbd.f"
	    if (diff_(&d__1, &dnorm) == 0.) {
#line 119 "qrbd.f"
		goto L100;
#line 119 "qrbd.f"
	    }
/*<                 CALL G1 (Q(I),F,CS,SN,Q(I))      >*/
#line 120 "qrbd.f"
	    g1_(&q[i__], &f, &cs, &sn, &q[i__]);
/*<                 IF (HAVERS) then >*/
#line 121 "qrbd.f"
	    if (havers) {
/*<                      DO 80 J=1,NCC   >*/
#line 122 "qrbd.f"
		i__3 = *ncc;
#line 122 "qrbd.f"
		for (j = 1; j <= i__3; ++j) {

/*                          Apply procedure G2 ( CS, SN, C(I,J), C(L-1,J) */

/*<                         TEMP = C(I,J) >*/
#line 126 "qrbd.f"
		    temp = c__[i__ + j * c_dim1];
/*<                         C(I,J)   = CS*TEMP + SN*C(L-1,J) >*/
#line 127 "qrbd.f"
		    c__[i__ + j * c_dim1] = cs * temp + sn * c__[l - 1 + j * 
			    c_dim1];
/*<                         C(L-1,J) =-SN*TEMP + CS*C(L-1,J) >*/
#line 128 "qrbd.f"
		    c__[l - 1 + j * c_dim1] = -sn * temp + cs * c__[l - 1 + j 
			    * c_dim1];
/*<    80                continue >*/
#line 129 "qrbd.f"
/* L80: */
#line 129 "qrbd.f"
		}
/*<                 endif >*/
#line 130 "qrbd.f"
	    }
/*<    90           CONTINUE >*/
#line 131 "qrbd.f"
/* L90: */
#line 131 "qrbd.f"
	}

/*         TEST FOR CONVERGENCE.. */
/*<   100      Z=Q(K)    >*/
#line 134 "qrbd.f"
L100:
#line 134 "qrbd.f"
	z__ = q[k];
/*<            IF (L.EQ.K) GO TO 170     >*/
#line 135 "qrbd.f"
	if (l == k) {
#line 135 "qrbd.f"
	    goto L170;
#line 135 "qrbd.f"
	}

/*         SHIFT FROM BOTTOM 2 BY 2 MINOR OF B**(T)*B. */
/*<            X=Q(L)    >*/
#line 138 "qrbd.f"
	x = q[l];
/*<            Y=Q(K-1)      >*/
#line 139 "qrbd.f"
	y = q[k - 1];
/*<            G=E(K-1)      >*/
#line 140 "qrbd.f"
	g = e[k - 1];
/*<            H=E(K)    >*/
#line 141 "qrbd.f"
	h__ = e[k];
/*<            F=((Y-Z)*(Y+Z)+(G-H)*(G+H))/(TWO*H*Y) >*/
#line 142 "qrbd.f"
	f = ((y - z__) * (y + z__) + (g - h__) * (g + h__)) / (h__ * 2. * y);
/*<            G=sqrt(ONE+F**2)  >*/
/* Computing 2nd power */
#line 143 "qrbd.f"
	d__1 = f;
#line 143 "qrbd.f"
	g = sqrt(d__1 * d__1 + 1.);
/*<            IF (F .ge. ZERO) then >*/
#line 144 "qrbd.f"
	if (f >= 0.) {
/*<               T=F+G >*/
#line 145 "qrbd.f"
	    t = f + g;
/*<            else >*/
#line 146 "qrbd.f"
	} else {
/*<               T=F-G >*/
#line 147 "qrbd.f"
	    t = f - g;
/*<            endif >*/
#line 148 "qrbd.f"
	}
/*<            F=((X-Z)*(X+Z)+H*(Y/T-H))/X   >*/
#line 149 "qrbd.f"
	f = ((x - z__) * (x + z__) + h__ * (y / t - h__)) / x;

/*         NEXT QR SWEEP.. */
/*<            CS=ONE    >*/
#line 152 "qrbd.f"
	cs = 1.;
/*<            SN=ONE    >*/
#line 153 "qrbd.f"
	sn = 1.;
/*<            LP1=L+1   >*/
#line 154 "qrbd.f"
	lp1 = l + 1;
/*<                 DO 160 I=LP1,K   >*/
#line 155 "qrbd.f"
	i__2 = k;
#line 155 "qrbd.f"
	for (i__ = lp1; i__ <= i__2; ++i__) {
/*<                 G=E(I)   >*/
#line 156 "qrbd.f"
	    g = e[i__];
/*<                 Y=Q(I)   >*/
#line 157 "qrbd.f"
	    y = q[i__];
/*<                 H=SN*G   >*/
#line 158 "qrbd.f"
	    h__ = sn * g;
/*<                 G=CS*G   >*/
#line 159 "qrbd.f"
	    g = cs * g;
/*<                 CALL G1 (F,H,CS,SN,E(I-1))   >*/
#line 160 "qrbd.f"
	    g1_(&f, &h__, &cs, &sn, &e[i__ - 1]);
/*<                 F=X*CS+G*SN  >*/
#line 161 "qrbd.f"
	    f = x * cs + g * sn;
/*<                 G=-X*SN+G*CS >*/
#line 162 "qrbd.f"
	    g = -x * sn + g * cs;
/*<                 H=Y*SN   >*/
#line 163 "qrbd.f"
	    h__ = y * sn;
/*<                 Y=Y*CS   >*/
#line 164 "qrbd.f"
	    y *= cs;
/*<                 IF (WNTV) then >*/
#line 165 "qrbd.f"
	    if (wntv) {

/*              ACCUMULATE ROTATIONS (FROM THE RIGHT) IN 'V' */

/*<                      DO 130 J=1,NRV  >*/
#line 169 "qrbd.f"
		i__3 = *nrv;
#line 169 "qrbd.f"
		for (j = 1; j <= i__3; ++j) {

/*                          Apply procedure G2 (CS,SN,V(J,I-1),V(J,I)) */

/*<                         TEMP = V(J,I-1) >*/
#line 173 "qrbd.f"
		    temp = v[j + (i__ - 1) * v_dim1];
/*<                         V(J,I-1) = CS*TEMP + SN*V(J,I) >*/
#line 174 "qrbd.f"
		    v[j + (i__ - 1) * v_dim1] = cs * temp + sn * v[j + i__ * 
			    v_dim1];
/*<                         V(J,I)   =-SN*TEMP + CS*V(J,I) >*/
#line 175 "qrbd.f"
		    v[j + i__ * v_dim1] = -sn * temp + cs * v[j + i__ * 
			    v_dim1];
/*<   130                continue >*/
#line 176 "qrbd.f"
/* L130: */
#line 176 "qrbd.f"
		}
/*<                 endif >*/
#line 177 "qrbd.f"
	    }
/*<                 CALL G1 (F,H,CS,SN,Q(I-1))   >*/
#line 178 "qrbd.f"
	    g1_(&f, &h__, &cs, &sn, &q[i__ - 1]);
/*<                 F=CS*G+SN*Y  >*/
#line 179 "qrbd.f"
	    f = cs * g + sn * y;
/*<                 X=-SN*G+CS*Y >*/
#line 180 "qrbd.f"
	    x = -sn * g + cs * y;
/*<                 IF (HAVERS) then >*/
#line 181 "qrbd.f"
	    if (havers) {
/*<                      DO 150 J=1,NCC  >*/
#line 182 "qrbd.f"
		i__3 = *ncc;
#line 182 "qrbd.f"
		for (j = 1; j <= i__3; ++j) {

/*                          Apply procedure G2 (CS,SN,C(I-1,J),C(I,J)) */

/*<                         TEMP = C(I-1,J) >*/
#line 186 "qrbd.f"
		    temp = c__[i__ - 1 + j * c_dim1];
/*<                         C(I-1,J) = CS*TEMP + SN*C(I,J) >*/
#line 187 "qrbd.f"
		    c__[i__ - 1 + j * c_dim1] = cs * temp + sn * c__[i__ + j *
			     c_dim1];
/*<                         C(I,J)   =-SN*TEMP + CS*C(I,J) >*/
#line 188 "qrbd.f"
		    c__[i__ + j * c_dim1] = -sn * temp + cs * c__[i__ + j * 
			    c_dim1];
/*<   150                continue >*/
#line 189 "qrbd.f"
/* L150: */
#line 189 "qrbd.f"
		}
/*<                 endif >*/
#line 190 "qrbd.f"
	    }

/*              APPLY ROTATIONS FROM THE LEFT TO */
/*              RIGHT HAND SIDES IN 'C'.. */

/*<   160           CONTINUE >*/
#line 195 "qrbd.f"
/* L160: */
#line 195 "qrbd.f"
	}
/*<            E(L)=ZERO     >*/
#line 196 "qrbd.f"
	e[l] = 0.;
/*<            E(K)=F    >*/
#line 197 "qrbd.f"
	e[k] = f;
/*<            Q(K)=X    >*/
#line 198 "qrbd.f"
	q[k] = x;
/*<            NQRS=NQRS+1   >*/
#line 199 "qrbd.f"
	++nqrs;
/*<            IF (NQRS.LE.N10) GO TO 20 >*/
#line 200 "qrbd.f"
	if (nqrs <= n10) {
#line 200 "qrbd.f"
	    goto L20;
#line 200 "qrbd.f"
	}
/*          RETURN TO 'TEST FOR SPLITTING'. */

/*<            SMALL=ABS(E(K)) >*/
#line 203 "qrbd.f"
	small = (d__1 = e[k], abs(d__1));
/*<            I=K      >*/
#line 204 "qrbd.f"
	i__ = k;
/*          IF FAILURE TO CONVERGE SET SMALLEST MAGNITUDE */
/*          TERM IN OFF-DIAGONAL TO ZERO.  CONTINUE ON. */
/*      .. */
/*<                 DO 165 J=L,K  >*/
#line 208 "qrbd.f"
	i__2 = k;
#line 208 "qrbd.f"
	for (j = l; j <= i__2; ++j) {
/*<                 TEMP=ABS(E(J)) >*/
#line 209 "qrbd.f"
	    temp = (d__1 = e[j], abs(d__1));
/*<                 IF(TEMP .EQ. ZERO) GO TO 165 >*/
#line 210 "qrbd.f"
	    if (temp == 0.) {
#line 210 "qrbd.f"
		goto L165;
#line 210 "qrbd.f"
	    }
/*<                 IF(TEMP .LT. SMALL) THEN >*/
#line 211 "qrbd.f"
	    if (temp < small) {
/*<                      SMALL=TEMP >*/
#line 212 "qrbd.f"
		small = temp;
/*<                      I=J >*/
#line 213 "qrbd.f"
		i__ = j;
/*<                 end if   >*/
#line 214 "qrbd.f"
	    }
/*<   165           CONTINUE >*/
#line 215 "qrbd.f"
L165:
#line 215 "qrbd.f"
	    ;
#line 215 "qrbd.f"
	}
/*<            E(I)=ZERO >*/
#line 216 "qrbd.f"
	e[i__] = 0.;
/*<            NQRS=0 >*/
#line 217 "qrbd.f"
	nqrs = 0;
/*<            FAIL=.TRUE.   >*/
#line 218 "qrbd.f"
	fail = TRUE_;
/*<            GO TO 20 >*/
#line 219 "qrbd.f"
	goto L20;
/*     .. */
/*     CUTOFF FOR CONVERGENCE FAILURE. 'NQRS' WILL BE 2*N USUALLY. */
/*<   170      IF (Z.GE.ZERO) GO TO 190  >*/
#line 222 "qrbd.f"
L170:
#line 222 "qrbd.f"
	if (z__ >= 0.) {
#line 222 "qrbd.f"
	    goto L190;
#line 222 "qrbd.f"
	}
/*<            Q(K)=-Z   >*/
#line 223 "qrbd.f"
	q[k] = -z__;
/*<            IF (WNTV) then >*/
#line 224 "qrbd.f"
	if (wntv) {
/*<                 DO 180 J=1,NRV   >*/
#line 225 "qrbd.f"
	    i__2 = *nrv;
#line 225 "qrbd.f"
	    for (j = 1; j <= i__2; ++j) {
/*<   180           V(J,K)=-V(J,K)   >*/
#line 226 "qrbd.f"
/* L180: */
#line 226 "qrbd.f"
		v[j + k * v_dim1] = -v[j + k * v_dim1];
#line 226 "qrbd.f"
	    }
/*<            endif >*/
#line 227 "qrbd.f"
	}
/*<   190      CONTINUE      >*/
#line 228 "qrbd.f"
L190:
/*         CONVERGENCE. Q(K) IS MADE NONNEGATIVE.. */

/*<   200      CONTINUE      >*/
#line 231 "qrbd.f"
/* L200: */
#line 231 "qrbd.f"
	;
#line 231 "qrbd.f"
    }
/*<       IF (N.EQ.1) RETURN >*/
#line 232 "qrbd.f"
    if (n == 1) {
#line 232 "qrbd.f"
	return 0;
#line 232 "qrbd.f"
    }
/*<            DO 210 I=2,N  >*/
#line 233 "qrbd.f"
    i__1 = n;
#line 233 "qrbd.f"
    for (i__ = 2; i__ <= i__1; ++i__) {
/*<            IF (Q(I).GT.Q(I-1)) GO TO 220 >*/
#line 234 "qrbd.f"
	if (q[i__] > q[i__ - 1]) {
#line 234 "qrbd.f"
	    goto L220;
#line 234 "qrbd.f"
	}
/*<   210      CONTINUE      >*/
#line 235 "qrbd.f"
/* L210: */
#line 235 "qrbd.f"
    }
/*<       IF (FAIL) IPASS=2  >*/
#line 236 "qrbd.f"
    if (fail) {
#line 236 "qrbd.f"
	*ipass = 2;
#line 236 "qrbd.f"
    }
/*<       RETURN >*/
#line 237 "qrbd.f"
    return 0;
/*     .. */
/*     EVERY SINGULAR VALUE IS IN ORDER.. */
/*<   220      DO 270 I=2,N  >*/
#line 240 "qrbd.f"
L220:
#line 240 "qrbd.f"
    i__1 = n;
#line 240 "qrbd.f"
    for (i__ = 2; i__ <= i__1; ++i__) {
/*<            T=Q(I-1)      >*/
#line 241 "qrbd.f"
	t = q[i__ - 1];
/*<            K=I-1 >*/
#line 242 "qrbd.f"
	k = i__ - 1;
/*<                 DO 230 J=I,N >*/
#line 243 "qrbd.f"
	i__2 = n;
#line 243 "qrbd.f"
	for (j = i__; j <= i__2; ++j) {
/*<                 IF (T.GE.Q(J)) GO TO 230 >*/
#line 244 "qrbd.f"
	    if (t >= q[j]) {
#line 244 "qrbd.f"
		goto L230;
#line 244 "qrbd.f"
	    }
/*<                 T=Q(J)   >*/
#line 245 "qrbd.f"
	    t = q[j];
/*<                 K=J      >*/
#line 246 "qrbd.f"
	    k = j;
/*<   230           CONTINUE >*/
#line 247 "qrbd.f"
L230:
#line 247 "qrbd.f"
	    ;
#line 247 "qrbd.f"
	}
/*<            IF (K.EQ.I-1) GO TO 270   >*/
#line 248 "qrbd.f"
	if (k == i__ - 1) {
#line 248 "qrbd.f"
	    goto L270;
#line 248 "qrbd.f"
	}
/*<            Q(K)=Q(I-1)   >*/
#line 249 "qrbd.f"
	q[k] = q[i__ - 1];
/*<            Q(I-1)=T      >*/
#line 250 "qrbd.f"
	q[i__ - 1] = t;
/*<            IF (HAVERS) then >*/
#line 251 "qrbd.f"
	if (havers) {
/*<                 DO 240 J=1,NCC   >*/
#line 252 "qrbd.f"
	    i__2 = *ncc;
#line 252 "qrbd.f"
	    for (j = 1; j <= i__2; ++j) {
/*<                 T=C(I-1,J)   >*/
#line 253 "qrbd.f"
		t = c__[i__ - 1 + j * c_dim1];
/*<                 C(I-1,J)=C(K,J)      >*/
#line 254 "qrbd.f"
		c__[i__ - 1 + j * c_dim1] = c__[k + j * c_dim1];
/*<   240           C(K,J)=T >*/
#line 255 "qrbd.f"
/* L240: */
#line 255 "qrbd.f"
		c__[k + j * c_dim1] = t;
#line 255 "qrbd.f"
	    }
/*<            endif >*/
#line 256 "qrbd.f"
	}
/*<   250      IF (WNTV) then >*/
#line 258 "qrbd.f"
/* L250: */
#line 258 "qrbd.f"
	if (wntv) {
/*<                 DO 260 J=1,NRV   >*/
#line 259 "qrbd.f"
	    i__2 = *nrv;
#line 259 "qrbd.f"
	    for (j = 1; j <= i__2; ++j) {
/*<                 T=V(J,I-1)   >*/
#line 260 "qrbd.f"
		t = v[j + (i__ - 1) * v_dim1];
/*<                 V(J,I-1)=V(J,K)      >*/
#line 261 "qrbd.f"
		v[j + (i__ - 1) * v_dim1] = v[j + k * v_dim1];
/*<   260           V(J,K)=T >*/
#line 262 "qrbd.f"
/* L260: */
#line 262 "qrbd.f"
		v[j + k * v_dim1] = t;
#line 262 "qrbd.f"
	    }
/*<            endif >*/
#line 263 "qrbd.f"
	}
/*<   270      CONTINUE      >*/
#line 264 "qrbd.f"
L270:
#line 264 "qrbd.f"
	;
#line 264 "qrbd.f"
    }
/*         END OF ORDERING ALGORITHM. */

/*<       IF (FAIL) IPASS=2  >*/
#line 267 "qrbd.f"
    if (fail) {
#line 267 "qrbd.f"
	*ipass = 2;
#line 267 "qrbd.f"
    }
/*<       RETURN >*/
#line 268 "qrbd.f"
    return 0;
/*<       END    >*/
} /* qrbd_ */

