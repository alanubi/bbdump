#include <ctype.h>
#include <bbdump/ansicolor.h>
#include <bbdump/switch.h>
#include "color.h"

/****************************************
 * Styles BOLD, INVERT and SHOW are considered widespread.
 ****************************************/

/* With styles UNDER and FAINT. */
const char *bytecolor_gray(int c)
{
	switch (c) {
	when (0x00) return CODELIST1(FAINT);
	when (0x0a) return CODELIST1(INVERT);

	when (0x09)
	and_when (0x0b)
	and_when (0x0c)
	and_when (0x0d)
	and_when (0x20) return CODELIST2(INVERT, FAINT);

	when (0x7f) return CODELIST2(UNDER, BOLD);
	when (0xfe) return CODELIST1(BOLD);
	when (0xff) return CODELIST2(UNDER, BOLD);

	otherwise return
		c < 0x20? CODELIST2(UNDER, BOLD):
		c < 0x80?
			isdigit(c)? CODELIST1(BOLD):
			isalpha(c)? CODELIST1(SHOW):
			CODELIST1(UNDER):
		CODELIST1(SHOW);
	}
}

/* With standard colors. */
const char *bytecolor_dim(int c)
{
	switch (c) {
	when (0x00) return CODELIST1(B);
	when (0x0a) return CODELIST1(INVERT);

	when (0x09)
	and_when (0x0b)
	and_when (0x0c)
	and_when (0x0d)
	and_when (0x20) return CODELIST2(INVERT, C);

	when (0x7f) return CODELIST1(BOLD);
	when (0xfe) return CODELIST2(Y, BOLD);
	when (0xff) return CODELIST2(R, BOLD);

	otherwise return
		c < 0x20? CODELIST1(BOLD):
		c < 0x80?
			isdigit(c)? CODELIST2(C, BOLD):
			isalpha(c)? CODELIST1(C):
			CODELIST1(SHOW):
		c < 0xc0? CODELIST1(G): CODELIST1(Y);
	}
}

/* With bright colors and style FAINT. */
const char *bytecolor_bright(int c)
{
	switch (c) {
	when (0x00) return CODELIST1(FAINT);
	when (0x0a) return CODELIST1(INVERT);

	when (0x09)
	and_when (0x0b)
	and_when (0x0c)
	and_when (0x0d)
	and_when (0x20) return CODELIST2(INVERT, FAINT);

	when (0x7f) return CODELIST1(BOLD);
	when (0xfe) return CODELIST2(YX, BOLD);
	when (0xff) return CODELIST2(RX, BOLD);

	otherwise return
		c < 0x20? CODELIST1(BOLD):
		c < 0x80?
			isdigit(c)? CODELIST2(CX, BOLD):
			isalpha(c)? CODELIST1(CX):
			CODELIST1(SHOW):
		c < 0xc0? CODELIST1(GX): CODELIST1(YX);
	}
}

char asciichar(int c)
{
	if (0x20 <= c && c < 0x7f)
		return (char)c;
	return '.';
}
