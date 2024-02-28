#
#    Copyright 2024 Grant Erickson. All Rights Reserved.
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
#    This file is the GNU automake template for the strntoul library.
#

include $(abs_top_nlbuild_autotools_dir)/automake/pre.am

lib_LTLIBRARIES                                                  = \
    libstrntoul.la                                                 \
    $(NULL)

SUBDIRS                                                          = \
    tests                                                          \
    $(NULL)

noinst_HEADERS                                                   = \
    $(NULL)

# Public library headers to distribute and install.

include_HEADERS                                                  = \
    strntol.h                                                      \
    strntoul.h                                                     \
    $(NULL)

libstrntoul_la_LDFLAGS                                           = \
    -version_info $(LIBSTRNTOUL_VERSION_INFO)                      \
    $(NULL)

libstrntoul_la_CPPFLAGS                                          = \
    -I$(top_srcdir)/src/include                                    \
    $(NULL)

libstrntoul_la_SOURCES                                           = \
    strntol.cpp                                                    \
    strntoul.cpp                                                   \
    $(NULL)

install-headers: install-includeHEADERS

include $(abs_top_nlbuild_autotools_dir)/automake/post.am
