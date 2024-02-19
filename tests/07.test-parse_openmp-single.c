#include "das-c/parse.h"
#include "test.h"

int main()
{
  open_test();

#ifndef NO_OPENMP
  clargs args;
  args.n_fields = 0;
  args.fields = NULL;
  args.skip = 0;
  args.mode = DASC_PARALLEL_MODE_OMP;
  args.n_threads = 1;
  args.verbose = false;

  printf("  Testing too many fields...\n");
  test_too_many_fields(args, parse_openmp);

  printf("  Testing invalid field...\n");
  test_invalid_field(args, parse_openmp);

  printf("  Testing too few fields...\n");
  test_too_few_fields(args, parse_openmp);

  printf("  Testing valid file, all fields...\n");
  test_valid_full(args, parse_openmp);

  printf("  Testing valid file, filtering...\n");
  test_filtering(args, parse_openmp);

  printf("  Testing valid file with commented lines, all fields...\n");
  test_valid_full_with_comments(args, parse_openmp);

  deinit_clargs(&args);
#else
  printf("  OpenMP not included in compilation, skipping...\n");
#endif

  close_test();
}
