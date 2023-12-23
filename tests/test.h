#ifndef DASC_TEST_HPP
#define DASC_TEST_HPP

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define DASC_TEST_THRESHOLD 1.0e-10

const char *sep = ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";

inline void open_test() { setvbuf(stdout, NULL, _IONBF, 0); }

inline void close_test() { printf("%s Test completed successfully\n\n", sep); }

inline bool assert_double_eq(const double d1, const double d2)
{
  return fabs(d1 - d2) <= DASC_TEST_THRESHOLD;
}

#endif
