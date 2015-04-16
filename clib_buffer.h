
//
// buffer.h
//
// Copyright (c) 2012 TJ Holowaychuk <tj@vision-media.ca>
//

#ifndef CLIB_BUFFER_H
#define CLIB_BUFFER_H 1

#include <sys/types.h>

/*
 * Default buffer size.
 */

#ifndef CLIB_BUFFER_DEFAULT_SIZE
#define CLIB_BUFFER_DEFAULT_SIZE 64
#endif

/*
 * Buffer struct.
 */

typedef struct {
  size_t len;
  char *alloc;
  char *data;
} clib_buffer_t;

// prototypes

clib_buffer_t *
clib_buffer_new();

clib_buffer_t *
clib_buffer_new_with_size(size_t n);

clib_buffer_t *
clib_buffer_new_with_string(char *str);

clib_buffer_t *
clib_buffer_new_with_string_length(char *str, size_t len);

clib_buffer_t *
clib_buffer_new_with_copy(char *str);

size_t
clib_buffer_size(clib_buffer_t *self);

size_t
clib_buffer_length(clib_buffer_t *self);

void
clib_buffer_free(clib_buffer_t *self);

int
clib_buffer_prepend(clib_buffer_t *self, char *str);

int
clib_buffer_append(clib_buffer_t *self, const char *str);

int
clib_buffer_appendf(clib_buffer_t *self, const char *format, ...);

int
clib_buffer_append_n(clib_buffer_t *self, const char *str, size_t len);

int
clib_buffer_equals(clib_buffer_t *self, clib_buffer_t *other);

ssize_t
clib_buffer_indexof(clib_buffer_t *self, char *str);

clib_buffer_t *
clib_buffer_slice(clib_buffer_t *self, size_t from, ssize_t to);

ssize_t
clib_buffer_compact(clib_buffer_t *self);

void
clib_buffer_fill(clib_buffer_t *self, int c);

void
clib_buffer_clear(clib_buffer_t *self);

void
clib_buffer_trim_left(clib_buffer_t *self);

void
clib_buffer_trim_right(clib_buffer_t *self);

void
clib_buffer_trim(clib_buffer_t *self);

void
clib_buffer_print(clib_buffer_t *self);

#define clib_buffer_string(self) (self->data)

#endif
