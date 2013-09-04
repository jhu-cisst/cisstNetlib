C     SUBROUTINE SVDRS (A, MDA, M1, N1, B, MDB, NB, S, WORK) 
C
C  SINGULAR VALUE DECOMPOSITION ALSO TREATING RIGHT SIDE VECTOR.
C
C  The original version of this code was developed by
C  Charles L. Lawson and Richard J. Hanson at Jet Propulsion Laboratory
C  1974 SEP 25, and published in the book
C  "SOLVING LEAST SQUARES PROBLEMS", Prentice-HalL, 1974.
C  Revised FEB 1995 to accompany reprinting of the book by SIAM.
C     ------------------------------------------------------------------   
C  This 1995 version differs from the original 1974 version by adding
C  the argument WORK().
C  WORK() provides 2*N1 locations of work space.  Originally S() was
C  required to have 3*N1 elements, of which the last 2*N1 were used for
C  work space.  Now S() only needs N1 elements.
C     ------------------------------------------------------------------
C  This subroutine computes the singular value decomposition of the
C  given M1 x N1 matrix, A, and optionally applys the transformations
C  from the left to the NB column vectors of the M1 x NB matrix B.
C  Either M1 .ge. N1  or  M1 .lt. N1 is permitted.
C
C       The singular value decomposition of A is of the form
C
C                  A  =  U * S * V**t
C
C  where U is M1 x M1 orthogonal, S is M1 x N1 diagonal with the
C  diagonal terms nonnegative and ordered from large to small, and
C  V is N1 x N1 orthogonal.  Note that these matrices also satisfy
C
C                  S = (U**t) * A * V
C
C       The matrix V is returned in the leading N1 rows and
C  columns of the array A(,).
C
C       The singular values, i.e. the diagonal terms of the matrix S,
C  are returned in the array S().  If M1 .lt. N1, positions M1+1
C  through N1 of S() will be set to zero.
C
C       The product matrix  G = U**t * B replaces the given matrix B
C  in the array B(,).
C
C       If the user wishes to obtain a minimum length least squares
C  solution of the linear system
C
C                        A * X ~=~ B
C
C  the solution X can be constructed, following use of this subroutine,
C  by computing the sum for i = 1, ..., R of the outer products
C
C          (Col i of V) * (1/S(i)) * (Row i of G)
C
C  Here R denotes the pseudorank of A which the user may choose
C  in the range 0 through Min(M1, N1) based on the sizes of the
C  singular values.
C     ------------------------------------------------------------------
C                    Subroutine Arguments
C
C  A(,)     (In/Out)  On input contains the M1 x N1 matrix A.
C           On output contains the N1 x N1 matrix V.
C
C  LDA      (In)  First dimensioning parameter for A(,).
C           Require LDA .ge. Max(M1, N1).
C
C  M1       (In)  No. of rows of matrices A, B, and G.
C           Require M1 > 0.
C
C  N1       (In)  No. of cols of matrix A, No. of rows and cols of
C           matrix V.  Permit M1 .ge. N1  or  M1 .lt. N1.
C           Require N1 > 0.
C
C  B(,)     (In/Out)  If NB .gt. 0 this array must contain an
C           M1 x NB matrix on input and will contain the
C           M1 x NB product matrix, G = (U**t) * B on output.
C
C  LDB      (In)  First dimensioning parameter for B(,).
C           Require LDB .ge. M1.
C
C  NB       (In)  No. of cols in the matrices B and G.
C           Require NB .ge. 0.
C
C  S()      (Out)  Must be dimensioned at least N1.  On return will
C           contain the singular values of A, with the ordering
C                S(1) .ge. S(2) .ge. ... .ge. S(N1) .ge. 0.
C           If M1 .lt. N1 the singular values indexed from M1+1
C           through N1 will be zero.
C           If the given integer arguments are not consistent, this
C           subroutine will return immediately, setting S(1) = -1.0.
C
C  WORK()  (Scratch)  Work space of total size at least 2*N1.
C           Locations 1 thru N1 will hold the off-diagonal terms of
C           the bidiagonal matrix for subroutine QRBD.  Locations N1+1
C           thru 2*N1 will save info from one call to the next of
C           H12.
C     ------------------------------------------------------------------
C  This code gives special treatment to rows and columns that are
C  entirely zero.  This causes certain zero sing. vals. to appear as
C  exact zeros rather than as about MACHEPS times the largest sing. val.
C  It similarly cleans up the associated columns of U and V.  
C
C  METHOD..  
C   1. EXCHANGE COLS OF A TO PACK NONZERO COLS TO THE LEFT.  
C      SET N = NO. OF NONZERO COLS.  
C      USE LOCATIONS A(1,N1),A(1,N1-1),...,A(1,N+1) TO RECORD THE    
C      COL PERMUTATIONS. 
C   2. EXCHANGE ROWS OF A TO PACK NONZERO ROWS TO THE TOP.   
C      QUIT PACKING IF FIND N NONZERO ROWS.  MAKE SAME ROW EXCHANGES 
C      IN B.  SET M SO THAT ALL NONZERO ROWS OF THE PERMUTED A   
C      ARE IN FIRST M ROWS.  IF M .LE. N THEN ALL M ROWS ARE 
C      NONZERO.  IF M .GT. N THEN      THE FIRST N ROWS ARE KNOWN    
C      TO BE NONZERO,AND ROWS N+1 THRU M MAY BE ZERO OR NONZERO.     
C   3. APPLY ORIGINAL ALGORITHM TO THE M BY N PROBLEM.   
C   4. MOVE PERMUTATION RECORD FROM A(,) TO S(I),I=N+1,...,N1.   
C   5. BUILD V UP FROM  N BY N  TO  N1 BY N1  BY PLACING ONES ON     
C      THE DIAGONAL AND ZEROS ELSEWHERE.  THIS IS ONLY PARTLY DONE   
C      EXPLICITLY.  IT IS COMPLETED DURING STEP 6.   
C   6. EXCHANGE ROWS OF V TO COMPENSATE FOR COL EXCHANGES OF STEP 2. 
C   7. PLACE ZEROS IN  S(I),I=N+1,N1  TO REPRESENT ZERO SING VALS.   
C     ------------------------------------------------------------------
      subroutine SVDRS (A, MDA, M1, N1, B, MDB, NB, S, WORK) 
      integer I, IPASS, J, K, L, M, MDA, MDB, M1
      integer N, NB, N1, NP1, NS, NSP1
