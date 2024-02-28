[![Build Status][strntoul-github-action-svg]][strntoul-github-action]
[![Coverage Status][strntoul-codecov-svg]][strntoul-codecov]

[strntoul-github]: https://github.com/gerickson/strntoul
[strntoul-github-action]: https://github.com/gerickson/strntoul/actions?query=workflow%3Abuild+branch%3Amain+event%3Apush
[strntoul-github-action-svg]: https://github.com/gerickson/strntoul/actions/workflows/build.yml/badge.svg?branch=main&event=push
[strntoul-codecov]: https://codecov.io/gh/Gerickson/strntoul
[strntoul-codecov-svg]: https://codecov.io/gh/Gerickson/strntoul/branch/main/graph/badge.svg

strntoul
========

# Introduction

_strntoul_ is a library adding the "missing" `strntol` and `strntoul`
interfaces from the C Standard Library which convert a bounded,
potentially non-null-terminated string to a long or unsigned long
integer, respectively.

These functions are similar to their C99 standard peers, `strtol` and
`strtoul`, except that they will use at most the specified, bounded
number of bytes from the specified string, which need not be
null-terminated if it contains the specified number or more bytes.

These functions can be useful for parsing files or text-based protocol
streams without the need to copy and/or null-terminate such data using
functions such as `strtok` or `strtok_r`.

# Getting Started with strntoul

## Building strntoul

If you are not using a prebuilt distribution of strntoul,
building strntoul should be a straightforward, two- or three-step
process. If you are building from the main branch, start with:

    % ./bootstrap

If you are building from the main branch, a release branch, or a
distribution package, continue (main branch) or start with:

    % ./configure
    % make

The first `bootstrap` step creates the `configure` script and
`Makefile.in` files from `configure.ac` and `Makefile.am` respectively
and only needs to be done once unless those input files have changed.

The second `configure` step generates `Makefile` files from
`Makefile.in` files and only needs to be done once unless those input
files have changed.

Although not strictly necessary, the additional step of sanity
checking the build results is recommended:

    % make check

### Dependencies

In addition to depending on the C Standard Library, strntoul depends
on:

  * [nlunit-test](https://github.com/Nuovations/nlunit-test)

However, nlunit-test is only required when building and running the strntoul
unit test suite.

If you want to modify or otherwise maintain the strntoul build
system, see "Maintaining strntoul" below for more information.

## Installing strntoul

To install strntoul for your use simply invoke:

    % make install

to install strntoul in the location indicated by the --prefix
`configure` option (default "/usr/local"). If you intended an
arbitrarily relocatable strntoul installation and passed
`--prefix=/` to `configure`, then you might use DESTDIR to, for
example install strntoul in your user directory:

    % make DESTIDIR="${HOME}" install

## Maintaining strntoul

If you want to maintain, enhance, extend, or otherwise modify
strntoul, it is likely you will need to change its build system,
based on GNU autotools, in some circumstances.

After any change to the strntoul build system, including any
*Makefile.am* files or the *configure.ac* file, you must run the
`bootstrap` or `bootstrap-configure` (which runs both `bootstrap` and
`configure` in one shot) script to update the build system.

### Dependencies

Due to its leverage of GNU autotools, if you want to modify or
otherwise maintain the strntoul build system, the following
additional packages are required and are invoked by `bootstrap`:

  * autoconf
  * automake
  * libtool

#### Linux

On Debian-based Linux distributions such as Ubuntu, these dependencies
can be satisfied with the following:

    % sudo apt-get install autoconf automake libtool

#### Mac OS X

On Mac OS X, these dependencies can be installed and satisfied using
[Brew](https://brew.sh/):

    % brew install autoconf automake libtool

# Interact

There are numerous avenues for strntoul support:

  * Bugs and feature requests — [submit to the Issue Tracker](https://github.com/gerickson/strntoul/issues)

# Versioning

strntoul follows the [Semantic Versioning guidelines](http://semver.org/)
for release cycle transparency and to maintain backwards compatibility.

# License

strntoul is released under the [Apache License, Version 2.0 license](https://opensource.org/licenses/Apache-2.0).
See the `LICENSE` file for more information.
