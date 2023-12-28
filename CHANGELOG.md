Change log
==========

3.2.0 (2023-12-29)
==================

* Use CLAPACK from jhu-cisst-external forks https://github.com/jhu-cisst-external/clapack (updated to compile on more recent compiler)
* Updated CMake to use VERSION and CMake variables renamed from `CISSTNETLIB_` to `cisstNetlib_`

3.1.0 (2023-11-21)
==================

* Fixed CMake for Ubuntu 18.04, 20.04
* Updated lapack version to 3.10.1
* Added project in subdirectories
* Force gfortran-9 when compiling on Ubuntu 22.04
* Added colcon support for ROS2