C     double precision A(MDA,N1),B(MDB,NB), S(N1)
      double precision A(MDA, *),B(MDB, *), S( *)
      double precision ONE, T, WORK(N1,2), ZERO
      parameter(ONE = 1.0d0, ZERO = 0.0d0)
C     -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
C                             BEGIN.. SPECIAL FOR ZERO ROWS AND COLS.   
C   
C                             PACK THE NONZERO COLS TO THE LEFT 
C   
      N=N1  
      IF (N.LE.0.OR.M1.LE.0) RETURN 
      J=N   
   10 CONTINUE  
         DO 20 I=1,M1  
            IF (A(I,J) .ne. ZERO) go to 50
   20    CONTINUE  
C   
C           COL J  IS ZERO. EXCHANGE IT WITH COL N.   
C   
         IF (J .ne. N) then
            DO 30 I=1,M1  
   30       A(I,J)=A(I,N) 
         endif
         A(1,N)=J  
         N=N-1 
   50    CONTINUE  
         J=J-1 
      IF (J.GE.1) GO TO 10  
C                             IF N=0 THEN A IS ENTIRELY ZERO AND SVD    
C                             COMPUTATION CAN BE SKIPPED    
      NS=0  
      IF (N.EQ.0) GO TO 240 
C                             PACK NONZERO ROWS TO THE TOP  
C                             QUIT PACKING IF FIND N NONZERO ROWS   
      I=1   
      M=M1  
   60 IF (I.GT.N.OR.I.GE.M) GO TO 150   
      IF (A(I,I)) 90,70,90  
   70     DO 80 J=1,N   
          IF (A(I,J)) 90,80,90  
   80     CONTINUE  
      GO TO 100 
   90 I=I+1 
      GO TO 60  
C                             ROW I IS ZERO     
C                             EXCHANGE ROWS I AND M 
  100 IF(NB.LE.0) GO TO 115 
          DO 110 J=1,NB 
          T=B(I,J)  
          B(I,J)=B(M,J) 
  110     B(M,J)=T  
  115     DO 120 J=1,N  
  120     A(I,J)=A(M,J) 
      IF (M.GT.N) GO TO 140 
          DO 130 J=1,N  
  130     A(M,J)=ZERO   
  140 CONTINUE  
C                             EXCHANGE IS FINISHED  
      M=M-1 
      GO TO 60  
C   
  150 CONTINUE  
