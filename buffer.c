
//
// buffer.c
//
// Copyright (c) 2012 TJ Holowaychuk <tj@vision-media.ca>
//

#include <string.h>
#include <stdlib.h>
#include "buffer.h"

/*
 * Compute the nearest multiple of `a` from `b`.
 */

#define nearest_multiple_of(a, b) \
  (((b) + ((a) - 1)) & ~((a) - 1))

/*
 * Allocate a new buffer with BUFFER_DEFAULT_SIZE.
 */

buffer_t *
buffer_new() {
  return buffer_new_with_size(BUFFER_DEFAULT_SIZE);
}

/*
 * Allocate a new buffer with `n` bytes.
 */

buffer_t *
buffer_new_with_size(size_t n) {
  buffer_t *self = malloc(sizeof(buffer_t));
  if (!self) return NULL;
  self->len = n;
  self->data = calloc(n, 1);
  return self;
}

/*
 * Allocate a new buffer with `str`.
 */

buffer_t *
buffer_new_with_string(char *str) {
  size_t len = strlen(str);
  buffer_t *self = buffer_new_with_size(len);
  if (!self) return NULL;
  memcpy(self->data, str, len);
  return self;
}

/*
 * Free the buffer.
 */

void
buffer_free(buffer_t *self) {
  free(self->data);
  free(self);
}

/*
 * Return buffer size.
 */

size_t
buffer_size(buffer_t *self) {
  return self->len;
}

/*
 * Return string length.
 */

size_t
buffer_length(buffer_t *self) {
  return strlen(self->data);
}

/*
 * Resize to hold `n` bytes.
 */

int
buffer_resize(buffer_t *self, size_t n) {
  n = nearest_multiple_of(1024, n);
  self->len = n;
  self->data = realloc(self->data, n);
  return self->data ? 0 : -1;
}

/*
 * Append `str` to `self` and return 0 on success, -1 on failure.
 */

int
buffer_append(buffer_t *self, char *str) {
  size_t len = strlen(str);
  size_t prev = strlen(self->data);
  size_t needed = len + prev;

  // enough space
  if (self->len > needed) {
    strcat(self->data, str);
    return 0;
  }

  // resize
  int ret = buffer_resize(self, needed);
  if (-1 == ret) return -1;
  strcat(self->data, str);

  return 0;
}

/*
 * Prepend `str` to `self` and return 0 on success, -1 on failure.
 */

int
buffer_prepend(buffer_t *self, char *str) {
  size_t len = strlen(str);
  size_t prev = strlen(self->data);
  size_t needed = len + prev;

  // enough space
  if (self->len > needed) goto move;

  // resize
  int ret = buffer_resize(self, needed);
  if (-1 == ret) return -1;

  // move
  move:
  memmove(self->data + len, self->data, len + 1);
  memcpy(self->data, str, len);

  return 0;
}

/*
 * Return a new buffer based on the `from..to` slice of `buf`,
 * or NULL on error.
 */

buffer_t *
buffer_slice(buffer_t *buf, size_t from, ssize_t to) {
  size_t len = strlen(buf->data);

  // bad range
  if (to < from) return NULL;

  // relative to end
  if (to < 0) to = len - ~to;

  // cap end
  if (to > len) to = len;

  size_t n = to - from;
  buffer_t *self = buffer_new_with_size(n + 1);
  memcpy(self->data, buf->data + from, n);
  return self;
}

/*
 * Return 1 if the buffers contain equivalent data.
 */

int
buffer_equals(buffer_t *self, buffer_t *other) {
  return 0 == strcmp(self->data, other->data);
}

