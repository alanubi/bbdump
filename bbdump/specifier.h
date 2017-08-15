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

#ifndef BBDUMP_SPECIFIER_H_
#define BBDUMP_SPECIFIER_H_

/* Specifier to put before an inline function. */
#if __STDC_VERSION__ >= 199901L
#define INLINE inline

#elif defined(__GNUC__)
#define INLINE __inline__

#else
#define INLINE
#endif

/* Specifier to put before a function that never returns. */
#if __STDC_VERSION__ >= 201112L
#define NORETURN _Noreturn

#elif defined(__GNUC__)
#define NORETURN __attribute__((noreturn))

#else
#define NORETURN
#endif

#endif
