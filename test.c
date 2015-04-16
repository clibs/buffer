
//
// test.c
//
// Copyright (c) 2012 TJ Holowaychuk <tj@vision-media.ca>
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "buffer.h"

void
equal(char *a, char *b) {
  if (strcmp(a, b)) {
    printf("\n");
    printf("  expected: '%s'\n", a);
    printf("    actual: '%s'\n", b);
    printf("\n");
    exit(1);
  }
}

void
test_clib_buffer_new() {
  clib_buffer_t *buf = clib_buffer_new();
  assert(CLIB_BUFFER_DEFAULT_SIZE == clib_buffer_size(buf));
  assert(0 == clib_buffer_length(buf));
  clib_buffer_free(buf);
}

void
test_clib_buffer_new_with_size() {
  clib_buffer_t *buf = clib_buffer_new_with_size(1024);
  assert(1024 == clib_buffer_size(buf));
  assert(0 == clib_buffer_length(buf));
  clib_buffer_free(buf);
}

void
test_clib_buffer_append() {
  clib_buffer_t *buf = clib_buffer_new();
  assert(0 == clib_buffer_append(buf, "Hello"));
  assert(0 == clib_buffer_append(buf, " World"));
  assert(strlen("Hello World") == clib_buffer_length(buf));
  equal("Hello World", clib_buffer_string(buf));
  clib_buffer_free(buf);
}

void
test_clib_buffer_append_n() {
  clib_buffer_t *buf = clib_buffer_new();
  assert(0 == clib_buffer_append_n(buf, "subway", 3));
  assert(0 == clib_buffer_append_n(buf, "marines", 6));
  assert(strlen("submarine") == clib_buffer_length(buf));
  equal("submarine", clib_buffer_string(buf));
  clib_buffer_free(buf);
}

void
test_clib_buffer_append__grow() {
  clib_buffer_t *buf = clib_buffer_new_with_size(10);
  assert(0 == clib_buffer_append(buf, "Hello"));
  assert(0 == clib_buffer_append(buf, " tobi"));
  assert(0 == clib_buffer_append(buf, " was"));
  assert(0 == clib_buffer_append(buf, " here"));

  char *str = "Hello tobi was here";
  equal(str, clib_buffer_string(buf));
  assert(1024 == clib_buffer_size(buf));
  assert(strlen(str) == clib_buffer_length(buf));
  clib_buffer_free(buf);
}

void
test_clib_buffer_prepend() {
  clib_buffer_t *buf = clib_buffer_new();
  assert(0 == clib_buffer_append(buf, " World"));
  assert(0 == clib_buffer_prepend(buf, "Hello"));
  assert(strlen("Hello World") == clib_buffer_length(buf));
  equal("Hello World", clib_buffer_string(buf));
  clib_buffer_free(buf);
}

void
test_clib_buffer_slice() {
  clib_buffer_t *buf = clib_buffer_new();
  clib_buffer_append(buf, "Tobi Ferret");

  clib_buffer_t *a = clib_buffer_slice(buf, 2, 8);
  equal("Tobi Ferret", clib_buffer_string(buf));
  equal("bi Fer", clib_buffer_string(a));

  clib_buffer_free(buf);
  clib_buffer_free(a);
}

void
test_clib_buffer_slice__range_error() {
  clib_buffer_t *buf = clib_buffer_new_with_copy("Tobi Ferret");
  clib_buffer_t *a = clib_buffer_slice(buf, 10, 2);
  assert(NULL == a);
  clib_buffer_free(buf);
}

void
test_clib_buffer_slice__end() {
  clib_buffer_t *buf = clib_buffer_new_with_copy("Tobi Ferret");

  clib_buffer_t *a = clib_buffer_slice(buf, 5, -1);
  equal("Tobi Ferret", clib_buffer_string(buf));
  equal("Ferret", clib_buffer_string(a));

  clib_buffer_t *b = clib_buffer_slice(buf, 5, -3);
  equal("Ferr", clib_buffer_string(b));

  clib_buffer_t *c = clib_buffer_slice(buf, 8, -1);
  equal("ret", clib_buffer_string(c));

  clib_buffer_free(buf);
  clib_buffer_free(a);
  clib_buffer_free(b);
  clib_buffer_free(c);
}

