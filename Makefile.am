
# preprocesor flags
AM_CPPFLAGS = \
	-include config.h \
	-D_FILE_OFFSET_BITS=64 -DBTRFS_FLAT_INCLUDES

# compiler flags
AM_CFLAGS = \
	-Wall -fno-strict-aliasing -fPIC \
	-rdynamic

# linker flags
AM_LDFLAGS = -L. -pthread -lm

# Additional static compilation flags
static_cflags = \
	-ffunction-sections -fdata-sections
static_ldflags = \
	-Wl,--gc-sections

SUBDIRS =
CLEANFILES =
EXTRA_DIST =
bin_PROGRAMS =
check_PROGRAMS =
UNINSTALL_HOOKS =
INSTALL_EXEC_HOOKS =

if BUILD_DOCUMENTATION
#SUBDIRS += Documentation
endif

common_sources = \
	backref.c \
	backref.h \
	bitops.h \
	config.h \
	ctree.c \
	dir-item.c \
	disk-io.c \
	disk-io.h \
	extent-cache.c \
	extent_io.c \
	extent-tree.c \
	file-item.c \
	free-space-cache.c \
	free-space-cache.h \
	hash.h \
	inode.c \
	inode-item.c \
	inode-map.c \
	list_sort.c \
	list_sort.h \
	print-tree.c \
	print-tree.h \
	props.c \
	props.h \
	qgroup.c \
	qgroup.h \
	qgroup-verify.c \
	qgroup-verify.h \
	radix-tree.c \
	raid6.c \
	rbtree_augmented.h \
	rbtree-utils.h \
	repair.c \
	repair.h \
	root-tree.c \
	string-table.c \
	string-table.h \
	task-utils.c \
	task-utils.h \
	transaction.h \
	ulist.c \
	ulist.h \
	utils.c \
	utils.h \
	volumes.c \
	volumes.h

common_libs = $(UUID_LIBS) $(BLKID_LIBS)
common_libs_static = $(UUID_LIBS_STATIC) $(BLKID_LIBS_STATIC)

cmds_sources = \
	chunk-recover.c \
	cmds-balance.c \
	cmds-check.c \
	cmds-device.c \
	cmds-fi-disk_usage.c \
	cmds-fi-disk_usage.h \
	cmds-filesystem.c \
	cmds-inspect.c \
	cmds-property.c \
	cmds-qgroup.c \
	cmds-quota.c \
	cmds-receive.c \
	cmds-replace.c \
	cmds-rescue.c \
	cmds-restore.c \
	cmds-scrub.c \
	cmds-send.c \
	cmds-subvolume.c \
	commands.h \
	super-recover.c

cmds_libs = $(ZLIB_LIBS) $(LZO2_LIBS)
cmss_libs_static = $(ZLIB_LIBS_STATIC) $(LZO2_LIBS_STATIC)



#
# libbtrfs
#
btrfsincdir = $(includedir)/btrfs
nodist_btrfsinc_HEADERS = version.h	# generated file
btrfsinc_HEADERS = \
	send-stream.h send-utils.h send.h rbtree.h btrfs-list.h \
	crc32c.h list.h kerncompat.h radix-tree.h extent-cache.h \
	extent_io.h ioctl.h ctree.h btrfsck.h

lib_LTLIBRARIES = libbtrfs.la
libbtrfs_la_SOURCES = \
	send-stream.c send-utils.c rbtree.c btrfs-list.c crc32c.c \
	uuid-tree.c utils-lib.c rbtree-utils.c rbtree_augmented.h \
	$(btrfsinc_HEADERS) $(nodist_btrfsinc_HEADERS)

libbtrfs_la_LDFLAGS = -version-info $(LIBBTRFS_VERSION_INFO)

libbtrfs_la_LIDADD = $(UUID_LIBS)
libbtrfs_la_DEPENDENCIES = version.h.in


EXTRA_DIST += version.h.in

#
# Programs
#
bin_PROGRAMS += btrfs
btrfs_SOURCES = btrfs.c help.c $(common_sources) $(cmds_sources)
btrfs_LDADD = libbtrfs.la $(common_libs) $(cmds_libs)

if BUILD_STATIC
bin_PROGRAMS += btrfs.static
btrfs_static_SOURCES = $(btrfs_SOURCES)
btrfs_static_CFLAGS = $(AM_CFLAGS) $(static_cflags)
btrfs_static_LDADD = libbtrfs.la $(common_libs_static) $(cmds_libs_static)
btrfs_static_LDFLAGS = -all-static $(static_ldflags)
endif


bin_PROGRAMS += mkfs.btrfs
mkfs_btrfs_SOURCES = mkfs.c $(common_sources)
mkfs_btrfs_LDADD = libbtrfs.la $(common_libs)

if BUILD_STATIC
bin_PROGRAMS += mkfs.btrfs.static
mkfs_btrfs_static_SOURCES = $(mkfs_btrfs_SOURCES)
mkfs_btrfs_static_CFLAGS = $(AM_CFLAGS) $(static_cflags)
mkfs_btrfs_static_LDADD = libbtrfs.la $(common_libs_static)
mkfs_btrfs_static_LDFLAGS = -all-static $(static_ldflags)
endif


