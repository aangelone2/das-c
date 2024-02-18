#ifndef DASC_TEST_H
#define DASC_TEST_H

#include "das-c/parse.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define DASC_TEST_ABS_THRESHOLD 1.0e-14
#define DASC_TEST_REL_THRESHOLD 2.0e-13

static inline void open_test() { setvbuf(stdout, NULL, _IONBF, 0); }

static inline void close_test()
{
  const char *sep = ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
  printf("%s Test completed successfully\n\n", sep);
}

static inline void assert_double_eq(const double d1, const double d2)
{
  // printf("%le\n", fabs(d1 - d2));
  assert(fabs(d1 - d2) <= DASC_TEST_ABS_THRESHOLD);

  // Any nonzero value is fine
  if (fabs(d2) > 0.0)
  {
    // printf("%le\n", fabs((d1 - d2)/d2));
    assert(fabs((d1 - d2) / d2) <= DASC_TEST_REL_THRESHOLD);
  }
}

// Tracks `resources/08.valid.dat`.
extern const double example_data[];

// Tracks `resources/09.valid_with_comments.dat`.
extern const double example_data_with_comments[];

// Typedef for pointer to parsing function.
typedef size_t (*parsing_func)(table *, const parse_info *);

// Common tests for parsing routines, will copy passed `clargs`.
void test_too_many_fields(clargs args, parsing_func parse);
void test_invalid_field(clargs args, parsing_func parse);
void test_too_few_fields(clargs args, parsing_func parse);
void test_valid_full(clargs args, parsing_func parse);
void test_filtering(clargs args, parsing_func parse);
void test_valid_full_with_comments(clargs args, parsing_func parse);
void test_4_threads(clargs args, parsing_func parse);
void test_imperfect_splitting(clargs args, parsing_func parse);

#endif
