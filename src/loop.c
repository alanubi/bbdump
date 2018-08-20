#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <bbmacro/label.h>
#include <bbmacro/ansicolor.h>
#include <bbmacro/static.h>
#include <bbmacro/vector.h>
#include <bbmacro/memory.h>
#include "color.h"
#include "loop.h"

#define hold_byte "  "
#define hold_ascii " "
#define sep_byte " "
#define sep_group "  "

BBSTATIC_BVECTOR(bline, char);
BBSTATIC_FVECTOR(fline, char);

static union {
	struct bline b;
	struct fline f;
} line_of_bytes;

static union {
	struct bline b;
} line_of_ascii;

static BBINLINE void append_bytes(char *str, size_t size, int rtl)
{
	if (rtl)
		memcpy(fline_agrowfront(size, &line_of_bytes.f), str, size);
	else
		memcpy(bline_agrowback(size, &line_of_bytes.b), str, size);
}

static BBINLINE void append_ascii(char *str, size_t size)
{
	memcpy(bline_agrowback(size, &line_of_ascii.b), str, size);
}

/* Print a byte or a byte placeholder, so that the last line
 * would have the same length as the others. */
static void print_one(int *c, int show_ascii, int rtl,
	BBUNUSED const char *(*bytecolor)(int c))
{
	static char tmpbuf[18]; /* Set + codelist + byte + reset. */
	size_t tmpcnt;

	if (*c == EOF) {
		append_bytes(hold_byte, sizeof(hold_byte) - 1, rtl);
		if (show_ascii) {
			append_ascii(hold_ascii, sizeof(hold_ascii) - 1);
		}
#ifndef ANSICOLOR_OFF
	} else if (bytecolor) {
		tmpcnt = sprintf(tmpbuf, ANSICOLOR("%s", "%2.2x"),
			bytecolor(*c), *c);
		append_bytes(tmpbuf, tmpcnt, rtl);
		if (show_ascii) {
			tmpcnt = sprintf(tmpbuf, ANSICOLOR("%s", "%c"),
				bytecolor(*c), asciichar(*c));
			append_ascii(tmpbuf, tmpcnt);
		}
		*c = getchar();
#endif
	} else {
		tmpcnt = sprintf(tmpbuf, "%2.2x", *c);
		append_bytes(tmpbuf, tmpcnt, rtl);
		if (show_ascii) {
			tmpcnt = sprintf(tmpbuf, "%c", asciichar(*c));
			append_ascii(tmpbuf, tmpcnt);
		}
		*c = getchar();
	}
}

/* Flush buffers. */
static void flush_line(unsigned long *total_cnt, unsigned bytes_per_line,
	int show_offset, int show_ascii, int rtl)
{
	if (rtl) {
		fwrite(fline_at(0, &line_of_bytes.f), 1,
			line_of_bytes.f.len, stdout);
		fline_clear(&line_of_bytes.f);
		if (show_offset) {
			printf("  %8.8lx", *total_cnt & 0xffffffffUL);
			*total_cnt += bytes_per_line;
		}
		if (show_ascii) {
			fputs("  ", stdout);
			fwrite(line_of_ascii.b.at, 1,
				line_of_ascii.b.len, stdout);
			bline_clear(&line_of_ascii.b);
		}
		fputs("\n", stdout);
	} else {
		if (show_ascii) {
			fwrite(line_of_ascii.b.at, 1,
				line_of_ascii.b.len, stdout);
			bline_clear(&line_of_ascii.b);
			fputs("  ", stdout);
		}
		if (show_offset) {
			printf("%8.8lx  ", *total_cnt & 0xffffffffUL);
			*total_cnt += bytes_per_line;
		}
		fwrite(line_of_bytes.b.at, 1,
			line_of_bytes.b.len, stdout);
		bline_clear(&line_of_bytes.b);
		fputs("\n", stdout);
	}
}

static void bytecolor_choose(BBUNUSED int coloring_mode,
	BBUNUSED const char *(**bytecolor)(int c))
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

int loop(int coloring_mode, int verbosity_level, int rtl,
	unsigned bytes_per_group, unsigned groups_per_line)
{
	unsigned bytes_per_line = bytes_per_group * groups_per_line;
	const char *(*bytecolor)(int c) = NULL;
	int show_offset = verbosity_level >= 1;
	int show_ascii = verbosity_level >= 2;

	unsigned byte_cnt = 0, group_cnt = 0;
	unsigned long total_cnt = 0;
	int c;

	if (rtl) {
		fline_ainit(0, &line_of_bytes.f);
	} else {
		bline_ainit(0, &line_of_bytes.b);
	}
	bline_ainit(0, &line_of_ascii.b);
	bytecolor_choose(coloring_mode, &bytecolor);

	c = getchar();
	SURE (c != EOF, goto exit);
	do {
		print_one(&c, show_ascii, rtl, bytecolor);

		/* Choose a separator. */
		SURE (++byte_cnt == bytes_per_group, goto byte_sep);
		SURE (++group_cnt == groups_per_line, goto group_sep);

		flush_line(&total_cnt, bytes_per_line,
			show_offset, show_ascii, rtl);

		/* Separate output. */
		SURE (c != EOF, goto exit);
		group_cnt = 0;
		SKIP (group_sep) {
			append_bytes(sep_group, sizeof(sep_group) - 1, rtl);
		}
		byte_cnt = 0;
		SKIP (byte_sep) {
			append_bytes(sep_byte, sizeof(sep_byte) - 1, rtl);
		}
	} LOOP (exit);

	bline_afini(&line_of_ascii.b);
	if (rtl) {
		fline_afini(&line_of_bytes.f);
	} else {
		bline_afini(&line_of_bytes.b);
	}

	return ferror(stdin) ? 1: 0;
}
