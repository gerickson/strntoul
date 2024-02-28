#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#
#    Copyright (c) 2024 Grant Erickson
#    Copyright (c) 2016-2018 Nest Labs Inc. All Rights Reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

#
#    Description:
#      This file is the GNU autoconf input source file for strntoul.
#

#
# Declare autoconf version requirements
#
AC_PREREQ([2.69])

#
# Initialize autoconf for the package
#
AC_INIT([strntoul],
        m4_esyscmd([third_party/nlbuild-autotools/repo/scripts/mkversion -b `cat .default-version` .]),
        [],
        [strntoul],
        [https://github.com/gerickson/strntoul/])

# Tell the rest of the build system the absolute path where the
# nlbuild-autotools repository is rooted at.

AC_SUBST(nlbuild_autotools_stem,[third_party/nlbuild-autotools/repo])
AC_SUBST(abs_top_nlbuild_autotools_dir,[\${abs_top_srcdir}/\${nlbuild_autotools_stem}])

#
# STRTOUL interface current, revision, and age versions.
#
# Maintainters: Please manage these fields as follows:
#
#   Interfaces removed:    CURRENT++, REVISION = 0, AGE = 0
#   Interfaces added:      CURRENT++, REVISION = 0, AGE++
#   Source changed:                   REVISION++
#
# Expressed more verbosely:
#
#   1. Start with version information of `0:0:0' for each libtool library.
#
#   2. Update the version information only immediately before a public
#      release of your software. More frequent updates are unnecessary,
#      and only guarantee that the current interface number gets larger
#      faster.
#
#   3. If the library source code has changed AT ALL since the last
#      update, then increment revision (`C:R:A' becomes `C:R+1:A').
#
#   4. If ANY interfaces have been added, removed, or changed since the
#      last update, increment current, and set revision to 0.
#
#   5. If ANY interfaces have been added since the last public release,
#      then increment age.
#
#   6. If ANY interfaces have been removed since the last public
#      release, then set age to 0.
#
AC_SUBST(LIBSTRNTOUL_VERSION_CURRENT,  [0])
AC_SUBST(LIBSTRNTOUL_VERSION_AGE,      [0])
AC_SUBST(LIBSTRNTOUL_VERSION_REVISION, [0])
AC_SUBST(LIBSTRNTOUL_VERSION_INFO,     [${LIBSTRNTOUL_VERSION_CURRENT}:${LIBSTRNTOUL_VERSION_REVISION}:${LIBSTRNTOUL_VERSION_AGE}])

#
# Check the sanity of the source directory by checking for the
# presence of a key watch file
#
AC_CONFIG_SRCDIR([src/strntoul.h])

#
# Tell autoconf where to find auxilliary build tools (e.g. config.guess,
# install-sh, missing, etc.)
#
AC_CONFIG_AUX_DIR([third_party/nlbuild-autotools/repo/third_party/autoconf])

#
# Tell autoconf where to find auxilliary M4 macros
#
# Note that nlbuild-autotools has macros in two subdirs, for local vs
# third-party scripts
#
AC_CONFIG_MACRO_DIRS([third_party/nlbuild-autotools/repo/third_party/autoconf/m4 third_party/nlbuild-autotools/repo/autoconf/m4])

#
# Tell autoconf what file the package is using to aggregate C preprocessor
# defines.
#
AC_CONFIG_HEADERS([src/strntoul-config.h])

#
# Figure out what the canonical build, host and target tuples are.
#
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

#
# Mac OS X / Darwin ends up putting some versioning cruft on the end of its
# tuple that we don't care about in this script. Create "clean" variables
# devoid of it.
#

NL_FILTERED_CANONICAL_BUILD
NL_FILTERED_CANONICAL_HOST
NL_FILTERED_CANONICAL_TARGET

#
# Configure automake with the desired options, indicating that this is not
# a native GNU package, that we want "silent" build rules, that we want
# objects built in the same subdirectory as their source rather than collapsed
# together at the top-level directory, that we want support for the
# PAX format for 'make dist', that we do not want emission of
# 'PACKAGE' and 'VERSION' since AC_INIT already emits 'PACKAGE_NAME'
# and 'PACKAGE_VERSION', that we do not want gzip-compressed distributions, and
# that we do want xz-compressed distributions.
#
# Disable silent build rules by either passing --disable-silent-rules to
# configure or passing V=1 to make
#
AM_INIT_AUTOMAKE([1.16.1 foreign silent-rules subdir-objects tar-pax no-define no-dist-gzip dist-xz])

#
# Silent build rules requires at least automake-1.11. Employ
# techniques for not breaking earlier versions of automake.
#
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AM_SILENT_RULES([yes])

#
# Disable maintainer mode to enable the package to automatically rebuild
# configure, Makefile.in, etc. when the files on which they depend change (for
# example, configure.ac, Makefile.am, etc).
#
# For those that do not desire this behavior, run configure with
# `--enable-maintainer-mode` and run the top-level `bootstrap` script manually.
#
AM_MAINTAINER_MODE([disable])

#
# Checks for build host programs
#

# If we are cross-compiling and we are on an embedded target that
# doesn't support independent, standalone executables, then all
# compiler tests that attempt to create an executable will fail. In
# such circumstances, set AC_NO_EXECUTABLES (see http://sourceware.org/
# ml/newlib/2006/msg00353.html).

AC_MSG_CHECKING([whether to disable executable checking])
if test "$cross_compiling" = yes; then
    AC_NO_EXECUTABLES
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no])
fi