C                             END.. SPECIAL FOR ZERO ROWS AND COLUMNS   
C                             BEGIN.. SVD ALGORITHM 
C     METHOD..  
C     (1)     REDUCE THE MATRIX TO UPPER BIDIAGONAL FORM WITH   
C     HOUSEHOLDER TRANSFORMATIONS.  
C          H(N)...H(1)AQ(1)...Q(N-2) = (D**T,0)**T  
C     WHERE D IS UPPER BIDIAGONAL.  
C   
C     (2)     APPLY H(N)...H(1) TO B.  HERE H(N)...H(1)*B REPLACES B    
C     IN STORAGE.   
C   
C     (3)     THE MATRIX PRODUCT W= Q(1)...Q(N-2) OVERWRITES THE FIRST  
C     N ROWS OF A IN STORAGE.   
C   
C     (4)     AN SVD FOR D IS COMPUTED.  HERE K ROTATIONS RI AND PI ARE 
C     COMPUTED SO THAT  
C          RK...R1*D*P1**(T)...PK**(T) = DIAG(S1,...,SM)    
C     TO WORKING ACCURACY.  THE SI ARE NONNEGATIVE AND NONINCREASING.   
C     HERE RK...R1*B OVERWRITES B IN STORAGE WHILE  
C     A*P1**(T)...PK**(T)  OVERWRITES A IN STORAGE. 
C   
C     (5)     IT FOLLOWS THAT,WITH THE PROPER DEFINITIONS,  
C     U**(T)*B OVERWRITES B, WHILE V OVERWRITES THE FIRST N ROW AND     
C     COLUMNS OF A.     
C   
      L=min(M,N)   
C             THE FOLLOWING LOOP REDUCES A TO UPPER BIDIAGONAL AND  
C             ALSO APPLIES THE PREMULTIPLYING TRANSFORMATIONS TO B.     
C   
          DO 170 J=1,L  
          IF (J.GE.M) GO TO 160     
          CALL H12 (1,J,J+1,M,A(1,J),1,T,A(1,J+1),1,MDA,N-J)
          CALL H12 (2,J,J+1,M,A(1,J),1,T,B,1,MDB,NB)
  160     IF (J.GE.N-1) GO TO 170   
          CALL H12 (1,J+1,J+2,N,A(J,1),MDA,work(J,2),A(J+1,1),MDA,1,M-J)   
  170     CONTINUE  
C   
C     COPY THE BIDIAGONAL MATRIX INTO S() and WORK() FOR QRBD.   
C 1986 Jan 8. C. L. Lawson. Changed N to L in following 2 statements.
      IF (L.EQ.1) GO TO 190 
          DO 180 J=2,L  
          S(J)=A(J,J) 
  180     WORK(J,1)=A(J-1,J)   
  190 S(1)=A(1,1)     
C   
      NS=N  
      IF (M.GE.N) GO TO 200 
      NS=M+1
      S(NS)=ZERO  
      WORK(NS,1)=A(M,M+1)  
  200 CONTINUE  
C   
C     CONSTRUCT THE EXPLICIT N BY N PRODUCT MATRIX, W=Q1*Q2*...*QL*I    
C     IN THE ARRAY A(). 
C   
          DO 230 K=1,N  
          I=N+1-K   
          IF (I .GT. min(M,N-2)) GO TO 210     
          CALL H12 (2,I+1,I+2,N,A(I,1),MDA,WORK(I,2),A(1,I+1),1,MDA,N-I)   
  210         DO 220 J=1,N  
  220         A(I,J)=ZERO   
  230     A(I,I)=ONE    
C   
C          COMPUTE THE SVD OF THE BIDIAGONAL MATRIX 
C   
      CALL QRBD (IPASS,S(1),WORK(1,1),NS,A,MDA,N,B,MDB,NB)   
C   
      if(IPASS .eq. 2) then
         write (*,'(/a)')
     *      ' FULL ACCURACY NOT ATTAINED IN BIDIAGONAL SVD'
      endif

  240 CONTINUE  
      IF (NS.GE.N) GO TO 260
      NSP1=NS+1 
          DO 250 J=NSP1,N   
  250     S(J)=ZERO   
  260 CONTINUE  
      IF (N.EQ.N1) RETURN   
      NP1=N+1   
C                                  MOVE RECORD OF PERMUTATIONS  
C                                  AND STORE ZEROS  
          DO 280 J=NP1,N1   
          S(J)=A(1,J) 
              DO 270 I=1,N  
  270         A(I,J)=ZERO   
  280     CONTINUE  
C                             PERMUTE ROWS AND SET ZERO SINGULAR VALUES.
          DO 300 K=NP1,N1   
          I=S(K)  
          S(K)=ZERO   
              DO 290 J=1,N1 
              A(K,J)=A(I,J) 
  290         A(I,J)=ZERO   
          A(I,K)=ONE    
  300     CONTINUE  
C                             END.. SPECIAL FOR ZERO ROWS AND COLUMNS   
      RETURN
      END   
