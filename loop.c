#include <stdio.h>
#include <bbdump/specifier.h>
#include <bbdump/ansicolor.h>
#include <bbdump/switch.h>
#include <bbdump/label.h>
#include "color.h"
#include "loop.h"

static int pos_bytes;
static int pos_ascii;

static INLINE void print_byte(int c, const char *(*bytecolor)(int c))
{
#ifndef ANSICOLOR_OFF
	if (bytecolor) {
		pos_bytes += sprintf(&line_bytes[pos_bytes],
			ANSICOLOR("%s", "%2.2x"), bytecolor(c), c);
		return;
	}
#endif
	pos_bytes += sprintf(&line_bytes[pos_bytes], "%2.2x", c);
}

static INLINE void print_byte_placeholder()
{
	pos_bytes += sprintf(&line_bytes[pos_bytes], "  ");
}

static INLINE void print_ascii(int c, const char *(*bytecolor)(int c))
{
#ifndef ANSICOLOR_OFF
	if (bytecolor) {
		pos_ascii += sprintf(&line_ascii[pos_ascii],
			ANSICOLOR("%s", "%c"), bytecolor(c), asciichar(c));
		return;
	}
#endif
	pos_ascii += sprintf(&line_ascii[pos_ascii], "%c", asciichar(c));
}

static INLINE void print_ascii_placeholder()
{
	pos_ascii += sprintf(&line_ascii[pos_ascii], " ");
}

/********************/

static void bytecolor_choose(int coloring_mode,
	const char *(**bytecolor)(int c))
{
#ifndef ANSICOLOR_OFF
	switch (coloring_mode) {
	when (0) (void)0;
	when (1) *bytecolor = &bytecolor_gray;
	when (2) *bytecolor = &bytecolor_dim;
	when (3) *bytecolor = &bytecolor_bright;
	}
#endif
}

int loop(int coloring_mode, int verbosity_level,
	unsigned bytes_per_group, unsigned groups_per_line)
{
	unsigned bytes_per_line = bytes_per_group * groups_per_line;
	const char *(*bytecolor)(int c) = NULL;
	int show_offset = verbosity_level >= 1;
	int show_ascii = verbosity_level >= 2;

	unsigned byte_cnt = 0, group_cnt = 0;
	unsigned long total_cnt = 0;
	int c;

	pos_bytes = 0;
	pos_ascii = 0;
	bytecolor_choose(coloring_mode, &bytecolor);
	c = getchar();
	ENSURE (c != EOF, exit);
	do {
		/* Print a byte or a byte placeholder, so that the last line
		 * would have the same length as the others. */
		if (c != EOF) {
			print_byte(c, bytecolor);
			if (show_ascii)
				print_ascii(c, bytecolor);
			c = getchar();
		} else {
			print_byte_placeholder();
			if (show_ascii)
				print_ascii_placeholder();
		}

		/* Choose a separator. */
		ENSURE (++byte_cnt == bytes_per_group, byte_sep);
		ENSURE (++group_cnt == groups_per_line, group_sep);

		/* Flush buffers. */
		if (show_ascii) {
			fputs(&line_ascii[pos_ascii = 0], stdout);
			fputs("  ", stdout);
		}
		if (show_offset) {
			printf("%8.8lx  ", total_cnt & 0xffffffffUL);
			total_cnt += bytes_per_line;
		}
		fputs(&line_bytes[pos_bytes = 0], stdout);
		fputs("\n", stdout);

		/* Separate output. */
		ENSURE (c != EOF, exit);
		group_cnt = 0;
		SKIP (group_sep)
			pos_bytes += sprintf(&line_bytes[pos_bytes], "  ");
		byte_cnt = 0;
		SKIP (byte_sep)
			pos_bytes += sprintf(&line_bytes[pos_bytes], " ");
	} LOOP (exit);
	return ferror(stdin)? 1: 0;
}
