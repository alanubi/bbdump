/*
  bbdump -- print human-readable colored hex dump
  Copyright (C) 2017 Alexey Gantura <ganturagantura@yandex.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BBDUMP_ANSICOLOR_H_
#define BBDUMP_ANSICOLOR_H_

/****************************************
 * ANSI font style escape codes.
 * These numbers are string constants, not integers.
 ****************************************/

/* Widely supported foreground colors. */
#define ANSICOLOR_CODE_K 30
#define ANSICOLOR_CODE_R 31
#define ANSICOLOR_CODE_G 32
#define ANSICOLOR_CODE_Y 33
#define ANSICOLOR_CODE_B 34
#define ANSICOLOR_CODE_M 35
#define ANSICOLOR_CODE_C 36
#define ANSICOLOR_CODE_W 37

/* Widely supported background colors. */
#define ANSICOLOR_CODE_BG_K 40
#define ANSICOLOR_CODE_BG_R 41
#define ANSICOLOR_CODE_BG_G 42
#define ANSICOLOR_CODE_BG_Y 43
#define ANSICOLOR_CODE_BG_B 44
#define ANSICOLOR_CODE_BG_M 45
#define ANSICOLOR_CODE_BG_C 46
#define ANSICOLOR_CODE_BG_W 47

/* Not widely supported foreground colors. */
#define ANSICOLOR_CODE_KX 90
#define ANSICOLOR_CODE_RX 91
#define ANSICOLOR_CODE_GX 92
#define ANSICOLOR_CODE_YX 93
#define ANSICOLOR_CODE_BX 94
#define ANSICOLOR_CODE_MX 95
#define ANSICOLOR_CODE_CX 96
#define ANSICOLOR_CODE_WX 97

/* Not widely supported background colors. */
#define ANSICOLOR_CODE_BG_KX 100
#define ANSICOLOR_CODE_BG_RX 101
#define ANSICOLOR_CODE_BG_GX 102
#define ANSICOLOR_CODE_BG_YX 103
#define ANSICOLOR_CODE_BG_BX 104
#define ANSICOLOR_CODE_BG_MX 105
#define ANSICOLOR_CODE_BG_CX 106
#define ANSICOLOR_CODE_BG_WX 107

/* Widely supported font styles. */
#define ANSICOLOR_CODE_BOLD   1
#define ANSICOLOR_CODE_INVERT 7

/* Not widely supported font styles. */
#define ANSICOLOR_CODE_FAINT  2
#define ANSICOLOR_CODE_ITALIC 3
#define ANSICOLOR_CODE_UNDER  4
#define ANSICOLOR_CODE_SLOW   5
#define ANSICOLOR_CODE_RAPID  6
#define ANSICOLOR_CODE_HIDDEN 8
#define ANSICOLOR_CODE_STRIKE 9

/* Font style for visible text.
 * A surrogate for the nonexistent code with zero effect. */
#define ANSICOLOR_CODE_SHOW 28

/* Special code for resetting all effects. */
#define ANSICOLOR_CODE_RESET 0

/* Universal code with the same prefix as the other codes. */
#define ANSICOLOR_CODE_N(codenumber) codenumber

/****************************************
 * Low-level macros.
 * Font styles can be disabled overall by defining ANSICOLOR_OFF.
 ****************************************/

/*
 * Stringify the result of a macro-expansion.
 * It looks somewhat tricky, but it is a common technique.
 */
#define ANSICOLOR_STR(codenumber) #codenumber
#define ANSICOLOR_XSTR(codename) ANSICOLOR_STR(codename)

/*
 * Take a clipped codename (name without the prefix)
 * and return the stringified code number. Examples:
 * ANSICOLOR_CODE(BOLD) is "1"
 * ANSICOLOR_CODE(N(100)) is "100"
 */
#define ANSICOLOR_CODE(style) ANSICOLOR_XSTR(ANSICOLOR_CODE_## style)

/*
 * Take a specified number of clipped codenames (names without the prefix)
 * and return a quoted list of semicolon-separated codes. Example:
 * ANSICOLOR_CODELIST3(BOLD, N(4), G) is "1;4;32"
 */
#define CODELIST1(style1) ANSICOLOR_CODE(style1)

#define CODELIST2(style1, style2) \
	CODELIST1(style1) ";" ANSICOLOR_CODE(style2)

#define CODELIST3(style1, style2, style3) \
	CODELIST2(style1, style2) ";" ANSICOLOR_CODE(style3)

#define CODELIST4(style1, style2, style3, style4) \
	CODELIST3(style1, style2, style3) ";" ANSICOLOR_CODE(style4)

/*
 * Set font styles, taking a quoted list of semicolon-separated codes.
 * Example:
 * puts(ANSICOLOR_SET("1;32") "Bold and green" ANSICOLOR_RESET());
 */
#ifndef ANSICOLOR_OFF
#define ANSICOLOR_SET(codelist) "\x1b[" codelist "m"
#else
#define ANSICOLOR_SET(codelist) ""
#endif

/* Reset font styles. */
#define ANSICOLOR_RESET() ANSICOLOR_SET(ANSICOLOR_CODE(RESET))

/****************************************
 * High-level macros.
 * They may be nested, but remember:
 * THEIR CLOSING PARENTHESES MUST ADJOIN!
 ****************************************/

/*
 * Take a quoted list of semicolon-separated codes and apply
 * the associated font styles to the string literal. Example:
 * puts(ANSICOLOR("1;4;32", "[ok]") " Everything is good");
 */
#define ANSICOLOR(codelist, string) \
	ANSICOLOR_SET(codelist) string ANSICOLOR_RESET()

/*
 * Take a specified number of clipped codenames (names without the prefix)
 * and apply the associated font styles to the string literal. Example:
 * puts(STYLE3(BOLD, N(4), G, "[ok]") " Everything is good");
 */
#define STYLE0(string) \
	"" string ANSICOLOR_RESET()

#define STYLE1(style1, string) \
	ANSICOLOR(CODELIST1(style1), string)

#define STYLE2(style1, style2, string) \
	ANSICOLOR(CODELIST2(style1, style2), string)

#define STYLE3(style1, style2, style3, string) \
	ANSICOLOR(CODELIST3(style1, style2, style3), string)

#define STYLE4(style1, style2, style3, style4, string) \
	ANSICOLOR(CODELIST4(style1, style2, style3, style4), string)

#endif
