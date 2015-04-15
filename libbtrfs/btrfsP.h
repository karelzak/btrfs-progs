/*
 * private library header file
 *
 * Copyright (C) 2015 Karel Zak <kzak@redhat.com>
 */
#ifndef _LIBBTRFS_PRIVATE_H_
#define _LIBBTRFS_PRIVATE_H_

#include "libbtrfs.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <dirent.h>

/*
 * Generic FS handler
 */
struct libbtrfs_fs {
	int	fd;		/* file descritor (usually mountpoint) */
	DIR	*dirstream;	/* usually mountpoint */

	char	*path;		/* FS path */

	int refcount;	/* reference counter */
};

#endif /* _LIBBTRFS_PRIVATE_H_ */