bin_PROGRAMS += btrfstune
btrfstune_SOURCES = btrfstune.c $(common_sources)
btrfstune_LDADD = libbtrfs.la $(common_libs)

if BUILD_STATIC
bin_PROGRAMS += btrfstune.static
btrfstune_static_SOURCES = $(btrfstune_SOURCES)
btrfstune_static_CFLAGS = $(AM_CFLAGS) $(static_cflags)
btrfstune_static_LDADD = libbtrfs.la $(common_libs_static)
btrfstune_static_LDFLAGS = -all-static $(static_ldflags)
endif


bin_PROGRAMS += btrfs-convert
btrfs_convert_SOURCES = btrfs-convert.c $(common_sources)
btrfs_convert_LDADD = libbtrfs.la $(common_libs) $(EXT2FS_LIBS) $(COM_ERR_LIBS)

if BUILD_STATIC
bin_PROGRAMS += btrfs-convert.static
btrfs_convert_static_SOURCES = $(btrfs_convert_SOURCES)
btrfs_convert_static_CFLAGS = $(AM_CFLAGS) $(static_cflags)
btrfs_convert_static_LDADD = libbtrfs.la $(common_libs_static) $(EXT2FS_LIBS_STATIC) $(COM_ERR_LIBS_STATIC)
btrfs_convert_static_LDFLAGS = -all-static $(static_ldflags)
endif


bin_PROGRAMS += btrfs-image
btrfs_image_SOURCES = btrfs-image.c $(common_sources)
btrfs_image_LDADD = libbtrfs.la $(common_libs) $(ZLIB_LIBS)

if BUILD_STATIC
bin_PROGRAMS += btrfs-image.static
btrfs_image_static_SOURCES = $(btrfs_image_SOURCES)
btrfs_image_static_CFLAGS = $(AM_CFLAGS) $(static_cflags)
btrfs_image_static_LDADD = libbtrfs.la $(common_libs_static) $(ZLIB_LIBS_STATIC)
btrfs_image_static_LDFLAGS = -all-static $(static_ldflags)
endif


bin_PROGRAMS += btrfs-debug-tree
btrfs_debug_tree_SOURCES = btrfs-debug-tree.c $(common_sources)
btrfs_debug_tree_LDADD = libbtrfs.la $(common_libs)

if BUILD_STATIC
bin_PROGRAMS += btrfs-debug-tree.static
btrfs_debug_tree_static_SOURCES = $(btrfs_debug_tree_SOURCES)
btrfs_debug_tree_static_CFLAGS = $(AM_CFLAGS) $(static_cflags)
btrfs_debug_tree_static_LDADD = libbtrfs.la $(common_libs_static)
btrfs_debug_tree_static_LDFLAGS = -all-static $(static_ldflags)
endif


bin_PROGRAMS += btrfs-find-root
btrfs_find_root_SOURCES = btrfs-find-root.c $(common_sources)
btrfs_find_root_LDADD = libbtrfs.la $(common_libs)

if BUILD_STATIC
bin_PROGRAMS += btrfs-find-root.static
btrfs_find_root_static_SOURCES = $(btrfs_debug_tree_SOURCES)
btrfs_find_root_static_CFLAGS = $(AM_CFLAGS) $(static_cflags)
btrfs_find_root_static_LDADD = libbtrfs.la $(common_libs_static)
btrfs_find_root_static_LDFLAGS = -all-static $(static_ldflags)
endif


bin_PROGRAMS += btrfs-map-logical
btrfs_map_logical_SOURCES = btrfs-map-logical.c $(common_sources)
btrfs_map_logical_LDADD = libbtrfs.la $(common_libs)

if BUILD_STATIC
bin_PROGRAMS += btrfs-map-logical.static
btrfs_map_logical_static_SOURCES = $(btrfs_debug_tree_SOURCES)
btrfs_map_logical_static_CFLAGS = $(AM_CFLAGS) $(static_cflags)
btrfs_map_logical_static_LDADD = libbtrfs.la $(common_libs_static)
btrfs_map_logical_static_LDFLAGS = -all-static $(static_ldflags)
endif


bin_PROGRAMS += btrfs-show-super
btrfs_show_super_SOURCES = btrfs-show-super.c $(common_sources)
btrfs_show_super_LDADD = libbtrfs.la $(common_libs)

if BUILD_STATIC
bin_PROGRAMS += btrfs-show-super.static
btrfs_show_super_static_SOURCES = $(btrfs_debug_tree_SOURCES)
btrfs_show_super_static_CFLAGS = $(AM_CFLAGS) $(static_cflags)
btrfs_show_super_static_LDADD = libbtrfs.la $(common_libs_static)
btrfs_show_super_static_LDFLAGS = -all-static $(static_ldflags)
endif


bin_PROGRAMS += btrfs-zero-log
btrfs_zero_log_SOURCES = btrfs-zero-log.c $(common_sources)
btrfs_zero_log_LDADD = libbtrfs.la $(common_libs)

