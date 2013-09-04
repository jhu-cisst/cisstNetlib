       double precision FUNCTION DIFF(X,Y)
C
C  Function used in tests that depend on machine precision.
C
C  The original version of this code was developed by
C  Charles L. Lawson and Richard J. Hanson at Jet Propulsion Laboratory
C  1973 JUN 7, and published in the book
C  "SOLVING LEAST SQUARES PROBLEMS", Prentice-HalL, 1974.
C  Revised FEB 1995 to accompany reprinting of the book by SIAM.
C
      double precision X, Y
      DIFF=X-Y  
      RETURN
      END   
