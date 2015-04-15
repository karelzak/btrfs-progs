
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "btrfsP.h"
#include "utils.h"

/**
 * btrfs_new_fs:
 *
 * The initial refcount is 1, and needs to be decremented to
 * release the resources of the filesystem.
 *
 * Returns: newly allocated struct libbtrfs_fs.
 */
struct libbtrfs_fs *btrfs_new_fs(void)
{
	struct libbtrfs_fs *fs = calloc(1, sizeof(*fs));
	if (!fs)
		return NULL;

	fs->refcount = 1;
	fs->fd = -1;
	return fs;
}

static void btrfs_free_fs(struct libbtrfs_fs *fs)
{
	assert(fs);
	assert(fs->refcount == 0);

	close_file_or_dir(fs->fd, fs->dirstream);
	free(fs->path);
	free(fs);
}

/**
 * btrfs_ref_fs:
 * @fs: fs pointer
 *
 * Increments reference counter.
 */
void btrfs_ref_fs(struct libbtrfs_fs *fs)
{
	if (fs)
		fs->refcount++;
}

/**
 * btrfs_unref_fs:
 * @fs: filesystem instance
 *
 * De-increments reference counter, on zero @fs is automatically
 * deallocated.
 */
void btrfs_unref_fs(struct libbtrfs_fs *fs)
{
	if (fs) {
		fs->refcount--;
		if (fs->refcount <= 0)
			btrfs_free_fs(fs);
	}
}

/**
 * btrfs_fs_set_path:
 * @fs: filesystem instance
 * @path: usually mountpoint or NULL to unset
 *
 * Sets path to the filesystem, the paths maybe later used for open().
 *
 * Returns: 0 on success, <0 on error
 */
int btrfs_fs_set_path(struct libbtrfs_fs *fs, const char *path)
{
	char *p = NULL;

	if (!fs)
		return -EINVAL;

	if (path) {
		p = strdup(path);
		if (!p)
			return -ENOMEM;
	}
	free(fs->path);
	fs->path = p;
	return 0;
}

/**
 * btrfs_fs_get_path:
 * @fs: filesystem instance
 *
 * Returns: pointer to path or NULL
 */
const char *btrfs_fs_get_path(struct libbtrfs_fs *fs)
{
	return fs->path;
}

/**
 * btrfs_fs_get_fd:
 * @fs: filesystem instance
 *
 * See also btrfs_fs_set_path().
 *
 * Returns: file descritor on success, <0 on error
 */
int btrfs_fs_get_fd(struct libbtrfs_fs *fs)
{
	if (!fs || !fs->path)
		return -EINVAL;

	if (fs->fd < 0) {
		struct stat st;

		if (stat(fs->path, &st) < 0)
			return -errno;
		if (S_ISDIR(st.st_mode)) {
			fs->dirstream = opendir(fs->path);
			if (!fs->dirstream)
				return -errno;
			fs->fd = dirfd(fs->dirstream);
		} else if (S_ISREG(st.st_mode))
			fs->fd = open(fs->path, O_RDWR);
		else
			return -EINVAL;

		if (fs->fd < 0) {
			if (fs->dirstream)
				closedir(fs->dirstream);
			fs->dirstream = NULL;
			fs->fd = -1;
		}
	}
	return fs->fd;
}

