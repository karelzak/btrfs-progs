#!/bin/sh

#
# Helps generate autoconf stuff, when code is checked out from SCM.
#
# Copyright (C) 2006-2014 - Karel Zak <kzak@redhat.com>
#

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

THEDIR=`pwd`
cd $srcdir
DIE=0

test -f btrfs.c || {
	echo
	echo "You must run this script in the top-level btrfs-progs directory"
	echo
	DIE=1
}

(autoconf --version) < /dev/null > /dev/null 2>&1 || {
	echo
	echo "You must have autoconf installed to generate btrfs-progs build system."
	echo
	DIE=1
}
(autoheader --version) < /dev/null > /dev/null 2>&1 || {
	echo
	echo "You must have autoheader installed to generate btrfs-progs build system."
	echo "The autoheader command is part of the GNU autoconf package."
	echo
	DIE=1
}
(libtoolize --version) < /dev/null > /dev/null 2>&1 || {
	echo
	echo "You must have libtool-2 installed to generate btrfs-progs build system."
	echo
	DIE=1
}
(automake --version) < /dev/null > /dev/null 2>&1 || {
	echo
	echo "You must have automake installed to generate btrfs-progs build system."
	echo 
	DIE=1
}

ltver=$(libtoolize --version | awk '/^libtoolize/ { print $4 }')
ltver=${ltver:-"none"}
test ${ltver##2.} = "$ltver" && {
	echo "You must have libtool version >= 2.x.x, but you have $ltver."
	DIE=1
}

if test "$DIE" -eq 1; then
	exit 1
fi

echo
echo "Generate build-system by:"
echo "   aclocal:    $(aclocal --version | head -1)"
echo "   autoconf:   $(autoconf --version | head -1)"
echo "   autoheader: $(autoheader --version | head -1)"
echo "   automake:   $(automake --version | head -1)"
echo "   libtoolize: $(libtoolize --version | head -1)"

chmod +x version.sh
rm -rf autom4te.cache
mkdir -p m4

libtoolize --force $LT_OPTS
aclocal -I m4 $AL_OPTS
autoconf $AC_OPTS
autoheader $AH_OPTS

automake --add-missing $AM_OPTS

cd $THEDIR

echo
echo "Now type '$srcdir/configure' and 'make' to compile."
echo
