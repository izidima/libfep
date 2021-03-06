# Copyright (C) 2012 Daiki Ueno <ueno@unixuser.org>
# Copyright (C) 2012 Red Hat, Inc.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

AC_PREREQ(2.63)

AC_INIT([libfep],
	m4_esyscmd([build-aux/git-version-gen --prefix '' .tarball-version]),
	[ueno@unixuser.org])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

FEP_API_VERSION=1.0
FEP_API_MAJOR_VERSION=1
FEP_API_MINOR_VERSION=0
FEP_API_PC_VERSION=1.0
FEP_LIBRARY_SUFFIX="-$FEP_API_VERSION"

AC_SUBST([FEP_API_VERSION])
AC_SUBST([FEP_API_MAJOR_VERSION])
AC_SUBST([FEP_API_MINOR_VERSION])
AC_SUBST([FEP_API_PC_VERSION])
AC_SUBST([FEP_LIBRARY_SUFFIX])
AC_SUBST([FEP_LIBRARY_SUFFIX_U],[AS_TR_SH([$FEP_LIBRARY_SUFFIX])])

dnl Init automake
AM_INIT_AUTOMAKE([color-tests])
AM_MAINTAINER_MODE([enable])
AC_GNU_SOURCE
AM_SILENT_RULES([no])

dnl Check for programs
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CC_STDC
AC_PROG_INSTALL
AC_C_BIGENDIAN

dnl gnulib
gl_EARLY
gl_INIT

# define PACKAGE_VERSION_* variables
AM_DISABLE_STATIC
AC_ISC_POSIX
AC_HEADER_STDC
LT_INIT

# If library source has changed since last release, increment revision
# If public symbols have been added, removed or changed since last release,
#  increment current and set revision to 0
# If public symbols have been added since last release, increment age
# If public symbols have been removed since last release, set age to 0
m4_define([libfep_lt_current], [0])
m4_define([libfep_lt_revision], [0])
m4_define([libfep_lt_age], [0])
LT_CURRENT=libfep_lt_current
LT_REVISION=libfep_lt_revision
LT_AGE=libfep_lt_age
AC_SUBST([LT_CURRENT])
AC_SUBST([LT_REVISION])
AC_SUBST([LT_AGE])

# check for ncurses
PKG_CHECK_MODULES([NCURSES], [ncurses], ,
  [AC_MSG_ERROR([can't find ncurses])])

# check for gobject
AC_ARG_ENABLE([glib],
	AS_HELP_STRING([--enable-glib], [Enable glib binding]),
	[enable_glib=$enableval], [enable_glib=auto])
if test "x$enable_glib" != "xno"; then
   AM_PATH_GLIB_2_0
   PKG_CHECK_MODULES([GIO], [gio-2.0], enable_glib=yes, enable_glib=no)
fi
AM_CONDITIONAL([ENABLE_GLIB], [test "x$enable_glib" = "xyes"])

# check for gtk-doc
m4_ifdef([GTK_DOC_CHECK], [
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC], false)
])

# check gobject introspection
GOBJECT_INTROSPECTION_CHECK([0.9.0])

# check vapigen
VAPIGEN_CHECK

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
lib/Makefile
fep/Makefile
libfep/Makefile
libfep/libfep.pc
libfep-glib/Makefile
libfep-glib/libfep-glib.pc
tools/Makefile
docs/Makefile
docs/libfep/Makefile
docs/libfep/version.xml
docs/libfep-glib/Makefile
docs/libfep-glib/version.xml])
AC_OUTPUT
