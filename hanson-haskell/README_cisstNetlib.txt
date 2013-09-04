Directories "fortran" and "fortran-tests" contain the original code.

Directories "fortran-f2c" and "fortran-tests-f2c" contain C code
generated using f2c (version 20100827) with options -a -c -g -P.
Generated files are .c and .P (for prototypes, i.e. header files).

CMakeLists.txt is created by hand to generate
cisstNetlib_hanson_haskell from f2c'd code.  Prototypes should only be
used by cisstNetlib-wrappers.


