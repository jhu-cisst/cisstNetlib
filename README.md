## cisstNetlib

# Introduction

cnetlib and cisstNetlib are two binary distributions of numerical routines found on  http://www.netlib.org. They basically provide the same features, the main difference being that cnetlib is based on C code while cisstNetlib can be built using the original Fortran code. cisstNetlib was introduced after cnetlib to solve some thread-safety issues.

Both of them have been created and compiled mainly to be used in combination with the cisst package which can be found at  https://github.com/jhu-cisst/cisst. To use the numerical functions of cisst, one must first download the binaries for cisstNetlib and then configure cisst (using CMake, see the build instructions for cisst) to indicate which version of netlib (if any) you have downloaded. Please note that cnetlib isn't supported nor used by any recent version of the cisst libraries.

We don't have any documentation nor support for our netlib distributions by themselves since they are intended to be used by the cisst package.

# Download

In CMake for cisst, you will have to indicate that you are using cisstNetlib by setting CISST_HAS_CISSTNETLIB. We recently added an option to download cisstNetlib from the CMake configuration for cisst, i.e. you have to set CISSTNETLIB_DOWNLOAD_NOW and you might have to pick which architecture you need, i.e. 32 or 64 bits. This solution is strongly recommended so you shouldn't download cisstNetlib manually.

# Disclaimer

<pre>
  Copyright 2005 Johns Hopkins University (JHU) All Rights Reserved.
  
  IN NO EVENT SHALL THE COPYRIGHT HOLDERS AND CONTRIBUTORS BE LIABLE TO
  ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
  DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
  EVEN IF THE COPYRIGHT HOLDERS AND CONTRIBUTORS HAVE BEEN ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.
  
  THE COPYRIGHT HOLDERS AND CONTRIBUTORS SPECIFICALLY DISCLAIM ANY
  EXPRESS OR IMPLIED WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
  PURPOSE, AND NON-INFRINGEMENT.
  
  THE SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
  IS." THE COPYRIGHT HOLDERS AND CONTRIBUTORS HAVE NO OBLIGATION TO
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
</pre>

# History

Programmers at the Engineering Research Center for Computer-Integrated Surgical Systems and Technology (ERC CISST) have been using different numerical libraries for years, including in-house routines. Most of our development relies on C/C++ code therefore we always looked for good C/C++ based numerical libraries.

Amongst them, we considered gsl (the GNU Scientific Library -  http://www.gnu.org/software/gsl), VNL (part of VXL -  http://vxl.sourceforge.net and also used by ITK -  http://www.itk.org) and a couple others.   This review was conducted in 2006.

gsl was based on code originally written in C and the storage order for matrices was row first (standard in C/C++). On the other side, VNL basically relied on code originally written in Fortran, i.e. BLAS and LAPACK. To use these Fortran routines, the original code had to be converted to C (using the program f2c) and the matrices had to be converted from row major to column major since the standard storage order in Fortran is column major.

With this issue in mind, we developped a vector and matrix library which can handle either storage order so that we could interface directly with a Fortran based numerical library such as LAPACK. This library (cisstVector) can be downloaded from  https://trac.lcsr.jhu.edu/cisst as part of the cisst package. One advantage of cisstVector over VNL was that it was possible to avoid all the copies required to pass back and forth between the different storage orders. Another one was thread safety (in cisstNetlib)

At that point our requirements were:

- A list of functionalities including SVD, LU, NNLS, ...
- A reliable library, well tested and stable.
- A somewhat efficient library (i.e. avoiding copies to transfer back and forth between different storage orders).
- No specific storage order

## Netlib, LAPACK and co.
From the netlib FAQ on  http://www.netlib.org, "The Netlib repository contains freely available software, documents, and databases of interest to the numerical, scientific computing, and other communities. The repository is maintained by AT&T Bell Laboratories, the University of Tennessee and Oak Ridge National Laboratory, and by colleagues world-wide."

Most of the routines available from the netlib repository are written in Fortran and distributed as source only. These routines come with numerous tests and have been widely used.

- BLAS -  http://www.netlib.org/blas
- LAPACK -  http://www.netlib.org/lapack
- Lawson and Hanson routines -  http://www.netlib.org/lawson-hanson
- Hanson and Haskell -  http://www.netlib.org/toms/ Ref: ACM TOMS 8 (1982) 323-333
- Minpack -  http://www.netlib.org/minpack

## cisstNetlib, Lapack, C or Fortran, CMake

Unfortunately, we still struggled to provide a binary distribution that worked flawlessly with binaries generated by the Microsoft compilers on Windows 64 bits OSs. While re-investigating our options, we found out that:

- Lapack now came with CMake configuration files
- A C version of Lapack was available on netlib.org, also with CMake configuration files. Icing on the cake, the C version is thread-safe.

We therefore decided to build cisstNetlib using CMake and provide an option during configuration to pick either C or Fortran. We strongly recommend using Fortran when a Fortran compiler is available and C otherwise (i.e. on Windows). The build process relies on CMake external projects to download and build Lapack. Also in CMake, we compile all the other numerical routines in cisstNetlib and create a package (.tgz, .zip) that includes all the required binaries, header files and a cisstNetlibConfig.cmake.


# Compilation

If you are using ''cisstNetlib'' as is on Linux, Darwin or Windows, you are not concerned by this document and you should download one of the pre-compiled versions available.

If you need to compile your own version of ''cisstNetlib'', you might want to read these notes.

## cisstNetlib with Lapack, fortran or C and CMake (current)

The code for this approach is in the repository, branches, CMake-C.

To build this code, you must first decide if you want to compile using the C version or Fortran version.  Please note that both come with a C wrapper so they are both designed to be called from C libraries (such as the ''cisst'' libraries).  We strongly recommend to use the Fortran version if you have a Fortran compiler available (on Linux this is trivial, on Mac OS packaging systems such as macports make it pretty easy).

When configuring using CMake, you will have choose with if you want to build using C or Fortran.  Make sure you select your build type, i.e. "Debug", "Release", ...
During the build process, Lapack C or Fortran will be downloaded, configured and build.  The BLAS/Lapack build relies on the CMake configuration files from netlib.org, we have no control on this step.  Once BLAS and Lapack are built, we compiled the few extra routines required for cisstNetlib.

To generate the binary distribution, use `make package`.
