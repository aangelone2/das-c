#include "das-c/table.h"
#include "test.h"

mask init_common_mask()
{
  mask msk;
  init_mask(&msk, 3);
  // Parsing all fields
  set_all(&msk);

  return msk;
}

void test_too_many_fields()
{
  mask msk = init_common_mask();
  file_info info;
  init_file_info(&info, "../resources/05.too_many_fields.dat");

  table tab;
  assert(init_table_parse(&tab, &info, &msk) == 3);
  deinit_table(&tab);

  deinit_file_info(&info);
  deinit_mask(&msk);
}

void test_invalid_field()
{
  mask msk = init_common_mask();
  file_info info;
  init_file_info(&info, "../resources/06.invalid_field.dat");

  table tab;
  assert(init_table_parse(&tab, &info, &msk) == 4);
  deinit_table(&tab);

  deinit_file_info(&info);
  deinit_mask(&msk);
}

void test_too_few_fields()
{
  mask msk = init_common_mask();
  file_info info;
  init_file_info(&info, "../resources/07.too_few_fields.dat");

  table tab;
  assert(init_table_parse(&tab, &info, &msk) == 5);
  deinit_table(&tab);

  deinit_file_info(&info);
  deinit_mask(&msk);
}

void test_valid_full()
{
  // Setting 4-4 field mask
  mask msk;
  init_mask(&msk, 4);
  set_all(&msk);

  file_info info;
  init_file_info(&info, "../resources/08.valid.dat");

  table tab;
  assert(!init_table_parse(&tab, &info, &msk));

  assert(tab.size == 4);
  for (size_t ic = 0; ic < tab.size; ++ic)
  {
    assert(tab.columns[ic].size == 64);

    // Checking each component
    for (size_t ir = 0; ir < 64; ++ir)
      assert_double_eq(
          tab.columns[ic].data[ir], (double)(ic) + example_data[ir]
      );
  }

  deinit_table(&tab);

  deinit_file_info(&info);
  deinit_mask(&msk);
}

void test_filtering()
{
  // Setting 2-4 field mask
  mask msk;
  init_mask(&msk, 4);
  set_field(&msk, 1);
  set_field(&msk, 2);

  file_info info;
  init_file_info(&info, "../resources/08.valid.dat");

  table tab;
  assert(!init_table_parse(&tab, &info, &msk));

  assert(tab.size == 2);
  for (size_t ic = 0; ic < tab.size; ++ic)
  {
    assert(tab.columns[ic].size == 64);

    // Checking each component
    for (size_t ir = 0; ir < 64; ++ir)
      assert_double_eq(
          tab.columns[ic].data[ir], (double)(ic) + 1.0 + example_data[ir]
      );
  }

  deinit_table(&tab);

  deinit_file_info(&info);
  deinit_mask(&msk);
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
