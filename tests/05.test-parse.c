#include "das-c/table.h"
#include "test.h"
#include <stdlib.h>

clargs default_clargs()
{
  clargs args;

  // Default values
  args.n_fields = 0;
  args.fields = NULL;
  args.skip = 0;
  args.n_threads = 1;
  args.verbose = false;

  return args;
}

void test_too_many_fields()
{
  clargs args = default_clargs();
  args.filename = "../resources/05.too_many_fields.dat";

  table tab;
  assert(parse(&tab, &args) == 1);

  deinit_table(&tab);
  deinit_clargs(&args);
}

void test_invalid_field()
{
  clargs args = default_clargs();
  args.filename = "../resources/06.invalid_field.dat";

  table tab;
  assert(parse(&tab, &args) == 2);

  deinit_table(&tab);
  deinit_clargs(&args);
}

void test_too_few_fields()
{
  clargs args = default_clargs();
  args.filename = "../resources/07.too_few_fields.dat";

  table tab;
  assert(parse(&tab, &args) == 3);

  deinit_table(&tab);
  deinit_clargs(&args);
}

void test_valid_full()
{
  clargs args = default_clargs();
  args.filename = "../resources/08.valid.dat";

  table tab;
  assert(!parse(&tab, &args));

  assert(tab.cols == 4);
  for (size_t ic = 0; ic < tab.cols; ++ic)
  {
    assert(tab.rows == 64);

    // Checking each component
    for (size_t ir = 0; ir < 64; ++ir)
      assert_double_eq(tab.data[ir][ic], (double)(ic) + example_data[ir]);
  }

  deinit_table(&tab);
  deinit_clargs(&args);
}

void test_filtering()
{
  clargs args = default_clargs();
  args.filename = "../resources/08.valid.dat";
  args.n_fields = 2;
  args.fields = malloc(2 * sizeof(size_t));
  args.fields[0] = 1;
  args.fields[1] = 2;

  table tab;
  assert(!parse(&tab, &args));

  assert(tab.cols == 2);
  for (size_t ic = 0; ic < tab.cols; ++ic)
  {
    assert(tab.rows == 64);

    // Checking each component
    for (size_t ir = 0; ir < 64; ++ir)
      assert_double_eq(
          tab.data[ir][ic], (double)(ic) + 1.0 + example_data[ir]
      );
  }

  deinit_table(&tab);
  deinit_clargs(&args);
}

int main()
{
  open_test();

  printf("  Testing too many fields...\n");
  test_too_many_fields();

  printf("  Testing invalid field...\n");
  test_invalid_field();

  printf("  Testing too few fields...\n");
  test_too_few_fields();

  printf("  Testing valid file, all fields...\n");
  test_valid_full();

  printf("  Testing valid file, filtering...\n");
  test_filtering();

  close_test();
}