# Passing -Werror to GCC-based or -compatible compilers breaks some
# autoconf tests (see
# http://lists.gnu.org/archive/html/autoconf-patches/2008-09/msg00014.html).
#
# If -Werror has been passed transform it into -Wno-error. We'll
# transform it back later with NL_RESTORE_WERROR.

NL_SAVE_WERROR

# Check for compilers.
#
# These should be checked BEFORE we check for and, implicitly,
# initialize libtool such that libtool knows what languages it has to
# work with.

AC_PROG_CPP
AC_PROG_CPP_WERROR

AC_PROG_CC
AC_PROG_CC_C_O

AC_PROG_CXXCPP

AC_PROG_CXX
AC_PROG_CXX_C_O

# Check for other compiler toolchain tools.

AC_CHECK_TOOL(AR, ar)
AC_CHECK_TOOL(RANLIB, ranlib)
AC_CHECK_TOOL(OBJCOPY, objcopy)
AC_CHECK_TOOL(STRIP, strip)

# Check for other host tools.

AC_PROG_INSTALL
AC_PROG_LN_S

AC_PATH_PROG(CLANG_FORMAT, clang-format)
AC_PATH_PROG(CMP, cmp)
AC_PATH_PROG(PERL, perl)

#
# Checks for specific compiler characteristics
#

#
# Common compiler flags we would like to have.
#
#   -Wall                        CC, CXX
#   -Wconversion                 CC, CXX
#   -Wextra                      CC, CXX
#   -Wheader-hygiene             CC, CXX
#   -Wshadow                     CC, CXX
#   -Wunused                     CC, CXX
#

PROSPECTIVE_CFLAGS="-Wall -Wconversion -Wextra -Wheader-hygiene -Wshadow -Wunused"
PROSPECTIVE_CXXFLAGS=""

# Check whether the C++ compiler supports C++14. If it is supported,
# enable it. Otherwise, proceed without error or warning.

AX_CXX_COMPILE_STDCXX_14([], [optional])

AX_CHECK_COMPILER_OPTIONS([C],   ${PROSPECTIVE_CFLAGS})
AX_CHECK_COMPILER_OPTIONS([C++], ${PROSPECTIVE_CFLAGS} ${PROSPECTIVE_CXXFLAGS})

# Check for and initialize libtool

LT_INIT

#
# Debug instances
#
AC_MSG_NOTICE([checking whether to build debug instances])

# Debug

NL_ENABLE_DEBUG([no])

AM_CONDITIONAL([STRNTOUL_BUILD_DEBUG], [test "${nl_cv_build_debug}" = "yes"])

#
# Code coverage and compiler optimization
#

# Coverage

NL_ENABLE_COVERAGE([no])

AM_CONDITIONAL([STRNTOUL_BUILD_COVERAGE], [test "${nl_cv_build_coverage}" = "yes"])

NL_ENABLE_COVERAGE_REPORTS([auto])

AM_CONDITIONAL([STRNTOUL_BUILD_COVERAGE_REPORTS], [test "${nl_cv_build_coverage_reports}" = "yes"])

