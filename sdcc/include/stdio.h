/*-------------------------------------------------------------------------
   stdio.h - ANSI functions forward declarations

   Copyright (C) 1998, Sandeep Dutta . sandeep.dutta@usa.net

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License 
   along with this library; see the file COPYING. If not, write to the
   Free Software Foundation, 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.

   As a special exception, if you link this library with other files,
   some of which are compiled with SDCC, to produce an executable,
   this library does not by itself cause the resulting executable to
   be covered by the GNU General Public License. This exception does
   not however invalidate any other reasons why the executable file
   might be covered by the GNU General Public License.


   kio 2014-11-26	removed test for other targets than z80
   kio 2014-11-26	removed keyword REENTRANT because functions in the z80 port are always reentrant
*/


#ifndef _STDIO_H
#define _STDIO_H 1

#include <term.h>
#include <stdarg.h>
#include <sdcc-lib.h>

#ifndef EOF
  #define EOF (-1)
#endif

#ifndef NULL
  #define NULL (void *)0
#endif

#ifndef __SIZE_T_DEFINED
#define __SIZE_T_DEFINED
  typedef unsigned int size_t;
#endif

/* Bounds-checking interfaces from annex K of the C11 standard. */
#if defined (__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__

#ifndef __RSIZE_T_DEFINED
#define __RSIZE_T_DEFINED
typedef size_t rsize_t;
#endif

#ifndef __ERRNO_T_DEFINED
#define __ERRNO_T_DEFINED
typedef int errno_t;
#endif

#endif

typedef unsigned fpos_t;

#define EOF       (-1)

#define FOPEN_MAX 0

int
fclose(FILE *stream);

int
fputs(const char *s, FILE *stream);

int
setvbuf(FILE *stream, char *buf, int mode, size_t size);

int
vfprintf(FILE *stream, const char *format, va_list args);

int
fprintf(FILE *stream, const char *format, ...);

typedef void (*pfn_outputchar)(char c, void* p);

extern int _print_format (pfn_outputchar pfn, void* pvoid, const char *format, va_list ap);

/*-----------------------------------------------------------------------*/

extern void printf_small (char *,...);
extern int printf (const char *,...);
extern int vprintf (const char *, va_list);
extern int sprintf (char *, const char *, ...);
extern int vsprintf (char *, const char *, va_list);
extern int puts(const char *);

#if __STDC_VERSION__ < 201112L
extern char *gets(char *);
#endif

extern char getchar(void);
extern void putchar(char);

#endif
