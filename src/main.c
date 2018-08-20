#include <stdio.h>
#include <stdlib.h>
#include <bbmacro/label.h>
#include <bbmacro/static.h>
#include "loop.h"
#include "defaults.h"

#define BYTES_PER_GROUP 4
#define GROUPS_PER_QWORD 2

#if DEFAULT_RIGHT_TO_LEFT == 1
#  define DEFAULT_DIRECTION_FLAG "r"
#else
#  define DEFAULT_DIRECTION_FLAG "l"
#endif

static BBNORETURN void usage(void)
{
	fputs(
"bbdump "bbstatic_xstr(BBDUMP_VERSION)"\n"
"Usage: bbdump [-cN|-qN|-vN|-l|-r]...\n"
"  -cN  - coloring mode N (0-3)\n"
"  -qN  - N qwords per line (1-8)\n"
"  -vN  - verbosity level N (0-2)\n"
"  -l   - left-to-right output\n"
"  -r   - right-to-left output\n"
"Default: bbdump -c"bbstatic_xstr(DEFAULT_COLORING_MODE)
	" -q"bbstatic_xstr(DEFAULT_QWORDS_PER_LINE)
	" -v"bbstatic_xstr(DEFAULT_VERBOSITY_LEVEL)
	" -"DEFAULT_DIRECTION_FLAG"\n"
		"", stderr);
	exit(1);
}

static int option_c(char *arg)
{
	char c = arg[0];
	if (c && !arg[1] && '0' <= c && c <= '3')
		return c - '0';
	usage();
}

static int option_q(char *arg)
{
	char c = arg[0];
	if (c && !arg[1] && '1' <= c && c <= '8')
		return c - '0';
	usage();
}

static int option_v(char *arg)
{
	char c = arg[0];
	if (c && !arg[1] && '0' <= c && c <= '2')
		return c - '0';
	usage();
}

static int option_l(char *arg)
{
	if (!arg[0])
		return 0;
	usage();
}

static int option_r(char *arg)
{
	if (!arg[0])
		return 1;
	usage();
}

int main(BBUNUSED int argc, char *argv[])
{
	int coloring_mode = DEFAULT_COLORING_MODE;
	int verbosity_level = DEFAULT_VERBOSITY_LEVEL;
	int right_to_left = DEFAULT_RIGHT_TO_LEFT;
	unsigned qwords_per_line = DEFAULT_QWORDS_PER_LINE;
	unsigned groups_per_line;
	char *arg;

	while ((arg = *++argv)) {
		if (arg[0] != '-')
			usage();
		switch (arg[1]) {
		when ('c') coloring_mode = option_c(&arg[2]);
		when ('q') qwords_per_line = option_q(&arg[2]);
		when ('v') verbosity_level = option_v(&arg[2]);
		when ('l') right_to_left = option_l(&arg[2]);
		when ('r') right_to_left = option_r(&arg[2]);
		otherwise usage();
		}
	}
	groups_per_line = qwords_per_line * GROUPS_PER_QWORD;
	return loop(coloring_mode, verbosity_level, right_to_left,
		BYTES_PER_GROUP, groups_per_line);
}