# Optimization

NL_ENABLE_OPTIMIZATION([yes])

AM_CONDITIONAL([STRNTOUL_BUILD_OPTIMIZED], [test "${nl_cv_build_optimized}" = "yes"])

#
# Treat Compiler Warnings as Errors
#
NL_ENABLE_WERROR([no])

#
# Tests
#
AC_MSG_NOTICE([checking whether to build tests])

# Tests

NL_ENABLE_TESTS([yes])

AM_CONDITIONAL([STRNTOUL_BUILD_TESTS], [test "${nl_cv_build_tests}" = "yes"])

#
# Documentation
#

# Determine whether or not documentation (via Doxygen) should be built
# or not, with 'auto' as the default and establish a default support
# value for GraphViz 'dot' support.

NL_ENABLE_DOCS([auto],[NO])

AM_CONDITIONAL(STRNTOUL_BUILD_DOCS, [test "${nl_cv_build_docs}" = "yes"])

#
# Checks for libraries and packages.
#
# The following packages are optional, depending on configuration:
#
#   * nlunit-test
#
AC_MSG_NOTICE([checking required package dependencies])

# Check if the build host has pkg-config

AC_PATH_PROG([PKG_CONFIG],[pkg-config])

#
# Nlunit-test
#

if test "${nl_cv_build_tests}" = "yes"; then
    NL_WITH_PACKAGE(
        [Nlunit-test],
        [NLUNIT_TEST],
        [nlunit_test],
        [-lnlunit-test],
        [
	    # At this point, the internal Nlunit-test package will be neither
	    # configured nor built, so the normal checks we undertake for an
	    # external package cannot be run here. Simply set the appropriate
	    # variables and trust all will be well.

            NLUNIT_TEST_CPPFLAGS="-I\${abs_top_srcdir}/third_party/nlunit-test/repo/src"
            NLUNIT_TEST_LDFLAGS="-L${ac_pwd}/third_party/nlunit-test/repo/src"
            NLUNIT_TEST_LIBS="-lnlunit-test"
        ],
        [
            # Check for required nlunit-test headers.

            AC_CHECK_HEADERS([nlunit-test.h],
            [],
            [
                AC_MSG_ERROR(The nlunit-test header "$ac_header" is required but cannot be found.)
            ])
        ])
fi

# Depending on whether nlunit-test has been configured for an internal
# location, its directory stem within this package needs to be set
# accordingly. In addition, if the location is internal, then we need
# to attempt to pull it down using the bootstrap makefile.

if test "${nl_with_nlunit_test}" = "internal"; then
    maybe_nlunit_test_dirstem="nlunit-test/repo"
    nlunit_test_dirstem="third_party/${maybe_nlunit_test_dirstem}"

    AC_MSG_NOTICE([attempting to create internal ${nlunit_test_dirstem}])

    ${MAKE-make} --no-print-directory -C ${srcdir} -f Makefile-bootstrap ${nlunit_test_dirstem}

    if test $? -ne 0; then
        AC_MSG_ERROR([failed to create ${nlunit_test_dirstem}. Please check your network connection or the correctness of 'repos.conf'])
    fi
else
    maybe_nlunit_test_dirstem=""
fi

AC_SUBST(NLUNIT_TEST_SUBDIRS, [${maybe_nlunit_test_dirstem}])
AM_CONDITIONAL([STRNTOUL_WITH_NLUNIT_TEST_INTERNAL], [test "${nl_with_nlunit_test}" = "internal"])

#
# Check for headers
#
AC_HEADER_STDBOOL
AC_HEADER_STDC

AC_CHECK_HEADERS([stdint.h])
AC_CHECK_HEADERS([string.h])

#
# Check for types and structures
#
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

#
# Checks for library functions
#

if test "${ac_no_link}" != "yes"; then
    AC_CHECK_FUNCS([memcpy])
fi

# Here is an example with nlunit-test. Uncomment and adapt or delete
# this, as needed.

# # Add any nlunit-test CPPFLAGS, LDFLAGS, and LIBS
#
# CPPFLAGS="${CPPFLAGS} ${NLUNIT_TEST_CPPFLAGS}"
# LDFLAGS="${LDFLAGS} ${NLUNIT_TEST_LDFLAGS}"
# LIBS="${LIBS} ${NLUNIT_TEST_LIBS}"

