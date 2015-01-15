cisstNetlib

# Introduction

cnetlib and cisstNetlib are two binary distributions of numerical routines found on  http://www.netlib.org. They basically provide the same features, the main difference being that cnetlib is based on C code while cisstNetlib can be built using the original Fortran code. cisstNetlib was introduced after cnetlib to solve some thread-safety issues.

Both of them have been created and compiled mainly to be used in combination with the cisst package which can be found at  https://trac.lcsr.jhu.edu/cisst. To use the numerical functions of cisst, one must first download the binaries for cisstNetlib and then configure cisst (using CMake, see the build instructions for cisst) to indicate which version of netlib (if any) you have downloaded. Please note that cnetlib isn't supported nor used by any recent version of the cisst libraries.

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

## The very first implementation: cnetlib

We, at the ERC-CISST, decided to put together a distribution of numerical routines from netlib.org which are used in the cisst package. We named this library cnetlib which can stand either for C netlib or cisst Netlib. This distribution includes:

- BLAS -  http://www.netlib.org/blas
- LAPACK -  http://www.netlib.org/lapack
- Lawson and Hanson routines -  http://www.netlib.org/lawson-hanson
- Hanson and Haskell -  http://www.netlib.org/toms/ Ref: ACM TOMS 8 (1982) 323-333
- Minpack -  http://www.netlib.org/minpack

We started with a source based distribution, i.e the user had to download all the sources and compile him or herself. Since we can't assume that everyone has a Fortran compiler installed on his or her computer we used CLAPACK ( http://www.netlib.org/clapack) which includes an f2c ed version of both BLAS and LAPACK and ran f2c on all the other Fortran routines we needed.

Because the compilation ended-up being fairly long and involved, we decided to provide a binary distribution for a limited number of operating systems (Windows, Linux and Mac OS X).

Since the API of the netlib.org routines is not that trivial, we added some wrappers to the cisst package (in the cisstNumerical library). These wrappers ensures that the different parameters are correct (in size and storage order) and can eventually perform the memory allocations for the results and workspace (aka scratch space).

## cisstNetlib, Lapack3e, Makefile and g95

cnetlib satisified all our requirements until we realized that CLAPACK was not thread safe. We created a test program running 50 threads and in each thread solving an SVD problem. This test program ended up calculating incorrect results and got sometimes stuck in an infinite loop.

To find the guilty party, we started to study the C code generated from LAPACK. We found static variables all over the library, including many introduced by f2c. On top of that, we discovered that the original routines in Fortran are not thread safe either.

We then decided to look for a thread safe version of LAPACK. There were a couple of commercial versions (including one by Intel, free for non commercial applications on Linux) but none was totally free and portable. We also found an updated version of LAPACK for Fortran 90 also available from the netlib repository; LAPACK3E -  http://www.netlib.org/lapack3e. The main issue of this library is that it requires a Fortran 90 compiler since f2c can only convert Fortran 77 code.

We have been using g95 -  http://www.g95.org (Fortran 95 compiler based on gcc-4) with success on Linux, Windows (with cygwin) and Mac OS X to compile not only LAPACK3E but also the MINPACK, Lawson and Hanson, Hanson and Haskell routines in their original Fortran versions. The main difficulty is to maintain a C header file to interface with the Fortran routines included in our new library: cisstNetlib

