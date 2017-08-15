#include <stdio.h>
#include <stdlib.h>
#include <bbdump/specifier.h>
#include <bbdump/ansicolor.h>
#include <bbdump/switch.h>
#include "color.h"
#include "loop.h"
#include "defaults.h"

#define BYTES_PER_GROUP  4
#define GROUPS_PER_QWORD 2

#define xstr(codename) ANSICOLOR_XSTR(codename)

#define MAX_CHARS_PER_LINE(contents, lesser_space, greater_space) \
	((((contents) \
		+ MAX_SETRESET_OVERHEAD + (lesser_space)) \
		* BYTES_PER_GROUP \
		- (lesser_space) + (greater_space)) \
		* GROUPS_PER_QWORD * 8 /* max qwords per line */ \
		- (greater_space) + 1 /* null character */)

/* KEEP UP TO DATE! */
char line_bytes[MAX_CHARS_PER_LINE(2, 1, 2)];
char line_ascii[MAX_CHARS_PER_LINE(1, 0, 0)];

static NORETURN void usage()
{
	fputs(
"bbdump "xstr(BBDUMP_VERSION)"\n"
"Usage: bbdump [-cN|-qN|-vN]...\n"
"  -cN  - coloring mode N (0-3)\n"
"  -qN  - N qwords per line (1-8)\n"
"  -vN  - verbosity level N (0-2)\n"
"Default: bbdump -c"xstr(DEFAULT_COLORING_MODE)
	" -q"xstr(DEFAULT_QWORDS_PER_LINE)
	" -v"xstr(DEFAULT_VERBOSITY_LEVEL)"\n"
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

int main(int argc, char *argv[])
{
	int coloring_mode = DEFAULT_COLORING_MODE;
	int verbosity_level = DEFAULT_VERBOSITY_LEVEL;
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
		otherwise  usage();
		}
	}
	groups_per_line = qwords_per_line * GROUPS_PER_QWORD;
	return loop(coloring_mode, verbosity_level,
		BYTES_PER_GROUP, groups_per_line);
}
