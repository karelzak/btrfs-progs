/*
 * version.c - Return the version of the library
 *
 * Copyright (C) 2015 Karel Zak <kzak@redhat.com>
 *
 * See COPYING.libbtrfs for the License of this software.
 */

#include <ctype.h>

#include "btrfsP.h"

static const char *lib_version = LIBBTRFS_VERSION;

/**
 * btrfs_parse_version_string:
 * @ver_string: version string (e.g "3.19.0")
 *
 * Returns: release version code.
 */
int btrfs_parse_version_string(const char *ver_string)
{
	const char *cp;
	int version = 0;

	for (cp = ver_string; *cp; cp++) {
		if (*cp == '.')
			continue;
		if (!isdigit(*cp))
			break;
		version = (version * 10) + (*cp - '0');
	}
	return version;
}

/**
 * btrfs_get_library_version:
 * @ver_string: return pointer to the static library version string if not NULL
 *
 * Returns: release version number.
 */
int btrfs_get_library_version(const char **ver_string)
{
	if (ver_string)
		*ver_string = lib_version;

	return btrfs_parse_version_string(lib_version);
}

