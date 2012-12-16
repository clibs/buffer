
//
// buffer.h
//
// Copyright (c) 2012 TJ Holowaychuk <tj@vision-media.ca>
//

#ifndef BUFFER
#define BUFFER

/*
 * Default buffer size.
 */

#ifndef BUFFER_DEFAULT_SIZE
#define BUFFER_DEFAULT_SIZE 64
#endif

/*
 * Buffer struct.
 */

typedef struct {
  size_t len;
  char *data;
} buffer_t;

// prototypes

buffer_t *
buffer_new();

buffer_t *
buffer_new_with_size(size_t n);

buffer_t *
buffer_new_with_string(char *str);

size_t
buffer_size(buffer_t *self);

size_t
buffer_length(buffer_t *self);

void
buffer_free(buffer_t *self);

int
buffer_prepend(buffer_t *self, char *str);

int
buffer_append(buffer_t *self, char *str);

int
buffer_equals(buffer_t *self, buffer_t *other);

buffer_t *
buffer_slice(buffer_t *self, size_t from, ssize_t to);

#define buffer_string(self) (self->data)

#endif
