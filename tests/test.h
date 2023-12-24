#ifndef DASC_TEST_HPP
#define DASC_TEST_HPP

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define DASC_TEST_THRESHOLD 1.0e-14

const char *sep = ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";

static inline void open_test() { setvbuf(stdout, NULL, _IONBF, 0); }

static inline void close_test()
{
  printf("%s Test completed successfully\n\n", sep);
}

static inline void assert_double_eq(const double d1, const double d2)
{
  //  printf("%lf\n", fabs(d1 - d2));
  assert(fabs(d1 - d2) <= DASC_TEST_THRESHOLD);
}

#endif
