#include <ctype.h>
#include <bbmacro/label.h>
#include <bbmacro/ansicolor.h>
#include "color.h"

/****************************************
 * Styles BOLD, INVERT and SHOW are considered widespread.
 ****************************************/

/* With styles UNDER and FAINT. */
const char *bytecolor_gray(int c)
{
	switch (c) {
	when (0x00) return ANSICOLOR_FONT_1(FAINT);
	when (0x0a) return ANSICOLOR_FONT_1(INVERT);

	when (0x09)
	and_when (0x0b)
	and_when (0x0c)
	and_when (0x0d)
	and_when (0x20) return ANSICOLOR_FONT_2(INVERT, FAINT);

	when (0x7f) return ANSICOLOR_FONT_2(UNDER, BOLD);
	when (0xfe) return ANSICOLOR_FONT_1(BOLD);
	when (0xff) return ANSICOLOR_FONT_2(UNDER, BOLD);

	otherwise return
		c < 0x20 ? ANSICOLOR_FONT_2(UNDER, BOLD):
		c < 0x80 ?
			isdigit(c) ? ANSICOLOR_FONT_1(BOLD):
			isalpha(c) ? ANSICOLOR_FONT_1(SHOW):
			ANSICOLOR_FONT_1(UNDER):
		ANSICOLOR_FONT_1(SHOW);
	}
}

/* With standard colors. */
const char *bytecolor_dim(int c)
{
	switch (c) {
	when (0x00) return ANSICOLOR_FONT_1(B);
	when (0x0a) return ANSICOLOR_FONT_1(INVERT);

	when (0x09)
	and_when (0x0b)
	and_when (0x0c)
	and_when (0x0d)
	and_when (0x20) return ANSICOLOR_FONT_2(INVERT, C);

	when (0x7f) return ANSICOLOR_FONT_1(BOLD);
	when (0xfe) return ANSICOLOR_FONT_2(Y, BOLD);
	when (0xff) return ANSICOLOR_FONT_2(R, BOLD);

	otherwise return
		c < 0x20 ? ANSICOLOR_FONT_1(BOLD):
		c < 0x80 ?
			isdigit(c) ? ANSICOLOR_FONT_2(C, BOLD):
			isalpha(c) ? ANSICOLOR_FONT_1(C):
			ANSICOLOR_FONT_1(SHOW):
		c < 0xc0? ANSICOLOR_FONT_1(G): ANSICOLOR_FONT_1(Y);
	}
}

/* With bright colors and style FAINT. */
const char *bytecolor_bright(int c)
{
	switch (c) {
	when (0x00) return ANSICOLOR_FONT_1(FAINT);
	when (0x0a) return ANSICOLOR_FONT_1(INVERT);

	when (0x09)
	and_when (0x0b)
	and_when (0x0c)
	and_when (0x0d)
	and_when (0x20) return ANSICOLOR_FONT_2(INVERT, FAINT);

	when (0x7f) return ANSICOLOR_FONT_1(BOLD);
	when (0xfe) return ANSICOLOR_FONT_2(YX, BOLD);
	when (0xff) return ANSICOLOR_FONT_2(RX, BOLD);

	otherwise return
		c < 0x20 ? ANSICOLOR_FONT_1(BOLD):
		c < 0x80 ?
			isdigit(c) ? ANSICOLOR_FONT_2(CX, BOLD):
			isalpha(c) ? ANSICOLOR_FONT_1(CX):
			ANSICOLOR_FONT_1(SHOW):
		c < 0xc0? ANSICOLOR_FONT_1(GX): ANSICOLOR_FONT_1(YX);
	}
}

char asciichar(int c)
{
	if (0x20 <= c && c < 0x7f)
		return (char)c;
	return '.';
}
