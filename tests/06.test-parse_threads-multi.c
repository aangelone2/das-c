#include "test.h"
#include <stdlib.h>

int main()
{
  open_test();

  clargs args;
  args.n_fields = 0;
  args.fields = NULL;
  args.skip = 0;
  args.mode = DASC_PARALLEL_MODE_THR;
  args.n_threads = 2;
  args.verbose = false;

  printf("  Testing too many fields...\n");
  test_too_many_fields(args, parse_threads);

  printf("  Testing invalid field...\n");
  test_invalid_field(args, parse_threads);

  printf("  Testing too few fields...\n");
  test_too_few_fields(args, parse_threads);

  printf("  Testing valid file, all fields...\n");
  test_valid_full(args, parse_threads);

  printf("  Testing valid file, filtering...\n");
  test_filtering(args, parse_threads);

  printf("  Testing valid file with commented lines, all fields...\n");
  test_valid_full_with_comments(args, parse_threads);

  printf("  Testing valid file, all fields, 4 threads...\n");
  test_4_threads(args, parse_threads);

  printf("  Testing valid file, all fields, imperfect splitting...\n");
  test_imperfect_splitting(args, parse_threads);

  deinit_clargs(&args);
  close_test();
}
