#ifndef TERM_H_INCLUDED
#define TERM_H_INCLUDED

#include <stddef.h>

#define BUFSIZ 256

#define _IONBF 0
#define _IOLBF 1
#define _IOFBF 2

extern struct term {
	unsigned char print_head[2];
	unsigned char clear_attr;
	unsigned char border_color;
	unsigned char just_wrapped;
} term;

typedef struct io_file {
	size_t        store_pos;
	unsigned char v_buf       :2,
	              stream_error:6;
	char          *buffer;
} FILE;

extern FILE *const stdin, *const stdout, *const stderr;

void
clear_term(void);

int
fputc(int c, FILE *stream);

void
fflush(FILE *stream);

#endif // TERM_H_INCLUDED
