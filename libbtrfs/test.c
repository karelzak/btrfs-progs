
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <getopt.h>
#include <err.h>

#include <libbtrfs.h>


static void usage(FILE *out)
{
	fprintf(out, " %s <command>\n", program_invocation_short_name);
	fputs("\nCommands\n", out);
	fputs(" --version        prints library version info\n", out);

	fputc('\n', out);
	exit(out == stderr ? EXIT_FAILURE : EXIT_SUCCESS);
}

static int ts_version(void)
{
	const char *ver;
	int code;

	code = btrfs_get_library_version(&ver);
	printf("Linked library: %s (code %d)\n", ver, code);

	code = btrfs_parse_version_string(LIBBTRFS_VERSION);
	printf("API version:    %s (code %d)\n", LIBBTRFS_VERSION, code);

	return 0;
}

int main(int argc, char **argv)
{
	enum {
		OPT_VERSION = CHAR_MAX + 1,
	};
	static const struct option longopts[] = {
		{ "version", no_argument, 0, OPT_VERSION},
		{ NULL, 0, 0, 0 }
	};

	int rc = EXIT_FAILURE, c;

	while ((c = getopt_long(argc, argv, "", longopts, NULL)) != -1) {
		switch (c) {
		case OPT_VERSION:
			rc = ts_version();
			break;
		default:
			usage(stderr);
			break;
		}
	}

	return rc == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
