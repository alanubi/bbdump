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

#ifndef BBDUMP_LABEL_H_
#define BBDUMP_LABEL_H_

/*
 * Jump to a label if a condition is not met. Usage:
 * ENSURE (.., label);
 */
#define ENSURE(condition, label) \
do { \
	if (!(condition)) \
		goto label; \
} while (0)

/*
 * A label after the end of unconditional `do` loop. Usage:
 * do { .... } LOOP (label);
 */
#define LOOP(label) \
	while (1); /* End of `do` loop. */ \
	label: ((void)0) /* Require semicolon. */

/*
 * A label at the beginning of unconditionally skipped block of code. Usage:
 * SKIP (label) { .... }
 * SKIP (label) ..;
 */
#define SKIP(label) \
	if (1) ; \
	else label: /* Naked `if` would be unsafe. */

#endif