void
test_clib_buffer_slice__end_overflow() {
  clib_buffer_t *buf = clib_buffer_new_with_copy("Tobi Ferret");
  clib_buffer_t *a = clib_buffer_slice(buf, 5, 1000);
  equal("Tobi Ferret", clib_buffer_string(buf));
  equal("Ferret", clib_buffer_string(a));
  clib_buffer_free(a);
  clib_buffer_free(buf);
}

void
test_clib_buffer_equals() {
  clib_buffer_t *a = clib_buffer_new_with_copy("Hello");
  clib_buffer_t *b = clib_buffer_new_with_copy("Hello");

  assert(1 == clib_buffer_equals(a, b));

  clib_buffer_append(b, " World");
  assert(0 == clib_buffer_equals(a, b));

  clib_buffer_free(a);
  clib_buffer_free(b);
}

void test_clib_buffer_formatting() {
  clib_buffer_t *buf = clib_buffer_new();
  int result = clib_buffer_appendf(buf, "%d %s", 3, "cow");
  assert(0 == result);
  equal("3 cow", clib_buffer_string(buf));
  result = clib_buffer_appendf(buf, " - 0x%08X", 0xdeadbeef);
  assert(0 == result);
  equal("3 cow - 0xDEADBEEF", clib_buffer_string(buf));
  clib_buffer_free(buf);
}

void
test_clib_buffer_indexof() {
  clib_buffer_t *buf = clib_buffer_new_with_copy("Tobi is a ferret");

  ssize_t i = clib_buffer_indexof(buf, "is");
  assert(5 == i);

  i = clib_buffer_indexof(buf, "a");
  assert(8 == i);

  i = clib_buffer_indexof(buf, "something");
  assert(-1 == i);

  clib_buffer_free(buf);
}

void
test_clib_buffer_fill() {
  clib_buffer_t *buf = clib_buffer_new_with_copy("Hello");
  assert(5 == clib_buffer_length(buf));

  clib_buffer_fill(buf, 0);
  assert(0 == clib_buffer_length(buf));
  clib_buffer_free(buf);
}

void
test_clib_buffer_clear() {
  clib_buffer_t *buf = clib_buffer_new_with_copy("Hello");
  assert(5 == clib_buffer_length(buf));

  clib_buffer_clear(buf);
  assert(0 == clib_buffer_length(buf));
  clib_buffer_free(buf);
}

void
test_clib_buffer_trim() {
  clib_buffer_t *buf = clib_buffer_new_with_copy("  Hello\n\n ");
  clib_buffer_trim(buf);
  equal("Hello", clib_buffer_string(buf));
  clib_buffer_free(buf);

  buf = clib_buffer_new_with_copy("  Hello\n\n ");
  clib_buffer_trim_left(buf);
  equal("Hello\n\n ", clib_buffer_string(buf));
  clib_buffer_free(buf);

  buf = clib_buffer_new_with_copy("  Hello\n\n ");
  clib_buffer_trim_right(buf);
  equal("  Hello", clib_buffer_string(buf));
  clib_buffer_free(buf);
}

void
test_clib_buffer_compact() {
  clib_buffer_t *buf = clib_buffer_new_with_copy("  Hello\n\n ");
  clib_buffer_trim(buf);
  assert(5 == clib_buffer_length(buf));
  assert(10 == clib_buffer_size(buf));

  ssize_t removed = clib_buffer_compact(buf);
  assert(5 == removed);
  assert(5 == clib_buffer_length(buf));
  assert(5 == clib_buffer_size(buf));
  equal("Hello", clib_buffer_string(buf));

  clib_buffer_free(buf);
}

int
main(){
  test_clib_buffer_new();
  test_clib_buffer_new_with_size();
  test_clib_buffer_append();
  test_clib_buffer_append__grow();
  test_clib_buffer_append_n();
  test_clib_buffer_prepend();
  test_clib_buffer_slice();
  test_clib_buffer_slice__range_error();
  test_clib_buffer_slice__end();
  test_clib_buffer_slice__end_overflow();
  test_clib_buffer_equals();
  test_clib_buffer_formatting();
  test_clib_buffer_indexof();
  test_clib_buffer_fill();
  test_clib_buffer_clear();
  test_clib_buffer_trim();
  test_clib_buffer_compact();
  printf("\n  \e[32m\u2713 \e[90mok\e[0m\n\n");
  return 0;
}
