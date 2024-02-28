#
#    Copyright (c) 2021-2024 Grant Erickson. All Rights Reserved.
#    Copyright 2016 Nest Labs Inc. All Rights Reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

##
#  @file
#      This file is the GNU automake template for the strntoul unit tests.
#

include $(abs_top_nlbuild_autotools_dir)/automake/pre.am

#
# Local headers to build against and distribute but not to install
# since they are not part of the package.
#
noinst_HEADERS                                   = \
    $(NULL)

#
# Other files we do want to distribute with the package.
#
EXTRA_DIST                                       = \
    $(NULL)

if STRNTOUL_BUILD_TESTS
# C preprocessor option flags that will apply to all compiled objects in this
# makefile.

AM_CPPFLAGS                                      = \
    -I$(top_srcdir)/src                            \
    $(NLUNIT_TEST_CPPFLAGS)                        \
    $(NULL)

AM_LDFLAGS                                       = \
    $(NLUNIT_TEST_LDFLAGS)                         \
    $(NULL)

LIBS                                            += \
    $(NLUNIT_TEST_LIBS)                            \
    $(NULL)

COMMON_LDADD                                     = \
    $(top_builddir)/src/libstrntoul.la             \
    $(NULL)

NLFOREIGN_FILE_DEPENDENCIES                      = \
    $(top_builddir)/src/libstrntoul.la             \
    $(NULL)

# Test applications that should be run when the 'check' target is run.

check_PROGRAMS                                   = \
    Test_strntol                                   \
    Test_strntoul                                  \
    $(NULL)

# Test applications and scripts that should be built and run when the
# 'check' target is run.

TESTS                                            = \
    $(check_PROGRAMS)                              \
    $(NULL)

# The additional environment variables and their values that will be
# made available to all programs and scripts in TESTS.

TESTS_ENVIRONMENT                                = \
    $(NULL)

# Source, compiler, and linker options for test programs.

Test_strntol_SOURCES                             = Test_strntol.cpp
Test_strntol_LDADD                               = $(COMMON_LDADD)

Test_strntoul_SOURCES                            = Test_strntoul.cpp
Test_strntoul_LDADD                              = $(COMMON_LDADD)

#
# Foreign make dependencies
#

NLFOREIGN_SUBDIR_DEPENDENCIES                    = \
   $(NLUNIT_TEST_FOREIGN_SUBDIR_DEPENDENCY)        \
   $(NULL)

if STRNTOUL_BUILD_COVERAGE
CLEANFILES                                       = $(wildcard *.gcda *.gcno)

if STRNTOUL_BUILD_COVERAGE_REPORTS
# The bundle should positively be qualified with the absolute build
# path. Otherwise, VPATH will get auto-prefixed to it if there is
# already such a directory in the non-colocated source tree.

STRNTOUL_COVERAGE_BUNDLE                          = ${abs_builddir}/${PACKAGE}${NL_COVERAGE_BUNDLE_SUFFIX}
STRNTOUL_COVERAGE_INFO                            = ${STRNTOUL_COVERAGE_BUNDLE}/${PACKAGE}${NL_COVERAGE_INFO_SUFFIX}

$(STRNTOUL_COVERAGE_BUNDLE):
	$(call create-directory)

# Generate the coverage report, filtering out platform and system
# directories and this test directory.

INCLUDE_PATHS                                   := $(subst -I,,$(sort $(NLUNIT_TEST_CPPFLAGS)))
INCLUDE_PATTERNS                                := $(if $(INCLUDE_PATHS),$(addsuffix *,$(INCLUDE_PATHS)),)

$(STRNTOUL_COVERAGE_INFO): check | $(STRNTOUL_COVERAGE_BUNDLE)
	$(call generate-coverage-report,${top_builddir}/src,${top_builddir}/src/tests ${INCLUDE_PATTERNS})

coverage: $(STRNTOUL_COVERAGE_INFO)

clean-local: clean-local-coverage

.PHONY: clean-local-coverage
clean-local-coverage:
	-$(AM_V_at)rm -rf $(STRNTOUL_COVERAGE_BUNDLE)
endif # STRNTOUL_BUILD_COVERAGE_REPORTS
endif # STRNTOUL_BUILD_COVERAGE
endif # STRNTOUL_BUILD_TESTS

include $(abs_top_nlbuild_autotools_dir)/automake/post.am
