
# buffer

  Tiny C string manipulation library.

## Installation

  Install with [clib](https://github.com/clibs/clib):

```
$ clib install clibs/buffer
```

## API

```c
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
clib_buffer_append(clib_buffer_t *self, char *str);

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
```

## License

  MIT
