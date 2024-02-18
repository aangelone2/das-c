#include "test.h"

int main()
{
  open_test();

  clargs args;
  args.n_fields = 0;
  args.fields = NULL;
  args.skip = 0;
  args.n_threads = 1;
  args.verbose = false;

  printf("  Testing too many fields...\n");
  test_too_many_fields(args);

  printf("  Testing invalid field...\n");
  test_invalid_field(args);

  printf("  Testing too few fields...\n");
  test_too_few_fields(args);

  printf("  Testing valid file, all fields...\n");
  test_valid_full(args);

  printf("  Testing valid file, filtering...\n");
  test_filtering(args);

  printf("  Testing valid file with commented lines, all fields...\n");
  test_valid_full_with_comments(args);

  deinit_clargs(&args);
  close_test();
}