if BUILD_STATIC
bin_PROGRAMS += btrfs-zero-log.static
btrfs_zero_log_static_SOURCES = $(btrfs_debug_tree_SOURCES)
btrfs_zero_log_static_CFLAGS = $(AM_CFLAGS) $(static_cflags)
btrfs_zero_log_static_LDADD = libbtrfs.la $(common_libs_static)
btrfs_zero_log_static_LDFLAGS = -all-static $(static_ldflags)
endif

#
# Tests
#
check_PROGRAMS += btrfs-calc-size
btrfs_calc_size_SOURCES = btrfs-calc-size.c $(common_sources)
btrfs_calc_size_LDADD = libbtrfs.la $(common_libs)

check_PROGRAMS += btrfs-corrupt-block
btrfs_corrupt_block_SOURCES = btrfs-corrupt-block.c $(common_sources)
btrfs_corrupt_block_LDADD = libbtrfs.la $(common_libs)

if BUILD_BTRFS_FRAGMENTS
check_PROGRAMS += btrfs-fragments
btrfs_fragments_SOURCES = btrfs-fragments.c $(common_sources)
btrfs_fragments_LDADD = libbtrfs.la $(common_libs) $(GDLIB_LIBS)
endif

check_PROGRAMS += btrfs-select-super
btrfs_select_super_SOURCES = btrfs-select-super.c $(common_sources)
btrfs_select_super_LDADD = libbtrfs.la $(common_libs)

#check_PROGRAMS += dir-test
#dir_test_SOURCES = dir-test.c $(common_sources)
#dir_test_LDADD = libbtrfs.la $(common_libs)

check_PROGRAMS += quick-test
quick_test_SOURCES = quick-test.c $(common_sources)
quick_test_LDADD = libbtrfs.la $(common_libs)

check_PROGRAMS += ioctl-test
ioctl_test_SOURCES = ioctl-test.c $(common_sources)
ioctl_test_LDADD = libbtrfs.la $(common_libs)

#check_PROGRAMS += send-test
#send_test_SOURCES = send-test.c $(common_sources)
#send_test_LDADD = libbtrfs.la $(common_libs)

#check_PROGRAMS += library-test
#library_test_SOURCES = library-test.c $(common_sources)
#library_test_LDADD = libbtrfs.la $(common_libs)

if BUILD_STATIC
check_PROGRAMS += library-test.static
library_test_static_SOURCES = $(library_test_SOURCES)
library_test_static_LDADD = libbtrfs.la $(common_libs_static)
library_test_static_LDFLAGS = -all-static $(static_ldflags)
library_test_static_CFLAGS = $(AM_CFLAGS) $(static_cflags)
endif

EXTRA_DIST += \
	tests/fsck-tests.sh \
	tests/convert-tests.sh \
	tests/fsck-tests

CLEANFILES += convert-tests-results.txt fsck-tests-results.txt generate_image.sh

check-local: $(check_PROGRAMS) btrfs btrfs-convert btrfs-image btrfs-corrupt-block
#broken	$(AM_V_GEN) bash $(top_srcdir)/tests/fsck-tests.sh
	$(AM_V_GEN) bash $(top_srcdir)/tests/convert-tests.sh

#
# Misc
#
#
# For backward compatibility, 'btrfs' changes behaviour to fsck if it's named 'btrfsck'
install-exec-hook-btrfs:
	cd $(DESTDIR)$(bindir) && $(LN_S) -f btrfs btrfsck
uninstall-hook-btrfs:
	rm -f $(DESTDIR)$(bindir)/btrfsck
INSTALL_EXEC_HOOKS += install-exec-hook-btrfs

if BUILD_STATIC
install-exec-hook-btrfs-static:
	cd $(DESTDIR)$(bindir) && $(LN_S) -f btrfs.static btrfsck.static
uninstall-hook-btrfs-static:
	rm -f $(DESTDIR)$(bindir)/btrfsck.static
UNINSTALL_HOOKS += uninstall-hook-btrfs-static
endif



install-exec-hook: $(INSTALL_EXEC_HOOKS)

uninstall-hook: $(UNINSTALL_HOOKS)



# make C=1 to enable sparse
#check_defs := .cc-defines.h 
#ifdef C
#	#
#	# We're trying to use sparse against glibc headers which go wild
#	# trying to use internal compiler macros to test features.  We
#	# copy gcc's and give them to sparse.  But not __SIZE_TYPE__
#	# 'cause sparse defines that one.
#	#
#	dummy := $(shell $(CC) -dM -E -x c - < /dev/null | \
#			grep -v __SIZE_TYPE__ > $(check_defs))
#	check = sparse -include $(check_defs) -D__CHECKER__ \
#		-D__CHECK_ENDIAN__ -Wbitwise -Wuninitialized -Wshadow -Wundef
#	check_echo = echo
#	# don't use FORTIFY with sparse because glibc with FORTIFY can
#	# generate so many sparse errors that sparse stops parsing,
#	# which masks real errors that we want to see.
#else
#	check = true
#	check_echo = true
#	CFLAGS += -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=2
#endif


test-build: $(check_PROGRAMS)

manpages:
	$(MAKE) -C Documentation