The API of LAPACK3E differs sligthly from the CLAPACK API, thus we updated cisstNumerical so that is can use either cnetlib or cisstNetlib. As we use CMake ( http://www.cmake.org) to build cisst, we added an option so that the user can choose which numerical package to use.

## cisstNetlib, Lapack and gfortran, still with Makefiles

One of the challenges we ran into was to support Windows 64 bits and mix GNU compiled libraries with the Microsoft compiler binaries for all our Visual Studio users. We started a transition to gfortran as this compiler was gaining popularity. We were also switch back to Lapack from Lapack3e as recent versions of Lapack are now thread safe. We still used Makefiles for the build process. This code in the repository, in cisstNetlib/gfortran-makefiles

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


## cisstNetlib with LAPACK 3.2.1, gfortran and Makefiles (old)

The code for this approach is in the repository, in branches, gfortran.

Starting with LAPACK 3.2, you must use a F90 compiler (g95 or gfortran). Older compilers such as f77 and g77 will not work. Note however that g95 is not available for 64 bits architecture.

To compile cisstNetlib under Windows you should install the MinGW environment. The reason for this is that MinGW does not requires a compatibility layer for WIN32 application. For example, in Cygwin, packages such as "gcc-mingw-*" provide native Windows headers and libraries for GCC. Unfortunately, there is no "mingw-gfortran" package in Cygwin. Until this happens you can't compile LAPACK for native Windows by using Cygwin's gfortran. Similarly "g95 for Cygwin" links against libcygwin.a. 

You can get away by only installing gfortran [http://gcc.gnu.org/wiki/GFortranBinaries] or g95 [http://www.ftp.g95.org/] (both MinGW) but then you would have to install ar, tar, gzip and make for Windows or run the compilers from Cygwin.

If you install the MinGW environment, follow the instructions on how to perform a "manual installation" [http://mingw.org/wiki/Getting_Started]. This consists of downloading and extracting a bunch of tar.gz. On my system I have the following:
  * binutils-2.20-1 (bin)
  * gcc-core-4.4.0 (bin and dll)
  * gcc-c++-4.4.0 (bin and dll) (not needed)
  * gcc-fortran-4.4.0 (bin and dll)
  * gmp-4.2.4 (dll)
  * libiconv-1.13.1 (dll)
  * make-3.81 (bin)
  * mingwrt-3.17 (bin and dev)
  * mpfr-2.4.1 (dll)
  * pthread-2.8.0 (dll)
  * w32api-3.14 (dev)
  * MSYS 1.01

  * If you want g95 you must download the self-extracting package for Windows (this is a MinGW compiler) [http://www.g95.org/downloads.shtml]. Note that there is no 64 bits g95 compiler.

### g95

To compile using g95. Open a shell and type "make FC=g95 OS=Windows". The result will be a cisstNetlib.lib, cisstNetlibgcc.lib and a cisstNetlibgfortran.lib. The cisstNetlibgfortran.lib is a misnomer since it is in fact libf95.a. 

### gfortran

If you use gfortran, you will need type simply "make OS=Windows". Although the build process is not as clean as with g95 since libgfortran.a links against some of MinGW run times modules (these modules are contained in the package mingwrt-3.17). In fact, the Makefile extract modules from libmingex.a library and adds them to cisstNetlibgfortran.lib and one module is added to cisstNetlib.lib. The list of modules is as follow:
  * cisstNetlibgfortran.lib: dmisc.o fpclassify.o fpclassifyf.o gdtoa.o gethex.o gmisc.o hd_init.o hexnan.o hexnan.o logf.o lroundf.o misc.o pformat.o smisc.o snprintf.o strtodg.o strtodnrp.o strtof.o strtopx.o sum.o vsnprintf.o vsprintf.o
  * cisstNetlib.lib: ctrmt.o

Most of the extra modules (the modules related to printf and strings) are for the "enhanced printf support" in MinGW. This is the result of compiling gfortran with that "feature". Recompiling gfortran without that feature should remove most of these dependencies.

### Summary

The options to compile cisstNetlib are:
 1 With cygwin: Install gfortran [http://gcc.gnu.org/wiki/GFortranBinaries] (select the installer for MinGW build).

 1 With MinGW: 
    - Install the MinGW suite [http://www.mingw.org/wiki/Getting_Started] including the gfortran packages (not the one above even though it should work as well). 
    - Install the MinGW suite with or without gfortran and download G95 [http://www.g95.org/downloads.shtml] (use the "Self-extracting Windows x86") and install it in the same place as the MinGW suite (i.e. C:\MinGW).


## cisstNetlib with Lapack3e, g95 and Makefiles (very old)

### The big picture

The ''cisstNetlib'' library is compiled from Fortran code, therefore a Fortran 90 compiler is required.  Please note that `f2c` works only on Fortran 77 code which explains why you can't get by with a C compiler.  The build process is based on Makefiles and also requires `m4` for text/code processing.

The different steps of the build are:
 * Unpack the ''LAPACK3E'' sources from the tar.gz file provided in the directory `unix`.
 * Patch the ''LAPACK3E'' sources.  Right now, this performed by copying files from the directory `unix/LAPACK3E-patches` in the `unix/LAPACK3E` directory.
 * Compile ''LAPACK3E''.
 * Compile the extra routines used in ''cisstNetlib''.
 * Copy some extra libraries required by the Fortran code (i.e. `libF95` and eventually `libgcc`).

These steps can be automatically performed on Linux, Darwin and Windows using `unix/Makefile`:
<pre>
 cd unix
 make install-lapack3e
 make lapack3e
 make cisstNetlib
</pre>

If you are compiling on a different system or you are not happy with the compilation on the supported systems, you will probably need to update the patches. 

### Binary distributions

The ideal solution is to place the source of ''cisstNetlib'' in a shared drive which can be accessed from a Linux computer, a Mac OS X computer and a Windows computer.  Then from each of these computer, go in the `unix` directory and build ''cisstNetlib'' as documented above.

Once this is done, pick one of your computers and go to the base directory of ''cisstNetlib''.  You might want to update the `release-notes.txt` file to reflect your modifications and then try:
<pre>
 make tarfiles
</pre>

If everything goes well, the directory `tar-files` should contain:
<pre>
cisstNetlib-Darwin-2005-11-30.tar.gz
cisstNetlib-Linux-2005-11-30.tar.gz
cisstNetlib-release-notes-2005-11-30.txt
cisstNetlib-src-2005-11-30.tar.gz
cisstNetlib-src-2005-11-30.zip
cisstNetlib-Windows-2005-11-30.zip
</pre>

You can now place these files on the web server.

### LAPACK3E Patches

By default, ''LAPACK3E'' can be compiled on Cray, Sun and IBM.  To support the other operating systems, we modified the main Makefile in `unix/LAPACK3E` and added a couple of files:
 * `LAPACK3E/make.def.$(OS)` - Defines the Fortran 90 compiler and other command names specific to your system configuration.
 * `LAPACK3E/INSTALL/rounding_mode.c.$(OS)` - You might need to change this because the C and Fortran compilers can use different name mangling.
 * `LAPACK3E/BLAS/SRC/Makefile.$(OS)` - By default ''LAPACK3E'' relies on vendor or system ''BLAS'' routines.  Since we want a binary distribution easy to install, we compile and package the ''BLAS'' routines with ''cisstNetlib''

For all these files, `$(OS)` is the result of the `uname` command.

The patches to support Linux, Windows and Darwin can be found in the `LAPACK3E-patches` directory and new patches should be placed there as well.

### Other Fortran code

For the other Fortran code, we are not using a pre-existing Makefile since the code didn't come with one.  The home-brewed `unix/Makefile` has the rules required to compile Lawson and Hanson, Hanson and Haskell, ''MINPACK'', ...  This Makefile uses the `unix/LAPACK3E/make.inc.$(OS)` to define the Fortran compiler as well as the compilation default options.

Some of the code has been modified (namely Hanson and Haskell) to port from Fortran 77 to Fortran 90.  The changes are under CVS.

### Misc. info
The Fortran compiler we use is g95 - http://www.g95.org.  We used the binary version provided on g95's web site for both Linux and Windows (as of November 2005).

On Windows, we also use cygwin which provides a shell, GNU make, m4 as well as tar, etc.

On Darwin (Mac OS X), we use the ''fink'' version of g95.
