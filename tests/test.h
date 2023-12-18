#ifndef DASC_TEST_HPP
#define DASC_TEST_HPP

#include <assert.h>
#include <stdio.h>

const char *sep = ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";

inline void open_test() { setvbuf(stdout, NULL, _IONBF, 0); }

inline void close_test() { printf("%s Test completed successfully\n\n", sep); }

#endif