# Add any code coverage CPPFLAGS, LDFLAGS, and LIBS

CPPFLAGS="${CPPFLAGS} ${NL_COVERAGE_CPPFLAGS}"
LDFLAGS="${LDFLAGS} ${NL_COVERAGE_LDFLAGS}"
LIBS="${LIBS} ${NL_COVERAGE_LIBS}"

# Fold in the warning-as-errors flag, unless it was already in effect.

if test "${nl_had_CPPFLAGS_werror}" = "no"; then
    CPPFLAGS="${CPPFLAGS} ${NL_WERROR_CPPFLAGS}"
fi

# At this point, we can restore the compiler flags to whatever the
# user passed in, now that we're clear of any -Werror issues by
# transforming -Wno-error back to -Werror.

NL_RESTORE_WERROR

# Configure any autotools-based subdirectories

if test "${nl_with_nlunit_test}" = "internal"; then
    AC_CONFIG_SUBDIRS([third_party/nlunit-test/repo])
    AC_SUBST(NLUNIT_TEST_FOREIGN_SUBDIR_DEPENDENCY,["${ac_pwd}/third_party/nlunit-test/repo/src"])
fi

#
# Identify the various makefiles and auto-generated files for the package
#
AC_CONFIG_FILES([
Makefile
third_party/Makefile
src/Makefile
src/tests/Makefile
])

#
# Generate the auto-generated files for the package
#
AC_OUTPUT

#
# Summarize the package configuration
#

AC_MSG_NOTICE([

  Configuration Summary
  ---------------------
  Package                                     : ${PACKAGE_NAME}
  Version                                     : ${PACKAGE_VERSION}
  Interface                                   : ${LIBSTRNTOUL_VERSION_INFO//:/.}
  Build system                                : ${build}
  Host system                                 : ${host}
  Target system                               : ${target}
  Target architecture                         : ${target_cpu}
  Target OS                                   : ${target_os}
  Filtered target system                      : ${nl_filtered_target}
  Filtered target architecture                : ${nl_filtered_target_cpu}
  Filtered target OS                          : ${nl_filtered_target_os}
  Prefix                                      : ${prefix}
  Include Directory                           : ${includedir}
  Cross compiling                             : ${cross_compiling}
  Build shared libraries                      : ${enable_shared}
  Build static libraries                      : ${enable_static}
  Build debug libraries                       : ${nl_cv_build_debug}
  Build optimized libraries                   : ${nl_cv_build_optimized}
  Build coverage libraries                    : ${nl_cv_build_coverage}
  Build coverage reports                      : ${nl_cv_build_coverage_reports}
  Lcov                                        : ${LCOV:--}
  Genhtml                                     : ${GENHTML:--}
  Build tests                                 : ${nl_cv_build_tests}
  Prefix                                      : ${prefix}
  Shadow directory program                    : ${LNDIR}
  Documentation support                       : ${nl_cv_build_docs}
  Doxygen                                     : ${DOXYGEN:--}
  GraphViz dot                                : ${DOT:--}
  PERL                                        : ${PERL:--}
  Nlunit-test source                          : ${nl_with_nlunit_test:--}
  Nlunit-test compile flags                   : ${NLUNIT_TEST_CPPFLAGS:--}
  Nlunit-test link flags                      : ${NLUNIT_TEST_LDFLAGS:--}
  Nlunit-test link libraries                  : ${NLUNIT_TEST_LIBS:--}
  Nlunit-test foreign subdirectory dependency : ${NLUNIT_TEST_FOREIGN_SUBDIR_DEPENDENCY:--}
  C Preprocessor                              : ${CPP}
  C Compiler                                  : ${CC}
  C++ Preprocessor                            : ${CXXCPP}
  C++ Compiler                                : ${CXX}
  Archiver                                    : ${AR}
  Archive Indexer                             : ${RANLIB}
  Symbol Stripper                             : ${STRIP}
  Object Copier                               : ${OBJCOPY}
  C Preprocessor flags                        : ${CPPFLAGS:--}
  C Compile flags                             : ${CFLAGS:--}
  C++ Compile flags                           : ${CXXFLAGS:--}
  Link flags                                  : ${LDFLAGS:--}
  Link libraries                              : ${LIBS}

])
